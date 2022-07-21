#ifndef GAME_H
#define GAME_H

#include <random>
#include <mutex>
#include <thread>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game : public std::enable_shared_from_this<Game>
{
 public:
  Game(std::size_t grid_width, std::size_t grid_height, int score, int speed_option);
  void Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration);
  void RunRender(Renderer& renderer, std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  bool running;

 private:
  //Snake snake;
  //Snake Computer_snake;
  //SDL_Point food;
  std::thread render_thread;
  std::thread comp_snake_thread;

  std::shared_ptr<Snake> snake;
  std::shared_ptr<Snake> computer_snake;
  std::shared_ptr<Food> food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void UpdateSnake();
};

#endif