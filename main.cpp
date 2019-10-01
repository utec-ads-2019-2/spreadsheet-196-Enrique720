#include <iostream>
#include <vector>
#include <cmath>
#include <string>
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
    return 0;
}

int final(string a){
    if (a.size() == 1){
        return finalIndex(a[0]);
    }
    else if (a.size() == 2){
        return 26*(finalIndex(a[0])+1) + finalIndex(a[1])+1;
    }
    else{
        return 1;
    }
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
        //cambiar parte
        for(int i  = 0; i  < subcels.size(); i++){
            int column = finalIndex(subcels[i][0]);
            char a = subcels[i][1];
            int ia = a - '0';
            int row;
            row = ia-1;
            subcels[i] = getCelvalue(celdas[row][column], celdas);
        }
        //aca
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
int main() {
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

//string a = "AA22";
//string index ;
//string column;
//for (int i = 0; i < a.size(); i++) {
//if(notNumber(a[i])){
//column = column + a[i];
//}
//else{
//index = index + a[i];
//}
//}
//cout << column  << " " << index;
