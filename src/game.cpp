#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, int score, int speed_option)
    : score(score),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) 
{
    running = true;
    snake = std::make_shared<Snake>(grid_width, grid_height, speed_option);
    computer_snake = std::make_shared<Snake>(grid_width, grid_height, 1);
    food = std::make_shared<Food>();
    PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration) 
{
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;

  // Launch Snake,
  render_thread = std::thread(&Game::RunRender, this, renderer, target_frame_duration);

  // Launch Computer Snake
  // comp_snake_thread = std::thread(&Game::RunCompSnake, this);

  while (running) {
      frame_start = SDL_GetTicks();

      // Input, Update, Render - the main game loop.
      controller.HandleInput(running, snake);
      UpdateSnake();

      frame_end = SDL_GetTicks();

      // Keep track of how long each loop through the input/update cycle
      // takes.
      frame_duration = frame_end - frame_start;

      // If the time for this frame is too small (i.e. frame_duration is
      // smaller than the target ms_per_frame), delay the loop to
      // achieve the correct frame rate.
      if (frame_duration < target_frame_duration) {
          SDL_Delay(target_frame_duration - frame_duration);
      }
  }
  std::cout << time_in_HH_MM_SS_MMM() << "Game::Run FINISHING ... waiting for render_thread.join();" << std::endl;

  render_thread.join();
}


void Game::RunRender(Renderer& renderer, std::size_t target_frame_duration)
{
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;

    while (running) {
        frame_start = SDL_GetTicks();

        renderer.Render(snake, food);

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
            renderer.UpdateWindowTitle(score, frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
            std::cout << time_in_HH_MM_SS_MMM() << "Game::RunRender every second" << std::endl;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }

    std::cout << time_in_HH_MM_SS_MMM() << "Game::RunRender FINISHING" << std::endl;

}

// Posible Monitor Object Pattern in order to place correctly the food
// 2 snakes could chase food at the same time, just one could PlaceFood.
// Currently both could PlaceFood, the last one thread (snake) will place the food on the final position. Not well resolved. 
void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake->SnakeCell(x, y)) 
    {
        SDL_Point p = { x, y };
        food->set_food_with_lock(p);
        return;
    }
  }
}

void Game::UpdateSnake() 
{
  if (!snake->alive) return;

  snake->Update();
  
  SDL_Point food_pos = food->get_food_with_lock();      // Mandatory when there are more than 1 snake. The other one could place the food. 

  int new_x = static_cast<int>(snake->head.x);
  int new_y = static_cast<int>(snake->head.y);

  // Check if there's food over here
  if (food_pos.x == new_x && food_pos.y == new_y)     // Thread snake doesn't need to lock head.x & head.y
  {
      switch (snake->Get_Speed_Option())
      {
        case 3: score++; 
        case 2: score++; 
        case 1: score++; 
      }
    PlaceFood();
    // Grow snake and increase speed.
    snake->GrowBody();
    snake->speed += 0.02f;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const  {     return snake->size;  }