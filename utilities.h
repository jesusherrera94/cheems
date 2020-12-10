#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include <windows.h>
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

class Utilities{
private:
public:
    Utilities(){}
    string tokenizer(string cadena, string divisor, int pos){
                        if(cadena.size()>0){
                         char oracion[cadena.size()];
                         for (int i=0;i<=cadena.size();i++)
                            {
                                oracion[i]=cadena[i];
                            }
                         char *ptrtoken;
                         int num=1;
                         const char* d=divisor.c_str();
                         ptrtoken = strtok(oracion , d);
                         while(ptrtoken){
                             if(num==pos){
                                return ptrtoken;
                                }
                             ptrtoken = strtok(NULL, d);
                             num++;
                        }
                         return "";
                       }
                       else{
                           return "";
                        }
        };
    string ExePath() {
       char buffer[MAX_PATH];
       GetModuleFileName( NULL, buffer, MAX_PATH );
       string::size_type pos = string( buffer ).find_last_of( "\\/" );
       return string( buffer ).substr( 0, pos-9);
    }
    //Terminar esto
    string getActualDate(){
        time_t t = time(0);
        struct tm * now = localtime( & t );
        stringstream day;
        day << now->tm_mday;
        stringstream month;
        month << (now->tm_mon + 1);
        stringstream year;
        year << (now->tm_year + 1900);
        string actualDate = day.str() + "/" + month.str() + "/" + year.str();
       return actualDate;
    }
    ~Utilities(){}
};


#endif // UTILITIES_H_INCLUDED
