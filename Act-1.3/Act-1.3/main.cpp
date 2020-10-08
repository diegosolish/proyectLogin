//
//  main.cpp
//  Act-1.3
//
//  Created by Diego Solis on 9/7/20.
//  Copyright © 2020 Diego Solis. All rights reserved.
//

#include <iostream>
using namespace std;
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <cstring>
#include <map>
#include <sstream>
#include "Registro.h"


void cargaArchivo(vector<Registro> &listaDeDatos) {
    string mes, hora, ipAddress, fallo;
    int dia;
    ifstream archivoEntrada;
    
    archivoEntrada.open("Bitacora.txt");
    while(archivoEntrada >> mes >> dia >> hora >> ipAddress) { // Lee toda la información
        getline(archivoEntrada, fallo); // Leer el mensaje de error de login
        fallo.erase(fallo.begin());
        
        listaDeDatos.push_back(Registro(mes, dia, hora, ipAddress, fallo)); // Se agrega a vector tipo Registro
    }
    archivoEntrada.close();
}


void ordenaArchivo(vector<Registro> &lista) {
    // Ordena mi archivo; Bubble sort algorithm
    for (int i = 0; i < lista.size() - 1; i++) {
        for (int j = 0; j < lista.size() - i - 1; j++) {
            if (lista[j].fechaCompleta() > lista[j+1].fechaCompleta()) {
                swap(lista[j + 1], lista[j]);
            }
        }
    }
}


int encuentraFechasUsuario(vector <Registro> totales, Registro busca) {
    // Encuentra límites ingresados por usuario
    // Se llama dos veces; fecha inicial y fecha final
    // Binary search
    int temp = 0;
    if (busca.fechaCompleta() > totales[totales.size()-1].fechaCompleta()) {
        return (int) totales.size()-1;
    } else {
        int inferior = 0;
        int superior = (int) totales.size()-1;
        while(inferior <= superior) {
            int centro = (inferior + superior) / 2;
            if (busca.fechaCompleta() > totales[centro].fechaCompleta()) {
                inferior = centro + 1;
                temp = inferior;
            } else if(busca.fechaCompleta() < totales[centro].fechaCompleta()) {
                superior = centro -1;
                temp = superior;
            } else {
                return centro; // Regresa la posición
            }
        }
    }
    
    return temp;
}

void imprimeResultados(vector<Registro> lista, int inicio, int fin) {
    cout << endl << "Información dentro del rango: " << endl;
    for (int i = inicio + 1; i < fin; i++) {
        cout << lista[i].imprimeInformacion() << endl; // muestra la información con método de struct
    }
    
}

void generaArchivoSalida(vector<Registro> lista) {
    ofstream archivoFinal;
    archivoFinal.open("BitacoraFin.txt");
    for (int i = 0; i < lista.size(); i++) {
        archivoFinal << lista[i].imprimeInformacion() << endl; // Agregar rango de datos en nuevo archivo
    }
    archivoFinal.close();
}

void solicitaFechasUsuario(vector<Registro> &lista, Registro &usuarioInic, Registro &usuarioFin) {
    int diaInicio, diaFinal;
    string mesInicio, mesFinal, horaInicial, horaFinal, hora, min, seg;
    cout << "~~~~~~~~~~~~~~~~~~ Rango de fechas ~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Fecha de inicio: " << endl;
    cout << "Mes inicial (e.g Aug): ";
    cin >> mesInicio;
    cout << "Día inicial: ";
    cin >> diaInicio;
    cout << "Ingresar cada unidad de tiempo con dos dígitos (e.g. 02) y en formato de 24 horas" << endl;
    cout << "Hora: ";
    cin >> hora;
    cout << "Minuto: ";
    cin >> min;
    cout << "Segundo: ";
    cin >> seg;
    horaInicial = hora + ":" + min + ":" + seg;
    usuarioInic = Registro(mesInicio, diaInicio, horaInicial, "NoHay", "NoHay");
    lista.push_back(usuarioInic);
    cout << endl << "Fecha de fin: " << endl;
    cout << "Mes final (e.g Aug): ";
    cin >> mesFinal;
    cout << "Día final: ";
    cin >> diaFinal;
    cout << "Ingresar cada unidad de tiempo con dos dígitos (e.g. 02) y en formato de 24 horas" << endl;
    cout << "Hora: ";
    cin >> hora;
    cout << "Minuto: ";
    cin >> min;
    cout << "Segundo: ";
    cin >> seg;
    horaFinal = hora + ":" + min + ":" + seg;
    usuarioFin = Registro(mesFinal, diaFinal, horaFinal, "NoHay", "NoHay");
    lista.push_back(usuarioFin);
}

int main() {
    Registro usuarioInic;
    Registro usuarioFin;
    vector<Registro> listaDeDatos;
    
    cargaArchivo(listaDeDatos);
    solicitaFechasUsuario(listaDeDatos, usuarioInic, usuarioFin);
    ordenaArchivo(listaDeDatos);
    
    int PosicIncio = encuentraFechasUsuario(listaDeDatos, usuarioInic);
    int PosicFinal = encuentraFechasUsuario(listaDeDatos, usuarioFin);
    
    imprimeResultados(listaDeDatos, PosicIncio, PosicFinal);
    generaArchivoSalida(listaDeDatos);
    return 0;
}

