#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

const int linnade_arv = 59;

vector<vector<int>> loe_andmed(const string& failinimi){

    vector<vector<int>> kauguste_maatriks;

    ifstream sisend(failinimi);
    sisend.ignore(1000, '\n'); //ignoreerin esimest rida
    if(sisend.is_open()){
        string rida;
        string arv = "";
        int kaugus = 0;
        for(unsigned int i = 0; i < linnade_arv; i++){
            vector<int> kaugused;
            sisend.ignore(256, ','); // ignoreerin linna nime
            getline (sisend, rida, '\n'); // loen terve rea sisse
            rida += ","; // lisan rea loppu koma, et saaks hiljem ka viimase kauguse kätte

            for (char j : rida) {
                if (j != ',') {           // kui antud kohal ei leidu koma, siis lisan selle tähe uude stringi
                    arv += j;
                }
                else {
                    kaugus = stoi(arv); // kui koma leidub siis panen olemasoleva stringi arvuna vectorisse ja algväärtustan string
                    kaugused.push_back(kaugus);
                    arv = "";
                }
            }
            kauguste_maatriks.push_back(kaugused); // lisan vastava linna kõik kaugused vectorisse
        }
        return kauguste_maatriks;
    }
    else {
        cout << "Faili ei leitud!" << endl;
        return kauguste_maatriks;
    }
}

int vanem[linnade_arv];

int leia(int i){
    while (vanem[i] != i)
        i = vanem[i];
    return i;
}

void union1(int i, int j){
    int a = leia(i);
    int b = leia(j);
    vanem[a] = b;
}

void kruskal(vector<vector<int>>& maatriks){
    int mincost = 0;
    for(int i = 0; i < linnade_arv; i++){
        vanem[i] = i;
    }
    int servade_arv = 0;
    while (servade_arv < linnade_arv - 1){
        int min = INT_MAX, a = - 1, b = - 1;
        for (int i = 0; i < linnade_arv; i++) {
            for (int j = 0; j < linnade_arv; j++) {
                if (leia(i) != leia(j) && maatriks[i][j] < min) {
                    min = maatriks[i][j];
                    a = i;
                    b = j;
                }
            }
        }
        union1(a, b);
        printf("Puu serv %d:(%d, %d) cost:%d \n", servade_arv++, a, b, min);
        mincost += min;
    }
    cout << "Minimaalse puu kogukaal = " << mincost << endl;
}

int main(){
    vector<vector<int>> maatriks = loe_andmed("linnade_kaugused.csv");
    kruskal(maatriks);
}