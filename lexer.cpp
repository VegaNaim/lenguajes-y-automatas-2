/*****************************************
LENGUAJES Y AUTÓMATAS II
GRUPO; 6A
DOCENTE; MARIBEL BUENO QUIÑONES
EQUIPO; 8
INTEGRANTES;
LEÓN LICEA JAFET GUIVANNI
RUIZ JAIME MATEO
VEGA LEDESMA NAIM
ETAPA 1 - 18-09-2026 - ETAPA 1 DEL PROYECTO FINAL
*****************************************/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int obtenerCategoria(char);
void Automata_Aritmetico(string);

int main() {   
    string nombre_archivo = "pruebas.txt";
    int opcion = -1;

    do {
        cout << "\n========================================" << endl;
        cout << "          MENU            " << endl;
        cout << "========================================" << endl;
        cout << "1. Evaluar 'pruebas.txt'" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                ifstream archivo(nombre_archivo);
                
                if (!archivo.is_open()) {
                    cout << "\nERROR: No se pudo abrir '" << nombre_archivo << "'. Asegurase de que el txt este en la misma carpeta que el ejecutable." << endl;
                    break;
                }

                string linea;
                bool archivo_tiene_datos = false;

                cout << "\n=== PROCESANDO ARCHIVO: " << nombre_archivo << " ===" << endl;
                
                while (getline(archivo, linea)) {
                    if (!linea.empty()) {
                        archivo_tiene_datos = true;
                        Automata_Aritmetico(linea);
                    }
                }

                if (!archivo_tiene_datos) {
                    cout << "\nEl archivo esta completamente vacio. No hay nada que evaluar." << endl;
                }
                
                archivo.close();
                break;
            }
            case 0:
                cout << "\nSaliendo del programa..." << endl;
                break;

            default:
                cout << "\nOpcion invalida. Por favor, ingrese 1 para ejecutar o 0 para salir." << endl;
                break;
        }

    } while (opcion != 0);

    return 0;
}

int obtenerCategoria(char c) {
    char L[52] = {
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };
    char N[10] = {'0','1','2','3','4','5','6','7','8','9'};
    char Guion[1] = {'_'};
    char Esp[4] = {' ', '\t', '\n', '\r'};
    char Ig[1] = {'='};
    char Op[4] = {'+', '-', '*', '/'};
    char Pto[1] = {'.'};
    char PIzq[1] = {'('};
    char PDer[1] = {')'};
    char PyC[1] = {';'};

    for (int col = 0; col < 52; col++) { if (L[col] == c) return 0; }       // 0: Letra
    for (int col = 0; col < 10; col++) { if (N[col] == c) return 1; }       // 1: Digito
    for (int col = 0; col < 1; col++)  { if (Guion[col] == c) return 2; }   // 2: [_]
    for (int col = 0; col < 4; col++)  { if (Esp[col] == c) return 3; }     // 3: [\s]
    for (int col = 0; col < 1; col++)  { if (Ig[col] == c) return 4; }      // 4: [=]
    for (int col = 0; col < 4; col++)  { if (Op[col] == c) return 5; }      // 5: Operador
    for (int col = 0; col < 1; col++)  { if (Pto[col] == c) return 6; }     // 6: [.]
    for (int col = 0; col < 1; col++)  { if (PIzq[col] == c) return 7; }    // 7: [(]
    for (int col = 0; col < 1; col++)  { if (PDer[col] == c) return 8; }    // 8: [)]
    for (int col = 0; col < 1; col++)  { if (PyC[col] == c) return 9; }     // 9: [;]
    
    return 10; // 10: (Error)
}

void Automata_Aritmetico(string cadena) {    
    int ID[19][11] = {
//        L   D   _  \s   =  Op   .   (   )   ; Otro
        { 1, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18 }, // Estado 0  (q0)
        { 1,  1,  1,  2,  3, 18, 18, 18, 18, 18, 18 }, // Estado 1  (q1)
        {18, 18, 18,  2,  3, 18, 18, 18, 18, 18, 18 }, // Estado 2  (q2)
        { 4,  5, 18,  3, 18, 18, 18,  8, 18, 18, 18 }, // Estado 3  (q3)
        { 4,  4,  4, 10, 18, 13, 18, 18, 11, 17, 18 }, // Estado 4  (q4)
        {18,  5, 18, 10, 18, 13,  6, 18, 11, 17, 18 }, // Estado 5  (q5)  
        {18,  7, 18, 18, 18, 18, 18, 18, 18, 18, 18 }, // Estado 6  (q6)
        {18,  7, 18, 10, 18, 13, 18, 18, 11, 17, 18 }, // Estado 7  (q7)  
        { 4,  5, 18,  8, 18, 18, 18,  8, 18, 18, 18 }, // Estado 8  (q8)
        { 4,  5, 18,  9, 18, 18, 18,  8, 18, 18, 18 }, // Estado 9  (q9)
        {18, 18, 18, 10, 18, 13, 18, 18, 11, 17, 18 }, // Estado 10 (q10)
        {18, 18, 18, 11, 18, 13, 18, 18, 11, 17, 18 }, // Estado 11 (q11)
        {18, 18, 18, 12, 18, 13, 18, 18, 11, 17, 18 }, // Estado 12 (q12)
        { 4,  5, 18, 14, 18, 18, 18, 15, 18, 18, 18 }, // Estado 13 (q13) 
        { 4,  5, 18, 14, 18, 18, 18, 15, 18, 18, 18 }, // Estado 14 (q14)
        { 4,  5, 18, 15, 18, 18, 18,  8, 18, 18, 18 }, // Estado 15 (q15)
        { 4,  5, 18, 16, 18, 18, 18,  8, 18, 18, 18 }, // Estado 16 (q16)
        {18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18 }, // Estado 17 (qF)
        {18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18 }  // Estado 18 (qE)
    };

    int estado_actual = 0;

    cout << "\nEvaluando: " << cadena << endl;
    
    if (cadena.empty()) {
        cout << "\n--- ANALISIS COMPLETADO ---" << endl;
        cout << "RESULTADO: [RECHAZADO]" << endl;
        cout << "La entrada no contiene ningun caracter." << endl;
        return;
    }

    cout << "LEXEMA\t\tTOKEN" << endl;
    cout << "-----------------------" << endl;

    int longitudcadena = cadena.length();
    for (int i = 0; i < longitudcadena; i++) {
        char caracter_actual = cadena[i];
        int cat_actual = obtenerCategoria(caracter_actual);
        estado_actual = ID[estado_actual][cat_actual];
        if (cat_actual == 0) {
            cout << caracter_actual << "\t\t[IDEVAR]" << endl;
        }
        if (cat_actual == 1) {
            cout << caracter_actual << "\t\t[INTNUM]" << endl;
        }
        if (cat_actual == 2) {
            cout << caracter_actual << "\t\t[SYMGUI]" << endl;
        }
        if (cat_actual == 3) {
            cout << caracter_actual << "\t\t[VOIDSP]" << endl;
        }
        if (cat_actual == 4) {
            cout << caracter_actual << "\t\t[SYMASG]" << endl;
        }
        if (cat_actual == 5) {
            cout << caracter_actual << "\t\t[SYMOPR]" << endl;
        }
        if (cat_actual == 6) {
            cout << caracter_actual << "\t\t[SYMPUN]" << endl;
        }
        if (cat_actual == 7) {
            cout << caracter_actual << "\t\t[PARIZQ]" << endl;
        }
        if (cat_actual == 8) {
            cout << caracter_actual << "\t\t[PARDER]" << endl;
        }
        if (cat_actual == 9) {
            cout << caracter_actual << "\t\t[DELPYC]" << endl;
        } 
        if (cat_actual == 10) {
            cout << caracter_actual << "\t\t[ERRLEX]" << endl;
        }
    }

    cout << "\n--- ANALISIS COMPLETADO ---" << endl;
    if (estado_actual == 17) {
        cout << "RESULTADO: [ACEPTADO]" << endl;
        cout << "La entrada \"" << cadena << "\" es una operacion valida." << endl;
        cout << "Estado final: qF (" << estado_actual << ")" << endl;
    } 
    else if (estado_actual == 18) {	
        cout << "RESULTADO: [RECHAZADO]" << endl;
        cout << "La entrada \"" << cadena << "\" contiene errores de sintaxis (Estado trampa qE)." << endl;
        cout << "Estado final: " << estado_actual << endl;
    }
    else {	
        cout << "RESULTADO: [RECHAZADO]" << endl;
        cout << "La entrada \"" << cadena << "\" no alcanzo un estado de aceptacion." << endl;
        cout << "Estado final: q" << estado_actual << endl;
    }
}
