#ifndef CLASEPERSONAARCHI_H_INCLUDED
#define CLASEPERSONAARCHI_H_INCLUDED

class PersonaArchi{
private:
    char _Nombre[50];

public:

    /// CONSTRUCTOR

    PersonaArchi(const char *N = "Clientes.dat" ){ strcpy(_Nombre,N); }

    /// MÉTODOS

    bool Escribir(Cliente Comprador);
    void Mostrar();
    void FiltrarCliente(int ID);
    bool EliminarCliente(int ID);

    float ObtenerSaldo(int ID);
    void ModificarSaldo(int ID, float Saldo);
    bool AgregarCredito(int ID, float CreditoAgregar);
    void ReestablacerSaldo(int IDCliente, float Saldo);

    void BackUp();

    int ObtenerRegistros();

    void mostrarClientesMas25();
    void FiltrarPorApellido(const char *_apellido);
    void AgregarStockPorApellido(const char *apellido);
    bool ExisteID(int ID);
    void FiltrarClientePorRango(int ID1, int ID2);
    void FiltrarClientePorPrefijo(const char *prefijo);

};

/// ------------------------------------------ [ MÉTODOS DE LA CLASE ] ------------------------------------------

/// ---------------- > ESCRIBIR

bool PersonaArchi::Escribir(Cliente Comprador){ /// RECIBE OBJETO CLIENTE PARA ESCRIBIR EN EL ARCHIVO

        FILE *pCliente = fopen(_Nombre,"rb+"); /// PUNTERO A ARCHIVO

        bool escribio, Bandera = true; /// ALMACENA EL RESULTADO DE LA ESCRITURA ( 1 -> SE ESCRIBIÓ, 2 -> NO SE ESCRIBIÓ)

        if(pCliente == NULL){
            exit(1); /// SE EJECUTA CUANDO NO SE PUDO ABRIR EL ARCHIVO
        }

        /// NUEVO

        Cliente obj;

        if( ObtenerRegistros() == 1 ){

            fseek(pCliente,0,0);
            fread(&obj,sizeof(Cliente),1,pCliente);

            if( !obj.getTarjeta() ){ /// ENTRA SI EL ESTADO ES FALSO

                fseek(pCliente,0,0);
                Comprador.setIDCliente(1);

                if( Comprador.getFechaNacimiento().getDia() != 0 && Comprador.getFechaNacimiento().getMes() != 0 ){

                    escribio = fwrite(&Comprador,sizeof(Cliente),1,pCliente);

                }else{ escribio = false; }

                Bandera = false;

            }

        }

        if( Bandera ){

            fseek(pCliente,0,2);

            if( Comprador.getFechaNacimiento().getDia() != 0 && Comprador.getFechaNacimiento().getMes() != 0 ){

                escribio = fwrite(&Comprador,sizeof(Cliente),1,pCliente);

            }else{ escribio = false; }

        }

        /// SDKAODKSA

        fclose(pCliente); /// CIERRO ARCHIVO

        return escribio;
}

/// ---------------- > MOSTRAR

void PersonaArchi::Mostrar(){

        Cliente Comprador;
        FILE *pClientes = fopen(_Nombre,"rb");

        if( pClientes == NULL ){
            exit(1);
        }

        while ( fread(&Comprador,sizeof(Cliente),1,pClientes) == 1 ){

            if( Comprador.getTarjeta() ){
                Comprador.Mostrar();
                cout<<"------------------------------------";
                cout<<endl;
            }

        }

        fclose(pClientes);
        system("pause");

}

/// ---------------- > FILTRAR CLIENTE POR ID

void PersonaArchi::FiltrarCliente(int ID){

    Cliente Comprador;
    FILE *pClientes = fopen(_Nombre,"rb");

    if( pClientes == NULL ){
        exit(1);
    }

    fseek(pClientes,sizeof(Cliente)*(ID-1),0);

    bool Encontro = fread(&Comprador,sizeof(Cliente),1,pClientes);

    if( Encontro && Comprador.getTarjeta() ) Comprador.Mostrar();
    else cout<<"[+] NO SE ENCONTRO CLIENTE CON DICHO ID"<<endl;

    fclose(pClientes);

}

/// ---------------- > ELIMINAR CLIENTE

bool PersonaArchi::EliminarCliente(int ID){

    bool Elimino = false;

    Cliente Comprador;
    FILE *pClientes = fopen(_Nombre,"rb+");

    if( pClientes == NULL ){
        exit(1);
    }

    fseek(pClientes,sizeof(Cliente)*(ID-1),0);

    if( fread(&Comprador,sizeof(Cliente),1,pClientes) == 1 ){

        if( Comprador.getTarjeta() ){
            Comprador.set_Tarjeta(false);
            fseek(pClientes,sizeof(Cliente)*(ID-1),0);
            Elimino = fwrite(&Comprador,sizeof(Cliente),1,pClientes);
        }else{
            cout<<"[+] NO SE ENCONTRO DICHA PELICULA"<<endl;
        }


    }else{
        cout<<"[+] NO EXISTE CLIENTE CON DICHO ID"<<endl;
    }

    fclose(pClientes);
    return Elimino;
}

/// ---------------- > OBTENER SALDO

float PersonaArchi::ObtenerSaldo(int ID){

    float Saldo = -1;
    Cliente Comprador;

    FILE *pCliente = fopen(_Nombre,"rb");

    if( pCliente == NULL ){
       exit(1);
    }

    fseek(pCliente,sizeof(Cliente)*(ID-1),0);

    if( fread(&Comprador,sizeof(Cliente),1,pCliente) == 1 ){

        if( Comprador.getTarjeta() ){ Saldo = Comprador.getCredito(); }

    }

    fclose(pCliente);

    return Saldo;
}

/// ---------------- > MODIFICAR SALDO

void PersonaArchi::ModificarSaldo(int ID, float Saldo){

    Cliente Comprador;
    FILE *pCliente = fopen(_Nombre,"rb+");

    if( pCliente == NULL ){
        exit(1);
    }

    fseek(pCliente,sizeof(Cliente)*(ID-1),0);
    fread(&Comprador,sizeof(Cliente),1,pCliente);

    Comprador.set_Credito(Saldo);

    fseek(pCliente,sizeof(Cliente)*(ID-1),0);
    fwrite(&Comprador,sizeof(Cliente),1,pCliente);

    fclose(pCliente);
}

/// ---------------- > AGREGAR CREDITO

bool PersonaArchi::AgregarCredito(int ID, float CreditoAgregar) {

    Cliente Comprador;
    FILE *pCliente = fopen(_Nombre, "rb+");

    if (pCliente == NULL) {
        exit(1);  // Salir si no se puede abrir el archivo
    }

    fseek(pCliente, sizeof(Cliente)*(ID - 1),0);

    bool Encontro = fread(&Comprador, sizeof(Cliente), 1, pCliente);

    if (Encontro) {
        float NuevoSaldo = Comprador.getCredito() + CreditoAgregar;
        Comprador.set_Credito(NuevoSaldo);

        fseek(pCliente, sizeof(Cliente) * (ID - 1), 0);
        fwrite(&Comprador, sizeof(Cliente), 1, pCliente);
    }

    fclose(pCliente);
    return Encontro;
}

/// ---------------- > HACER BACKUP

void PersonaArchi::BackUp(){

    Cliente Comprador;

    FILE *pArchivo = fopen("Clientes.Dat","wb");

    if( pArchivo == NULL ){
        exit(1);
    }

    FILE *pArchivo2 = fopen("Clientes.bkp","rb");

    if( pArchivo2 == NULL ){
        exit(1);
    }

    while( fread(&Comprador,sizeof(Cliente),1,pArchivo2) == 1 ){
        fwrite(&Comprador,sizeof(Cliente),1,pArchivo);
    }

    fclose(pArchivo);
    fclose(pArchivo2);

}

/// ---------------- > REESTABLECER EL SALDO DEL CLIENTE

void PersonaArchi::ReestablacerSaldo(int IDCliente,float Saldo){

    FILE *pCliente = fopen(_Nombre, "rb+");

    if (pCliente == NULL) {
        exit(1);
    }

    Cliente Comprador;

    fseek(pCliente,sizeof(Cliente)*(IDCliente - 1),0);
    fread(&Comprador,sizeof(Cliente),1,pCliente);

    Comprador.set_Credito( Comprador.getCredito() + Saldo );

    fseek(pCliente,sizeof(Cliente)*(IDCliente - 1),0);
    fwrite(&Comprador,sizeof(Cliente),1,pCliente);

    fclose(pCliente);
}

/// ---------------- > OBTENER REGISTROS

int PersonaArchi::ObtenerRegistros(){

    int Registros;

    FILE *pCliente = fopen(_Nombre,"rb");

    if(pCliente == NULL){
        exit(1);
    }

    fseek(pCliente,0,2);
    Registros = ftell(pCliente) / sizeof(Cliente);

    fclose(pCliente);
    return Registros;
}

/// ---------------- > MOSTRAR CLIENTES MAS 25

void PersonaArchi::mostrarClientesMas25(){

FILE *pCliente = fopen(_Nombre, "rb");

Cliente cli;

 if(pCliente == NULL){
        exit(1);
    }
int aux=0;

    while (fread(&cli, sizeof(Cliente),1, pCliente) == 1){

        if (2024 - cli.getFechaNacimiento().getAnio() > 25){
            cli.Mostrar();
            cout<<"---------------------"<<endl;
            aux++;
        }
    }

    if(aux==0){
        cout<<"No se encontraron clientes mayores a 25"<<endl;
    }

    fclose(pCliente);

}

/// ---------------- > FILTRAR POR APELLIDO

void PersonaArchi::FiltrarPorApellido(const char *_apellido){

FILE *pCliente = fopen(_Nombre, "rb");

Cliente cli;
bool encontrado = false;

 if(pCliente == NULL){
        exit(1);
    }

while (fread(&cli, sizeof(Cliente), 1, pCliente)==1){

    if(strcasecmp(_apellido, cli.getApellido())==0){

        cli.Mostrar();
        encontrado = true;

    }

}
 if (!encontrado) {
        cout << " No se encontro ningun cliente con el apellido \"" << _apellido << "\"." << endl;
    }


fclose(pCliente);

}

/// ---------------- > AGREGAR STOCK POR APELLIDO

void PersonaArchi::AgregarStockPorApellido(const char *_apellido) {
    FILE *pClientes = fopen("Clientes.dat", "rb+");

    if (pClientes == NULL) {
        exit(1);
    }

    Cliente cliente;
    bool encontrado = false;

    while (fread(&cliente, sizeof(Cliente), 1, pClientes) == 1) {
        if (strcasecmp(_apellido, cliente.getApellido()) == 0) {
            encontrado = true;

            // Pedir cantidad de stock para agregar
            int nuevoCredito;
            cout << "Ingrese la cantidad de credito a agregar: ";
            cin >> nuevoCredito;

            // Validar entrada
            if (nuevoCredito > 0) {
                cliente.set_Credito(cliente.getCredito() + nuevoCredito);

                // Posicionarse para actualizar el registro
                fseek(pClientes, -sizeof(Cliente), 1);
                fwrite(&cliente, sizeof(Cliente), 1, pClientes);

                cout << "Se ha agregado el credito correctamente." << endl;
            } else {
                cout << " La cantidad ingresada debe ser positiva." << endl;
            }

            break;
        }
    }

    if (!encontrado) {
        cout << " No se encontro ningun cliente con el apellido \"" << _apellido << "\"." << endl;
    }

    fclose(pClientes);
}

/// ---------------- > VERIFICAR SI EXISTE ID

bool PersonaArchi::ExisteID(int ID) {
    FILE *pCliente = fopen("Clientes.dat", "rb");

    if (pCliente == NULL) {
        return false;
    }

    Cliente obj1;

    while (fread(&obj1, sizeof(Cliente), 1, pCliente) == 1) {
        if (obj1.getIDCliente() == ID) { // Compara con el ID buscado
            fclose(pCliente);
            return true; // Si lo encuentra, retorna verdadero
        }
    }

    fclose(pCliente);
    return false; // Si no lo encuentra, retorna falso
}

/// ---------------- > FLISTRAR CLIENTES POR DOS RANGOS DE ID

void PersonaArchi::FiltrarClientePorRango(int ID1, int ID2) {
    FILE *pCliente = fopen("Clientes.Dat", "rb");

    if (pCliente == NULL) {
       exit(1);
    }

    Cliente obj1;


    cout << " CLiente en el rango de ID " << ID1 << " a " << ID2 << ":" << endl;

    while (fread(&obj1, sizeof(Cliente), 1, pCliente) == 1) {
        int idActual = obj1.getIDCliente();
        if (idActual >= ID1 && idActual <= ID2) {
            obj1.Mostrar(); // Método que imprime los datos de la película
            cout << "--------------------------" << endl;

        }
        if(idActual <= ID1 && idActual >= ID2){
            obj1.Mostrar(); // Método que imprime los datos de la película
            cout << "--------------------------" << endl;

        }

    }
    fclose(pCliente);
}

/// ---------------- > FILTRAR CLIENTE POR PREFIJO

void PersonaArchi::FiltrarClientePorPrefijo(const char *prefijo) {
    FILE *pClientes = fopen(_Nombre, "rb");

    if (pClientes == NULL) {
        exit(1); // Si el archivo no se abre correctamente
    }

    Cliente cli;
    bool encontrado = false; // Para verificar si encontramos coincidencias

    // Convertir el prefijo a minúsculas para comparación insensible
    char prefijoMinuscula[100];
    strcpy(prefijoMinuscula, prefijo);
    for (int i = 0; prefijoMinuscula[i]; i++) {
        prefijoMinuscula[i] = tolower(prefijoMinuscula[i]);
    }

    cout << "Clientes cuyos apellidos comienzan con: " << prefijo << endl;

    while (fread(&cli, sizeof(Cliente), 1, pClientes) == 1) {
        const char *apellido = cli.getApellido(); // Obtenemos el apellido del cliente

        // Crear una copia del apellido en minúsculas para comparación
        char apellidoMinuscula[100];
        strcpy(apellidoMinuscula, apellido);
        for (int i = 0; apellidoMinuscula[i]; i++) {
            apellidoMinuscula[i] = tolower(apellidoMinuscula[i]);
        }

        // Verificar si el apellido comienza con el prefijo en minúsculas
        if (strncmp(apellidoMinuscula, prefijoMinuscula, strlen(prefijoMinuscula)) == 0) {
            cli.Mostrar(); // Mostrar los datos del cliente
            cout << endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron clientes cuyos apellidos comiencen con la/s letra/s '" << prefijo << "'." << endl;
    }

    fclose(pClientes); // Cerramos el archivo
}



#endif // CLASEPERSONAARCHI_H_INCLUDED
