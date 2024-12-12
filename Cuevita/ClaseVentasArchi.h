#ifndef CLASEVENTASARCHI_H_INCLUDED
#define CLASEVENTASARCHI_H_INCLUDED

class VentasArchi{
private:
    char _Nombre[50];

public:

    /// CONSTRUCTOR

    VentasArchi(const char *N = "Ventas.dat" ){ strcpy(_Nombre,N); }

    /// GETTER

    int getStock(int IDV);
    int getIDPelicula(int IDV);
    int getIDCliente(int IDV);
    float getSaldo(int IDV);

    /// MÉTODOS

    bool RegistrarVenta(Venta RegistroVenta);
    void Mostrar();
    void MostrarVentaXCliente(int ID);

    void CargaVentas(int *VPeliculas);
    void Eliminar(int ID);
    void FiltrarVentaporID(int ID);
    bool ExisteID(int ID);
    void FiltrarPorRango(int ID1, int ID2);

    /// REPORTES

    void ObtenerRegistroXMes(int Mes);
    void MostrarPeliculasNoVendidas();
    void MostrarVentasPorCliente();

};

/// ------------------------------------------ [ MÉTODOS DE LA CLASE ] ------------------------------------------

/// ---------------- > REGISTRAR VENTA

bool VentasArchi::RegistrarVenta(Venta RegistroVenta){

    bool Escribio = false;
    FILE *pVenta = fopen(_Nombre,"ab+");

    if( pVenta == NULL ){
        exit(1);
    }

    if( RegistroVenta.getFechaCompra().getDia() != 0 && RegistroVenta.getFechaCompra().getMes() != 0 ){

        if ( fwrite(&RegistroVenta,sizeof(Venta),1,pVenta) == 1 ){

            cout<<"[+] VENTA REGISTRADA"<<endl;
            Escribio = true;

        }else { cout<<"[+] NO SE PUDO REGISTRAR LA VENTA "<<endl; }

    }else{
            cout<<"[+] NO SE PUDO REGISTRAR LA VENTA "<<endl;
    }

    fclose(pVenta);

    return Escribio;
}

/// ---------------- > MOSTRAR TODAS LAS VENTAS

void VentasArchi::Mostrar(){

    Venta DetalleVenta;
    FILE *pVentas = fopen(_Nombre,"rb");

    if( pVentas == NULL ){
        exit(1);
    }

    while( fread(&DetalleVenta,sizeof(Venta),1,pVentas) == 1 ){
        DetalleVenta.Mostrar();
    }

    fclose(pVentas);

}

/// ---------------- > MOSTRAR VENTAS POR CLIENTE

void VentasArchi::MostrarVentaXCliente(int ID){

    Venta DetalleVenta;
    FILE *pVentas = fopen(_Nombre,"rb");


    if( pVentas == NULL ){
        exit(1);
    }

    int contador = 0;

    while( fread(&DetalleVenta,sizeof(Venta),1,pVentas) == 1 ){
        if( DetalleVenta.getIDCliente() == ID ){
            DetalleVenta.Mostrar();
            cout<<endl;
            contador = contador+1;
        }

    }

    fclose(pVentas);
    cout<<"La cantidad de ventas de este cliente es: "<<contador<<endl;
}

/// ---------------- > CARGAR VENTAS

void VentasArchi::CargaVentas(int *VPeliculas){

    FILE *pVenta = fopen(_Nombre,"rb");
    Venta DetalleVenta;

    if(pVenta == NULL){
        exit(1);
    }

    while( fread(&DetalleVenta,sizeof(Venta),1,pVenta) == 1 ){

        if( DetalleVenta.getEstado() ){
            VPeliculas[ DetalleVenta.getIDPelicula() - 1 ] += DetalleVenta.getCantidad();
        }

    }

    fclose(pVenta);

}

/// ---------------- > OBTENER EL TOTAL DE REGISTROS POR MES

void VentasArchi::ObtenerRegistroXMes(int Mes){

    Venta Ventas;

    FILE *pArchivo = fopen(_Nombre,"rb");

     if (pArchivo == NULL) {
        exit(1);
    }

    int contador = 0;

    while( fread(&Ventas,sizeof(Venta),1,pArchivo) == 1 ){
        if( Ventas.getFechaCompra().getMes() == Mes ){
            Ventas.Mostrar();
             contador++;
            cout<<endl;
        }
    }

    fclose(pArchivo);

    if (contador == 0) {
        cout << "No hay ventas registradas en el mes ingresado." << endl;
    }
}

/// ---------------- > ELIMINAR VENTAS

void VentasArchi::Eliminar(int ID){

    Venta RegistroVenta;

    FILE *pVentas = fopen(_Nombre,"rb+");

    if( pVentas == NULL ){
        exit(1);
    }

    fseek(pVentas,sizeof(Venta)*(ID-1),0);

    if( fread(&RegistroVenta,sizeof(Venta),1,pVentas) == 1 ){

        fseek(pVentas,sizeof(Venta)*(ID-1),0);
        RegistroVenta.setEstado(false);

        if( fwrite(&RegistroVenta,sizeof(Venta),1,pVentas) == 1 ){
            cout<<"[+] VENTA ELIMINADA CORRECTAMENTE"<<endl;
        }else{
            cout<<"[+] NO SE PUDO ELIMINAR LA VENTA"<<endl;
        }

    }else{
        cout<<"[+] NO SE ENCONTRO DICHA VENTA"<<endl;
    }

    fclose(pVentas);

}

/// ---------------- > OBTENER STOCK ( CANTIDAD VENDIDA )

int VentasArchi::getStock(int IDV){

    Venta RegistroVenta;

    FILE *pVentas = fopen(_Nombre,"rb");

    if( pVentas == NULL ){
        exit(1);
    }

    fseek(pVentas,sizeof(Venta)*(IDV-1),0);
    fread(&RegistroVenta,sizeof(Venta),1,pVentas);

    fclose(pVentas);

    return RegistroVenta.getCantidad();
}

/// ---------------- > OBTENER ID DE LA PELICULA VENDIDA

int VentasArchi::getIDPelicula(int IDV){

    Venta RegistroVenta;

    FILE *pVentas = fopen(_Nombre,"rb");

    if( pVentas == NULL ){
        exit(1);
    }

    fseek(pVentas,sizeof(Venta)*(IDV-1),0);
    fread(&RegistroVenta,sizeof(Venta),1,pVentas);

    fclose(pVentas);

    return RegistroVenta.getIDPelicula();

}

/// ---------------- > OBTENER ID DEL CLIENTE VENDIDA

int VentasArchi::getIDCliente(int IDV){

    Venta RegistroVenta;

    FILE *pVentas = fopen(_Nombre,"rb");

    if( pVentas == NULL ){
        exit(1);
    }

    fseek(pVentas,sizeof(Venta)*(IDV-1),0);
    fread(&RegistroVenta,sizeof(Venta),1,pVentas);

    fclose(pVentas);

    return RegistroVenta.getIDCliente();

}

/// ---------------- > OBTENER SALDO DEL CLIENTE VENDIDA

float VentasArchi::getSaldo(int IDV){

    Venta RegistroVenta;

    FILE *pVentas = fopen(_Nombre,"rb");

    if( pVentas == NULL ){
        exit(1);
    }

    fseek(pVentas,sizeof(Venta)*(IDV-1),0);
    fread(&RegistroVenta,sizeof(Venta),1,pVentas);

    fclose(pVentas);
    return RegistroVenta.getPrecio();

}

/// ---------------- > OBTENER PELICULAS NO VENDIDAS

void VentasArchi::MostrarPeliculasNoVendidas() {
    bool *Peliculas;  // Arreglo dinámico para indicar si una película está vendida

    FILE *pPeliculas = fopen("Peliculas.dat", "rb");

    if (pPeliculas == NULL) {
        exit(1);  // Si el archivo de películas no se abre, salir
    }

    fseek(pPeliculas, 0, 2);  // Mueve el puntero de archivo al final

    int Cant = ftell(pPeliculas) / sizeof(Pelicula);  // Calcula la cantidad de películas
    Peliculas = new bool[Cant];  // Crea el arreglo dinámico

    for (int i = 0; i < Cant; i++) {
        Peliculas[i] = false;  // Inicializa el arreglo como "no vendida"
    }

    fclose(pPeliculas);  // Cierra el archivo de películas

    FILE *pVentas = fopen(_Nombre, "rb");  // Abre el archivo de ventas

    if (pVentas == NULL) {  // Verifica si el archivo de ventas no se abre correctamente
        exit(1);  // Si no se puede abrir, salir
    }

    Venta RegistroVenta;

    while (fread(&RegistroVenta, sizeof(Venta), 1, pVentas) == 1) {  // Lee las ventas
        if (RegistroVenta.getEstado()) {  // Si la venta está activa
            Peliculas[RegistroVenta.getIDPelicula() - 1] = true;  // Marca la película como vendida
        }
    }

    fclose(pVentas);  // Cierra el archivo de ventas

    // Volvemos a abrir el archivo de películas para mostrar los nombres
    pPeliculas = fopen("Peliculas.dat", "rb");

    if (pPeliculas == NULL) {
        delete[] Peliculas;
        exit(1);
    }

    Pelicula peli;

    cout << "\n[+] Peliculas no vendidas:" << endl;

    for (int i = 0; i < Cant; i++) {
        if (!Peliculas[i]) {  // Si la película no está vendida
            fseek(pPeliculas, i * sizeof(Pelicula), 0);  // Posiciona el puntero en la película correspondiente
            fread(&peli, sizeof(Pelicula), 1, pPeliculas);  // Lee los datos de la película

            cout << "ID PELICULA: " << i + 1 << " | Titulo: " << peli.getTitulo() << endl;
        }
    }

    delete[] Peliculas;  // Libera la memoria del arreglo dinámico
    fclose(pPeliculas);  // Cierra el archivo de películas
}

/// ---------------- > OBTENER CANTIDAD DE VENTAS POR CLIENTE

void VentasArchi::MostrarVentasPorCliente() {
    // Abrimos el archivo de clientes para obtener el total de clientes
    FILE *pClientes = fopen("Clientes.dat", "rb"); // Asumimos que el archivo de clientes se llama "Clientes.dat"
    if (pClientes == NULL) {
        cout << "Error al abrir el archivo de clientes." << endl;
        return;  // Salimos si no se puede abrir el archivo
    }

    // Contamos cuántos clientes hay en el archivo
    fseek(pClientes, 0, SEEK_END);
    int totalClientes = ftell(pClientes) / sizeof(Cliente); // Calculamos el número de clientes
    fclose(pClientes);  // Cerramos el archivo de clientes

    // Verificamos si hay clientes
    if (totalClientes == 0) {
        cout << "No hay clientes registrados." << endl;
        return;
    }

    // Creamos un arreglo dinámico para contar las ventas por cliente
    int *ventasPorCliente = new int[totalClientes];

    // Inicializamos el arreglo con ceros
    for (int i = 0; i < totalClientes; i++) {
        ventasPorCliente[i] = 0;
    }

    // Abrimos el archivo de ventas
    FILE *pVentas = fopen(_Nombre, "rb");
    if (pVentas == NULL) {
        cout << "Error al abrir el archivo de ventas." << endl;
        delete[] ventasPorCliente;
        return;  // Salimos si no se puede abrir el archivo
    }

    Venta detalleVenta;
    while (fread(&detalleVenta, sizeof(Venta), 1, pVentas) == 1) {
        if (detalleVenta.getEstado()) {  // Solo contamos las ventas activas
            int idCliente = detalleVenta.getIDCliente();
            if (idCliente > 0 && idCliente <= totalClientes) {
                ventasPorCliente[idCliente - 1]++;  // Incrementamos la cantidad de ventas para el cliente
            }
        }
    }

    fclose(pVentas);  // Cerramos el archivo de ventas

    // Mostrar la cantidad de ventas por cliente
    cout << "[+] Ventas por cliente:" << endl;
    for (int i = 0; i < totalClientes; i++) {
        cout << "Cliente con ID: " << i + 1 << " tiene " << ventasPorCliente[i] << " ventas registradas." << endl;
    }

    delete[] ventasPorCliente;  // Liberamos la memoria del vector dinámico
}

/// ---------------- > OBTENER FILTRADO DE VENTAS POR ID

void VentasArchi::FiltrarVentaporID(int ID){

    Venta idVenta;
    FILE *pVenta = fopen(_Nombre,"rb");

    if( pVenta == NULL ){
        exit(1);
    }

    fseek(pVenta,sizeof(Venta)*(ID-1),0);

    bool Encontro = fread(&idVenta,sizeof(Venta),1,pVenta);

    if( Encontro && idVenta.getEstado() ) idVenta.Mostrar();
    else cout<<"[+] NO SE ENCONTRO LA VENTA CON DICHO ID"<<endl;

    fclose(pVenta);

}

/// ---------------- > OBTENER SI EXISTE EL ID INGRESADO

bool VentasArchi::ExisteID(int ID) {
    FILE *pVentas = fopen("Ventas.dat", "rb");

    if (pVentas == NULL) {
        exit(1);
    }

    Venta IdVenta;

    while (fread(&IdVenta, sizeof(Venta), 1, pVentas) == 1) {
        if (IdVenta.getIDVenta() == ID) { // Compara con el ID buscado
            fclose(pVentas);
            return true; // Si lo encuentra, retorna verdadero
        }
    }

    fclose(pVentas);
    return false; // Si no lo encuentra, retorna falso
}

/// ---------------- > OBTENER FILTRADO DE VENTAS ENTRE DOS RANGOS

void VentasArchi::FiltrarPorRango(int ID1, int ID2) {
    FILE *pVentas = fopen("Ventas.dat", "rb");

    if (pVentas == NULL) {
       exit(1);
    }

   Venta IdVenta;

    cout << " Ventas en el rango de ID " << ID1 << " a " << ID2 << ":" << endl;

    while (fread(&IdVenta, sizeof(Venta), 1, pVentas) == 1) {
        int idActual = IdVenta.getIDVenta();
        if (idActual >= ID1 && idActual <= ID2) {
            IdVenta.Mostrar(); // Método que imprime los datos de la película
            cout << "--------------------------" << endl;

        }
        if(idActual <= ID1 && idActual >= ID2){
            IdVenta.Mostrar(); // Método que imprime los datos de la película
            cout << "--------------------------" << endl;

        }

    }

    fclose(pVentas);
}




#endif // CLASEVENTASARCHI_H_INCLUDED
