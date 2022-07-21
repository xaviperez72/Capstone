#include "snake.h"
#include <cmath>
#include <iostream>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <iomanip>

// https://stackoverflow.com/questions/24686846/get-current-time-in-milliseconds-or-hhmmssmmm-format

// It is good to show on logs time and thread id. It helps on debugging or chasing a bug. 
// I learned this in my previous job (in 2008) on a multithread  TCP/IP dispatcher in C language. 

std::string time_in_HH_MM_SS_MMM()
{
    using namespace std::chrono;
    // get current time
    auto now = system_clock::now();

    // get number of milliseconds for the current second
     // (remainder after division into seconds)
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // convert to std::time_t in order to convert to std::tm (broken time)

    std::time_t timer = system_clock::to_time_t(now);

    // convert to broken time
    struct std::tm* ptm = std::localtime(&timer);

    std::ostringstream oss;

    oss << std::put_time(ptm, "%H:%M:%S"); // HH:MM:SS
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count() << ' ' << std::this_thread::get_id() << ' ';

    return oss.str();
}

SDL_Point Food::get_food_with_lock()
{
    std::lock_guard<std::mutex> lock(mtx);
    return food;
}

void Food::set_food_with_lock(SDL_Point f)
{
    std::lock_guard<std::mutex> lock(mtx);
    food.x = f.x;
    food.y = f.y;
}

Snake::Snake(int grid_width, int grid_height, int speed_option)
    : grid_width(grid_width),
    grid_height(grid_height),
    speed_option(speed_option)
{
    SDL_Point s;
    s.x = grid_width / 2;
    s.y = grid_height / 2;

    set_head_with_lock(s);      // Just in case Render got it first, otherwise it wouldn´t be necesary

    switch (speed_option)
    {
        case 1: speed = 0.1f; break;
        case 2: speed = 0.2f;  break;
        case 3: speed = 0.4f;  break;
    }
}

SDL_Point Snake::get_head_with_lock()
{
    std::lock_guard<std::mutex> lock(mtx);
    return head;
}

void Snake::set_head_with_lock(SDL_Point f)
{
    std::lock_guard<std::mutex> lock(mtx);
    head.x = f.x;
    head.y = f.y;
}

std::vector<SDL_Point> Snake::get_body_with_lock()
{
    std::lock_guard<std::mutex> lock(mtx);
    return body;
}


void Snake::Update() {
  std::lock_guard<std::mutex> lock(mtx);
  SDL_Point prev_cell = head;
  UpdateHead();
  SDL_Point current_cell = head;
  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
     UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head.y -= speed;
      break;

    case Direction::kDown:
      head.y += speed;
      break;

    case Direction::kLeft:
      head.x -= speed;
      break;

    case Direction::kRight:
      head.x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head.x = (int) fmod(head.x + grid_width, grid_width);
  head.y = (int) fmod(head.y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) 
{
  if (x == head.x && y == head.y) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}