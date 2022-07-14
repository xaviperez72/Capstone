#ifndef SCORETABLE_H
#define SCORETABLE_H

#include <vector>
#include <string>
#include <utility>
#include <fstream>

using namespace std;

class ScoreTable {

private:
    void Press_Enter(string msg);
    int Press_YN();
    void Show_Help();
    void Read_Scoress_From_File();
    void Sort_Scores();
    void Better_Score();
    string Ask_Player_Name();

    pair<string, float> _Better_Player;
    
    float _Current_Score;
    const string _Score_File_Name = "./Snake_Users_Scores.txt";
    vector<pair<string, float>>::iterator _it_cur_player;

    ofstream writeFile;  
    ifstream ReadFile;

public:
    vector<pair<string, float>>::iterator Exist_Current_Player();
    vector<pair<string, float>> _Scores_Table;

    auto getScoresTable() const     {   return &_Scores_Table;   }
    auto getmaxScoredPlayer() const {   return &_Better_Player;  }

    ScoreTable();
    ~ScoreTable();
    void Write_Scores_To_File(float score);
    void PrintComputerScore(float score);

};

#endif