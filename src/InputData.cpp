#include "ScoreTable.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
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
    _it_cur_player = _Scores_Table.end();
    current_player = Ask_Player_Name();

    Read_Scoress_From_File();

    if (_Scores_Table.size()) {
        if ((_it_cur_player = Exist_Current_Player(current_player)) != _Scores_Table.end()) {
            std::cout << endl << "Wellcome back " << current_player << ". Glad to see you again. You will continue with " << _it_cur_player->second << " score!! " << endl << endl;

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

    if (_it_cur_player == _Scores_Table.end()) 
    {
        _Scores_Table.emplace_back(make_pair(current_player, 0.0));
        _it_cur_player = std::prev(_Scores_Table.end());
    }

    if (need_help)
        Show_Help();
}


void ScoreTable::Press_Enter(string msg)
{
    std::cout << endl << msg << endl;
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

vector<pair<string, int>>::iterator ScoreTable::Exist_Current_Player(const string current_player)
{
    vector<pair<string, int>> v1;
    v1.emplace_back(make_pair(current_player, 0.0));

    return std::search(_Scores_Table.begin(), _Scores_Table.end(), v1.begin(), v1.end(), [](pair<string, int> a, pair<string, int> b) {     return (a.first == b.first); });
}

// Rewrite all score table to file.  Format:  Name:Score  (Example: Lucas:3.4)

void ScoreTable::Write_Scores_To_File(int score)
{
    _it_cur_player->second = score;

    writeFile.open(_Score_File_Name, std::ofstream::out);

    if (writeFile.is_open())
    {
        for_each(_Scores_Table.begin(), _Scores_Table.end(), [&](pair<string, int> a) { writeFile << a.first << ":" << to_string(a.second) << endl; });
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
    string line, field;
    istringstream sline;
    vector<string> v_fields;

    ReadFile.open(_Score_File_Name);
    if (ReadFile.is_open())
    {
        while (ReadFile.getline(line_char,256,'\n'))
        {
            line = line_char;
            
            istringstream sline(line);
            v_fields.clear();

            while (std::getline(sline, field, ':')) {	// Cut fields
                v_fields.push_back(field);
            }

            if(v_fields.size()==2) 
            {
                std::string::size_type sz;
                int score = std::stoi(v_fields[1], &sz);
                _Scores_Table.emplace_back(v_fields[0], score); //store the player names and scores in _Scores_Table to sort scores in descending order and to find max score.
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
    sort(_Scores_Table.begin(), _Scores_Table.end(), [](pair<string, int> a, pair<string, int> b) { return a.second > b.second; });
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

    if (_it_cur_player->second > Get_Better_Player()->second)
    {
        std::cout << "\n\t\t CONGRATULATIONS!! You got the highest score." << endl << endl;
    }
    else if (_it_cur_player->second == Get_Better_Player()->second)
    {
        std::cout << "\t\t Congratulations!! You got new highscore sharing top position with " << Get_Better_Player()->first << "." << endl << endl;
    }
    
    
    float score = _it_cur_player->second;

    std::cout << "\t\t ********************************************************************************************" << endl;
    int fill = 74 - (_it_cur_player->first.size() >= 74 ? 74 : _it_cur_player->first.size());

    string space_filled(fill, ' ');
    std::cout << "\t\t ** PLAYER NAME: " << _it_cur_player->first.substr(0,74) << space_filled << "**" << endl;
    fill = 74 - (to_string(_it_cur_player->second).size() >= 74 ? 74 : to_string(_it_cur_player->second).size());
    space_filled = std::string(fill, ' ');
    std::cout << "\t\t **       SCORE: " << to_string(_it_cur_player->second) << space_filled << "**" << endl;

    std::cout << "\t\t ********************************************************************************************" << endl << endl;

    std::cout << "\t\t ********************************************************************************************" << endl;
    std::cout << "\t\t ******************************  T O P      S C O R E S  ************************************" << endl;
    std::cout << "\t\t ********************************************************************************************" << endl;

    Sort_Scores();

    for_each(_Scores_Table.begin(), _Scores_Table.end(), [&top, &fill, &space_filled](pair<string, int> a) {
        ++top; 
        fill = 70 - (a.first.size() >= 70 ? 70 : a.first.size());
        space_filled = std::string(fill, '.');

        std::cout << "\t\t ** " << setw(5) << to_string(top) << ". " << a.first << "  " << space_filled << "  " << to_string(a.second) << "     **" << endl;
        
        });

    std::cout << "\t\t ********************************************************************************************" << endl;

}


void ScoreTable::Show_Computer_Score(int score)
{
    std::cout << "\t\t    COMPUTER SCORE IS " << score << endl;
}