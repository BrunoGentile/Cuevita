#ifndef CLASEPELICULAARCHI_H_INCLUDED
#define CLASEPELICULAARCHI_H_INCLUDED

class PeliculaArchi{
private:
    char _Nombre[30];

public:

    /// CONSTRUCTOR

    PeliculaArchi(const char *N = "Peliculas.dat" ){ strcpy(_Nombre,N); }

    /// MÉTODOS

    bool Cargar(Pelicula obj);
    void Mostrar();
    void FiltrarPelicula(int ID);
    bool EliminarPelicula(int ID);


    int ObtenerTotalPeliculas(int IDP); /// STOCK
    float ObtenerPrecio(int ID);
    void ModificarTotal(int ID,int Cant);
    bool StockAgregar(int ID, int Cantidad);

    int ObtenerRegistros();

    void BackUp();
    void MostrarPeliculaConMasStock();

    void ReestablecerStock(int IDPelicula, int Stock);
    void MostrarNombreMasVendida(int IDMasVendida);
    void FiltrarPorGenero(const char *_genero);
    void MostrarPeliculasSinStock();
    void FiltrarPorTitulo(const char *_titulo);
    void FiltrarPorRango(int ID1, int ID2);
    bool ExisteID(int ID);
    void FiltrarPeliculaPorPrefijo(const char *prefijo);

};

/// ------------------------------------------ [ MÉTODOS DE LA CLASE ] ------------------------------------------

/// --------------- > CARGAR

bool PeliculaArchi::Cargar(Pelicula obj){

    FILE *pArchivo = fopen(_Nombre, "rb+");

    if (pArchivo == NULL){
        exit(1);
    }

    bool escribio, Bandera = true;/// 'escribio' indica si se escribió correctamente, 'Bandera' controla si se encuentra un registro disponible
    Pelicula Peli;

    if( ObtenerRegistros() == 1 ){ /// Si solo existe un registro en el archivo

        fseek(pArchivo,0,0);/// Mueve el puntero de archivo al inicio
        fread(&Peli,sizeof(Pelicula),1,pArchivo);/// Lee el único registro en el archivo y lo almacena en 'Peli'.

        if( !Peli.getEstado() ){ /// ENTRA SI EL ESTADO ES FALSO
            fseek(pArchivo,0,0);/// Mueve el puntero al inicio del archivo.
            obj.setIdPelicula(1);/// Asigna el ID de película como 1 al objeto 'obj'.
            escribio = fwrite(&obj,sizeof(Pelicula),1,pArchivo);
            Bandera = false;/// Cambia 'Bandera' a 'false' para indicar que el registro fue sobreescrito.
        }

    }

    if(Bandera){/// Si 'Bandera' es true, indica que no se encontró un registro inactivo.
        fseek(pArchivo,0,2);
        escribio = fwrite(&obj, sizeof(obj),1,pArchivo);
    }

    fclose(pArchivo);
    return escribio;

}

/// ---------------- > MOSTRAR

void PeliculaArchi::Mostrar(){

        Pelicula Pelicula;
        FILE *pPelicula = fopen(_Nombre,"rb");

        if( pPelicula == NULL ){
            exit(1);
        }

        while ( fread(&Pelicula,sizeof(Pelicula),1,pPelicula) == 1 ){
            Pelicula.Mostrar();
            cout<<endl;
        }

        fclose(pPelicula);
        system("pause");

}

/// ---------------- > FILTRAR POR ID

void PeliculaArchi::FiltrarPelicula(int ID){

    Pelicula idPelicula;
    FILE *pPeliculas = fopen(_Nombre,"rb");

    if( pPeliculas == NULL ){
        exit(1);
    }

    fseek(pPeliculas,sizeof(Pelicula)*(ID-1),0);

    bool Encontro = fread(&idPelicula,sizeof(Pelicula),1,pPeliculas);

    if( Encontro && idPelicula.getEstado() ) idPelicula.Mostrar();
    else cout<<"[+] NO SE ENCONTRO LA PELICULA CON DICHO ID"<<endl;

    fclose(pPeliculas);

}

/// ---------------- > ELIMINAR PELICULA

bool PeliculaArchi::EliminarPelicula(int ID){

    bool Elimino = false;

    Pelicula titulo;
    FILE *pPeliculas = fopen(_Nombre,"rb+");

    if( pPeliculas == NULL ){
        exit(1);
    }

    fseek( pPeliculas,sizeof(Pelicula)*(ID-1),0 );

    if( fread(&titulo,sizeof(Pelicula),1,pPeliculas) == 1 ){

        if( titulo.getEstado() ){
            titulo.setEstado(false);
            fseek( pPeliculas,sizeof(Pelicula)*(ID-1),0 );
            Elimino = fwrite(&titulo,sizeof(Pelicula),1,pPeliculas);
        }else{
            cout<<"[+] NO SE ENCONTRO DICHA PELICULA"<<endl;
        }

    }else{
        cout<<"[+] NO EXISTE PELICULA CON DICHO ID"<<endl;
    }

    fclose(pPeliculas);
    return Elimino;
}

/// ---------------- > OBTENER TOTAL PELICULAS

int PeliculaArchi::ObtenerTotalPeliculas(int IDP){

    int Cant;

    Pelicula Peli;
    FILE *pPelicula = fopen(_Nombre,"rb");

    if(pPelicula == NULL){
        exit(1);
    }

    fseek(pPelicula,sizeof(Pelicula)*(IDP-1),0);
    fread(&Peli,sizeof(Pelicula),1,pPelicula);

    Cant = Peli.getStock();

    fclose(pPelicula);
    return Cant;
}

/// ---------------- > OBTENER PRECIO

float PeliculaArchi::ObtenerPrecio(int ID){

    float Precio = -1;
    Pelicula Peli;

    FILE *pPelicula = fopen(_Nombre,"rb");

    if(pPelicula == NULL){
        exit(1);
    }

    fseek(pPelicula,sizeof(Pelicula)*(ID-1),0);

    if( fread(&Peli,sizeof(Pelicula),1,pPelicula) == 1 ){

        if( Peli.getEstado() ){ Precio = Peli.getPrecio(); }

    }

    fclose(pPelicula);

    return Precio;
}

/// ---------------- > MODIFICAR TOTAL

void PeliculaArchi::ModificarTotal(int ID,int Cant){

    FILE *pPelicula = fopen(_Nombre,"rb+");
    Pelicula Peli;

    if(pPelicula == NULL){
        exit(1);
    }

    fseek(pPelicula,sizeof(Pelicula)*(ID-1),0);
    fread(&Peli,sizeof(Pelicula),1,pPelicula);

    Peli.setStock( Cant );

    fseek(pPelicula,sizeof(Pelicula)*(ID-1),0);
    fwrite(&Peli,sizeof(Pelicula),1,pPelicula);

    fclose(pPelicula);

}

/// ---------------- > OBTENER REGISTROS

int PeliculaArchi::ObtenerRegistros(){

    int Registros;

    FILE *pPelicula = fopen(_Nombre,"rb");

    if(pPelicula == NULL){
        exit(1);
    }

    fseek(pPelicula,0,2);
    Registros = ftell(pPelicula) / sizeof(Pelicula);

    fclose(pPelicula);
    return Registros;
}

/// ---------------- > HACER BACKUP

void PeliculaArchi::BackUp(){

    Pelicula Peli;

    FILE *pArchivo = fopen("Peliculas.Dat","wb");

    if( pArchivo == NULL ){
        exit(1);
    }

    FILE *pArchivo2 = fopen("Peliculas.bkp","rb");

    if( pArchivo2 == NULL ){
        exit(1);
    }

    while( fread(&Peli,sizeof(Pelicula),1,pArchivo2) == 1 ){
        fwrite(&Peli,sizeof(Pelicula),1,pArchivo);
    }

    fclose(pArchivo);
    fclose(pArchivo2);

}

bool PeliculaArchi::StockAgregar(int ID, int cantidad){


FILE *pPelicula = fopen(_Nombre,"rb+");
Pelicula Peli;
bool escribio;

 if( pPelicula == NULL ){
        exit(1);
    }

     fseek(pPelicula,sizeof(Pelicula)*(ID-1),0);

     if(fread(&Peli,sizeof(Pelicula),1,pPelicula)==1){

    Peli.setStock( (Peli.getStock() + cantidad) );

    fseek(pPelicula,sizeof(Pelicula)*(ID-1),0);

    escribio = fwrite(&Peli,sizeof(Pelicula),1,pPelicula);
     }
     else{escribio=false;}

    fclose(pPelicula);

 return escribio;
}

/// ---------------- > PELICULA CON MAS STOCK


void PeliculaArchi::MostrarPeliculaConMasStock() {

    FILE *pPelicula = fopen("Peliculas.dat", "rb");

    if (pPelicula == NULL) {
        exit(1);
    }

    Pelicula peli;
    int maxStock = 0;
    char tituloMaxStock[30]; /// ALMACENA EL TÍTULO DE LA PELÍCULA CON MÁS STOCK
    bool peliculaEncontrada = false;

    /// RECORREMOS TODOS LOS REGISTROS DEL ARCHIVO
    while (fread(&peli, sizeof(Pelicula), 1, pPelicula) == 1) {
        int stockActual = peli.getStock();

    /// VERIFICA SI ESTE STOCK ES EL MÁS GRANDE ENCONTRADO AL MOMENTO.
        if (stockActual > maxStock) {
            maxStock = stockActual;
            strcpy(tituloMaxStock, peli.getTitulo());
            peliculaEncontrada = true;
        }
    }

    /// VERIFICA SI SE ENCONTRÓ ALGUNA PELICULA
    if (peliculaEncontrada) {
        cout << "PELICULA CON MAS STOCK: " << tituloMaxStock << " con " << maxStock << " unidades en stock" <<endl;
    } else { cout << "[+] NO SE ENCONTRO PELICULA EN EL ARCHIVO" << endl; }

    fclose(pPelicula);

}

/// ---------------- > REESTABLECER EL STOCK

void PeliculaArchi::ReestablecerStock(int IDPelicula, int Stock){

    FILE *pPelicula = fopen("Peliculas.dat", "rb+");

    if (pPelicula == NULL) {
        exit(1);
    }

    Pelicula Peli;

    fseek(pPelicula,sizeof(Pelicula)*(IDPelicula - 1),0);
    fread(&Peli,sizeof(Pelicula),1,pPelicula);

    Peli.setStock( Peli.getStock() + Stock);

    fseek(pPelicula,sizeof(Pelicula)*(IDPelicula - 1),0);
    fwrite(&Peli,sizeof(Pelicula),1,pPelicula);

    fclose(pPelicula);
}

void PeliculaArchi::MostrarNombreMasVendida(int IDMasVendida){

FILE *pPelicula = fopen ("Peliculas.dat", "rb");

if (pPelicula == NULL) {
    exit(1);
    }

    Pelicula Peli;

    fseek(pPelicula, sizeof(Pelicula)*(IDMasVendida - 1), 0);
    fread(&Peli, sizeof(Pelicula),1, pPelicula);

    cout<<"El nombre es: "<<Peli.getTitulo()<<endl;

    fclose(pPelicula);

}

void PeliculaArchi::FiltrarPorGenero(const char *_genero){
    FILE *pPelicula = fopen("Peliculas.dat", "rb");

    if (pPelicula == NULL) {
        exit(1);
    }

    Pelicula Peli;
    bool encontrado = false;

    while (fread(&Peli, sizeof(Pelicula), 1, pPelicula) == 1) {
        // Usamos strcasecmp para comparar sin distinguir entre mayúsculas y minúsculas
        if (strcasecmp(_genero, Peli.getGenero()) == 0) {
            Peli.Mostrar();
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << " No se encontro ninguna pelicula con el genero \"" << _genero << "\"." << endl;
    }

    fclose(pPelicula);
}


void PeliculaArchi::MostrarPeliculasSinStock() {
    // Abrir el archivo Peliculas.dat
    FILE *pPeliculas = fopen("Peliculas.dat", "rb");
    if (pPeliculas == NULL) {
        exit(1);
}

    Pelicula pelicula;  // Objeto para leer cada registro de película
    bool hayPeliculasSinStock = false;

    cout << "[+] Películas sin stock actualmente:" << endl;

    // Leer cada registro del archivo
    while (fread(&pelicula, sizeof(Pelicula), 1, pPeliculas) == 1) {
        if (pelicula.getStock() <= 0) {  // Películas con stock <= 0
            cout << "Película con ID: " << pelicula.getId();
              cout   << " (" << pelicula.getTitulo() << ") no tiene stock disponible." << endl;
            hayPeliculasSinStock = true;
        }
    }

    // Si no se encontraron películas sin stock
    if (!hayPeliculasSinStock) {
        cout << "Todas las películas tienen stock disponible." << endl;
    }

    fclose(pPeliculas);  // Cerrar el archivo
}

bool PeliculaArchi::ExisteID(int ID) {
    FILE *pPeliculas = fopen("Peliculas.dat", "rb");

    if (pPeliculas == NULL) {
        exit(1);
    }

    Pelicula Peli;

    while (fread(&Peli, sizeof(Pelicula), 1, pPeliculas) == 1) {
        if (Peli.getId() == ID) { // Compara con el ID buscado
            fclose(pPeliculas);
            return true; // Si lo encuentra, retorna verdadero
        }
    }

    fclose(pPeliculas);
    return false; // Si no lo encuentra, retorna falso
}

void PeliculaArchi::FiltrarPorTitulo(const char *_titulo) {
    FILE *pPelicula = fopen("Peliculas.dat", "rb");

    if (pPelicula == NULL) {
        exit(1);
    }

    Pelicula Peli;


    while (fread(&Peli, sizeof(Pelicula), 1, pPelicula) == 1) {
        // Usamos strcasecmp para comparar sin distinguir entre mayúsculas y minúsculas
        if (strcasecmp(_titulo, Peli.getTitulo()) == 0) {
            Peli.Mostrar();

        }
    }

    fclose(pPelicula);
}



void PeliculaArchi::FiltrarPorRango(int ID1, int ID2) {
    FILE *pPeliculas = fopen("Peliculas.dat", "rb");

    if (pPeliculas == NULL) {
       exit(1);
    }

    Pelicula Peli;


    cout << " Peliculas en el rango de ID " << ID1 << " a " << ID2 << ":" << endl;

    while (fread(&Peli, sizeof(Pelicula), 1, pPeliculas) == 1) {
        int idActual = Peli.getId();
        if (idActual >= ID1 && idActual <= ID2) {
            Peli.Mostrar(); // Método que imprime los datos de la película
            cout << "--------------------------" << endl;

        }
        if(idActual <= ID1 && idActual >= ID2){
            Peli.Mostrar(); // Método que imprime los datos de la película
            cout << "--------------------------" << endl;

        }

    }

    fclose(pPeliculas);
}

void PeliculaArchi::FiltrarPeliculaPorPrefijo(const char *prefijo) {
    FILE *pPelicula = fopen(_Nombre, "rb");

    if (pPelicula == NULL) {
        exit(1); // Si el archivo no se abre correctamente
    }

    Pelicula peli;
    bool encontrado = false; // Para verificar si encontramos coincidencias

    // Convertir el prefijo a minúsculas para comparación insensible
    char prefijoMinuscula[100];
    strcpy(prefijoMinuscula, prefijo);
    for (int i = 0; prefijoMinuscula[i]; i++) {
    ///Corta automáticamente cuando encuentra el carácter nulo ('\0') al final de la cadena prefijoMinuscula.
        prefijoMinuscula[i] = tolower(prefijoMinuscula[i]);
    }

    cout << "Peliculas que comienzan con la/s letra/s: " << prefijo << endl;

    while (fread(&peli, sizeof(Pelicula), 1, pPelicula) == 1) {
        const char *titulo = peli.getTitulo(); // Obtenemos el título de la película

        // Crear una copia del título en minúsculas para comparación
        char tituloMinuscula[100];
        strcpy(tituloMinuscula, titulo);
        for (int i = 0; tituloMinuscula[i]; i++) {
            tituloMinuscula[i] = tolower(tituloMinuscula[i]);
        }

        // Verificar si el título comienza con el prefijo en minúsculas
        if (strncmp(tituloMinuscula, prefijoMinuscula, strlen(prefijoMinuscula)) == 0) {///strlen: Indica cuántos caracteres iniciales de ambas cadenas deben compararse.
            peli.Mostrar(); // Mostrar los datos de la película
            cout << endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron peliculas que comiencen con la/s letra/s '" << prefijo << "'." << endl;
    }

    fclose(pPelicula); // Cerramos el archivo
}




#endif // CLASEPELICULAARCHI_H_INCLUDED
