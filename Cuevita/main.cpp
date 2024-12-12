/// -------------------------------------------- [ LIBRER�AS ] ---------------------------------------------

/// " LIBRER�AS GENERALES "

#include <iostream>
#include <string.h>

using namespace std;

/// " .H "

#include "FuncionesGlobales.h" /// CONTIENE FUNCIONES UTILES PARA LA MAYOR�A DE LAS CLASES
#include "ClaseFecha.h" /// CONTIENE LA CLASE FECHA

#include "ClasePelicula.h" /// CONTIENE LA CLASE PELICULA
#include "ClasePersona.h" /// CONTIENE LA CLASE PERSONA
#include "ClaseCliente.h" /// CONTIENE LA CLASE CLIENTE -> HEREDA PERSONA
#include "ClaseVendedor.h" /// CONTIENE LA CLASE VENDEDOR -> HEREDA PERSONA
#include "ClaseVentas.h" /// CONTIENE LAS VENTAS REALIZADAS

#include "ClasePersonaArchi.h" /// CONTIENE LA CLASE QUE TRABAJA SOBRE EL ARCHIVO DE PERSONA/CLIENTE
#include "ClasePeliculaArchi.h" /// CONTIENE LA CLASE QUE TRABAJA SOBRE EL ARCHIVO DE PELICULAS
#include "ClaseVentasArchi.h" /// CONTIENE LA CLASE QUE TRABAJA SOBRE EL ARCHIVO DE VENTAS
#include "ClaseVendedorArchi.h" /// CONTIENE LA CLASE QUE TRABAJA SOBRE EL ARCHIVO VENDEDOR

#include "MenuPeliculas.h" /// CONTIENE EL SUB-MEN� PARA GESTIONAR LAS PELICULAS
#include "MenuClientes.h" /// CONTIENE EL SUB-MEN� PARA GESTIONAR LOS CLIENTES
#include "MenuVentas.h" /// CONTIENE EL SUB-MEN� PARA GESTIONAR LAS VENTAS
#include "MenuConfiguracion.h" /// CONTIENE EL MEN� CONFIGURACI�N
#include "MenuReportes.h" /// CONTIENE EL MEN� DE LOS REPORTES


/// ------------------------------------------ [ MEN� PRINCIPAL ] ------------------------------------------

int main(){

    system("COLOR fd"); /// COLOR DE FONDO Y COLOR DE LETRAS --> | f -> FONDO BLANCO | d -> LETRA PURPURA FUERTE |
    int Contra, Intentos = 0;
    VendedorArchi ArchiVendedor;

    /// VERIFICADOR DE CONTRASE�A

    do{

        if( Intentos == 3 ){
            cout<<"[+] HAS INTENTADO MUCHAS VECES...";
            return -1;
        }

        cout<<"[+] INGRESE EL PIN DE ACCESO: "; cin>>Contra;
        Intentos++;

    }while( !ArchiVendedor.VerificarContrasenia(Contra) );

    /// PROGRAMA PRINCIPAL

    int Opc; /// VARIABLE "OPCI�N", UTILIZADA PARA EL SWITCH

    while(true){

        system("cls");

        cout<<"\t\t-------------------------------------------------"<<endl;
        cout<<"|--------------|\t\t  MENU PRINCIPAL\t\t |"<<endl;
        cout<<"|\t\t-------------------------------------------------"<<endl;
        cout<<"|\n|-------[1] - GESTIONAR PELICULAS"<<endl;
        cout<<"|-------[2] - GESTIONAR CLIENTES"<<endl;
        cout<<"|-------[3] - GESTIONAR VENTAS"<<endl;
        cout<<"|-------[4] - MENU REPORTES"<<endl;
        cout<<"|-------[5] - CONFIGURACION"<<endl;
        cout<<"|-------[0] - CERRAR EL PROGRAMA"<<endl;

        cout<<"\n [+] INGRESE UNA OPCION: "; cin>>Opc;

        system("cls");

        switch(Opc){
            case 1:
                MenuPeliculas(); /// ACCEDE AL MEN� PEL�CULAS
                break;
            case 2:
                MenuClientes(); /// ACCEDE AL MEN� CLIENTES
                break;
            case 3:
                MenuVentas(); /// ACCEDE AL MEN� VENTAS
                break;
            case 4:
                MenuReportes(); /// ACCEDE AL MEN� REPORTES
                break;
            case 5:
                MenuConfiguracion(); /// ACCEDE AL MEN� CONFIGURACI�N
                break;
            case 0:
                return 0; /// FINALIZA EL PROGRAMA
            default:
                cout<<"\n[+] HAS INGRESADO UNA OPCION INCORRECTA... VUELVE A INTENTARLO"<<endl<<endl;
                system("pause");
                break;
        }

    }

}
