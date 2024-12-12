#ifndef CLASEVENTAS_H_INCLUDED
#define CLASEVENTAS_H_INCLUDED

class Venta{
private:
    int _IDVenta;
    int _IDCliente;
    int _IDPelicula;
    int _Cantidad;
    float _Precio;
    Fecha _FechaCompra;
    bool Estado;

public:

    /// SETTER

    void setIDVenta(int IDV){ _IDVenta = IDV; }
    void setIDCliente(int IDC){ _IDCliente = IDC; }
    void setIDPelicula(int IDP){ _IDPelicula = IDP; }
    void setCantidad(int C){ _Cantidad = C; }
    void setPrecio(float P){ _Precio = P; }
    void setFechaCompra(Fecha FC){ _FechaCompra = FC; }
    void setEstado(bool E){ Estado = E; }

    /// GETTER

    int getIDVenta(){ return _IDVenta; }
    char getIDCliente(){ return _IDCliente; }
    int getIDPelicula(){ return _IDPelicula; }
    int getCantidad(){ return _Cantidad; }
    float getPrecio(){ return _Precio; }
    Fecha getFechaCompra(){ return _FechaCompra; }
    bool getEstado(){ return Estado; }

    /// MÉTODOS

    bool Cargar(int IDC, float Saldo, int IDP, float Precio, int Cant);
    void Mostrar();

};

/// ------------------------------------------ [ MÉTODOS DE LA CLASE ] ------------------------------------------

/// --------------- > CARGAR

bool Venta::Cargar(int IDC, float Saldo, int IDP, float Precio, int Cant){ ///

    bool Cargo = false;

    if( Saldo >= (Precio * Cant) ){

        /// ASIGNACIÓN DE ID

        FILE *pVentas = fopen("Ventas.dat", "ab+");

        if(pVentas == NULL){
            exit(1);
        }

        fseek(pVentas,0,2);
        int Registros = ftell(pVentas) / sizeof(Venta);

        fclose(pVentas);
        _IDVenta = Registros + 1;

        /// ASIGNACIÓN DE ID CLIENTE, PELICULA Y PRECIO

        _IDCliente = IDC;
        _IDPelicula = IDP;
        _Cantidad = Cant;
        _Precio = Precio*Cant;

        cout<<"INGRESE LA FECHA DE COMPRA: "; _FechaCompra.Cargar();

        Cargo = true;
        Estado = true;
    }else{
        cout<<"[+] EL CLIENTE NO CUENTA CON EL SALDO SUFICIENTE PARA REALIZAR LA COMPRA "<<endl;
    }

    return Cargo;
}

/// --------------- > MOSTRAR

void Venta::Mostrar(){

    if(Estado){
        cout<<"ID: "<<_IDVenta<<endl;
        cout<<"ID CLIENTE: "<<_IDCliente<<endl;
        cout<<"ID PELICULA: "<<_IDPelicula<<endl;
        cout<<"CANTIDAD: "<<_Cantidad<<endl;
        cout<<"PRECIO: "<<_Precio<<endl;
        cout<<"FECHA COMPRA: "; _FechaCompra.Mostrar();
    }

}

#endif // CLASEVENTAS_H_INCLUDED
