#ifndef _STRING_TOOLS_H_
#define _STRING_TOOLS_H_

#include <bits/stdc++.h>

using std::string;
using std::stringstream;
using std::setw;
using std::setfill;
using std::vector;
using std::ifstream;

class StringTools {
public:

    static string IntToString(int val);

    static int StringToInt(string str);

    /**
        清除某一行的注释
        1, 第一版只清除# 后面的东西
    */
    static void clearComment(string &str);

    /**
        按照某个符号切割字符串
    */
    static vector<string> splitString(const string &str, char splitChar = ';');

    /**
        去除前后空格符    
    */
    static void trim(string &str);
};

#endif