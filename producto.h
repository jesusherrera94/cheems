#ifndef PRODUCTO_H_INCLUDED
#define PRODUCTO_H_INCLUDED



class Producto{
private:
    int ID;
    string nombre;
    string tipo;
    int stock;
    float precioUnitario;
public:
    Producto(){}
    Producto(int id, string nombre,string tipo, int stock, float precioUnitario){
        this -> ID = id;
        this -> nombre = nombre;
        this -> tipo = tipo;
        this -> stock = stock;
        this -> precioUnitario = precioUnitario;
    }
    void setId(int id){
        this -> ID = id;
    }
    void setNombre(string nombre){
        this -> nombre = nombre;
    }
    void setTipo(string tipo){
        this -> tipo = tipo;
    }
    void setStock(int stock){
        this -> stock = stock;
    }
    void setPrecioUnitario(float precio){
        this -> precioUnitario = precio;
    }

    int getId(){
        return this -> ID;
    }
    string getNombre(){
        return this -> nombre;
    }
    string getTipo(){
        return this -> tipo;
    }
    int getStock(){
        return this -> stock;
    }
    float getPrecioUnitario(){
        return this -> precioUnitario;
    }
};


#endif // PRODUCTO_H_INCLUDED
