#ifndef MENUCLIENTES_H_INCLUDED
#define MENUCLIENTES_H_INCLUDED

int MenuClientes(){

    int Opc; /// VARIABLE "OPCIÓN", UTILIZADA PARA EL SWITCH

    while(true){

        system("cls");

        cout<<"\t\t-------------------------------------------------"<<endl;
        cout<<"|--------------|\t\t  MENU CLIENTES\t\t\t |"<<endl;
        cout<<"|\t\t-------------------------------------------------"<<endl;
        cout<<"|\n|-------[1] - CARGAR CLIENTE"<<endl;
        cout<<"|-------[2] - MOSTRAR CLIENTES"<<endl;
        cout<<"|-------[3] - FILTRAR CLIENTE POR ID"<<endl;
        cout<<"|-------[4] - ELIMINAR CLIENTE POR ID"<<endl;
        cout<<"|-------[5] - AGREGAR CREDITO A CLIENTE POR ID"<<endl; /// HACER
        cout<<"|-------[6] - FILTRAR CLIENTE POR APELLIDO"<<endl;
        cout<<"|-------[7] - AGREGAR CREDITO POR APELLIDO"<<endl;
        cout<<"|-------[8] - FILTRAR CLIENTES POR DOS RANGOS DE ID"<<endl;
        cout<<"|-------[9] - FILTRAR CLIENTES POR BUSQUEDA DE LETRAS(APELLIDOS)"<<endl;
        cout<<"|-------[0] - VOLVER AL MENU PRINCIPAL"<<endl;

        cout<<"\n [+] INGRESE UNA OPCION: "; cin>>Opc;

        system("cls");

        switch(Opc){
            case 1: {

                Cliente Comprador;
                Comprador.Cargar();

                PersonaArchi ArchCliente; /// OBJETO ARCHIVO CLIENTE ( TRABAJA SOBRE EL ARCHIVO )

                if( ArchCliente.Escribir(Comprador) ){

                    cout<<"\n[+] CLIENTE CARGADO"<<endl;


                }else{ cout<<"\n[+] NO SE PUDO CARGAR EL CLIENTE"<<endl; }

                system("pause");
                break;
            }
            case 2: {

                PersonaArchi ArchCliente;

                ArchCliente.Mostrar();

                break;
            }
            case 3: {

                int IDCliente;
                PersonaArchi ArchCliente;

                cout<<"INGRESE EL ID DEL CLIENTE: "; cin>>IDCliente;
                cout<<endl;

                if( IDCliente <= 0 ){ cout<<"[+] EL ID INGRESADO NO ES VALIDO"<<endl; }
                else { ArchCliente.FiltrarCliente(IDCliente); }

                system("pause");

                break;
            }
            case 4:{

                int IDCliente;
                PersonaArchi ArchCliente;

                cout<<"INGRESE EL ID DEL CLIENTE QUE DESEA ELIMINAR: "; cin>>IDCliente;

                if( ArchCliente.EliminarCliente(IDCliente) ) cout<<"[+] CLIENTE ELIMINADO"<<endl;
                else cout<<"[+] NO PUDO ELIMINARSE EL CLIENTE... "<<endl;

                system("pause");
                break;
            }
            case 5: {
                int IDCliente;
                float CreditoAgregar;

                PersonaArchi ArchCliente;

                cout << "INGRESE EL ID DEL CLIENTE: ";
                cin >> IDCliente;

                if (!ArchCliente.ExisteID(IDCliente))
                {
                    cout << "EL ID INGRESADO NO EXISTE EN EL SISTEMA." << endl;
                    system("pause");
                    break;
                }

                // Solo si el ID es válido, pedimos el crédito a agregar
                cout << "INGRESE EL CREDITO A AGREGAR: ";
                cin >> CreditoAgregar;

                if (ArchCliente.AgregarCredito(IDCliente, CreditoAgregar))
                {
                    cout << "CREDITO AGREGADO CORRECTAMENTE." << endl;
                }
                else
                {
                    cout << "ERROR: NO SE PUDO AGREGAR EL CREDITO." << endl;
                }

                system("pause");
                break;
            }
            case 6: {

            PersonaArchi ArchivoCliente;

            char _apellido[30];

            cout<<"Ingrese el apellido: "<<endl;
            CargarCadena(_apellido,30);

            ArchivoCliente.FiltrarPorApellido(_apellido);

            cout<<endl;

            system("pause");


            break;
            }

        case 7: {

                char apellido[50];
                cout << "Ingrese el apellido del cliente: ";
                cin >> apellido;

                PersonaArchi archivoClientes;
                archivoClientes.AgregarStockPorApellido(apellido);

                cout<<endl;

                system("pause");

            break;
            }
            case 8:
            {

                PersonaArchi ArchivoPersona;

                int idCliente1, idCliente2;

                // Solicitar el primer ID y verificar su existencia
                cout << "Ingrese el primer ID del cliente: " << endl;
                cin >> idCliente1;

                if (!ArchivoPersona.ExisteID(idCliente1))
                {
                    cout << "El primer ID ingresado no existe en el sistema." << endl;
                    system("pause");
                    break; // Salimos del caso si el ID no es válido
                }

                // Solicitar el segundo ID si el primero es válido
                cout << "Ingrese el segundo ID del cliente: " << endl;
                cin >> idCliente2;

                if (!ArchivoPersona.ExisteID(idCliente2))
                {
                    cout << "El segundo ID ingresado no existe en el sistema." << endl;
                    system("pause");
                    break; // Salimos del caso si el segundo ID no es válido
                }

                // Si ambos IDs existen, procedemos a filtrar
                ArchivoPersona.FiltrarClientePorRango(idCliente1, idCliente2);

                cout << endl;

                system("pause");

                break;
            }
        case 9: { // Filtrar clientes por prefijo de apellido
                char prefijo[100];

                PersonaArchi ArchivoPersona;

                cout << "Ingrese la/s letra/s del apellido que desea filtrar: ";
                CargarCadena(prefijo, 100);  // Usamos CargarCadena para permitir espacios

                ArchivoPersona.FiltrarClientePorPrefijo(prefijo);

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

#endif // MENUCLIENTES_H_INCLUDED
