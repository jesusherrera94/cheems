#ifndef IOS_H_INCLUDED
#define IOS_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include<conio.h>
#include<stdlib.h>
#include"usuarios.h"
#include "producto.h"
#include "utilities.h"

using namespace std;

//in and out
class IOS{
    private:
        Usuarios urs[1000];
        Producto productos[1000];
        //añadir arreglo de clientes....
        string txtUsrs[1000];
        Utilities ut;
        string path;
    public:
        IOS(string path){
            this -> path = path;
        };
        string* getTxtUsrs(){
            return this -> txtUsrs;
        }
        Usuarios* getAllUsrsObj(){
            return this -> urs;
        }
        Producto* getAllProducts(){
            return this -> productos;
        }

        void leerTodosUsuarios(){
            string cadena;
            int i=0;

            ifstream fe(this -> path + "/BD/usuarios.txt");

              while (getline(fe,cadena)) {
                urs[i].setID(stoi(ut.tokenizer(cadena,",",1)));
                urs[i].setNombre(ut.tokenizer(cadena,",",2));
                urs[i].setIdentidad(ut.tokenizer(cadena,",",3));
                urs[i].setFechaNacimiento(ut.tokenizer(cadena,",",4));
                urs[i].setPin(stoi(ut.tokenizer(cadena,",",5)));
                urs[i].setTipo(stoi(ut.tokenizer(cadena,",",6)));
                urs[i].setUltimoLogin(ut.tokenizer(cadena,",",7));
                txtUsrs[i] = cadena;
                i++;
              }
              fe.close();
        }
        //lectura de clientes
        void leerTodosClientes(string path){
            string cadena;
            ifstream fe(path + "/BD/clientes.txt");

              while (!fe.eof()) {
                getline(fe,cadena);
                cout << cadena << endl;
              }
              fe.close();
        }

        void leerTodosLosProductos(){
             string cadena;
             int i=0;
                ifstream fe(this -> path + "/BD/productos.txt");

                  while (!fe.eof()) {
                    getline(fe,cadena);
                    productos[i].setId(stoi(ut.tokenizer(cadena,",",1)));
                    productos[i].setNombre(ut.tokenizer(cadena,",",2));
                    productos[i].setTipo(ut.tokenizer(cadena,",",3));
                    productos[i].setStock(stoi(ut.tokenizer(cadena,",",4)));
                    string precioUnitario= ut.tokenizer(cadena,",",5);
                    //convertir de formato internacional a europeo
                    int pos = precioUnitario.find(".",0);
                    precioUnitario.replace(pos,1,",");
                    //insertar el valor unitario en float
                    productos[i].setPrecioUnitario(stof(precioUnitario));
                    i++;
                  }
                  fe.close();
        }
};


#endif // IOS_H_INCLUDED
