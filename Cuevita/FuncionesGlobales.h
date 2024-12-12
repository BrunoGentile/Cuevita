#ifndef FUNCIONESGLOBALES_H_INCLUDED
#define FUNCIONESGLOBALES_H_INCLUDED

void CargarCadena(char *pal, int tam){

    int i;
    fflush(stdin);

    for(i=0;i<tam;i++){
        pal[i]=cin.get();
        if(pal[i]=='\n') break;
    }

    pal[i]='\0';
    fflush(stdin);
}

/// ----------- INCIALIZAR EN 0 VECTOR TIPO ENTERO

void InicializarCero(int *V,int Cant){

    for(int i = 0; i<Cant; i++){
        V[i] = 0;
    }

}

/// ----------- REESTABLECER ARCHIVOS

void RestablecerArchivo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "wb");
    if (archivo != nullptr) {
        fclose(archivo);
        cout << "[+] ARCHIVO " << nombreArchivo << " RESTABLECIDO CON EXITO." << endl;
    } else {
        cout << "[!] NO SE PUDO ABRIR EL ARCHIVO " << nombreArchivo << " PARA RESTABLECER." << endl;
    }
}

/// Función para restablecer todos los archivos
void RestablecerTodo() {
    RestablecerArchivo("Clientes.dat");
    RestablecerArchivo("Peliculas.dat");
    RestablecerArchivo("Ventas.dat");
}

#endif // FUNCIONESGLOBALES_H_INCLUDED
