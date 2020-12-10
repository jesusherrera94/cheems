#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED



#include <iostream>
using namespace std;

class Persona{
private:
    int ID;
    string nombre;
    string identidad;
    string fechaNacimiento;
public:
    Persona(){}
    Persona(int id, string nombre, string identidad, string fechaNacimiento){
        this ->ID = id;
        this -> nombre = nombre;
        this -> identidad = identidad;
        this -> fechaNacimiento = fechaNacimiento;
    }
    void setID(int id){
        this->ID = id;
    }
    void setNombre(string nombre){
        this ->nombre = nombre;
    }
    void setIdentidad(string identidad){
        this ->identidad = identidad;
    }
    void setFechaNacimiento(string fechaNacimiento){
        this ->fechaNacimiento = fechaNacimiento;
    }
    int getID(){
        return this -> ID;
    }
    string getNombre(){
        return this -> nombre;
    }
    string getIdentidad(){
        return this -> identidad;
    }
    string getFechaNacimiento(){
        return this -> fechaNacimiento;
    }
    ~Persona(){};
};

#endif // PERSONA_H_INCLUDED
