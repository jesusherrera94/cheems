#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED
#include <iostream>
#include "usuarios.h"
#include "validations.h"
#include "ios.h"
#include "utilities.h"
#include "menu.h"

using namespace std;

class login{
    private:
        Usuarios sesion;
    public:
        void doLogin(){
            int pin=0;
            bool finished = false;
            do{
                cout<<"Ingrese pin: ";
                cin>>pin;
                Validations vt;
                cout<<vt.isUserExists(pin)<<endl;
                if(vt.validateUsrPinFormt(pin)){
                    Utilities ut;
                    IOS is(ut.ExePath());
                    if(vt.isUserExists(pin)){
                        this -> sesion = is.getUser(pin);
                        system("cls");
                        Menu menu(sesion);
                        vt.updateLastLogin(sesion.getPin());
                        switch(sesion.getTipo()){
                            case 1:
                                menu.adminMainMenu();
                                finished = true;
                                break;
                            case 2:
                                menu.bomberoMainMenu();
                                finished = true;
                                break;
                            default:
                                finished = false;
                                cout<<"Error al iniciar sesión....";
                        }
                    }
                    else{
                        cout<<"El usuario no existe"<<endl;
                    }
                }
                else{
                    cout<<"El formato del pin debe de ser de 4 dígitos"<<endl;
                }
            }
            while(finished==false);
        }
};

#endif // LOGIN_H_INCLUDED
