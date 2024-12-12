#ifndef MENUPELICULAS_H_INCLUDED
#define MENUPELICULAS_H_INCLUDED

int MenuPeliculas()
{

    int Opc; /// VARIABLE "OPCIÓN", UTILIZADA PARA EL SWITCH

    while(true)
    {

        system("cls");

        cout<<"\t\t-------------------------------------------------"<<endl;
        cout<<"|--------------|\t\t  MENU PELICULAS\t\t |"<<endl;
        cout<<"|\t\t-------------------------------------------------"<<endl;
        cout<<"|\n|-------[1] - CARGAR PELICULAS"<<endl;
        cout<<"|-------[2] - MOSTRAR TODAS LAS PELICULAS"<<endl;
        cout<<"|-------[3] - FILTRAR PELICULAS POR ID"<<endl;
        cout<<"|-------[4] - ELIMINAR PELICULA POR ID"<<endl;
        cout<<"|-------[5] - AUMENTAR STOCK DE PELICULA POR ID"<<endl;
        cout<<"|-------[6] - FILTRAR PELICULA POR GENERO"<<endl;
        cout<<"|-------[7] - FILTRAR PELICULA POR TITULO"<<endl;
        cout<<"|-------[8] - FILTRAR PELICULAS ENTRE DOS RANGOS DE ID"<<endl;
        cout<<"|-------[9] - FILTRAR PELICULAS POR BUSQUEDA DE LETRAS(TITULOS)"<<endl;
        cout<<"|-------[0] - VOLVER AL MENU PRINCIPAL"<<endl;

        cout<<"\n [+] INGRESE UNA OPCION: ";
        cin>>Opc;

        system("cls");

        switch(Opc)
        {
        case 1:
        {
            Pelicula obj;
            obj.Cargar();

            PeliculaArchi ArchiPelicula; /// OBJETO ARCHIVO CLIENTE ( TRABAJA SOBRE EL ARCHIVO )

            if( ArchiPelicula.Cargar(obj) )
            {

                cout<<"\n[+] PELICULA CARGADA"<<endl;
                system("pause");

            }
            else
            {
                cout<<"\n[+] NO SE PUDO CARGAR LA PELICULA"<<endl;
            }

            break;
        }
        case 2:
        {

            PeliculaArchi ArchPelicula;

            ArchPelicula.Mostrar();
            break;
        }
        case 3:
        {
            int IDPelicula;
            PeliculaArchi ArchPelicula;

            cout<<"INGRESE EL ID DE LA PELICULA: ";
            cin>>IDPelicula;
            cout<<endl;

            if( IDPelicula <= 0 )
            {
                cout<<"[+] EL ID INGRESADO NO ES VALIDO"<<endl;
            }
            else
            {
                ArchPelicula.FiltrarPelicula(IDPelicula);
            }

            cout<<endl;
            system("pause");
            break;
        }
        case 4:
        {

            int IDPelicula;
            PeliculaArchi ArchPelicula;

            cout<<"INGRESE EL ID DE LA PELICULA A ELIMINAR: ";
            cin>>IDPelicula;

            if( ArchPelicula.EliminarPelicula(IDPelicula) ) cout<<"[+] PELICULA ELIMINADA"<<endl;
            else cout<<"[+] NO PUDO ELIMINARSE LA PELICULA... "<<endl;

            system("pause");
            break;

        }
        case 5:
        {
            int IDPelicula;
            int AgregarStock;

            cout<< "INGRESE EL ID DE LA PELICULA: "<<endl;
            cin>> IDPelicula;

            PeliculaArchi ArchPelicula;

            if (!ArchPelicula.ExisteID(IDPelicula))
            {
                cout << "EL ID INGRESADO NO EXISTE EN EL SISTEMA. NO SE PUEDE AGREGAR STOCK." << endl;
                system("pause");
                break; // Salir del caso si el ID no existe
            }

            cout << "INGRESE LA CANTIDAD DE STOCK A AGREGAR: ";
            cin >> AgregarStock;

            if (ArchPelicula.StockAgregar(IDPelicula, AgregarStock))
            {
                cout << "STOCK AGREGADO CORRECTAMENTE" << endl;
            }
            else
            {
                cout << "NO SE PUDO AGREGAR EL STOCK" << endl;
            }

            system("pause");
            break;

        }
        case 6:
        {

            PeliculaArchi ArchivoPelicula;

            char _genero[30];

            cout<<"Ingrese el genero de la pelicula: "<<endl;

            CargarCadena(_genero,30);

            ArchivoPelicula.FiltrarPorGenero(_genero);

            cout<<endl;

            system("pause");


            break;
        }
        case 7:
        {
            PeliculaArchi ArchivoPelicula;
            char _titulo[30];

            cout<<"Ingrese el titulo de la pelicula: "<<endl;

            CargarCadena(_titulo,30);

            ArchivoPelicula.FiltrarPorTitulo(_titulo);

            cout<<endl;

            system("pause");

            break;
        }
        case 8:
        {

            PeliculaArchi ArchivoPelicula;

            int idPelicula1, idPelicula2;

            // Solicitar el primer ID y verificar su existencia
            cout << "Ingrese el primer ID de la pelicula: " << endl;
            cin >> idPelicula1;

            if (!ArchivoPelicula.ExisteID(idPelicula1))
            {
                cout << "El primer ID ingresado no existe en el sistema." << endl;
                system("pause");
                break; // Salimos del caso si el ID no es válido
            }

            // Solicitar el segundo ID si el primero es válido
            cout << "Ingrese el segundo ID de la pelicula: " << endl;
            cin >> idPelicula2;

            if (!ArchivoPelicula.ExisteID(idPelicula2))
            {
                cout << "El segundo ID ingresado no existe en el sistema." << endl;
                system("pause");
                break; // Salimos del caso si el segundo ID no es válido
            }

            // Si ambos IDs existen, procedemos a filtrar
            ArchivoPelicula.FiltrarPorRango(idPelicula1, idPelicula2);

            cout << endl;

            system("pause");

            break;
        }
        case 9:
        {
            PeliculaArchi ArchivoPelicula;

            // Definimos el prefijo que se ingresará con espacios
            char prefijo[100];

            cout << "Ingrese la/s letra/s para filtrar las peliculas (puede incluir espacios): ";
            CargarCadena(prefijo, 100); // Usamos la función CargarCadena para permitir espacios

            ArchivoPelicula.FiltrarPeliculaPorPrefijo(prefijo); // Llamamos al método FiltrarPeliculaPorPrefijo

            system("pause");
            break;
        }


        case 0:
            return 0;
            break;
        default:
            cout<<"\n[+] HAS INGRESADO UNA OPCION INCORRECTA... VUELVE A INTENTARLO"<<endl<<endl;
            system("pause");
            break;
        }

    }

}

#endif // MENUPELICULAS_H_INCLUDED
