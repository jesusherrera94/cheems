#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED
#include "persona.h"

//fijarse aqui
class Usuarios: public Persona{

private:
    int pin;
    int tipo;
    string ultimoLogin;
public:
    Usuarios(){}
    //aqui tambien
    Usuarios(int id,string nombre, string identidad, string fechaNacimiento, int pin, int tipo, string ultimoLogin):
        Persona(id,nombre,identidad,fechaNacimiento){
        this -> pin = pin;
        this -> tipo = tipo;
        this -> ultimoLogin = ultimoLogin;
    }
    void setPin(int pin){
        this -> pin = pin;
    }
    void setTipo(int tipo){
        this -> tipo = tipo;
    }
    void setUltimoLogin(string ultimoLogin){
        this -> ultimoLogin = ultimoLogin;
    }
    int getPin(){
        return this -> pin;
    }
    int getTipo(){
        return this -> tipo;
    }
    string getUltimoLogin(){
        return this -> ultimoLogin;
    }
} ;

#endif // USUARIOS_H_INCLUDED
