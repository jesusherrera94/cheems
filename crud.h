#ifndef CRUD_H_INCLUDED
#define CRUD_H_INCLUDED

#include <unistd.h>
#include <fstream>
#include "utilities.h"
#include "validations.h"
#include "ios.h"
#include "usuarios.h"
#include "cliente.h"
#include "producto.h"
#include <cstring>
#include <cstdio>

class CRUD{
private:
    Utilities ut;
    string path = ut.ExePath();
public:
//USUARIOS==================================================================================================================================================================
    //agregar usuario
        void nuevoUsuario(){
            system("cls");
            cout<<"\t__==Gasolinera CEUTEC==__\n\t     creación de usuario"<<endl;
            string nombre, identidad, fechaNacimiento, ultimoLogin, cadena;
            int id=0, pin, tipo, i=1;
            Validations vt;
            IOS is(ut.ExePath());
            ifstream fe(this -> path + "/BD/usuarios.txt");
            while (!fe.eof()) {
                getline(fe,cadena);
                id = stoi(ut.tokenizer(cadena,",",1));
                pin = stoi(ut.tokenizer(cadena,",",5));
            }
            cin.ignore();
            while(i<=4){
                switch(i){
                    case 1:
                        cout<<"Ingrese nombre: ";
                        getline(cin,nombre);
                        if(vt.validateTextField(nombre)){
                            i++;
                        }else{
                            cout<<"***Error, debe de ingresar el nombre"<<endl;
                        }
                        break;
                    case 2:
                        cout<<"Ingrese número de identidad(sin guiones): ";
                        getline(cin,identidad);
                        if(vt.validateTextField(identidad)/*&&strlen(identidad)==13*/){
                            i++;
                        }
                        else{
                            cout<<"****Error: La identidad debe ser al menos de 13 carácteres"<<endl;
                        }
                        break;
                    case 3:
                        cout<<"Ingrese fecha de nacimiento(ejemplo: 12/12/2002): ";
                        getline(cin,fechaNacimiento);
                        if(vt.validateTextField(fechaNacimiento)){
                            i++;
                        }
                        else{
                            cout<<"****Error: La fecha de nacimiento no puede quedar vacía"<<endl;
                        }
                        break;
                    case 4:
                        cout<<"Ingrese Tipo de usuario[1-administrador, 2-cajero/bombero]: ";
                        cin>>tipo;
                        if(vt.validateNumberField(tipo)&&(tipo==1||tipo==2)){
                            i++;
                        }else{
                            cout<<"****Error: Formato de tipo de usuario inválido"<<endl;
                        }
                        break;
                }
            }
            ofstream file;
            file.open(this -> path  + "/BD/usuarios.txt",ios::app);
            file <<"\n"<<(id+1)<<","<<nombre<<","<<identidad<<","<<fechaNacimiento<<","<<(pin+1)<<","<<tipo<<","<<ut.getActualDate();
            file.close();
            cout<<"*****Ususario creado con éxito"<<endl;
            cout<<"El PIN del nuevo usuario es: "<<( pin + 1 )<<endl;
            system("pause");
            system("cls");

        }
    //Listar los ususarios
    void listUsers(Usuarios sesion){
        system("cls");
        IOS is(ut.ExePath());
        Validations vt;
        int index=0,j, aSize=0;
        cout<<"\t__==Gasolinera CEUTEC==__\n\t     lista de usuarios"<<endl;
        cout<<"====================================================================================================================="<<endl;
        cout<<"||\tID\t||\tNombre\t||\tIdentidad\t||\t tipo de ususario\t ||\tUltimo login\t||"<<endl;
        cout<<"====================================================================================================================="<<endl;
        is.leerTodosUsuarios();
        for(int i=0;i<1000;i++){
                if(is.getAllUsrsObj()[i].getNombre()!=""){
                    cout <<"||\t"<< is.getAllUsrsObj()[i].getID()<<"\t||\t"<<is.getAllUsrsObj()[i].getNombre()<<"\t||\t"<<is.getAllUsrsObj()[i].getIdentidad()<<"\t||\t";
                    switch(is.getAllUsrsObj()[i].getTipo()){
                    case 1:
                        cout<<"admin";
                        break;
                    case 2:
                        cout<<"cajero";
                        break;
                    default:
                        cout<<"N/A";
                    }
                    cout<<"\t||\t"<<is.getAllUsrsObj()[i].getUltimoLogin()<<"\t||"<<endl;
                    aSize++;
                }

            }
        cout<<"====================================================================================================================="<<endl;
        do{
            cout<<"1)Editar usuario\n2)Dar de baja\n3)Regresar\nIngrese opción: ";
            cin>>index;
            switch(index){
                case 1:
                    {cout<<"Ingrese ID de usuario a editar: ";
                    cin>>j;
                    j= vt.getUserPos(j);
                    if(j!=-1){
                        is.getAllUsrsObj()[j] = this ->editarUsuario(is.getAllUsrsObj()[j]);
                        ofstream file;
                        file.open(this -> path  + "/BD/usuarios.txt");
                        int k = 0;
                        while(k<aSize){
                         if(is.getAllUsrsObj()[k].getNombre()!=""){

                                if(aSize-k>1){
                                    file << is.getAllUsrsObj()[k].getID()<<","<<is.getAllUsrsObj()[k].getNombre()<<","<<is.getAllUsrsObj()[k].getIdentidad()
                                    <<","<<is.getAllUsrsObj()[k].getFechaNacimiento()<<","<<is.getAllUsrsObj()[k].getPin()<<","<<is.getAllUsrsObj()[k].getTipo()<<","<<is.getAllUsrsObj()[k].getUltimoLogin()<<"\n";
                                }
                                else{
                                    file << is.getAllUsrsObj()[k].getID()<<","<<is.getAllUsrsObj()[k].getNombre()<<","<<is.getAllUsrsObj()[k].getIdentidad()
                                    <<","<<is.getAllUsrsObj()[k].getFechaNacimiento()<<","<<is.getAllUsrsObj()[k].getPin()<<","<<is.getAllUsrsObj()[k].getTipo()<<","<<is.getAllUsrsObj()[k].getUltimoLogin();
                                }
                                k++;
                            }
                        }
                        cout<<"Usuario editado con éxito"<<endl;
                        file.close();
                        system("pause");
                        system("cls");
                    }else{
                        cout<<"Usuario no encontrado"<<endl;
                    }
                    break;
                    }
                case 2:
                    {
                    char yesnt;
                    cout<<"Ingrese ID de usuario a eliminar: ";
                    cin>>j;
                    j= vt.getUserPos(j);
                        if(is.getAllUsrsObj()[j].getPin()!=sesion.getPin()){
                        cout<<"Está seguro de eliminar usuario "<<is.getAllUsrsObj()[j].getNombre()<<"?, [ si:S ,n:N ]: ";
                        cin>>yesnt;
                            if(tolower(yesnt)=='s'){
                                ofstream file;
                                file.open(this -> path  + "/BD/usuarios.txt");
                                int ii = 0;
                                while(ii<aSize){
                                     if(is.getAllUsrsObj()[ii].getNombre()!=""&&ii!=j){
                                            if(aSize-ii>1){
                                                file << is.getAllUsrsObj()[ii].getID()<<","<<is.getAllUsrsObj()[ii].getNombre()<<","<<is.getAllUsrsObj()[ii].getIdentidad()
                                                <<","<<is.getAllUsrsObj()[ii].getFechaNacimiento()<<","<<is.getAllUsrsObj()[ii].getPin()<<","<<is.getAllUsrsObj()[ii].getTipo()<<","<<is.getAllUsrsObj()[ii].getUltimoLogin()<<"\n";
                                            }
                                            else{
                                                file << is.getAllUsrsObj()[ii].getID()<<","<<is.getAllUsrsObj()[ii].getNombre()<<","<<is.getAllUsrsObj()[ii].getIdentidad()
                                                <<","<<is.getAllUsrsObj()[ii].getFechaNacimiento()<<","<<is.getAllUsrsObj()[ii].getPin()<<","<<is.getAllUsrsObj()[ii].getTipo()<<","<<is.getAllUsrsObj()[ii].getUltimoLogin();
                                            }
                                        }
                                    ii++;
                                }
                                cout<<"Usuario Eliminado con éxito"<<endl;
                                file.close();
                                system("pause");
                                system("cls");
                            }
                        }else{
                            cout<<"*****Error:No puede eliminar su mismo usuario"<<endl;
                        }
                    break;
                    }
                case 3:{
                    system("cls");
                    break;
                    }
                default:
                    cout<<"Opción no válida...."<<endl;
            }
        }while(index!=3);

    }

    Usuarios editarUsuario(Usuarios usr){
        system("cls");
        cin.ignore();
        string nombre, identidad, fechaNacimiento;
        int tipo,index=0;
        Validations vt;
        cout<<"\t__==Gasolinera CEUTEC==__\n\t     Editar usuario"<<endl;
        cout<<"1)Nombre\n2)Identidad\n3)Fecha Nacimiento\n4)Tipo de usuario\n5)Regresar\nIngrese opción: ";
        cin>>index;
        cin.ignore();
        switch(index){
            case 1:
                cout<<"Ingrese nombre a editar: ";
                getline(cin,nombre);
                        if(vt.validateTextField(nombre)){
                            usr.setNombre(nombre);
                        }else{
                            cout<<"***Error, debe de ingresar el nombre"<<endl;
                        }
                break;
            case 2:
                cout<<"Ingrese número de identidad(sin guiones): ";
                        getline(cin,identidad);
                        if(vt.validateTextField(identidad)/*&&strlen(identidad)==13*/){
                            usr.setIdentidad(identidad);
                        }
                        else{
                            cout<<"****Error: La identidad debe ser al menos de 13 carácteres"<<endl;
                        }
                break;
            case 3:
                cout<<"Ingrese fecha de nacimiento(ejemplo: 12/12/2002): ";
                        getline(cin,fechaNacimiento);
                        if(vt.validateTextField(fechaNacimiento)){
                            usr.setFechaNacimiento(fechaNacimiento);
                        }
                        else{
                            cout<<"****Error: La fecha de nacimiento no puede quedar vacía"<<endl;
                        }
                        break;
                break;
            case 4:
                cout<<"Ingrese Tipo de usuario[1-administrador, 2-cajero/bombero]: ";
                        cin>>tipo;
                        if(vt.validateNumberField(tipo)&&(tipo==1||tipo==2)){
                            usr.setTipo(tipo);
                        }else{
                            cout<<"****Error: Formato de tipo de usuario inválido"<<endl;
                        }
                break;
            case 5:
                system("cls");
                break;
            default:
                cout<<"No es una opción..."<<endl;
        }
        return usr;
    }
//FIN DE USUSARIOS======================================================================================================================================================
//INICIO DE CLIENTES======================================================================================================================================================
void nuevoCliente(){
    system("cls");
    cout<<"\t__==Gasolinera CEUTEC==__\n\t     creación de usuario"<<endl;
    string nombre, identidad, fechadenacimiento, fechaUltimaCompra, cadena;
    int id=0, pin, i=1;
    Validations vt;
    IOS is(ut.ExePath());
    ifstream fe(this -> path + "/BD/clientes.txt");
    while (!fe.eof()) {
        getline(fe,cadena);
        id = stoi(ut.tokenizer(cadena,",",1));
        pin = stoi(ut.tokenizer(cadena,",",5));
    }
    cin.ignore();
    while (i<=3)
    {
        switch (i)
        {
        case 1:
            cout<<"Ingrese nombre: ";
            getline(cin,nombre);
            if(vt.validateTextField(nombre))
            {
                i++;
            }
            else
            {
                cout<<"***Error, debe ingresar el nombre"<<endl;
            }
            break;
        case 2:
            cout<<"Ingrese número de identidad(sin nombres): ";
            getline(cin,identidad);
            if(vt.validateTextField(identidad)/*&&strlen(identidad)==13*/)
            {
                i++;
            }
            else
            {
                cout<<"***Error: La identidad debe ser al menos 13 carácteres"<<endl;
            }
            break;
        case 3:
            cout<<"Ingrese fecha de nacimiento(ejemplo: 12/12/2002): ";
            getline(cin,fechadenacimiento);
            if(vt.validateTextField(fechadenacimiento))
            {
                i++;
            }
            else
            {
                cout<<"***Error: La fecha de nacimiento no puede quedar vacía"<<endl;
            }
            break;
            default:
                cout<<"Opción no válida";
                break;
        }
    }
            ofstream file;
            file.open(this -> path  + "/BD/clientes.txt",ios::app);
            file <<"\n"<<(id+1)<<","<<nombre<<","<<identidad<<","<<fechadenacimiento<<","<<(pin+1)<<","<<ut.getActualDate()<<","<<1;
            file.close();
            cout<<"*****Cliente creado con éxito"<<endl;
            cout<<"El PIN del nuevo cliente es: "<<( pin + 1 )<<endl;
            system("pause");
            system("cls");
}
void listClients(){
        system("cls");
        IOS is(ut.ExePath());
        Validations vt;
        int index=0,j, aSize=0;
        cout<<"\t__==Gasolinera CEUTEC==__\n\t     Lista de clientes"<<endl;
        cout<<"====================================================================================================================="<<endl;
        cout<<"||\tID\t||\tNombre\t||\tIdentidad\t||\t No. Compras\t ||\tÚltima compra\t||"<<endl;
        cout<<"====================================================================================================================="<<endl;
        is.leerTodosClientes();
        for(int i=0;i<1000;i++){
                if(is.getAllClientsObj()[i].getNombre()!=""){
                    cout <<"||\t"<< is.getAllClientsObj()[i].getID()<<" \t||\t"<<is.getAllClientsObj()[i].getNombre()<<"\t||\t"<<is.getAllClientsObj()[i].getIdentidad()<<"\t||\t";
                    cout<<is.getAllClientsObj()[i].Obtenernvisitas()<<"\t||\t"<<is.getAllClientsObj()[i].ObtenerfechaUltimaCompra()<<"\t||"<<endl;
                    aSize++;
                }

            }
        cout<<"====================================================================================================================="<<endl;
        do{
            cout<<"1)Editar Cliente\n2)Dar de baja\n3)Regresar\nIngrese opción: ";
            cin>>index;
            switch(index){
                case 1:
                    {
                    cout<<"Ingrese ID de cliente a editar: ";
                    cin>>j;
                    j=vt.getClientPos(j);
                    if(j!=-1){
                        is.getAllClientsObj()[j] = this ->editarClient(is.getAllClientsObj()[j]);
                        ofstream file;
                        file.open(this -> path  + "/BD/clientes.txt");
                        int k = 0;
                        while(k<aSize){
                         if(is.getAllClientsObj()[k].getNombre()!=""){

                                if(aSize-k>1){
                                    file << is.getAllClientsObj()[k].getID()<<","<<is.getAllClientsObj()[k].getNombre()<<","<<is.getAllClientsObj()[k].getIdentidad()
                                    <<","<<is.getAllClientsObj()[k].getFechaNacimiento()<<","<<is.getAllClientsObj()[k].Obtenerpin()<<","<<is.getAllClientsObj()[k].ObtenerfechaUltimaCompra()<<","<<is.getAllClientsObj()[k].Obtenernvisitas()<<"\n";
                                }
                                else{
                                    file << is.getAllClientsObj()[k].getID()<<","<<is.getAllClientsObj()[k].getNombre()<<","<<is.getAllClientsObj()[k].getIdentidad()
                                    <<","<<is.getAllClientsObj()[k].getFechaNacimiento()<<","<<is.getAllClientsObj()[k].Obtenerpin()<<","<<is.getAllClientsObj()[k].ObtenerfechaUltimaCompra()<<","<<is.getAllClientsObj()[k].Obtenernvisitas();
                                }
                                k++;
                            }

                            }
                        cout<<"*****Cliente editado con éxito"<<endl;
                        file.close();
                        system("pause");
                        system("cls");
                        }
                    else{
                        cout<<"***Error: Cliente no encontrado"<<endl;
                    }
                    break;
                    }
                case 2:
                    {
                        char yesnt;
                        cout<<"Ingrese ID de cliente a eliminar: ";
                        cin>>j;
                        j=vt.getClientPos(j);
                        if(j!=-1){
                        cout<<"Está seguro de eliminar Cliente "<<is.getAllClientsObj()[j].getNombre()<<"?, [ si:S ,n:N ]: ";
                        cin>>yesnt;
                            if(tolower(yesnt)=='s'){
                                ofstream file;
                                file.open(this -> path  + "/BD/clientes.txt");
                                int ii = 0;
                                while(ii<aSize){
                                     if(is.getAllClientsObj()[ii].getNombre()!=""&&ii!=j){
                                            if(aSize-ii>1){
                                                file << is.getAllClientsObj()[ii].getID()<<","<<is.getAllClientsObj()[ii].getNombre()<<","<<is.getAllClientsObj()[ii].getIdentidad()
                                                    <<","<<is.getAllClientsObj()[ii].getFechaNacimiento()<<","<<is.getAllClientsObj()[ii].Obtenerpin()<<","<<is.getAllClientsObj()[ii].ObtenerfechaUltimaCompra()<<","<<is.getAllClientsObj()[ii].Obtenernvisitas()<<"\n";
                                            }
                                            else{
                                                 file << is.getAllClientsObj()[ii].getID()<<","<<is.getAllClientsObj()[ii].getNombre()<<","<<is.getAllClientsObj()[ii].getIdentidad()
                                                    <<","<<is.getAllClientsObj()[ii].getFechaNacimiento()<<","<<is.getAllClientsObj()[ii].Obtenerpin()<<","<<is.getAllClientsObj()[ii].ObtenerfechaUltimaCompra()<<","<<is.getAllClientsObj()[ii].Obtenernvisitas();
                                            }
                                        }
                                    ii++;
                                }
                                cout<<"Cliente Eliminado con éxito"<<endl;
                                file.close();
                                system("pause");
                                system("cls");
                            }
                        }
                        else{
                            cout<<"*****Error: cliente no encontrado"<<endl;
                        }

                    break;
                    }
                case 3:{
                    system("cls");
                    break;
                    }
                default:
                    cout<<"Opción no válida...."<<endl;
                }
        }while(index!=3);
        }

    Cliente editarClient(Cliente clt){
        system("cls");
        cin.ignore();
        string nombre, identidad, fechaNacimiento;
        int index=0;
        Validations vt;
        cout<<"\t__==Gasolinera CEUTEC==__\n\t     Editar cliente"<<endl;
        cout<<"1)Nombre\n2)Identidad\n3)Fecha Nacimiento\n4)Regresar\nIngrese opción: ";
        cin>>index;
        cin.ignore();
        switch(index){
            case 1:
                cout<<"Ingrese nombre a editar: ";
                getline(cin,nombre);
                        if(vt.validateTextField(nombre)){
                            clt.setNombre(nombre);
                        }else{
                            cout<<"***Error, debe de ingresar el nombre"<<endl;
                        }
                break;
            case 2:
                cout<<"Ingrese número de identidad(sin guiones): ";
                        getline(cin,identidad);
                        if(vt.validateTextField(identidad)/*&&strlen(identidad)==13*/){
                            clt.setIdentidad(identidad);
                        }
                        else{
                            cout<<"****Error: La identidad debe ser al menos de 13 carácteres"<<endl;
                        }
                break;
            case 3:
                cout<<"Ingrese fecha de nacimiento(ejemplo: 12/12/2002): ";
                        getline(cin,fechaNacimiento);
                        if(vt.validateTextField(fechaNacimiento)){
                            clt.setFechaNacimiento(fechaNacimiento);
                        }
                        else{
                            cout<<"****Error: La fecha de nacimiento no puede quedar vacía"<<endl;
                        }
                        break;
                break;
            case 4:
                system("cls");
                break;
            default:
                cout<<"No es una opción..."<<endl;
        }
        return clt;
    }
//FIN DE CLIENTES======================================================================================================================================================
//INICIO DE PRODUCTOS======================================================================================================================================================

void nuevoProducto(){
    string nombre,tipo, cadena;
    int i = 1;
    int id=0;
    int stock;
    float precio;
    cout<<"\t__==Gasolinera CEUTEC==__\n\t     Añadir nuevo producto"<<endl;
    Validations vt;
    IOS is(ut.ExePath());
    ifstream fe(this -> path + "/BD/productos.txt");
    while (!fe.eof()) {
        getline(fe,cadena);
        id = stoi(ut.tokenizer(cadena,",",1));
    }
    cin.ignore();
    while(i<=4)
    {
        switch(i)
        {
        case 1:
            cout<<"Ingrese nombre: ";
            getline(cin,nombre);
            if(vt.validateTextField(nombre))
            {
                i++;
            }
            else
            {
                cout<<"***Error, debe ingresar el nombre"<<endl;
            }
            break;
        case 2:
            cout<<"Ingrese el tipo de producto: ";
            getline(cin,tipo);
            if(vt.validateTextField(tipo))
            {
                i++;
            }
            else
            {
                cout<<"***Error, debe ingresar el tipo de producto"<<endl;
            }
            break;
        case 3:
            cout<<"Ingrese la cantidad de producto: ";
            cin>>stock;
            if(vt.validateNumberField(stock))
            {
                i++;
            }
            else
            {
                cout<<"***Error, debe ingresar la cantidad de producto"<<endl;
            }
            break;
        case 4:
            cout<<"Ingrese precio unitario del producto: ";
            cin>>precio;
            if(vt.validateNumberField(precio))
            {
                i++;
            }
            else
            {
                cout<<"***Error, debe ingresar el precio del producto"<<endl;
            }
            break;
        default:
                cout<<"Opción no válida...."<<endl;
                break;

        }
    }

    ofstream file;
    file.open(this -> path  + "/BD/productos.txt", ios::app);
    file<<"\n"<<(id+1)<<","<<nombre<<","<<tipo<<","<<stock<<","<<precio;
    file.close();
    cout<<"*****producto creado con éxito"<<endl;
    cout<<"El ID del nuevo producto es: "<<( id + 1 )<<endl;
    system("pause");
    system("cls");
}

void listProductos(){
        system("cls");
        IOS is(ut.ExePath());
        Validations vt;
        int index=0,j, aSize=0;
        cout<<"\t__==Gasolinera CEUTEC==__\n\t     lista de clientes"<<endl;
        cout<<"====================================================================================================================="<<endl;
        cout<<"||\tID\t||\tNombre\t||\tTipo\t||\t Cantidad \t ||\tPrecio unitario(Lps)\t||"<<endl;
        cout<<"====================================================================================================================="<<endl;
        is.leerTodosLosProductos();
        for(int i=0;i<1000;i++){
                if(is.getAllProducts()[i].getNombre()!=""){
                    cout <<"||\t"<< is.getAllProducts()[i].getId()<<"\t||\t"<<is.getAllProducts()[i].getNombre()<<"\t||\t"<<is.getAllProducts()[i].getTipo()<<"\t||\t";
                    cout<<is.getAllProducts()[i].getStock()<<"\t||\t"<<is.getAllProducts()[i].getPrecioUnitario()<<"\t||"<<endl;
                    aSize++;
                }

            }
        cout<<"====================================================================================================================="<<endl;
        do{
            cout<<"1)Editar producto\n2)Dar de baja\n3)Regresar\nIngrese opción: ";
            cin>>index;
            switch(index){
                case 1:
                    {
                    cout<<"Ingrese ID de producto a editar: ";
                    cin>>j;
                    j= vt.getProductPos(j);
                    if(j!=-1){
                        is.getAllProducts()[j] = this ->editarProducto(is.getAllProducts()[j]);
                        ofstream file;
                        file.open(this -> path  + "/BD/productos.txt");
                        int k = 0;
                        while(k<aSize){
                         if(is.getAllProducts()[k].getNombre()!=""){

                                if(aSize-k>1){
                                    file << is.getAllProducts()[k].getId()<<","<<is.getAllProducts()[k].getNombre()<<","<<is.getAllProducts()[k].getTipo()
                                    <<","<<is.getAllProducts()[k].getStock()<<","<<is.getAllProducts()[k].getPrecioUnitario()<<"\n";
                                }
                                else{
                                    file << is.getAllProducts()[k].getId()<<","<<is.getAllProducts()[k].getNombre()<<","<<is.getAllProducts()[k].getTipo()
                                    <<","<<is.getAllProducts()[k].getStock()<<","<<is.getAllProducts()[k].getPrecioUnitario();
                                }
                                k++;
                            }
                        }
                        cout<<"*****Producto editado con éxito"<<endl;
                        file.close();
                        system("pause");
                        system("cls");
                    }
                    else{
                        cout<<"***Error: producto no encontrado"<<endl;
                    }

                    break;
                    }
                case 2:
                    {
                        char yesnt;
                        cout<<"Ingrese ID del producto a eliminar: ";
                        cin>>j;
                         j= vt.getProductPos(j);
                        if(j!=-1){
                        cout<<"Está seguro de eliminar producto "<<is.getAllProducts()[j].getNombre()<<"?, [ si:S ,n:N ]: ";
                        cin>>yesnt;
                            if(tolower(yesnt)=='s'){
                                ofstream file;
                                file.open(this -> path  + "/BD/productos.txt");
                                int ii = 0;
                                while(ii<aSize){
                                     if(is.getAllProducts()[ii].getNombre()!=""&&ii!=j){
                                            if(aSize-ii>1){
                                                file << is.getAllProducts()[ii].getId()<<","<<is.getAllProducts()[ii].getNombre()<<","<<is.getAllProducts()[ii].getTipo()
                                                        <<","<<is.getAllProducts()[ii].getStock()<<","<<is.getAllProducts()[ii].getPrecioUnitario()<<"\n";
                                            }
                                            else{
                                                 file << is.getAllProducts()[ii].getId()<<","<<is.getAllProducts()[ii].getNombre()<<","<<is.getAllProducts()[ii].getTipo()
                                                        <<","<<is.getAllProducts()[ii].getStock()<<","<<is.getAllProducts()[ii].getPrecioUnitario();
                                            }
                                        }
                                    ii++;
                                }
                                cout<<"Producto Eliminado con éxito"<<endl;
                                file.close();
                                system("pause");
                                system("cls");
                            }

                    }
                    else{
                        cout<<"***Error: Producto no encontrado"<<endl;
                    }
                    break;
                    }
                case 3:{
                    system("cls");
                    break;
                    }
                default:
                    cout<<"Opción no válida...."<<endl;
                }
        }while(index!=3);
        }

Producto editarProducto(Producto prod){
    system("cls");
        cin.ignore();
        string nombre, tipo;
        int stock,index=0;
        float precioUnitario;
        Validations vt;
        cout<<"\t__==Gasolinera CEUTEC==__\n\t     Editar producto"<<endl;
        cout<<"1)Nombre\n2)Tipo\n3)Stock\n4)Precio Unitario\n5)Regresar\nIngrese opción: ";
        cin>>index;
        cin.ignore();
        switch(index){
            case 1:
                cout<<"Ingrese nombre a editar: ";
                getline(cin,nombre);
                        if(vt.validateTextField(nombre)){
                            prod.setNombre(nombre);
                        }else{
                            cout<<"***Error, debe de ingresar el nombre"<<endl;
                        }
                break;
            case 2:
                cout<<"Ingrese Tipo de producto: ";
                        getline(cin,tipo);
                        if(vt.validateTextField(tipo)/*&&strlen(identidad)==13*/){
                            prod.setTipo(tipo);
                        }
                        else{
                            cout<<"****Error: El tipo es obligatorio"<<endl;
                        }
                break;
            case 3:
                cout<<"Ingrese la cantidad en stock: ";
                        cin>>stock;
                        if(vt.validateNumberField(stock)){
                            prod.setStock(stock);
                        }
                        else{
                            cout<<"****Error: El stock debe ser mayor a cero"<<endl;
                        }
                        break;
                break;
            case 4:
                cout<<"Ingrese nuevo precio unitario: ";
                        cin>>precioUnitario;
                        if(vt.validateNumberField(precioUnitario)){
                            prod.setPrecioUnitario(precioUnitario);
                        }else{
                            cout<<"****Error: El precio unitario debe ser mayor a cero"<<endl;
                        }
                break;
            case 5:
                system("cls");
                break;
            default:
                cout<<"No es una opción..."<<endl;
        }
        return prod;
}


bool productLess(int id, int qty){
    Validations vt;
    int j;
    IOS is(this->ut.ExePath());
    is.leerTodosLosProductos();
    int aSize = vt.getProductZise();
    if(vt.productMTZ(id,qty)){
       j= vt.getProductPos(id);
       if(j!=-1){
                        is.getAllProducts()[j].setStock((is.getAllProducts()[j].getStock() - qty));
                        ofstream file;
                        file.open(this -> path  + "/BD/productos.txt");
                        int k = 0;
                        while(k<aSize){
                         if(is.getAllProducts()[k].getNombre()!=""){
                                if(aSize-k>1){
                                    file << is.getAllProducts()[k].getId()<<","<<is.getAllProducts()[k].getNombre()<<","<<is.getAllProducts()[k].getTipo()
                                    <<","<<is.getAllProducts()[k].getStock()<<","<<is.getAllProducts()[k].getPrecioUnitario()<<"\n";
                                }
                                else{
                                    file << is.getAllProducts()[k].getId()<<","<<is.getAllProducts()[k].getNombre()<<","<<is.getAllProducts()[k].getTipo()
                                    <<","<<is.getAllProducts()[k].getStock()<<","<<is.getAllProducts()[k].getPrecioUnitario();
                                }
                                k++;
                            }
                        }
                        file.close();
        }

    }else{
        cout<<"****Error: No hay suficiente en stock...."<<endl;
        return false;
    }
    return true;
}

//FIN DE PRODUCTOS======================================================================================================================================================

};

#endif // CRUD_H_INCLUDED
