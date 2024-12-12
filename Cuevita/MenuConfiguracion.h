#ifndef MENUCONFIGURACION_H_INCLUDED
#define MENUCONFIGURACION_H_INCLUDED

int MenuConfiguracion(){

    int Opc;

    while(true){

        system("cls");

        cout<<"\t\t-------------------------------------------------"<<endl;
        cout<<"|--------------|\t\t  MENU CONFIGURACION\t\t |"<<endl;
        cout<<"|\t\t-------------------------------------------------"<<endl;
        cout<<"|\n|-------[1] - REESTABLECER TODO"<<endl;
        cout<<"|-------[2] - HACER BACKUP"<<endl;
        cout<<"|-------[3] - OBTENER DATOS DEL PROPIETARIO"<<endl;
        cout<<"|-------[4] - MODIFICAR CLAVE"<<endl;
        cout<<"|-------[0] - VOLVER AL MENU PRINCIPAL"<<endl;

        cout<<"\n [+] INGRESE UNA OPCION: "; cin>>Opc;

        system("cls");

        switch(Opc){
            case 1: {
                RestablecerTodo();
                system("pause");
                break;
            }
            case 2: {

                PersonaArchi ArchiPersona;
                PeliculaArchi ArchiPelicula;

                ArchiPersona.BackUp();
                ArchiPelicula.BackUp();

                cout<<"[+] BACKUP FINALIZADO"<<endl<<endl;
                system("pause");
                break;
            }
            case 3: {

                VendedorArchi ArchiVendedor;

                ArchiVendedor.MostrarDatosPropietario();

                system("pause");
                break;
            }
            case 4:{

                VendedorArchi ArchiVendedor;
                int Clave;

                cout<<"INGRESE LA NUEVA CLAVE: "; cin>>Clave;

                ArchiVendedor.ModificarClave(Clave);

                system("Pause");
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

#endif // MENUCONFIGURACION_H_INCLUDED
