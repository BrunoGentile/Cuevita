#ifndef CLASEVENDEDOR_H_INCLUDED
#define CLASEVENDEDOR_H_INCLUDED

class Vendedor:public Persona{
private:
    int _Contrasenia;

public:

    /// SETTER

    void set_Contrasenia( int C ){ _Contrasenia = C; }

    /// GETTER

    int get_Contrasenia(){ return _Contrasenia; }

    /// MÉTODOS

    void Cargar();
    void Mostrar();

};

/// ------------------------------------------ [ MÉTODOS DE LA CLASE ] ------------------------------------------

void Vendedor::Cargar(){

    int C;

    Persona::Cargar();

    cout<<"INGRESE LA CLAVE: "; cin>>C; set_Contrasenia(C);

}

void Vendedor::Mostrar(){

    Persona::Mostrar();

    cout<<"CLAVE: "<<get_Contrasenia()<<endl;
    cout<<endl;

}

#endif // CLASEVENDEDOR_H_INCLUDED
