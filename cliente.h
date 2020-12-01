#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include "comprascliente.h"


class Cliente
{
private:
    int pin;
    comprasreciente compras_cliente[1000];
    string fechaUltimaCompra;
    int nvisitas;
public:
void Establecerpin(int _pin)
{
    pin = _pin;
}

void EstablecerfechaUltimaCompra(string _fechaUltimaCompra)
{
   fechaUltimaCompra = _fechaUltimaCompra;
}

void Establecernvisitas(int _nvisitas)
{
    nvisitas = _nvisitas;
}

int Obtenerpin()
{
    return pin;
}

string ObtenerfechaUltimaCompra()
{
    return fechaUltimaCompra;
}

int Obtenernvisitas()
{
    return nvisitas;
}

};

#endif // CLIENTE_H_INCLUDED
