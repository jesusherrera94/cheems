#ifndef VALIDATIONS_H_INCLUDED
#define VALIDATIONS_H_INCLUDED

#define NULL 0
#include "utilities.h"
#include "ios.h"
class Validations{

    private:

    public:
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
                if(is.getAllUsrsObj()[i].getPin()==pin){
                    acum++;
                }
                if(is.getAllUsrsObj()[i].getPin()==NULL){
                    break;
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
                if(is.getAllProducts()[i].getPrecioUnitario()==NULL){
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
        //crear una funcion que valide si el cliente existe...

};



#endif // VALIDATIONS_H_INCLUDED
