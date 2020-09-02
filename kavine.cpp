#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Client{
    string name;
    int entry, exit;
};

int timeToMinutes(string time){
    // time[x] - '0' grazina skaitmeni is char.
    // sitas visas apskaiciavimas grazina laika minutemis is hh:mm formato
    return ((((time[0] - '0') * 10) + (time[1] - '0')) * 60) + (time[3] - '0') * 10 + (time[4] - '0');
}

bool sortByName(Client var1, Client var2){
    if(var1.name < var2.name){
        return true;
    }
    return false;
}

vector<Client> readData(int &_count, int &_result){
    cin >> _count >> _result;
    vector<Client> clientList;

    for(int i = 0; i != _count; i++){
        string name, time;
        char status;
        cin >> name >> time >> status;
        // tikriname ar ieina ar iseina
        if(status == '+'){
            // jei ieina, sukuriame nauja 'klienta' ir irasome laika kada jis atejo minutemis
            Client client;
            client.name = name;
            client.entry = timeToMinutes(time);
            clientList.push_back(client);
        } else if(status == '-'){
            // jei iseina, surandame 'klienta' ir irasome laika kada jis isejo minutemis
            for(Client &client : clientList){
                if(client.name == name){
                    client.exit = timeToMinutes(time);
                    break;
                }
            }
        }
    }
    return clientList;
}

vector<Client> clientsOnTime(vector<Client> clientList, int time){
    vector<Client> currentClients;
    // surandame visus klientus kurie buvo kavineje tuo metu
    for(Client &client : clientList){
        if(client.entry <= time && client.exit >= time){
            currentClients.push_back(client);
        }
    }
    return currentClients;
}

int main(){

    freopen("U2.txt", "r", stdin);
    freopen("U2rez.txt", "w", stdout);
    int _count, _result;
    vector<Client> clientList = readData(_count, _result);

    for(int i = 0; i != _result; i++){
        //perskaitome laika kurio informacijos mums reikia ir ji paverciame minutemis
        string currentTime;
        cin >> currentTime;
        int convertedTime = timeToMinutes(currentTime);

        vector<Client> currentClients = clientsOnTime(clientList, convertedTime);
        // isrikiuojame abeceliskai ir spausdiname
        sort(currentClients.begin(), currentClients.end(), sortByName);
        cout << currentClients.size() << " ";
        for(Client client : currentClients){
            cout << client.name << " ";
        }
        cout << endl;
    }
}
