#ifndef FACTURACION_H_INCLUDED
#define FACTURACION_H_INCLUDED

#include <iostream>
#include "validations.h"
#include "ios.h"
#include "utilities.h"
#include "crud.h"
#include <string>
#include "producto.h"
#include <fstream>
using namespace std;

class Facturacion{
private:
    string carrito[100][6];
public:
    Facturacion(){};
    void facturarProducto(string nombreCajero,int pinCajero){
        system("cls");
        int productID = 0;
        int cantidad = 0;
        float total = 0;
        int pinCliente = 0;
        int index = 0;
        bool clientFlag = true;
        int bombaCaja = 0;
        string nombreCliente;
        Validations vt;
        Utilities ut;
        IOS is(ut.ExePath());
        CRUD cr;
        string fechaFacturacion = ut.getActualDate();
        int facturaNo= vt.getLastFactura()+1;
        //leer el numero de factura
        cout<<"\t__==Gasolinera CEUTEC==__\n\t    Facturar Producto"<<endl;
        cout<<"Ingrese bomba/caja:";
        cin>>bombaCaja;
        cout<<"Cajero: "<<nombreCajero<<endl;
        //ingresar datos del cliente
        do{
            cout<<"Ingrese pin del cliente: ";
            cin>>pinCliente;
            if(vt.validateClntPinFormt(pinCliente)){
                if(vt.isClientExists(pinCliente)){
                    vt.updateLastVisita(pinCliente);
                    clientFlag = false;
                }else{
                    cout<<"Cliente no existe en base de datos"<<endl;
                    clientFlag = true;
                }
            }else{
                cout<<"Formato de pin de cliente invalido"<<endl;
                clientFlag = true;
            }

        }while(clientFlag);

        is.leerTodosClientes();
        nombreCliente = is.getAllClientsObj()[vt.getClientPosByPin(pinCliente)].getNombre();
        cout<<"Nombre de cliente: "<<nombreCliente<<endl;
        is.leerTodosLosProductos();
        do{
            cout<<"Ingrese id del producto, si desea terminar ingrese -1: ";
            cin>>productID;
            if(vt.isProductExists(productID)&&productID!=-1){
                    cout<<"Ingrese la cantidad de producto: ";
                    cin>>cantidad;
                    if(vt.validateNumberField(cantidad)){
                        //is.leerTodosLosProductos();
                        Producto pr = is.getAllProducts()[vt.getProductPos(productID)];
                        cout<<pr.getNombre()<<endl;
                        this -> carrito[index][0] = to_string(index + 1);
                        this -> carrito[index][1] = pr.getNombre();
                        this -> carrito[index][2] = to_string(pr.getPrecioUnitario());
                        this -> carrito[index][3] = to_string(cantidad);
                        this -> carrito[index][4] = to_string(pr.getPrecioUnitario() * cantidad);
                        if(cr.productLess(productID,cantidad)){
                            cout<<"Producto agregado al carrito"<<endl;
                            total += pr.getPrecioUnitario() * cantidad;
                            index++;
                        }
                    }
                    else{
                        cout<<"****Error: La cantidad no es un valor valido"<<endl;
                    }
                    //insertar producto en un arreglo nombre, cantidad y precio unitario

            }else{
                if(productID!=-1){
                    cout<<"Producto no existe"<<endl;
                }
            }
        }while(productID > -1);
        cout<<"====================================================================================================================="<<endl;
        cout<<"Factura No. "<<facturaNo<<endl;
        cout<<"Nombre de cliente: "<<nombreCliente<<endl;
        cout<<"Nombre del cajero: "<<nombreCajero<<endl;
        cout<<"Bomba o Caja: "<<bombaCaja<<endl;
        cout<<"Fecha: "<<fechaFacturacion<<endl;
        cout<<"====================================================================================================================="<<endl;
        cout<<"||\tID\t||\tNombre\t||\tPrecio unitario(Lps)\t||\t cantidad \t ||\tSub-Total(Lps)\t||"<<endl;
        cout<<"====================================================================================================================="<<endl;
        for(int i = 0; i<100; i++){
                if(carrito[i][1]==""){
                    break;
                }
                else{
                 cout<<"||\t"<<this ->carrito[i][0]<<"\t||\t"<<this ->carrito[i][1]<<"\t||\t"<<this ->carrito[i][2]<<"\t||\t"<<this ->carrito[i][3]<<"\t||\t"<<this ->carrito[i][4]<<"\t||"<<endl;
                }
        }
        cout<<"====================================================================================================================="<<endl;
        cout<<"Total a pagar: "<<total<<endl;

        //guardar factura a BD
        ofstream file;
        file.open(ut.ExePath() + "/BD/facturas.txt",ios::app);

        file <<"\n"<<facturaNo<<","<<nombreCajero<<","<<pinCajero<<","<<nombreCliente<<","<<pinCliente<<","<<fechaFacturacion<<","<<facturaNo<<","<<total<<","<<bombaCaja;
        file.close();
        cout<<"****Factura guardada****"<<endl;
        system("pause");
        for(int i = 0; i<100; i++){
                if(carrito[i][1]==""){
                    break;
                }
                else{
                    this -> carrito[i][0] = "";
                        this -> carrito[i][1] = "";
                        this -> carrito[i][2] = "";
                        this -> carrito[i][3] = "";
                        this -> carrito[i][4] = "";
                }
        }
        system("cls");

    }

    void ventasDiarias(){
        Utilities ut;
        IOS is(ut.ExePath());
        is.leerTodasLasFacturas();
        float totalVentasDiarias = 0;
        char respuesta;
        cout<<"\t__==Gasolinera CEUTEC==__\n\t    Reporte de Ventas diarias"<<endl;
        cout<<"====================================================================================================================="<<endl;
        cout<<"||\tFactura No. \t||\t Bomba o caja \t||\tFecha\t||\tTotal(Lps)\t||"<<endl;
        cout<<"====================================================================================================================="<<endl;
        for(int i=0;i<100;i++){
                if(is.getAllFacturas()[i].getCajero()==""){
                    break;
                }else{
                    if(is.getAllFacturas()[i].getFecha()==ut.getActualDate()){
                        cout<<"||\t"<<is.getAllFacturas()[i].getID()<<"\t||\t"<<is.getAllFacturas()[i].getBombaCaja()<<"\t||\t"<<is.getAllFacturas()[i].getFecha()<<
                            "\t||\t"<<is.getAllFacturas()[i].getTotal()<<"\t||"<<endl;
                            totalVentasDiarias += is.getAllFacturas()[i].getTotal();
                    }
                }
        }
        cout<<"====================================================================================================================="<<endl;
        cout<<"Total de ventas al dia: "<<totalVentasDiarias<<endl;
        cout<<"Desea guardar el reporte en la base de datos?[S:si, N:no]: ";
        cin>>respuesta;
        if(tolower(respuesta)=='s'){
            ofstream file;
            file.open(ut.ExePath() + "/BD/ventasDiarias.txt",ios::app);
            file<<"\n"<<ut.getActualDate()<<","<<totalVentasDiarias;
            file.close();
            cout<<"*****Reporte agregado con exito"<<endl;
        }
        system("pause");
        system("cls");
    }

    void ventasDiariasXUsuario(int pin){
        Utilities ut;
        IOS is(ut.ExePath());
        is.leerTodasLasFacturas();
        float totalVentasDiarias = 0;
        cout<<"\t__==Gasolinera CEUTEC==__\n\t    Reporte de Ventas diarias"<<endl;
        cout<<"====================================================================================================================="<<endl;
        cout<<"||\tFactura No. \t||\t Bomba o caja \t||\tFecha\t||\tTotal(Lps)\t||"<<endl;
        cout<<"====================================================================================================================="<<endl;
        for(int i=0;i<100;i++){
                if(is.getAllFacturas()[i].getCajero()==""){
                    break;
                }else{
                    if(is.getAllFacturas()[i].getFecha()==ut.getActualDate() && is.getAllFacturas()[i].getPinCajero()==pin){
                        cout<<"||\t"<<is.getAllFacturas()[i].getID()<<"\t||\t"<<is.getAllFacturas()[i].getBombaCaja()<<"\t||\t"<<is.getAllFacturas()[i].getFecha()<<
                            "\t||\t"<<is.getAllFacturas()[i].getTotal()<<"\t||"<<endl;
                            totalVentasDiarias += is.getAllFacturas()[i].getTotal();
                    }
                }
        }
        cout<<"====================================================================================================================="<<endl;
        cout<<"Total de ventas al dia: "<<totalVentasDiarias<<endl;
        system("pause");
        system("cls");
    }

    void ventasTotales(){
        string cadena,ventasTotales[100][2];
        Utilities ut;
        int index=0;
        cout<<"\t__==Gasolinera CEUTEC==__\n\t    Reporte de todas las ventas"<<endl;
        cout<<"====================================================================================================================="<<endl;
        cout<<"||\tFecha\t||\t Total diario \t||"<<endl;
        cout<<"====================================================================================================================="<<endl;
        ifstream fe(ut.ExePath() + "/BD/ventasDiarias.txt");
        while (!fe.eof()) {
            getline(fe,cadena);
             ventasTotales[index][0] = ut.tokenizer(cadena,",",1);
             ventasTotales[index][1] = ut.tokenizer(cadena,",",2);
             index++;
        }
        fe.close();
        for(int i=0;i<100;i++){
            if(ventasTotales[i][0]==""){
                break;
            }
            else{
                cout<<"||\t"<<ventasTotales[i][0]<<"\t||\t"<<ventasTotales[i][1]<<"\t||"<<endl;
            }
        }
        cout<<"====================================================================================================================="<<endl;
        system("pause");
        system("cls");
    }

    ~Facturacion(){};
};


#endif // FACTURACION_H_INCLUDED
