#include <windows.h>
#include <iostream>
#include <fstream>
#include <wchar.h>
#include <locale.h>
#include<string.h>
#include "login.h"


using namespace std;

string exePath() {
       char buffer[MAX_PATH];
       GetModuleFileName( NULL, buffer, MAX_PATH );
       string::size_type pos = string( buffer ).find_last_of( "\\/" );
       return string( buffer ).substr( 0, pos-9);
    }

int main()
{
    setlocale(LC_ALL, "spanish");
    login lg;
    lg.doLogin();

    return 0;
}



using namespace std;
