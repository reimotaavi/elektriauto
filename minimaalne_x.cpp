#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int linnade_arv = 59;

void loe_andmed(const string& failinimi){

    vector<vector<int>> kauguste_maatriks;

    ifstream sisend(failinimi);
    sisend.ignore(1000, '\n'); //ignoreerin esimest rida
    while(sisend.is_open()){
        string rida;
        vector<int> kaugused;
        for(unsigned int i = 0; i < linnade_arv; i++){
            for(unsigned int j = 0; j <= linnade_arv; j++){
                getline(sisend, rida, ',');
                if(j != 0){
                    int kaugus = stoi(rida);
                    cout << kaugus;
                    kaugused[j - 1] = kaugus;
                }
            }
            cout << endl;
            kauguste_maatriks[i] = kaugused;
        }
    }
}

int main(){
    loe_andmed("linnade_kaugused.csv");
}