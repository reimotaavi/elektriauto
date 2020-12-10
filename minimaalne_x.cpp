#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <string>

using namespace std;


void loe_andmed(const string& failinimi){

    int linnade_arv = 59;
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

            for (unsigned int j = 0; j<rida.size(); j++) {
                if (rida[j] != ',') {           // kui antud kohal ei leidu koma, siis lisan selle tähe uude stringi
                    arv += rida[j];
                }
                else {
                    kaugus = stoi(arv); // kui koma leidub siis panen olemasoleva stringi arvuna vectorisse ja algväärtustan string
                    kaugused.push_back(kaugus);
                    arv = "";
                }
            }
                kauguste_maatriks.push_back(kaugused); // lisan vastava linna kõik kaugused vectorisse
        }
        // kuvan maatriksi vektori kontrolliks
        for (unsigned int i = 0; i<kauguste_maatriks.size(); i++) {
            cout << endl << endl << i+1 << ". linna kaugused: ";
            for (unsigned int j = 0; j<kauguste_maatriks[i].size(); j++) {
                cout << kauguste_maatriks[i][j] << ", ";
            }
        }
    }
    else {
        cout << "Faili ei leitud!" << endl;
    }
}

int main(){
    loe_andmed("linnade_kaugused.csv");
}
