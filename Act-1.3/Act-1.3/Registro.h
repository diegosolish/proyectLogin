//
//  Registro.h
//  Act-1.3
//
//  Created by Diego Solis on 9/8/20.
//  Copyright © 2020 Diego Solis. All rights reserved.
//

#ifndef Registro_h
#define Registro_h

struct Registro{
    string mes;
    int dia;
    string hora;
    string ipAddress;
    string fallo;
    
    Registro() {
        
    }
    
    Registro(string mes, int dia, string hora, string ipAddress, string fallo) {
        this-> mes = mes;
        this-> dia = dia;
        this-> hora = hora;
        this-> ipAddress = ipAddress;
        this-> fallo = fallo;
    }
    int fechaCompleta();
    string imprimeInformacion();
    
};

int Registro::fechaCompleta() { // Regresa un tipo de ID el cual incluye el mes, dia, hora, minuto y segundo
    map<string, int> meses = { {"Ene",1}, {"Feb",2}, {"Mar",3}, {"Abr",4}, {"May",5},  {"Jun",6}, {"Jul",7}, {"Aug",8}, {"Sep",9}, {"Oct",10}, {"Nov",11}, {"Dic",12}};
    int mesF = meses.find(mes)-> second * 100000000; // Se busca número de mes en map 'meses'
    int diaF = dia * 1000000;
    int horaF = stoi(hora.substr(0,2)) * 10000;
    int minutoF = stoi(hora.substr(3,2)) * 100;
    int segundoF = stoi(hora.substr(6,2));
    int horaLarga = mesF + diaF + horaF + minutoF + segundoF; // Id de fecha; este valor es único
    
    return horaLarga;
}

string Registro::imprimeInformacion() { // Imprimir mi información
    return  mes + " " + to_string(dia) + " " + hora + " " + ipAddress + " " + fallo;
}

#endif /* Registro_h */
