#ifndef FACTURA_H_INCLUDED
#define FACTURA_H_INCLUDED

class Factura{
private:
    int id;
    string cajero;
    int pinCajero;
    string cliente;
    int pinCliente;
    string fecha;
    int numeroFactura;
    float total;
    int bombaCaja;
public:
    Factura(){};
    Factura(int id,string cajero, int pinCajero, string cliente, int pinCliente, string fecha, int numeroFactura, float total,int bombaCaja){
        this -> id = id;
        this ->cajero = cajero;
        this ->pinCajero = pinCajero;
        this ->cliente = cliente;
        this ->pinCliente = pinCliente;
        this ->fecha = fecha;
        this ->numeroFactura = numeroFactura;
        this -> total = total;
        this ->bombaCaja = bombaCaja;
    }
    //setters
    void setID(int id){
        this -> id = id;
    }
    void setCajero(string cajero){
        this ->cajero = cajero;
    }
    void setPinCajero(int pinCajero){
        this ->pinCajero = pinCajero;
    }
    void setCliente(string cliente){
        this ->cliente = cliente;
    }
    void setPinCliente(int pinCliente){
        this->pinCliente=pinCliente;
    }
    void setFecha(string fecha){
        this->fecha=fecha;
    }
    void setNumeroFactura(int numeroFactura){
        this->numeroFactura=numeroFactura;
    }
    void setTotal(float total){
        this->total=total;
    }
    void setBombaCaja(int bombaCaja){
        this->bombaCaja = bombaCaja;
    }
    //getters
    int getID(){
        return this -> id;
    }
    string getCajero(){
        return this ->cajero;
    }
    int getPinCajero(){
        return this ->pinCajero;
    }
    string getCliente(){
        return this ->cliente;
    }
    int getPinCliente(){
        return this->pinCliente;
    }
    string getFecha(){
        return this->fecha;
    }
    int getNumeroFactura(){
        return this->numeroFactura;
    }
    float getTotal(){
        return this->total;
    }
    int getBombaCaja(){
        return this->bombaCaja;
    }
    ~Factura(){}
};

#endif // FACTURA_H_INCLUDED
