#include "InputData.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <regex>



using namespace std;

// InputData Constructor.
// 

InputData::InputData()
{
    _int_val = 0;
    _float_val = 0.0;
    _string_val.clear();
}


void InputData::Press_Enter(string msg)
{
    std::cout << endl << msg << endl;
    std::cout << "Press Enter key to continue!" << endl;
    while (getchar() != '\n');
}

void InputData::Show_Msg(string msg)
{
    std::cout << endl << msg << endl;
}

int InputData::Press_YN()
{
    int ret;
    bool ok = false;

    _string_val.clear();

    while (!ok)
    {
        getline(cin, _string_val);
        ok = std::regex_match(_string_val, std::regex("^[YyNn]$"));
        
        if (_string_val.empty() || !ok)
        {
            std::cout << "Please, [Y/N]:";
        }
    }
    ret = _string_val[0];
    return ret;
}

int InputData::get_options(string msg, int lower_option, int higher_option)
{
    int choice = 0;
    bool ok = false, ok2;

    while (!ok)
    {
        choice = this->Ask_Int(ok2, msg);
        if (ok2) {
            if (choice >= lower_option && choice <= higher_option)
                ok = true;
        }
    }
    return choice;
}

string InputData::Ask_Name(bool& ok, string msg)
{   
    std::cout << msg;
    ok = false;
    
    _string_val.clear();

    while (!ok)
    {
        getline(cin, _string_val);
        if (_string_val.empty())
        {
            std::cout << "Please, " << msg;
        }
        
        ok = std::regex_match(_string_val, std::regex("^[A-Za-z ]+$"));
    } 
    return _string_val;
}

int InputData::Ask_Int(bool& ok, string msg)
{
    std::cout << msg;
    ok = false;

    _string_val.clear();

    while (!ok)
    {
        getline(cin, _string_val);
        if (_string_val.empty())
        {
            std::cout << "Please, " << msg;
        }

        ok = std::regex_match(_string_val, std::regex("^[0-9]+$"));
    }
    
    return std::stoi(_string_val);
}

