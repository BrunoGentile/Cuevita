#ifndef CLASEVENDEDORARCHI_H_INCLUDED
#define CLASEVENDEDORARCHI_H_INCLUDED

class VendedorArchi{
private:
    char _Nombre[50];

public:

    /// CONSTRUCTOR

    VendedorArchi(const char *N = "Vendedor.dat" ){ strcpy(_Nombre,N); }

    /// MÉTODOS

    bool VerificarContrasenia(int C);
    void MostrarDatosPropietario();
    void ModificarClave(int Clave);

};

/// ------------------------------------------ [ MÉTODOS DE LA CLASE ] ------------------------------------------

/// ---------------- > VERIFICAR CONTRASENIA

bool VendedorArchi::VerificarContrasenia(int C){

    bool Comprobar = false;

    Vendedor Duenio;

    FILE *pArchivo = fopen(_Nombre,"rb");

    if( pArchivo == NULL ){
        exit(1);
    }

    fread(&Duenio,sizeof(Vendedor),1,pArchivo);

    if( Duenio.get_Contrasenia() == C ){
        Comprobar = true;
    }

    fclose(pArchivo);
    return Comprobar;

}

/// ---------------- > MOSTRAR LOS DATOS DEL PROPIETARIO

void VendedorArchi::MostrarDatosPropietario(){

    Vendedor Duenio;

    FILE *pArchivo = fopen(_Nombre,"rb");

    if( pArchivo == NULL ){
        exit(1);
    }

    fread(&Duenio,sizeof(Vendedor),1,pArchivo);

    Duenio.Mostrar();

    fclose(pArchivo);

}

/// ---------------- > MODIFICAR CLAVE

void VendedorArchi::ModificarClave(int Clave){

    Vendedor Duenio;

    FILE *pArchivo = fopen(_Nombre,"rb+");

    if( pArchivo == NULL ){
        exit(1);
    }

    fseek(pArchivo,0,0);
    fread(&Duenio,sizeof(Vendedor),1,pArchivo);

    Duenio.set_Contrasenia(Clave);

    fseek(pArchivo,0,0);

    if( fwrite(&Duenio,sizeof(Vendedor),1,pArchivo) == 1 ){
        cout<<"[+] CLAVE MODIFICADA"<<endl;
    }else{
        cout<<"[+] NO SE PUDO MODIFICAR LA CLAVE"<<endl;
    }

    fclose(pArchivo);

}

#endif // CLASEVENDEDORARCHI_H_INCLUDED
