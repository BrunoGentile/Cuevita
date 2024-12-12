#ifndef CLASEPERSONA_H_INCLUDED
#define CLASEPERSONA_H_INCLUDED

class Persona{
private:
    char _Nombre[20], _Apellido[20];
    int _DNI;
    char _Genero;
    Fecha _FechaNacimiento;
    char _Telefono[20];
    char _Direccion[20];
    char _Mail[30];
    bool _Estado;

public:

    /// SETTER

    void setNombre(const char *N){ strcpy(_Nombre,N); }

    void setApellido(const char *A){ strcpy(_Apellido,A); }

    void setDNI(int D){ _DNI = D; }
    void setGenero(char G){ _Genero = G; }
    void setFechaNacimiento(Fecha FN){ _FechaNacimiento = FN; }
    void setEstado( bool E ){ _Estado = E; }
    void setTelefono(const char *T) {strcpy(_Telefono,T);}
    void setDireccion (const char *D) {strcpy (_Direccion,D);}
    void setMail (const char *M) {strcpy(_Mail, M);}

    /// GETTER

    const char *getNombre(){ return _Nombre; }
    const char *getApellido(){ return _Apellido; }
    int getDNI(){ return _DNI; }
    char getGenero(){ return _Genero; }
    Fecha getFechaNacimiento(){ return _FechaNacimiento; }
    bool getEstado(){ return _Estado; }
    char *getTelefono() { return _Telefono; }
    char *getDireccion(){ return _Direccion; }
    char *getMail() { return _Mail;}

    /// MÉTODOS

    void Cargar();
    void Mostrar();

};

/// ------------------------------------------ [ MÉTODOS DE LA CLASE ] ------------------------------------------

void Persona::Cargar(){

    cout<<"NOMBRE: "; cin>>_Nombre;
    cout<<"APELLIDO: "; cin>>_Apellido;
    cout<<"DNI: "; cin>>_DNI;
    cout<<"GENERO (M/F/X): "; cin>>_Genero;

    cout<<"TELEFONO: "; CargarCadena(_Telefono,20);
    cout<<"DIRECCION: "; CargarCadena(_Direccion,20);
    cout<<"MAIL: "; cin>> _Mail;

    cout<<"FECHA DE NACIMIENTO: "<<endl;
    _FechaNacimiento.Cargar(); /// LLAMA AL MÉTODO CARGAR DEL OBJETO "_FechaNacimiento" CONSTRUIDO EN LA CLASE FECHA

    _Estado = true;

}

void Persona::Mostrar(){

    cout<<_Apellido<<", "<<_Nombre<<endl;
    cout<<"DNI: "<<_DNI<<endl;
    cout<<"GENERO: "<<_Genero<<endl;

    cout<<"FECHA DE NACIMIENTO: ";
    _FechaNacimiento.Mostrar(); /// LLAMA AL MÉTODO MOSTRAR DEL OBJETO "_FechaNacimiento" CONSTRUIDO EN LA CLASE FECHA

    cout<<"TELEFONO: "<<_Telefono<<endl;
    cout<<"DIRECCION: "<< _Direccion<<endl;
    cout<< "MAIL: "<<_Mail<<endl;

}

#endif // CLASEPERSONA_H_INCLUDED
