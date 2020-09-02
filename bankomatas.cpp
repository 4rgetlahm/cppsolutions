#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>

class Banknote{
    int value, amount;
public:
    Banknote(int value){
        this->value = value;
    }

    int getValue(){
        return this->value;
    }

    int getAmount(){
        return this->amount;
    }

    void setAmount(int amount){
        this->amount = amount;
    }
};

std::vector<int> getChange(std::vector<Banknote*> &banknoteList, int returnSize){
    std::vector<int> returnVector;
    bool update = true;
    while(update){
        update = false;
        for(Banknote* &banknote : banknoteList){
            ///cia surandame visus banknotus kuriuos isduosime sumai atiduoti
            if(returnSize >= banknote->getValue() && banknote->getAmount() > 0){
                returnVector.push_back(banknote->getValue());
                returnSize -= banknote->getValue();
                banknote->setAmount(banknote->getAmount()-1);
                update = true;
                break;
            }
        }
    }
    if(returnSize > 0){
        ///jeigu nepavyko isduoti visos sumos, sugrazinam banknotus atgal i bankomata ir graziname tuscia vektoriu
        for(int addNote : returnVector){
            for(Banknote* banknote : banknoteList){
                if(banknote->getValue() == addNote){
                    banknote->setAmount(banknote->getAmount()+1);
                }
            }
        }
        std::vector<int> emptyVector;
        return emptyVector;
    }
    return returnVector;
}

int main(){
    freopen("U1.txt", "r", stdin);
    freopen("U1rez.txt", "w", stdout);

    std::vector<Banknote*> banknoteList;

    int banknote_count;
    std::cin >> banknote_count;
    ///perskaitome visas banknotu sumas
    for(int i = 0; i != banknote_count; i++){
        int read_value;
        std::cin >> read_value;
        banknoteList.push_back(new Banknote(read_value));
    }
    /// perskaitome banknotu kiekius
    for(int i = 0; i != banknote_count; i++){
        int read_amount;
        std::cin >> read_amount;
        banknoteList[i]->setAmount(read_amount);
    }
    /// del viso pikto (nes salygoje nepamineta, kad jie buna visada isrusiuoti), isrusiuojame banknotus pagal didejimo tvarka
    sort(banknoteList.begin(), banknoteList.end(), [](Banknote* var1, Banknote* var2) -> bool{
         if(var1->getValue() > var2->getValue()){
            return true;
         }
         return false;
    });


    int _count;
    std::cin >> _count;
    for(int i = 0; i != _count; i++){
        int returnSize;
        std::cin>>returnSize;
        std::cout << i+1 << ". ";
        ///gauname banknotu sarasa kuriuos isduosime, ir poto vyksta algoritmas kuris apskaiciuoja kiek butent banknotu is vienos sumos atiduosime
        std::vector<int> banknotes = getChange(banknoteList, returnSize);
        if(banknotes.size() > 0){
            int dupe_count = 0;
            for(int j = 1; j != banknotes.size(); j++){
                if(banknotes[j-1] == banknotes[j]){
                    dupe_count++;
                } else{
                    std::cout << banknotes[j-1] << " - " << dupe_count+1 << " ";
                    dupe_count = 0;
                }
            }
            std::cout << banknotes[banknotes.size()-1] << " - " << dupe_count+1 << std::endl;
        } else{
            std::cout << "NEPAVYKO" << std::endl;
        }
    }

}
