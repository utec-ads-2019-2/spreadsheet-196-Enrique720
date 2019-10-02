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
    int finalIndex(string ind){
        string letras[26] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
        for( int i  = 0; i < 26; i++)
            if (letras[i] == ind)
                return i;
    }

    int final(string palabra,int end){
        int contador=0;
        string temporal;
        for (int i=0;i<end;i++){
            temporal=palabra[i];
            contador+=((finalIndex(temporal)+1)*pow(26,end-1-i));
        }
        return contador-1;
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
                int fin_col = final(column,column.size());
                int row;
                row = stoi(index);
                subcels[i] = getCelvalue(celdas[row-1][fin_col], celdas);
                }
              
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
        for(int a=0;a<filas;a++){
            for (int b=0;b<columnas;b++){
                if (b!=columnas-1){
                    cout<<celdas[a][b]<<" ";
                }else{
                    cout<<celdas[a][b];
                }
            }cout<<endl;
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
