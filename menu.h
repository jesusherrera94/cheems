#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "usuarios.h"
#include <iostream>
#include "utilities.h"
#include "crud.h"
#include "facturacion.h"
class Menu{
private:
    Usuarios sesion;
public:
        Menu(){}
        Menu(Usuarios sesion){
            this -> sesion = sesion;
        }
        void adminMainMenu(){
            int index = 0;
            system("cls");
            do{
                cout<<"\t__==Gasolinera CEUTEC==__\n\t     Administraci�n"<<endl;
                cout<<"1)Usuarios\n2)Clientes\n3)Inventario\n4)Facturaci�n\n5)Salir\nIngrese una opci�n: ";
                cin>>index;
                switch(index){
                    case 1:
                        this -> menuUsuarios();
                        break;
                    case 2:
                        this ->menuClientes();
                        break;
                    case 3:
                        this ->menuInventario();
                        break;
                    case 4:
                        this -> menuFacturacion();
                        break;
                    case 5:
                        cout<<"Saliendo del sistema..."<<endl;
                        break;
                    default:
                        cout<<"***Error: Opci�n no v�lida..."<<endl;
                        break;
                }

            }while(index!=5);
        }
        void bomberoMainMenu(){
            int index = 0;
            system("cls");
            do{
                cout<<"\t__==Gasolinera CEUTEC==__\n\t     Bombero/Cajero"<<endl;
                cout<<"1)Clientes\n2)Facturar\n3)Salir\nIngrese una opci�n: ";
                cin>>index;
                switch(index){
                    case 1:
                        this -> menuClientes();
                        break;
                    case 2:
                        this ->menuFacturacion();
                        break;
                    case 3:
                        cout<<"Saliendo del sistema..."<<endl;
                        break;
                    default:
                        cout<<"***Error: Opci�n no v�lida"<<endl;
                        break;
                }
            }while(index!=3);
        }

        void menuUsuarios(){
            system("cls");
            int index = 0;
            CRUD cr;
            do{
                cout<<"\t__==Gasolinera CEUTEC==__\n\t     Men� de Gesti�n Usuarios"<<endl;
                cout<<"1)Listar Usuarios\n2)A�adir Usuario\n3)Regresar\nIngrese una opci�n: "<<endl;
                cin>>index;
                switch(index){
                    case 1:
                        cr.listUsers(sesion);
                        break;
                    case 2:
                        cr.nuevoUsuario();
                        break;
                    case 3:
                        system("cls");
                        break;
                    default:
                        cout<<"***Error: Opci�n no v�lida"<<endl;
                }
            }while(index!=3);

        }

        void menuClientes(){
            system("cls");
            int index = 0;
            CRUD cr;
            switch(this->sesion.getTipo()){
                case 1:
                    do{
                        cout<<"\t__==Gasolinera CEUTEC==__\n\t     Men� de gesti�n clientes"<<endl;
                        cout<<"1)Listar clientes\n2)A�adir cliente\n3)Regresar\nIngrese una opci�n: "<<endl;
                        cin>>index;
                        switch(index){
                                case 1:
                                    cr.listClients();
                                    break;
                                case 2:
                                    cr.nuevoCliente();
                                    break;
                                case 3:
                                    system("cls");
                                    break;
                                default:
                                    cout<<"*****Error: Opci�n no v�lida"<<endl;
                        }
                    }while(index!=3);
                    break;
                case 2:
                    do{
                        cout<<"\t__==Gasolinera CEUTEC==__\n\t     Men� de Gesti�n clientes"<<endl;
                        cout<<"1)A�adir cliente\n2)Regresar\nIngrese una opci�n: "<<endl;
                        cin>>index;
                        switch(index){
                        case 1:
                            cr.nuevoCliente();
                            break;
                        case 2:
                            system("cls");
                            break;
                        default:
                            cout<<"***Error: Opci�n no v�lida"<<endl;
                        }
                    }while(index!=2);
                    break;
                default:
                    cout<<"***Error al identificar el usuario"<<endl;
            }
        }

        void menuInventario(){
            system("cls");
            int index = 0;
            CRUD cr;
            do{
                cout<<"\t__==Gasolinera CEUTEC==__\n\t     Men� de Gesti�n de Inventario"<<endl;
                cout<<"1)Listar inventario\n2)A�adir producto\n3)Regresar\nIngrese una opci�n: ";
                cin>>index;
                switch(index){
                    case 1:
                        cr.listProductos();
                        break;
                    case 2:
                        cr.nuevoProducto();
                        break;
                    case 3:
                        system("cls");
                        break;
                    default:
                        cout<<"***Error: Opci�n no v�lida"<<endl;
                }

            }while(index!=3);
        }
        void menuFacturacion(){
            system("cls");
            int index = 0;
            Facturacion fc;
            switch(this->sesion.getTipo()){
                case 1:
                    do{
                        cout<<"\t__==Gasolinera CEUTEC==__\n\t     Men� de Facturaci�n"<<endl;
                        cout<<"1)Facturar Producto\n2)Ver Ventas de hoy\n3)Ver sus ventas de hoy\n4)Ver total de ventas\n5)Regresar\nIngrese una opci�n: "<<endl;
                        cin>>index;
                        switch(index){
                        case 1:
                            fc.facturarProducto(this->sesion.getNombre(),this->sesion.getPin());
                            break;
                        case 2:
                            fc.ventasDiarias();
                            break;
                        case 3:
                            fc.ventasDiariasXUsuario(this->sesion.getPin());
                            break;
                        case 4:
                            fc.ventasTotales();
                            break;
                        case 5:
                            system("cls");
                            break;
                        default:
                            cout<<"***Error: Opci�n no v�lida"<<endl;
                        }
                    }while(index!=5);
                    break;
                case 2:
                    do{
                        cout<<"\t__==Gasolinera CEUTEC==__\n\t     Men� de Facturaci�n"<<endl;
                        cout<<"1)Facturar Producto\n2)Ver sus ventas de hoy\n3)Regresar\nIngrese una opci�n: "<<endl;
                        cin>>index;
                        switch(index){
                            case 1:
                                fc.facturarProducto(this->sesion.getNombre(),this->sesion.getPin());
                                break;
                            case 2:
                                fc.ventasDiariasXUsuario(this->sesion.getPin());
                                break;
                            case 3:
                                system("cls");
                                break;
                            default:
                                cout<<"***Error: Opci�n no v�lida"<<endl;
                        }
                    }while(index!=3);
                    break;
                default:
                    cout<<"Error al identificar el usuario"<<endl;
            }
        }


        ~Menu(){}
};


#endif // MENU_H_INCLUDED
