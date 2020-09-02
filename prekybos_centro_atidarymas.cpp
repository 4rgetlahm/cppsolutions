#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>

struct Person{

    Person(int initial_time, int id){
        this->initial_time = initial_time;
        this->time_left_inside = initial_time;
        this->id = id;
        std::vector<Person*> emptyVec;
        this->leavingWith = emptyVec;
    }

    bool inside = false;
    int id;
    int initial_time;
    int time_left_inside;
    int wait_time = 0;
    std::vector<Person*> leavingWith;
};

bool tick(std::vector<Person*> &personList, std::vector<Person*> &insiders, int multiplier, int &rounds){ // true - repeat, false - stop
    std::vector<Person*> leavingList;

    for(Person* person : personList){
        if(!person->inside){
            person->wait_time++;
        }
    }

    for(Person* person : insiders){
        person->time_left_inside--;
        if(person->time_left_inside == 0){
            leavingList.push_back(person);
        }
    }

    bool _clear = false;
    while(!_clear){
        _clear = true;
        for(int i = 0; i != insiders.size(); i++){
            if(insiders[i]->time_left_inside == 0){
                _clear = false;
                insiders[i]->leavingWith = leavingList;
                insiders.erase(insiders.begin()+i);
                break;
            }
        }
    }

    while(insiders.size() <= 2 * multiplier){
        int upTo;
        if(multiplier*(rounds+1) >= personList.size()){
            upTo = personList.size();
        } else {
            upTo = multiplier*(rounds+1);
        }
        if(multiplier*rounds >= upTo){
            break;
        }
        for(int i = multiplier*rounds; i != upTo; i++){
            personList[i]->inside = true;
            insiders.push_back(personList[i]);
        }
        rounds++;
    }

    if(insiders.size() == 0){
        return false;
    }

    return true;
}

int main(){

    freopen("U2.txt", "r", stdin);
    freopen("U2rez.txt", "w", stdout);

    std::vector<Person*> personList;
    std::vector<Person*> insiders;
    int _count;
    std::cin >> _count;
    for(int i = 0; i != _count; i++){
        int read_time;
        std::cin >> read_time;
        personList.push_back(new Person(read_time, i));
    }

    int multiplier;
    int rounds = 0;

    std::cin >> multiplier;

    int upTo;
    if(multiplier*3 >= personList.size()){
        upTo = personList.size();
    } else {
        upTo = multiplier*3;
    }

    for(int i = 0; i != upTo; i++){
        personList[i]->inside = true;
        insiders.push_back(personList[i]);
    }
    rounds += 3;

    while(tick(personList, insiders, multiplier, rounds))
        ;;

    int report_1, report_2;
    std::cin>> report_1 >> report_2;

    std::cout << report_1 << ": " << personList[report_1-1]->wait_time << std::endl;
    std::cout << report_2 << ": ";
    personList[report_2-1]->leavingWith.erase(std::remove(personList[report_2-1]->leavingWith.begin(), personList[report_2-1]->leavingWith.end(), personList[report_2-1]),
                                              personList[report_2-1]->leavingWith.end());
    if(personList[report_2-1]->leavingWith.size() != 0){
        for(Person* person : personList[report_2-1]->leavingWith){
            std::cout << person->id+1 << " ";
        }
    } else{
        std::cout << "ne";
    }

}
