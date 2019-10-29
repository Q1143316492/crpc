#include "conf.h"
#include "stringTools.h"

void CConfigKV::init()
{
    this->load();
}

void CConfigKV::load(string strFilePath)
{
    this->confFileName = strFilePath;
    if (strFilePath.empty() || strFilePath == "") {
        strFilePath = DEFAULT_CONFKV_PATH;
    }
    ifstream fp(strFilePath);
    string strLine;
    int iLineNum = 0;
    while (getline(fp, strLine)) {
        iLineNum++;
        if (strLine.size() > MAX_CONF_LINE_SIZE) {
            continue;
        }
        StringTools::clearComment(strLine);
        if (strLine.size() == 0 || strLine == "") {
            continue;
        }
        vector<string>vecKv = StringTools::splitString(strLine, '=');
        if (vecKv.size() != 2) {
            continue;
        }
        StringTools::trim(vecKv[0]);
        StringTools::trim(vecKv[1]);
        if (!vecKv[0].size() || !vecKv[1].size()) {
            continue;
        }
        if (confkv.count(vecKv[0])) {
            confkv[ vecKv[0] ] += ";";
            confkv[ vecKv[0] ] += vecKv[1];
        } else {
            confkv[ vecKv[0] ] = vecKv[1];
        }
    }
}

string CConfigKV::showConf()
{
    stringstream ss("");
    for (unordered_map<string, string>::iterator it = confkv.begin(); it != confkv.end(); it++ ) {
        ss << it->first << " " << it->second << "\n";
    }
    return ss.str();
}

string CConfigKV::get_conf(string key)
{
    if (this->confkv.count(key)) {
        return this->confkv[key];
    }
    return "";
}