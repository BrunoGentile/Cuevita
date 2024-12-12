#ifndef CLASECLIENTE_H_INCLUDED
#define CLASECLIENTE_H_INCLUDED

class Cliente:public Persona{
private:
    int _IDCliente;
    float _Credito;
    bool _Tarjeta;

public:

    /// SETTER

    void setIDCliente(int ID){ _IDCliente = ID; }
    void set_Credito( float C ){ _Credito = C; }
    void set_Tarjeta( bool T ){ _Tarjeta = T; }

    /// GETTER

    int getIDCliente(){ return _IDCliente; }
    float getCredito(){ return _Credito; }
    bool getTarjeta(){ return _Tarjeta; }

    /// MÉTODOS

    void Cargar();
    void Mostrar(){

        if( _Tarjeta ){
            cout<<"ID CLIENTE: "<<_IDCliente<<endl;
            cout<<"CREDITO: "<<_Credito<<endl;
            Persona::Mostrar();
        }

    }

};

/// ------------------------------------------ [ MÉTODOS DE LA CLASE ] ------------------------------------------

void Cliente::Cargar(){

    FILE *pClientes = fopen("Clientes.dat","ab+");

    if( pClientes == NULL ){
        exit(1);
    }

    fseek(pClientes,0,2);
    int Registros = ftell(pClientes) / sizeof(Cliente);

    fclose(pClientes);
    _IDCliente = Registros + 1;

    Persona::Cargar();
    cout <<"Ingrese el credito a cargar: "; cin>>_Credito;



    _Tarjeta = true;
    cout<<"[+] TARJETA ACTIVADA";
}

#endif // CLASECLIENTE_H_INCLUDED
