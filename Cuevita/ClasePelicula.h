#ifndef CLASEPELICULA_H_INCLUDED
#define CLASEPELICULA_H_INCLUDED

class Pelicula{
private:
    int _IdPelicula;
    char _Titulo[30];
    char _Genero [20];
    int _Stock;
    float _Precio;
    char _Descripcion [150];
    bool _Estado;

public:

    /// SETTER

    void setGenero(const char *G){ strcpy (_Genero,G); }
    void setStock(int S){ _Stock = S; }
    void setPrecio(float P){ _Precio = P; }
    void setDescripcion(const char *D){ strcpy (_Descripcion, D);}
    void setIdPelicula (int I) { _IdPelicula= I;}
    void setTitulo (const char *T) {strcpy (_Titulo, T);}
    void setEstado(bool E){ _Estado = E; }

    /// GETTER

    const char *getGenero(){ return _Genero; }
    int getStock(){ return _Stock; }
    float getPrecio(){ return _Precio; }
    const char *getDescripcion(){ return _Descripcion; }
    int getId() { return _IdPelicula;}
    const char *getTitulo() {return _Titulo;}
    bool getEstado(){ return _Estado; }

    /// MÉTODOS

    void Cargar();
    void Mostrar();

};

/// ------------------------------------------ [ MÉTODOS DE LA CLASE ] ------------------------------------------


void Pelicula::Cargar(){

    cout<<"GENERO: "; CargarCadena(_Genero,20);
    cout<<"STOCK: "; cin>>_Stock;
    cout<<"PRECIO: "; cin>>_Precio;
    cout<<"DESCRIPCION: "; CargarCadena(_Descripcion,150);
    cout<<"TITULO: "; CargarCadena(_Titulo,30);

    FILE *pPelicula = fopen("Peliculas.dat", "ab+");

    if(pPelicula == NULL){
        exit(1);
    }

    fseek(pPelicula,0,2);

    int Registros = ftell(pPelicula) / sizeof(Pelicula);

    fclose(pPelicula);
    _IdPelicula = Registros + 1;
    _Estado = true;
}

void Pelicula::Mostrar(){

    if( _Estado ){

        cout<<"ID: " << _IdPelicula<<endl;
        cout<<"GENERO: "<<_Genero<<endl;
        cout<<"STOCK: "<<_Stock<<endl;
        cout<<"PRECIO: "<<_Precio<<endl;
        cout<<"DESCRIPCION: "<<_Descripcion<<endl;
        cout<<"TITULO: "<< _Titulo;
    }

    cout<<endl;

}

#endif // CLASEPELICULA_H_INCLUDED
