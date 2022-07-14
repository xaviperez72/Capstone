#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "ScoreTable.h"

int main(int argc, char* argv[])
{
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{800};
  constexpr std::size_t kScreenHeight{800};
  constexpr std::size_t kGridWidth{50};
  constexpr std::size_t kGridHeight{50};

  // TASK 1 - Allow users to enter their names and save it in a text file with their scores, so they can get the top score.
  ScoreTable Table_of_scores;

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";

  table.WriteScoreToFile(game.GetScore());
  if (playAlongComputer)
      table.PrintComputerScore(game.GetScore()); 

  return 0;
}