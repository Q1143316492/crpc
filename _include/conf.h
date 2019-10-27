#ifndef _CONF_H_
#define _CONF_H_

#include <bits/stdc++.h>
using namespace std;

#define DEFAULT_CONFKV_PATH "conf/main.conf"
#define MAX_CONF_LINE_SIZE  500

class CConfigKV {
public:
    void load(string filepath = DEFAULT_CONFKV_PATH);
    string showConf();
private:
    unordered_map<string, string> confkv;
    string confFileName;
};

#endif
