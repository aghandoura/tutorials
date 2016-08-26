#include <iostream>
#include <cmath>
#include <climits>
#include <string>
#include <sstream>
#include <cstdlib>
#include <regex>

#define EXIT_NUMBER (42)
using namespace std;

int main(int argc, const char *argv[])
{

    float input1;
    float input2;
    string date("1:20:50AM");
    //regex pattern("((0?[0-9])|(1[0-2])):[0-5][0-9]:[0-5][0-9]((PM)|AM))");
    //regex pattern("((1[0-2])|(0?[1-9])):([0-5][0-9])((am)|(pm))");
    string pattern_str("^[a-z]");
    regex pattern(pattern_str);

    if (regex_match(date, pattern))
        cout << "string match pattern" <<endl<<date<<endl;
    else
        cout << "string does not match pattern" <<endl<<date<<endl;


    int hours = atoi((date.substr (0, 2)).c_str());

    size_t found = string::npos;
    found = date.find('P', date.size()-2);

    if (found!=string::npos)
       hours += 12;

    date.resize(date.size()-2);
    date.erase(date.begin() , date.begin() + 2);

    if (hours < 10)
    cout << "0";

    cout <<hours<< date;


    return 0;
}

