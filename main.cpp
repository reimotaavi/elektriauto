#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <climits>
#include <algorithm>

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

vector<vector<int>> leia_kaugused(vector<vector<int>>& maatriks, int sisend){
    vector<vector<int>> kaugused;
    for(unsigned int i = 0; i < linnade_arv; i++){
        kaugused.push_back(vector<int>(linnade_arv, numeric_limits<int>::max()));
        for(unsigned int j = 0; j < linnade_arv; j++){
            if(maatriks[i][j] <= sisend){
                kaugused[i][j] = maatriks[i][j];
            }
        }
        kaugused[i][i] = 0;
    }
    for(unsigned int tipp = 0; tipp < linnade_arv; tipp++){
        for (unsigned int algus = 0; algus < linnade_arv; algus++) {
            if (kaugused[algus][tipp] == std::numeric_limits<int>::max()) {
                continue;
            }
            for (unsigned int lopp = 0; lopp < linnade_arv; lopp++) {
                if (kaugused[tipp][lopp] == std::numeric_limits<int>::max()) {
                    continue;
                }
                if (kaugused[algus][tipp] + kaugused[tipp][lopp] < kaugused[algus][lopp]){
                    kaugused[algus][lopp] = kaugused[algus][tipp] + kaugused[tipp][lopp];
                }
            }
        }
    }
    return kaugused;
}

void valjasta(vector<vector<int>> kaugused, const string& failinimi){

    ofstream valjund(failinimi);

    if(valjund.is_open()) {
    for (unsigned int i = 0; i < linnade_arv; i++) {
        for (unsigned int j = 0; j < linnade_arv; j++) {
            valjund << kaugused[i][j] << ",";
        }
        valjund << endl;
            }
    }
}

int main() {
    vector<vector<int>> maatriks = loe_andmed("linnade_kaugused.csv");
    int sisend;

    cout << "Sisesta soiduulatus: ";
    cin >> sisend;
    vector<vector<int>> kaugused = leia_kaugused(maatriks, sisend);
    valjasta(kaugused, "valjund.csv");

//
//    floydWarshall(maatriks, sisend);

}