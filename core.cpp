/*****************************************
LENGUAJES Y AUTÓMATAS II
GRUPO; 6A
DOCENTE; MARIBEL BUENO QUIÑONES
EQUIPO; 8
INTEGRANTES;
LEÓN LICEA JAFET GUIVANNI
RUIZ JAIME MATEO
VEGA LEDESMA NAIM
ETAPA 2 - 18-10-2026 - ETAPA 2 DEL PROYECTO FINAL
*****************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

int obtenerCategoria(char);
string tokens(int);
int generarID(string);
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
                    cout << "\nERROR: No se pudo abrir '" << nombre_archivo << "'." << endl;
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
                    cout << "\nEl archivo esta vacio." << endl;
                }
                
                archivo.close();
                break;
            }
            case 0:
                cout << "\nSaliendo..." << endl;
                break;
            default:
                cout << "\nOpcion invalida." << endl;
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

string tokens(int c) {
    string tok[11] = {
        "[IDEVAR]", "[INTNUM]", "[SYMGUI]", "[VOIDSP]", "[SYMASG]", 
        "[SYMOPR]", "[SYMPUN]", "[PARIZQ]", "[PARDER]", "[DELPYC]", "[ERRLEX]"
    };
    return (c >= 0 && c <= 10) ? tok[c] : "[DESCONOCIDO]";
}

int generarID(string token) {
  
    static int c_idevar = 1, c_intnum = 1, c_dounum = 1, c_symgui = 1;
    static int c_voidsp = 1, c_symasg = 1, c_symopr = 1, c_sympun = 1;
    static int c_parizq = 1, c_parder = 1, c_delpyc = 1, c_errlex = 1;

    if (token == "RESET") {
        c_idevar = c_intnum = c_dounum = c_symgui = 1;
        c_voidsp = c_symasg = c_symopr = c_sympun = 1;
        c_parizq = c_parder = c_delpyc = c_errlex = 1;
        return 0;
    }

    if (token == "[IDEVAR]") return 1000 + c_idevar++;
    if (token == "[INTNUM]") return 2000 + c_intnum++;
    if (token == "[DOUNUM]") return 3000 + c_dounum++;
    if (token == "[SYMGUI]") return 4000 + c_symgui++;
    if (token == "[VOIDSP]") return 5000 + c_voidsp++;
    if (token == "[SYMASG]") return 6000 + c_symasg++;
    if (token == "[SYMOPR]") return 7000 + c_symopr++;
    if (token == "[SYMPUN]") return 8000 + c_sympun++;
    if (token == "[PARIZQ]") return 9000 + c_parizq++;
    if (token == "[PARDER]") return 10000 + c_parder++;
    if (token == "[DELPYC]") return 11000 + c_delpyc++;
    
    return 12000 + c_errlex++;
}

void Automata_Aritmetico(string cadena) {

    generarID("RESET");

    int ID[19][11] = {
//        L   D   _  \s   =  Op   .   (   )   ; Otro
        { 1, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18 },	//	q(0)
        { 1,  1,  1,  2,  3, 18, 18, 18, 18, 18, 18 },	//	q(1)
        {18, 18, 18,  2,  3, 18, 18, 18, 18, 18, 18 },	//	q(2)
        { 4,  5, 18,  3, 18, 18, 18,  8, 18, 18, 18 },	//	q(3)
        { 4,  4,  4, 10, 18, 13, 18, 18, 11, 17, 18 },	//	q(4)
        {18,  5, 18, 10, 18, 13,  6, 18, 11, 17, 18 },	//	q(5)
        {18,  7, 18, 18, 18, 18, 18, 18, 18, 18, 18 },	//	q(6)
        {18,  7, 18, 10, 18, 13, 18, 18, 11, 17, 18 },	//	q(7)
        { 4,  5, 18,  8, 18, 18, 18,  8, 18, 18, 18 },	//	q(8)
        { 4,  5, 18,  9, 18, 18, 18,  8, 18, 18, 18 },	//	q(9)
        {18, 18, 18, 10, 18, 13, 18, 18, 11, 17, 18 },	//	q(10)
        {18, 18, 18, 11, 18, 13, 18, 18, 11, 17, 18 },	//	q(11)
        {18, 18, 18, 12, 18, 13, 18, 18, 11, 17, 18 },	//	q(12)
        { 4,  5, 18, 14, 18, 18, 18, 15, 18, 18, 18 },	//	q(13)
        { 4,  5, 18, 14, 18, 18, 18, 15, 18, 18, 18 },	//	q(14)
        { 4,  5, 18, 15, 18, 18, 18,  8, 18, 18, 18 },	//	q(15)
        { 4,  5, 18, 16, 18, 18, 18,  8, 18, 18, 18 },	//	q(16)
        {18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18 },	//	q(17)
        {18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18 }	//	q(18)
    };

    int estado_actual = 0;
    int i = 0;
    int longitudcadena = cadena.length();

    cout << "\nEvaluando: " << cadena << endl;

    cout << left
         << setw(35) << "LEXEMA"
         << setw(12) << "TOKEN"
         << setw(100) << "TRANSICION"
         << "SUB ID" << endl;

    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

    while (i < longitudcadena) {

        char c = cadena[i];
        int cat_actual = obtenerCategoria(c);

        // IDENTIFICADORES
        
        if (cat_actual == 0) {

            string lexema = "";
            string transicion = "q" + to_string(estado_actual);

            while (i < longitudcadena) {

                int cat_temp = obtenerCategoria(cadena[i]);

                if (cat_temp == 0 || cat_temp == 1 || cat_temp == 2) {

                    lexema += cadena[i];

                    int sig_estado = ID[estado_actual][cat_temp];

                    transicion += ",q" + to_string(sig_estado);

                    estado_actual = sig_estado;

                    i++;
                }
                else {
                    break;
                }
            }

            cout << left
                 << setw(35) << lexema
                 << setw(12) << "[IDEVAR]"
                 << setw(100) << transicion
                 << generarID("[IDEVAR]") << endl;

            continue;
        }

        // NUMEROS
        
        if (cat_actual == 1) {

            string lexema = "";
            bool es_decimal = false;

            string transicion = "q" + to_string(estado_actual);

            while (i < longitudcadena) {

                int cat_temp = obtenerCategoria(cadena[i]);

                if (cat_temp == 1) {

                    lexema += cadena[i];

                    int sig_estado = ID[estado_actual][cat_temp];

                    transicion += ",q" + to_string(sig_estado);

                    estado_actual = sig_estado;

                    i++;
                }
                else if (cat_temp == 6 && !es_decimal) {

                    es_decimal = true;

                    lexema += cadena[i];

                    int sig_estado = ID[estado_actual][cat_temp];

                    transicion += ",q" + to_string(sig_estado);

                    estado_actual = sig_estado;

                    i++;
                }
                else {
                    break;
                }
            }

            string token_asignado =
                es_decimal ? "[DOUNUM]" : "[INTNUM]";

            cout << left
                 << setw(35) << lexema
                 << setw(12) << token_asignado
                 << setw(100) << transicion
                 << generarID(token_asignado) << endl;

            continue;
        }

        // ESPACIOS
        
        if (cat_actual == 3) {

            int estado_previo = estado_actual;

            string lexema_print = "";

            if (c == ' ')
                lexema_print = "' '";
            else if (c == '\t')
                lexema_print = "\\t";
            else if (c == '\n')
                lexema_print = "\\n";
            else if (c == '\r')
                lexema_print = "\\r";

            estado_actual = ID[estado_actual][cat_actual];

            string transicion =
                "q" + to_string(estado_previo) +
                ",q" + to_string(estado_actual);

            cout << left
                 << setw(35) << lexema_print
                 << setw(12) << tokens(3)
                 << setw(100) << transicion
                 << generarID(tokens(3)) << endl;

            i++;
            continue;
        }

        // RESTO DE SIMBOLOS

        int estado_previo = estado_actual;

        estado_actual = ID[estado_actual][cat_actual];

        string lexema_print(1, c);
        string token_str = tokens(cat_actual);

        string transicion =
            "q" + to_string(estado_previo) +
            ",q" + to_string(estado_actual);

        cout << left
             << setw(35) << lexema_print
             << setw(12) << token_str
             << setw(100) << transicion
             << generarID(token_str) << endl;

        i++;
    }

    cout << "\n--- ANALISIS COMPLETADO ---" << endl;

    if (estado_actual == 17) {

        cout << "RESULTADO: [ACEPTADO]" << endl;
        cout << "La entrada es sintacticamente valida." << endl;

    } else if (estado_actual == 18) {

        cout << "RESULTADO: [RECHAZADO]" << endl;
        cout << "Error de sintaxis. Se detuvo o cayo en trampa." << endl;

    } else {

        cout << "RESULTADO: [RECHAZADO]" << endl;
        cout << "La entrada no alcanzo un estado de aceptacion." << endl;
    }

    cout << "Estado final: q" << estado_actual << endl;
}
