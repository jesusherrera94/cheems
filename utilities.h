#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include <windows.h>
#include <iostream>

using namespace std;

class Utilities{
private:
public:
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
};


#endif // UTILITIES_H_INCLUDED
