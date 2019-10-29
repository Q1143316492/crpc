#ifndef _CONF_H_
#define _CONF_H_

#include <bits/stdc++.h>

using std::string;
using std::unordered_map;

#define DEFAULT_CONFKV_PATH "conf/main.conf"
#define MAX_CONF_LINE_SIZE  500

class CConfigKV {
public:
    void load(string filepath = DEFAULT_CONFKV_PATH);
    void init();
    string get_conf(string key);
    string showConf();
private:
    unordered_map<string, string> confkv;
    string confFileName;
};
#endif
