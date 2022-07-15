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

    pair<string, int> _Better_Player;

    const string _Score_File_Name = "./Snake_Users_Scores.txt";
    vector<pair<string, int>>::iterator _it_cur_player;
    vector<pair<string, int>>::iterator Exist_Current_Player(const string current_player);
    vector<pair<string, int>> _Scores_Table;

    ofstream writeFile;  
    ifstream ReadFile;

public:

    ScoreTable();
    ~ScoreTable();
    auto Get_Better_Player() const { return &_Better_Player; }
    int Get_Current_Score() const { return _it_cur_player->second; }
    void Show_Computer_Score(int score);
    void Write_Scores_To_File(int score);
};

#endif