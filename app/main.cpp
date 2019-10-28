#include <bits/stdc++.h>
#include "conf.h"
#include "clog.h"
#include "timeTools.h"

using namespace std;

CConfigKV *g_conf = nullptr;
CLog      *g_log  = nullptr;

void test() {

}

int main(int argc, char **argv)
{
    do {
        g_conf = new CConfigKV();
        g_conf->init();
        g_log  = new CLog();

        if (g_conf == nullptr || g_log == nullptr) {
            // 日志模块和配置模块都失败就没救了...
            break;
        }
        INFO_LOG("Success to init log and config");

        

        

    } while(false);

    return 0;
}
