#include "ScoreTable.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// ScoreTable Constructor.
// Ask Player Name. If exists on scores file then it gets back to carry on with the previous score. Shows help if is needed. 

ScoreTable::ScoreTable()
{
    string current_player;
    int need_help = 0;

    _Scores_Table.clear();
    current_player.clear();
    _Current_Score = 0.0;
    _it_cur_player = _Scores_Table.end();
    current_player = Ask_Player_Name();

    Read_Scoress_From_File();

    if (_Scores_Table.size()) {
        if ((_it_cur_player = Exist_Current_Player()) != _Scores_Table.end()) {
            _Current_Score = _it_cur_player->second;
            std::cout << endl << "Wellcome back " << current_player << ". Glad to see you again. You will continue with " << _Current_Score << " score!! " << endl << endl;

            std::cout << "Do you want to remind the game rules (Y/N)? ";
            int c = Press_YN();
            if (c == 'Y' || c == 'y')
                need_help = 1;
        }
        else
            need_help = 1;
    }
    else
        need_help = 1;

    if (_it_cur_player == _Scores_Table.end()) {
        _Scores_Table.emplace_back(make_pair(current_player, 0.0);
        _it_cur_player == std::prev(_Scores_Table.end());
    }

    if (need_help)
        Show_Help();

}


void ScoreTable::Press_Enter(string msg)
{
    std::cout << msg << endl;
    std::cout << "Press Enter key to continue!" << endl;
    while (getchar() != '\n');
}

void ScoreTable::Show_Help()
{
    Press_Enter("It could be a strange thing who likes to chase your snake!!. Well, just if you choose to have it! "); 
    Press_Enter("Your score will be stored whenever you quit the game. You will can carry on with the same score when you come back.");
}

int ScoreTable::Press_YN()
{
    int c;
    do { c = getchar(); } while (c != 'Y' && c != 'y' && c != 'N' && c != 'n');
    return c;
}

string ScoreTable::Ask_Player_Name()
{   
    string player; 

    std::cout << endl;
    std::cout << "****************************" << endl;
    std::cout << "!! Wellcome to Snake Game !!" << endl;
    std::cout << "****************************" << endl;
    std::cout << endl;

    std::cout << "Please, enter your name: ";
    
    player.clear();

    while (player.empty())
    {
        getline(cin, player);
        if (player.empty())
        {
            std::cout << "Please, enter your name to play:" << endl;
        }
    } 
    return player;
}

bool mypredicate(int i, int j) {
    return (i == j);
}


// Search the current player in the score vector

vector<pair<string, float>>::iterator ScoreTable::Exist_Current_Player(const string current_player)
{
    //vector<pair<string, float>> v1;
    // v1.emplace_back(make_pair(current_player, 0.0));

    //return std::search(_Scores_Table.begin(), _Scores_Table.end(), v1.begin(), v1.end(), [](pair<string, float> a, pair<string, float> b) {     return (a.first == b.first); });
    std::vector<int> haystack;

    // set some values:        haystack: 10 20 30 40 50 60 70 80 90
    for (int i = 1; i < 10; i++) haystack.push_back(i * 10);

    // using default comparison:
    int needle1[] = { 40,50,60,70 };
    std::vector<int>::iterator it;
    it = std::search(haystack.begin(), haystack.end(), needle1, needle1 + 4);

    if (it != haystack.end())
        std::cout << "needle1 found at position " << (it - haystack.begin()) << '\n';
    else
        std::cout << "needle1 not found\n";

    // using predicate comparison:
    int needle2[] = { 20,30,50 };
    it = std::search(haystack.begin(), haystack.end(), needle2, needle2 + 3, mypredicate);

}

// Rewrite all score table to file.  Format:  Name:Score  (Example: Lucas:3.4)

void ScoreTable::Write_Scores_To_File(float score)
{
    _it_cur_player->second = score;

    writeFile.open(_Score_File_Name, std::ofstream::out);

    if (writeFile.is_open())
    {
        for_each(_Scores_Table.begin(), _Scores_Table.end(), [&](pair<string, float> a) { writeFile << a.first << ":" << to_string(a.second) << endl; });
        writeFile.close();
    }
    else
    {
        std::cout << "Problem with open file!";
    }

}

// Read all lines with format:  Name:Score  (Example: Lucas:3.4)

void ScoreTable::Read_Scoress_From_File()
{
    char line_char[260];
    string line;

    ReadFile.open(_Score_File_Name);
    if (ReadFile.is_open())
    {
        while (ReadFile.getline(line_char,256,'\n'))
        {
            line = line_char;
            size_t position = line.find(":");
            if (position++ != string::npos) {
                float scoreFromFile = stof(line.substr(position, line.size()-position));
                position -= 2;
                string playerFromFile = line.substr(0, position);
                _Scores_Table.emplace_back(playerFromFile, scoreFromFile); //store the player names and scores in _Scores_Table to sort scores in descending order and to find max score.
            }
            else {
                std::cout << "File " << _Score_File_Name << " bad format. Exiting..." << endl;
                exit(1);
            }
        }
        Sort_Scores();
        Better_Score();
    }
}

// 

void ScoreTable::Sort_Scores()
{
    sort(_Scores_Table.begin(), _Scores_Table.end(), [](pair<string, float> a, pair<string, float> b) { return a.second > b.second; });
}

// To get the high score from the list of scores stored in the file

void ScoreTable::Better_Score()
{
    _Better_Player = _Scores_Table.front();
}

// Displays game stats

ScoreTable::~ScoreTable()
{
    int top = 0;

    if (_it_cur_player->second > getmaxScoredPlayer()->second)
    {
        std::cout << "\t\t CONGRATULATIONS!! You got the highest score." << endl;
    }
    else if (_it_cur_player->second == getmaxScoredPlayer()->second)
    {
        std::cout << "\t\t Congratulations!! You got new highscore sharing top position with " << getmaxScoredPlayer()->first << "." << endl << endl;
    }
    
    
    float score = _it_cur_player->second;

    std::cout << "\t\t ********************************************************************************************" << endl;
    int fill = 74 - (_it_cur_player->first.size() >= 74 ? 74 : _it_cur_player->first.size());

    string space_filled(fill, ' ');
    std::cout << "\t\t ** PLAYER NAME: " << _it_cur_player->first.substr(0,74) << space_filled << "*" << endl;
    fill = 74 - (to_string(_it_cur_player->second).size() >= 74 ? 74 : to_string(_it_cur_player->second).size());
    string space_filled2(fill, ' ');
    std::cout << "\t\t **       SCORE: " << to_string(_it_cur_player->second) << space_filled2 << "*" << endl;

    std::cout << "\t\t ********************************************************************************************" << endl << endl;

    std::cout << "\t\t ********************************************************************************************" << endl;
    std::cout << "\t\t **************************  T O P      S C O R E S  ****************************************" << endl;
    std::cout << "\t\t ********************************************************************************************" << endl;

    for_each(_Scores_Table.begin(), _Scores_Table.end(), [&top](pair<string, float> a) { ++top; std::cout << setw(5) << to_string(top) << a.first << "  --  " << to_string(a.second) << endl; });

    std::cout << "\t\t ********************************************************************************************" << endl;

}


void ScoreTable::PrintComputerScore(float score)
{
    std::cout << "\t\t    COMPUTER SCORE IS " << score << endl;
}