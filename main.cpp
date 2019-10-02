#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;
bool notNumber(char a){
    char letras[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    for( int i  = 0; i < 26; i++)
        if (letras[i] == a)
            return true;
    return false;
}
bool isSolved(string celda){
    return celda[0] != '=';
}
int finalIndex(char ind){
    char letras[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    for( int i  = 0; i < 26; i++)
        if (letras[i] == ind)
            return i;
}

int final(string a){
    if (a.size() == 1){
        return finalIndex(a[0]);
    }
    else if (a.size() == 2){
        return 26*(finalIndex(a[0])+1) + finalIndex(a[1]);
    }
    else{
        return pow(26,2)*(finalIndex(a[0])+1) + 26*(finalIndex(a[0])+1) + finalIndex(a[1]) ;
    }
}
string getCelvalue(string &celda, string** celdas) {
    if (isSolved(celda)) {
        return celda;
    } else {
        vector<string> subcels;
        string f = "";
        for (int i = 1; i < celda.size(); i++) {
            if (celda[i] != '+')
                f = f + celda[i];
            else {
                subcels.push_back(f);
                f = "";
            }
            if (i == celda.size() - 1)
                subcels.push_back(f);
        }
        //cambiar parte
        for (int i = 0; i < subcels.size(); i++) {
            string index;
            string column;
            string a = subcels[i];
            for (int j = 0; j < a.size(); j++) {
                if (notNumber(a[j])) {
                    column = column + a[j];
                } else {
                    index = index + a[j];
                }
            }
            int fin_col = final(column);
            int row;
            row = stoi(index);
            subcels[i] = getCelvalue(celdas[row-1][fin_col], celdas);
            }
            //aca
            int finalRes = 0;
            for (int i = 0; i < subcels.size(); i++) {
                finalRes = finalRes + stoi(subcels[i]);
            }
            string res = to_string(finalRes);
            return res;
        }
    }


void solveMat(string** celdas,int filas, int columnas){
    for(int i = 0; i < filas ; i ++){
        for(int j = 0; j < columnas; j++){
            celdas[i][j]  = getCelvalue(celdas[i][j],celdas);
        }
    }
}
void print(string** celdas,int filas, int columnas){
    for(int i = 0; i < filas ; i ++){
        for(int j = 0; j < columnas; j++){
            cout   << celdas[i][j]  << " ";
        }
        cout << endl;
    }
}
int main() {
    int numExcels;
    cin >> numExcels;
    for(int p = 0 ; p < numExcels; p++) {
        int filas, columnas;
        cin >> columnas >> filas;
        string **celdas;
        celdas = new string *[filas];
        for (int i = 0; i < filas; i++) {
            celdas[i] = new string[columnas];
        }
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                cin >> celdas[i][j];
            }
        }
        solveMat(celdas, filas, columnas);
        print(celdas, filas, columnas);
    }
}
