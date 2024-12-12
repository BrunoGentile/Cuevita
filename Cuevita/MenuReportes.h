#ifndef MENUREPORTES_H_INCLUDED
#define MENUREPORTES_H_INCLUDED

int MenuReportes(){

    int Opc;

    while(true){

        system("cls");

        cout<<"\t\t-------------------------------------------------"<<endl;
        cout<<"|--------------|\t\t  MENU REPORTES\t\t\t |"<<endl;
        cout<<"|\t\t-------------------------------------------------"<<endl;
        cout<<"|\n|-------[1] - MOSTRAR LA PELICULA MAS VENDIDA"<<endl;
        cout<<"|-------[2] - FILTRAR VENTAS POR MES"<<endl;
        cout<<"|-------[3] - FILTRAR CANTIDAD DE VENTAS POR ID CLIENTE"<<endl;
        cout<<"|-------[4] - MOSTRAR LA PELICULA CON MAS STOCK"<<endl;
        cout<<"|-------[5] - MOSTRAR CLIENTES CON MAS DE 25 ANIOS"<<endl;
        cout<<"|-------[6] - MOSTRAR LAS PELICULAS QUE NO SE VENDIERON"<<endl;
        cout<<"|-------[7] - MOSTRAR LA CANTIDAD DE VENTAS POR CLIENTE"<<endl;
        cout<<"|-------[8] - MOSTRAR LAS PELICULAS SIN STOCK ACTUALMENTE"<<endl;
        cout<<"|-------[0] - VOLVER AL MENU PRINCIPAL"<<endl;

        cout<<"\n [+] INGRESE UNA OPCION: "; cin>>Opc;

        system("cls");

        switch(Opc){
            case 1:{

                int TotalRegistros_Peli, *VPeliculas;

                PeliculaArchi ArchiPelicula;
                VentasArchi ArchiVentas;

                TotalRegistros_Peli = ArchiPelicula.ObtenerRegistros();

                VPeliculas = new int[TotalRegistros_Peli]; /// DECLARO VECTOR DINÁMICO
                InicializarCero(VPeliculas,TotalRegistros_Peli); /// INICIALIZO TODO EL VECTOR DINÁMICO EN 0

                ArchiVentas.CargaVentas(VPeliculas); /// CARGO LAS VENTAS EN EL VECTOR DINÁMICO

                int IDMasVendida = -1, MayorCant = 0;

                for(int i = 0; i<TotalRegistros_Peli; i++){

                    if( MayorCant < VPeliculas[i] ){
                        IDMasVendida = i + 1;
                        MayorCant = VPeliculas[i];
                    }

                }
                if (IDMasVendida < 0){ cout<<"NO HAY VENTAS"<<endl; } else{
                cout<<"[+] EL ID DE LA PELICULA MAS VENDIDA ES: "<<IDMasVendida<<endl<<endl;};

                ArchiPelicula.MostrarNombreMasVendida(IDMasVendida);


                delete[] VPeliculas; /// LIBERO MEMORIA

                system("pause");
                break;
            }
            case 2: {

                int Mes;
                VentasArchi ArchiVentas;


                cout<<"INGRESE EL MES: ";
                cin>>Mes;

                if (Mes<1 || Mes>12)
                {
                    cout<<"El numero ingresado no equivale a un numero de mes"<<endl;
                    system("pause");
                    break;
                }

                ArchiVentas.ObtenerRegistroXMes( Mes ); /// HACER

                system("pause");
                break;
            }
            case 3: {

                VentasArchi ArchiVentas;

                int ID;
                cout<<"INGRESE EL ID DEL CLIENTE: "; cin>>ID;

                ArchiVentas.MostrarVentaXCliente(ID);


                system("pause");
                break;
            }
            case 4:{

                PeliculaArchi archivoPeliculas;

                archivoPeliculas.MostrarPeliculaConMasStock();

                system("pause");

                break;
            }
            case 5:{

                PersonaArchi archivoCliente;

                archivoCliente.mostrarClientesMas25();

                cout<<endl;

                system("pause");

            break;
            }
            case 6:{
                VentasArchi ventas;
                ventas.MostrarPeliculasNoVendidas();
                cout<<endl;
                system("pause");


            break;
            }
            case 7: {

                VentasArchi ventasArchivo;
                ventasArchivo.MostrarVentasPorCliente();
                cout<<endl;
                system("pause");

                break;

            }

            case 8: {
                PeliculaArchi ArchivoPeliculas;
                ArchivoPeliculas.MostrarPeliculasSinStock();
                cout<<endl;
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

#endif // MENUREPORTES_H_INCLUDED
