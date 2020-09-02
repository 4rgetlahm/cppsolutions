#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

vector<int> evaluateGold(vector<int> baseGold){
    vector<int> addGold(10, 0); // apskaiciuotu aukso luitu masyvas
    for(int i = 0; i != 10; i++){
        int upTo;
        if(i+baseGold[i] > 9){
            upTo = 9;
        } else{
            upTo = i+baseGold[i];
        }
        for(int j = i; j != upTo; j++){ // algoritmas
            addGold[j+1]++;
            baseGold[i]--;
        }
        if(baseGold[i] > 0){
            addGold[i] += baseGold[i];
        }
    }
    return addGold;
}

int main(){
    freopen("U1.txt", "r", stdin); // skaitymas
    freopen("U1rez.txt", "w", stdout); // rasymas
    vector<int> gold; // pradiniu aukso luitu masyvas
    for(int i = 0; i != 5; i++){
        int bar_amount;
        cin >> bar_amount;
        gold.push_back(bar_amount); //perskaitomos pradines reiksmes
    }
    while(gold.size() != 10){ // papildomas masyvas kitais "piratais"
        gold.push_back(0);
    }
    sort(gold.rbegin(), gold.rend()); // rikiavimas mazejimo tvarka
    for(auto x : evaluateGold(gold)){ // rasymas
        cout << x << " ";
    }
}
