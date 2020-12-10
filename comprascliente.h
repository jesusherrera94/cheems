#ifndef COMPRASCLIENTE_H_INCLUDED
#define COMPRASCLIENTE_H_INCLUDED


class comprasreciente
{
private:
    int Id;
    string Nombreproducto;
    int cantidad;
    float costounitario;
    float subtotal;
public:
    void EstablecerId(int);
    void EstablecerCantidad(string);
    void EstablecerCostoUnitario(float);
    void EstablecerSubtotal(float);
    int ObtenerId();
    string ObtenerNombreproducto();
    int ObtenerCantidad();
    float ObtenerCostoUnitario();
    float ObtenerSubtotal();
};
void comprasreciente::EstablecerId(int _Id)
{
    Id = _Id;
}

void comprasreciente::EstablecerCantidad(string _Nombreproducto)
{
    Nombreproducto = _Nombreproducto;
}

void comprasreciente::EstablecerCostoUnitario(float _costounitario)
{
    costounitario = _costounitario;
}

void comprasreciente::EstablecerSubtotal(float _subtotal)
{
    subtotal = _subtotal;
}

int comprasreciente::ObtenerId()
{
    return Id;
}

string comprasreciente::ObtenerNombreproducto()
{
    return Nombreproducto;
}

int comprasreciente::ObtenerCantidad()
{
    return cantidad;
}

float comprasreciente::ObtenerCostoUnitario()
{
    return costounitario;
}

float comprasreciente::ObtenerSubtotal()
{
    return subtotal;
}

#endif // COMPRASCLIENTE_H_INCLUDED
