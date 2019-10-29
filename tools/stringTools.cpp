#include "stringTools.h"
#include "conf.h"

extern CConfigKV g_conf;

string StringTools::IntToString(int val)
{
    stringstream ss;
    ss << val;
    return ss.str();
}

int StringTools::StringToInt(string str)
{
    int val = 0;
    for(size_t i = 0; i < str.size(); i++ ) {
        val = val * 10 + str[i] - '0';
    }
    return val;
}

void StringTools::clearComment(string &str)
{
    char markComment[] = "#[({<";
    for (size_t i = 0; i < str.size(); i++ ) {
        for (size_t j = 0; markComment[j]; j++ ) {
            if (str[i] == markComment[j]) {
                str = str.substr(0, i);
                return ;
            }
        }
    }
}

vector<string> StringTools::splitString(const string &str, char splitChar)
{
    vector<string> vecSplitStr;
    stringstream ss;
    for (size_t i = 0; i < str.size(); i++ ) {
        if (str[i] == splitChar) {
            vecSplitStr.push_back(ss.str());
            ss.str("");
        } else {
            ss << str[i];
        }
    }
    if (ss.str().size() != 0) {
        vecSplitStr.push_back(ss.str());
        ss.clear();
    }
    return vecSplitStr;
}

void StringTools::trim(string &str)
{
    if (str == "" || str.empty()) {
        return ;
    }
    int l = 0, r = str.size() - 1;
    while(str[l] == ' ') { l++; }
    while(str[r] == ' ') { r--; }
    str = str.substr(l, r - l + 1);
}