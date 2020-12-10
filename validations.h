#ifndef VALIDATIONS_H_INCLUDED
#define VALIDATIONS_H_INCLUDED

#include "utilities.h"
#include "ios.h"

class Validations{

    private:

    public:
        Validations(){}
        bool validateUsrPinFormt(int pin){
            bool val = false;
            if(pin > 999 && pin <10000){
                val = true;
            }
            else{
                val = false;
            }
            return val;
        }
        bool validateClntPinFormt(int pin){
            bool val = false;
            if(pin > 99999 && pin <1000000){
                val = true;
            }
            else{
                val = false;
            }
            return val;
        }
        bool validateTextField(string valor){
            if(valor!=""){
                return true;
            }
            return false;
        }
        bool validateNumberField(float valor){
            if(valor>0){
                return true;
            }
            return false;
        }
        bool isUserExists(int pin){
            int acum=0;
            Utilities ut;
            IOS is(ut.ExePath());
            is.leerTodosUsuarios();
            for(int i=0;i<1000;i++){
                if(is.getAllUsrsObj()[i].getNombre()==""){
                    break;
                }else{
                    if(is.getAllUsrsObj()[i].getPin()==pin){
                        acum++;
                    }
                }
            }
            if(acum>0){
                return true;
            }
            return false;
        }

        bool isClientExists(int pin){
            int acum=0;
            Utilities ut;
            IOS is(ut.ExePath());
            is.leerTodosClientes();
            for(int i=0;i<10000;i++){
                if(is.getAllClientsObj()[i].Obtenerpin()==0){
                    break;
                }else{
                    if(is.getAllClientsObj()[i].Obtenerpin()==pin){
                        acum++;
                    }
                }
            }
            if(acum>0){
                return true;
            }
            return false;
        }

        bool isProductExists(int id){
            int acum = 0;
            Utilities ut;
            IOS is(ut.ExePath());
            is.leerTodosLosProductos();
            for(int i=0;i<1000;i++){
                if(is.getAllProducts()[i].getPrecioUnitario()==0){
                    break;
                }else{
                    if(is.getAllProducts()[i].getId()==id){
                        acum++;
                    }
                }
            }
            if(acum>0){
                return true;
            }
            return false;
        }

        int getProductZise(){
        int acum = 0;
            Utilities ut;
            IOS is(ut.ExePath());
            is.leerTodosLosProductos();
            for(int i=0;i<1000;i++){
                if(is.getAllProducts()[i].getNombre()==""){
                    break;
                }else{
                        acum++;
                }
            }
            return acum;
        }

        void updateLastLogin(int pin){
            int acum = 0;
            Utilities ut;
            IOS is(ut.ExePath());
            is.leerTodosUsuarios();
            for(int i=0;i<1000;i++){
                if(is.getAllUsrsObj()[i].getNombre()==""){
                    break;
                }else{
                    acum++;
                    if(is.getAllUsrsObj()[i].getPin()==pin){
                          is.getAllUsrsObj()[i].setUltimoLogin(ut.getActualDate());
                        //cout<<is.getAllUsrsObj()[i].getUltimoLogin()<<endl;
                    }
                }
            }
            is.escribirUsuarios(acum);
        }

        void updateLastVisita(int pin){
            int acum = 0;
            Utilities ut;
            IOS is(ut.ExePath());
            is.leerTodosClientes();
            for(int i=0;i<1000;i++){
                if(is.getAllClientsObj()[i].getNombre()==""){
                    break;
                }else{
                    acum++;
                    if(is.getAllClientsObj()[i].Obtenerpin()==pin){
                          is.getAllClientsObj()[i].EstablecerfechaUltimaCompra(ut.getActualDate());
                          is.getAllClientsObj()[i].Establecernvisitas((is.getAllClientsObj()[i].Obtenernvisitas() + 1));
                    }
                }
            }
            is.escribirClientes(acum);
        }

        int getUserPos(int id){
            int acum = 0;
            Utilities ut;
            IOS is(ut.ExePath());
            is.leerTodosUsuarios();
            for(int i=0;i<1000;i++){
                if(is.getAllUsrsObj()[i].getNombre()==""){
                    break;
                }else{
                    acum++;
                    if(is.getAllUsrsObj()[i].getID()==id){
                          return i;
                    }
                }
            }
            return -1;
        }

        int getClientPos(int id){
            Utilities ut;
            IOS is(ut.ExePath());
            is.leerTodosClientes();
            for(int i=0;i<10000;i++){
                if(is.getAllClientsObj()[i].getNombre()==""){
                    break;
                }else{
                    if(is.getAllClientsObj()[i].getID()==id){
                        return i;
                    }
                }
            }
            return -1;
        }

        int getClientPosByPin(int pin){
            Utilities ut;
            IOS is(ut.ExePath());
            is.leerTodosClientes();
            for(int i=0;i<10000;i++){
                if(is.getAllClientsObj()[i].getNombre()==""){
                    break;
                }else{
                    if(is.getAllClientsObj()[i].Obtenerpin()==pin){
                        return i;
                    }
                }
            }
            return -1;
        }

        int getProductPos(int id){
            Utilities ut;
            IOS is(ut.ExePath());
            is.leerTodosLosProductos();
            for(int i=0;i<1000;i++){
                if(is.getAllProducts()[i].getNombre()==""){
                    break;
                }else{
                    if(is.getAllProducts()[i].getId()==id){
                        return i;
                    }
                }
            }
            return -1;
        }

        int getLastFactura(){
            int acum = 0;
            Utilities ut;
            IOS is(ut.ExePath());
            is.leerTodasLasFacturas();
            for(int i = 0; i<1000; i++){
                if(is.getAllFacturas()[i].getCajero()==""){
                    break;
                }else{
                    acum = i;
                }
            }

            return is.getAllFacturas()[acum].getID();
        }

        bool productMTZ(int id,int qt){
            Utilities ut;
            IOS is(ut.ExePath());
            is.leerTodosLosProductos();
            for(int i=0;i<1000;i++){
                if(is.getAllProducts()[i].getNombre()==""){
                    break;
                }else{
                    if(is.getAllProducts()[i].getId()==id){
                        if(((is.getAllProducts()[i].getStock()- qt) >=0)&&(qt>0)){
                            return true;
                        }
                    }
                }
            }
            return false;
        }


        ~Validations(){}

};

#endif // VALIDATIONS_H_INCLUDED
