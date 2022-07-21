#include <iostream>
#include <string>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "ScoreTable.h"
#include "InputData.h"

using namespace std; 

int main(int argc, char* argv[])
{
    int playAlongComputer = 0;
    int Speed_Option;
    InputData input;

  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{800};
  constexpr std::size_t kScreenHeight{800};
  constexpr std::size_t kGridWidth{50};
  constexpr std::size_t kGridHeight{50};

  // TASK 1 - Allow users to enter their names and save it in a text file with their scores.
  ScoreTable Table_of_scores;

  // TASK 2 - Allow the user to select the initial speed (Slow - Normal - Fast)
  Speed_Option = input.get_options("Please enter speed.\n 1. Slow (score +1).\n 2. Normal (score +2).\n 3. Fast (score +3):\n", 1, 3);

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, Table_of_scores.Get_Current_Score(), Speed_Option);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n\n";

  Table_of_scores.Write_Scores_To_File(game.GetScore());
  if (playAlongComputer)
      Table_of_scores.Show_Computer_Score(game.GetScore());

  return 0;
}