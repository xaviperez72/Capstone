#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <memory>
#include <mutex>
#include "SDL.h"

std::string time_in_HH_MM_SS_MMM();

class Food {
public:
    Food() { food.x = 0; food.y = 0; };
    SDL_Point get_food_with_lock();
    void set_food_with_lock(SDL_Point f);
private:
    SDL_Point food;
    std::mutex mtx;
};

typedef struct {
    float x;
    float y;
} Head;

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, int speed_option);
  int Get_Speed_Option() { return speed_option; };
  void Update();
  void GrowBody();
  bool SnakeCell(int x, int y);
  Head get_head_with_lock();
  std::vector<SDL_Point> get_body_with_lock();
  void set_head_with_lock(Head f);  

  Direction direction = Direction::kUp;

  int speed_option;
  float speed{0.1f};
  int size{1};
  bool alive{true};
  Head head; 
  //float head_x;
  //float head_y;
  std::vector<SDL_Point> body;

 private:
  std::mutex mtx;
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif