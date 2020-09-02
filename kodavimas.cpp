#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <map>

std::map<std::string, char> key_list = { //saraselis musu koduku
    {"ABC", '2'},
    {"DEF", '3'},
    {"GHI", '4'},
    {"JKL", '5'},
    {"MNO", '6'},
    {"PQR", '7'},
    {"STU", '8'},
    {"VWX", '9'},
};

std::string fix_hash(std::string part){ // taisys tris raideles
    for(auto const &key : key_list){ // tikrina artimiausia koduka
        if((key.first.find(part[0]) != std::string::npos && key.first.find(part[1]) != std::string::npos)
        || (key.first.find(part[1]) != std::string::npos && key.first.find(part[2]) != std::string::npos)
        || (key.first.find(part[0]) != std::string::npos && key.first.find(part[2]) != std::string::npos)){
            return key.first;
        }
    }
}

std::pair<std::string, int> decrypt(std::string &_hash){ //grazinsim skaiciu ir klaidu kieki
    std::string returnNumber;
    int mistake_count = 0;
    for(int i = 0; i != 7; i++){
        std::string part;
        part += _hash[i*3];
        part += _hash[(i*3)+1];
        part += _hash[(i*3)+2]; // sukuriame 3 raidziu daly
        if(key_list.find(part) == key_list.end()){ // jeigu dalyje yra klaida (neranda musu sarase)
            mistake_count++;
            std::string fixed_part = fix_hash(part); //gaunam sutvarkyta koduka ir ji pataisome
            _hash[i*3] = fixed_part[0];
            _hash[(i*3)+1] = fixed_part[1];
            _hash[(i*3)+2] = fixed_part[2];
            returnNumber += key_list.find(fixed_part)->second; //isgauname skaiciuka ir pridedame prie numerio
        } else {
            returnNumber += key_list.find(part)->second; // taspac
        }
    }
    return std::make_pair(returnNumber, mistake_count); // graziname skaiciu ir klaidu kieki
}

int main(){
    freopen("U1.txt", "r", stdin);
    freopen("U1rez.txt", "w", stdout);
    int _count;
    std::cin >> _count;
    for(int i = 0; i != _count; i++){
        std::string _hash;
        std::cin >> _hash;
        std::pair<std::string, int> decryption_result = decrypt(_hash);
        std::cout << _hash << " Klaidos: " << decryption_result.second << " Tel. nr.: " << decryption_result.first << std::endl;
    }
}
