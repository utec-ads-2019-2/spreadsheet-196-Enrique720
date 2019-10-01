#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;
bool isSolved(string celda){
    return celda[0] != '=';
}
int finalIndex(char ind){
    char letras[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    for( int i  = 0; i < 27; i++)
        if (letras[i] == ind)
            return i;
    return 0;
}
string getCelvalue(string &celda, string** celdas){
    if(isSolved(celda)){
        return celda;
    }
    else{
        vector<string> subcels;
        string f = "";
        for(int i = 1; i < celda.size();i++){
            if(celda[i] != '+')
                f = f + celda[i];
            else{
                subcels.push_back(f);
                f = "";
            }
            if(i == celda.size()-1)
                subcels.push_back(f);
        }
        for(int i  = 0; i  < subcels.size(); i++){
            int column = finalIndex(subcels[i][0]);
            char a = subcels[i][1];
            int ia = a - '0';
            int row;
            row = ia-1;
            subcels[i] = getCelvalue(celdas[row][column], celdas);
        }
        int finalRes = 0;
        for(int i = 0; i < subcels.size(); i++){
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
            cout << celdas[i][j] << " ";
        }
        cout << endl;
    }
}
int main(){

    int filas,columnas;
    cin >> columnas >> filas;
    string ** celdas;
    celdas = new string*[filas];
    for(int i  = 0; i < filas; i++){
        celdas[i] = new string[columnas];
    }
    for(int i  = 0 ; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            cin >> celdas[i][j];
        }
    }
    solveMat(celdas,filas,columnas);
    print(celdas,filas,columnas);

}








