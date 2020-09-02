#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>


using namespace std;

struct Farmer{

    Farmer(char full_name[20], int package1, int package2){ //konstruktorius
        this->full_name = full_name;
        this->package1 = package1;
        this->package2 = package2;
    }

    string full_name;
    int package1, package2;
};

struct Client{
    Client(char full_name[20], int amount){ //konstruktorius
        this->full_name = full_name;
        this->amount = amount;
        this->_tempamount = amount;
    }

    string full_name;
    int amount, _tempamount;

    int bought1 = 0, bought2 = 0;
};

int main(){

    freopen("U2.txt", "r", stdin);
    freopen("U2rez.txt", "w", stdout);
    vector<Client*> clientList;
    vector<Farmer*> farmerList;
    int _count;
    cin >> _count;
    cin.ignore(80, '\n');
    for(int i = 0; i != _count; i++){
        char full_name[20];
        int amount;
        cin.get(full_name, 20);
        cin >> amount;
        clientList.push_back(new Client(full_name, amount)); // perskaitome pirkeja ir ji irasome i sarasa
        cin.ignore(80, '\n');
    }
    cin >> _count;
    cin.ignore(80,'\n');
    for(int i = 0; i != _count; i++){
        char full_name[20];
        int package1, package2;
        cin.get(full_name, 20);
        cin >> package1 >> package2;
        farmerList.push_back(new Farmer(full_name, package1, package2)); // perskaitome ukininka ir ji irasome i sarasa
        cin.ignore(80, '\n');
    }

    int need1 = 0, need2 = 0;
    for(Client* client : clientList){ // pirkeju reikalavimu apskaiciavimas
        need2 += (client->amount-(client->amount%2))/2;
        need1 += client->amount%2;
    }
    cout << need1 << " " << need2 << endl;

    int total1 = 0, total2 = 0;
    for(Farmer* farmer : farmerList){ // ukininku pasiulos apskaiciavimas
        total1 += farmer->package1;
        total2 += farmer->package2;
    }
    cout << total1 << " " << total2 << endl;

    for(Client* client : clientList){ // algoritmas ispirkti 2 kg paketus, pirma einame per pirkejus
        while(client->amount > 1){ // jei pirkejas turi pirkti daugiau nei 1kg
            bool outofpackages = true; // kintamasis tikrinimui ar dar yra 2kg paketu
            for(Farmer* farmer : farmerList){ // einame per kiekviena is ukininku
                while(farmer->package2 > 0){ // jei ukininkas turi paketu
                    if(client->amount-2 >= 0){ // jei perka 2kg ar daugiau
                        farmer->package2--; // panaikiname viena paketa
                        client->amount -= 2; // nuimame 2kg nuo pirkejo
                        client->bought2++; // pridedame viena paketa prie pirkejo
                    } else if(client->amount-2 < 0 || client->amount == 0){ // jeigu 2kg butu per daug ar klientas jau nusipirko viska ko reikia, stabdome cikla
                        break;
                    }
                }
                if(farmer->package2 > 0){ // jei paketu dar yra, nekeiciame bool reiksmes, jei nera, stabdysim cikla
                    outofpackages = false;
                }
            }
            if(outofpackages){ // stabdom ciklu jei paketu nera
                break;
            }
        }
    }

    for(Client* client : clientList){ // kartojame tapati su 1kg paketais
        while(client->amount > 0){ // jei pirkejas nori pirkti
            bool outofpackages = true;
            for(Farmer* farmer : farmerList){ // einame per kiekviena ukininka
                while(farmer->package1 > 0){ // jei turi 1kg paketu
                    if(client->amount-1 >= 0){ // tikriname ar nebus per daug (nors ne visai butina)
                        farmer->package1--; // panaikiname 1 paketa is ukininko
                        client->amount--; // nuimame 1kg nuo pirkimo
                        client->bought1++; // pridedame 1 paketa pirkejui
                    } else if(client->amount-1 < 0 || client->amount == 0){
                        break;
                    }
                }
                if(farmer->package1 > 0){ // jei paketu dar yra, nekeiciame bool reiksmes, jei nera, stabdysim cikla
                    outofpackages = false;
                }
            }
            if(outofpackages){
                break;
            }
        }
    }

    bool enough = true;
    for(Client* client : clientList){
        if(client->amount > 0){
            cout << "NE" << endl;
            enough = false;
            break;
        }
    }
    if(enough){
        cout << "TAIP" << endl;
    }

    for(Client* client : clientList){ //pirkeju informacijos spausdinimas
        cout << client->full_name << " " << client->_tempamount << " " << client->bought1 << " " << client->bought2 << endl;
    }

    for(Farmer* farmer : farmerList){ //ukininku informacijos spausdinimas
        cout << farmer->full_name << " " << farmer->package1 << " " << farmer->package2 << endl;
    }


}
