#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <vector>
#include <string>
#include <utility>
#include <fstream>

using namespace std;

class InputData {

public:

    InputData();
    void Press_Enter(string msg = "");
    int Press_YN();
    void Show_Msg(string msg);
    string Ask_Name(bool& ok, string msg = "");
    int Ask_Int(bool& ok, string msg = "");
    int get_options(string msg, int lower_option, int higher_option);

private:
    int _int_val;
    float _float_val;
    string _string_val;
};

#endif