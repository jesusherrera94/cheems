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
#include "cliente.h"
#include "validations.h"
#include <string.h>
#include "factura.h"

using namespace std;

//in and out
class IOS{
    private:
        Usuarios urs[100];
        Producto productos[100];
        Cliente clientes[1000];
        string txtUsrs[100];
        Factura facturas[100];
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
        Cliente* getAllClientsObj(){
            return this -> clientes;
        }
        Producto* getAllProducts(){
            return this -> productos;
        }

        Factura* getAllFacturas(){
            return this ->facturas;
        }

        void leerTodosUsuarios(){
            string cadena;
            int i=0;

            //ifstream fe("C:/Users/jesus/Documents/Tareas/Programacion de sistemas/ejemplos de clase/cheemsv1/BD/usuarios.txt");
            ifstream fe(this -> path + "/BD/usuarios.txt");
              while (!fe.eof()) {
                getline(fe,cadena);
                if(cadena!=""&&cadena!="\n"){
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
              }
              fe.close();
        }
        //lectura de clientes
        void leerTodosClientes(){
            string cadena;
            int i = 0;
            ifstream fe(this -> path + "/BD/clientes.txt");
              while (!fe.eof()) {
                getline(fe,cadena);
                clientes[i].setID(stoi(ut.tokenizer(cadena,",",1)));
                clientes[i].setNombre(ut.tokenizer(cadena,",",2));
                clientes[i].setIdentidad(ut.tokenizer(cadena,",",3));
                clientes[i].setFechaNacimiento(ut.tokenizer(cadena,",",4));
                clientes[i].Establecerpin(stoi(ut.tokenizer(cadena,",",5)));
                clientes[i].EstablecerfechaUltimaCompra(ut.tokenizer(cadena,",",6));
                clientes[i].Establecernvisitas(stoi(ut.tokenizer(cadena,",",7)));
                i++;
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
                    if(pos!=-1){
                      precioUnitario.replace(pos,1,",");
                    }
                    //insertar el valor unitario en float
                    productos[i].setPrecioUnitario(stof(precioUnitario));
                    i++;
                  }
                  fe.close();
        }
        void leerTodasLasFacturas(){
            string cadena;
            int i=0;
            ifstream fe(this -> path + "/BD/facturas.txt");
                  while (!fe.eof()) {
                    getline(fe,cadena);
                    facturas[i].setID(stoi(ut.tokenizer(cadena,",",1)));
                    facturas[i].setCajero(ut.tokenizer(cadena,",",2));
                    facturas[i].setPinCajero(stoi(ut.tokenizer(cadena,",",3)));
                    facturas[i].setCliente(ut.tokenizer(cadena,",",4));
                    facturas[i].setPinCliente(stoi(ut.tokenizer(cadena,",",5)));
                    facturas[i].setFecha(ut.tokenizer(cadena,",",6));
                    facturas[i].setNumeroFactura(stoi(ut.tokenizer(cadena,",",7)));
                    string total= ut.tokenizer(cadena,",",8);
                    int pos = total.find(".",0);
                    if(pos!=-1){
                      total.replace(pos,1,",");
                    }
                    facturas[i].setTotal(stof(total));
                    facturas[i].setBombaCaja(stoi(ut.tokenizer(cadena,",",9)));
                    i++;
                  }
            fe.close();
        }

        Usuarios getUser(int pin){
            string cadena;
            ifstream fe(this -> path + "/BD/usuarios.txt");
            Usuarios usuario;
            while (!fe.eof()) {
                getline(fe,cadena);
                if(stoi(ut.tokenizer(cadena,",",5))==pin){
                        //int id,string nombre, string identidad, string fechaNacimiento, int pin, int tipo, string ultimoLogin
                    usuario.setNombre(ut.tokenizer(cadena,",",2));
                    usuario.setPin(stoi(ut.tokenizer(cadena,",",5)));
                    usuario.setTipo(stoi(ut.tokenizer(cadena,",",6)));
                }
            }
            fe.close();
            return usuario;
        }

        void escribirUsuarios(int aSize){
            ofstream file;
                    file.open(this -> path  + "/BD/usuarios.txt");
                    int k = 0;
                    while(k<aSize){
                     if(this ->getAllUsrsObj()[k].getNombre()!=""){

                            if(aSize-k>1){
                                file << this -> getAllUsrsObj()[k].getID()<<","<<this ->getAllUsrsObj()[k].getNombre()<<","<<this ->getAllUsrsObj()[k].getIdentidad()
                                <<","<<this ->getAllUsrsObj()[k].getFechaNacimiento()<<","<<this ->getAllUsrsObj()[k].getPin()<<","<<this ->getAllUsrsObj()[k].getTipo()<<","<<this ->getAllUsrsObj()[k].getUltimoLogin()<<"\n";
                            }
                            else{
                                file << this ->getAllUsrsObj()[k].getID()<<","<<this ->getAllUsrsObj()[k].getNombre()<<","<<this ->getAllUsrsObj()[k].getIdentidad()
                                <<","<<this ->getAllUsrsObj()[k].getFechaNacimiento()<<","<<this ->getAllUsrsObj()[k].getPin()<<","<<this ->getAllUsrsObj()[k].getTipo()<<","<<this ->getAllUsrsObj()[k].getUltimoLogin();
                            }
                            k++;
                        }
                    }
                    file.close();
        }

        void escribirClientes(int aSize){
        ofstream file;
                    file.open(this -> path  + "/BD/clientes.txt");
                    int k = 0;
                    while(k<aSize){
                     if(this ->getAllClientsObj()[k].getNombre()!=""){
                                if(aSize-k>1){
                                    file <<this ->getAllClientsObj()[k].getID()<<","<<this ->getAllClientsObj()[k].getNombre()<<","<<this ->getAllClientsObj()[k].getIdentidad()
                                    <<","<<this ->getAllClientsObj()[k].getFechaNacimiento()<<","<<this ->getAllClientsObj()[k].Obtenerpin()<<","<<this ->getAllClientsObj()[k].ObtenerfechaUltimaCompra()<<","<<this ->getAllClientsObj()[k].Obtenernvisitas()<<"\n";
                                }
                                else{
                                    file << this ->getAllClientsObj()[k].getID()<<","<<this ->getAllClientsObj()[k].getNombre()<<","<<this ->getAllClientsObj()[k].getIdentidad()
                                    <<","<<this ->getAllClientsObj()[k].getFechaNacimiento()<<","<<this ->getAllClientsObj()[k].Obtenerpin()<<","<<this ->getAllClientsObj()[k].ObtenerfechaUltimaCompra()<<","<<this ->getAllClientsObj()[k].Obtenernvisitas();
                                }
                                k++;
                        }
                    }
                    file.close();
        }

        ~IOS(){}
};

#endif // IOS_H_INCLUDED
