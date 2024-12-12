#ifndef MENUVENTAS_H_INCLUDED
#define MENUVENTAS_H_INCLUDED

int MenuVentas(){

    int Opc; /// VARIABLE "OPCIÓN", UTILIZADA PARA EL SWITCH

    while(true){

        system("cls");

        cout<<"\t\t-------------------------------------------------"<<endl;
        cout<<"|--------------|\t\t   MENU VENTAS\t\t\t |"<<endl;
        cout<<"|\t\t-------------------------------------------------"<<endl;
        cout<<"|\n|-------[1] - REGISTRAR NUEVA VENTA"<<endl;
        cout<<"|-------[2] - MOSTRAR TODAS LAS VENTAS"<<endl;
        cout<<"|-------[3] - ELIMINAR VENTA"<<endl; /// HACER
        cout<<"|-------[4] - FILTRAR VENTA POR ID"<<endl;
        cout<<"|-------[5] - FILTRAR VENTAS ENTRE DOS RANGOS DE ID"<<endl;
        cout<<"|-------[0] - VOLVER AL MENU PRINCIPAL"<<endl;

        cout<<"\n [+] INGRESE UNA OPCION: "; cin>>Opc;

        system("cls");

        switch(Opc){
            case 1:{

                /// IDC -> ID CLIENTE | IDP -> ID PELICULA
                int IDC, IDP, Cant, CantTotal;
                float Saldo, Precio;

                Venta RegistroVenta;

                PersonaArchi ArchiCliente;
                PeliculaArchi ArchiPeli;
                VentasArchi ArchiVentas;

                cout<<"INGRESE EL ID DEL CLIENTE QUE REALIZO LA COMPRA: "; cin>>IDC;
                Saldo = ArchiCliente.ObtenerSaldo(IDC); /// OBTENEMOS EL SALDO DEL CLIENTE | -1 SI EL ESTADO ES FALSO

                cout<<"INGRESE EL ID DE LA PELICULA COMPRADA: "; cin>>IDP;
                Precio = ArchiPeli.ObtenerPrecio(IDP); /// OBTENEMOS EL PRECIO DE LA PELICULA | -1 SI EL ESTADO ES FALSO

                if( Saldo < 0 || Precio < 0 ){ /// VERIFICAMOS QUE TANTO SALDO Y PRECIO NO SEAN MENORES A 0
                    cout<<"[+] LOS DATOS INGRESADOS SON INCORRECTOS"<<endl;
                }else{

                    cout<<"INGRESE LA CANTIDAD DE PELICULAS QUE DESEA COMPRAR: "; cin>>Cant;
                    CantTotal = ArchiPeli.ObtenerTotalPeliculas(IDP); /// VERIFICAMOS QUE SE CUENTE CON EL STOCK PELICULAS

                    if( RegistroVenta.Cargar(IDC,Saldo,IDP,Precio,Cant) && (Cant <= CantTotal) ){

                        if( ArchiVentas.RegistrarVenta(RegistroVenta) ){
                            Saldo -= Precio*Cant; /// ESTABLECEMOS EL NUEVO SALDO DEL CLIENTE
                            Cant = CantTotal - Cant;
                            ArchiCliente.ModificarSaldo(IDC,Saldo); /// MODIFICAMOS EL SALDO RESTANTE DEL CLIENTE
                            ArchiPeli.ModificarTotal(IDP,Cant); /// MODIFICAMOS EL STOCK RESTANTE DE LA PELICULA
                        }

                    }

                }
                system("pause");
                break;
            }
            case 2:{

                VentasArchi ArchiVentas;

                ArchiVentas.Mostrar();

                system("pause");
                break;
            }
            case 3:{

                int IDV;
                VentasArchi ArchiVentas;
                PeliculaArchi ArchiPelicula;
                PersonaArchi ArchiPersona;

                cout<<"INGRESE EL ID DE LA VENTA A ELIMINAR: "; cin>>IDV;

                ArchiVentas.Eliminar(IDV);

                /// OBTENER STOCK Y EL ID DE LA PELICULA ELIMINADA Y ALMACENARLO EN UNA VARIABLE
                int Stock = ArchiVentas.getStock(IDV);
                int IDPelicula = ArchiVentas.getIDPelicula(IDV);

                /// OBTENER IDCLIENTE Y EL SALDO Y LO ALMACENAMOS EN UNA VARIABLE
                int IDCliente = ArchiVentas.getIDCliente(IDV);
                float Saldo = ArchiVentas.getSaldo(IDV);

                /// REESTABLECER STOCK CON ESE ID Y EL SALDO
                ArchiPelicula.ReestablecerStock(IDPelicula, Stock);
                ArchiPersona.ReestablacerSaldo(IDCliente, Saldo);

                system("pause");
                break;
            }
             case 4:{

                 int IDVenta;
                VentasArchi ArchVentas;

                cout<<"INGRESE EL ID DE LA VENTA: "; cin>>IDVenta;
                cout<<endl;

                if( IDVenta <= 0 ){ cout<<" EL ID INGRESADO NO ES VALIDO"<<endl; }
                else { ArchVentas.FiltrarVentaporID(IDVenta); }

                cout<<endl;
                system("pause");
                break;

            }
            case 5:{
                VentasArchi ArchivoVentas;

                int idVenta1, idVenta2;

                // Solicitar el primer ID y verificar su existencia
                cout << "Ingrese el primer ID de la Venta: " << endl;
                cin >> idVenta1;

                if (!ArchivoVentas.ExisteID(idVenta1))
                {
                    cout << "El primer ID ingresado no existe en el sistema." << endl;
                    system("pause");
                    break; // Salimos del caso si el ID no es válido
                }

                // Solicitar el segundo ID si el primero es válido
                cout << "Ingrese el segundo ID de la Venta: " << endl;
                cin >> idVenta2;

                if (!ArchivoVentas.ExisteID(idVenta2))
                {
                    cout << "El segundo ID ingresado no existe en el sistema." << endl;
                    system("pause");
                    break; // Salimos del caso si el segundo ID no es válido
                }

                // Si ambos IDs existen, procedemos a filtrar
                ArchivoVentas.FiltrarPorRango(idVenta1, idVenta2);

                cout << endl;

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

#endif // MENUVENTAS_H_INCLUDED
