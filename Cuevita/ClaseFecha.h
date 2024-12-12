#ifndef CLASEFECHA_H_INCLUDED
#define CLASEFECHA_H_INCLUDED

class Fecha{
private:
    int _Dia, _Mes, _Anio;

public:

    /// SETTER

    void setDia(int D){ if(D>0 && D<=30){ _Dia = D;} else{_Dia = 0;}}
    void setMes(int M){ if(M>0 && M<=12) {_Mes = M;} else {_Mes=0;} }
    void setAnio(int A){ _Anio = A; }

    /// GETTER

    int getDia(){ return _Dia; }
    int getMes(){ return _Mes; }
    int getAnio(){ return _Anio; }

    /// MÉTODOS

    void Cargar();
    void Mostrar(){ cout<<_Dia<<"/"<<_Mes<<"/"<<_Anio<<endl; };

};

/// ------------------------------------------ [ MÉTODOS DE LA CLASE ] ------------------------------------------

void Fecha::Cargar(){

    int dia,mes;

    cout<<"DIA, MES, ANIO: "; cin>>dia>>mes>>_Anio;

    setDia(dia);
    setMes(mes);

}


#endif // CLASEFECHA_H_INCLUDED
