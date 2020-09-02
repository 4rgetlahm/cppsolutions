#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

struct Person{

    Person(string name, string id, int points, int startTime){
        this->name = name;
        this->id = id;
        this->points = points;
        this->startTime = startTime;

        if(id[0] == '1'){
            this->gender = 1;
        } else if(id[0] == '2'){
            this->gender = 2;
        }
    }

    long getScoreTime(){
        return this->scoreTime;
    }

    string name;
    string id;
    short gender;
    int points;
    long startTime;
    long scoreTime = 0;
};

bool sortByScore(Person* var1, Person* var2){
    if(var1->scoreTime == var2->scoreTime){
        if(var1->name < var2->name){
            return true;
        }
        return false;
    } else if(var1->scoreTime < var2->scoreTime){
        return true;
    }
    return false;
}

void writeToFile(vector<Person*> participantList){
    freopen("U2rez.txt", "w", stdout);
    cout << "Merginos" << endl;
    for(Person* person : participantList){
        if(person->gender == 1 && person->scoreTime > 0){
            int hours = person->scoreTime/3600;
            int minutes = (person->scoreTime%3600) / 60;
            int seconds = (person->scoreTime%3600) % 60;
            cout << person->id << " " << person->name << " " << hours << " " << minutes << " " << seconds << endl;
        }
    }
    cout << "Vaikinai" << endl;
    for(Person* person : participantList){
        if(person->gender == 2 && person->scoreTime > 0){
            int hours = person->scoreTime/3600;
            int minutes = (person->scoreTime%3600) / 60;
            int seconds = (person->scoreTime%3600) % 60;
            cout << person->id << " " << person->name << " " << hours << " " << minutes << " " << seconds << endl;
        }
    }
}

int main(){
    freopen("U2.txt", "r", stdin);

    vector<Person*> participants;

    int _count;
    cin >> _count;
    cin.ignore(80, '\n');
    for(int i = 0; i != _count; i++){
        string id, conv_name;
        int hours, minutes, seconds;
        long time;
        char name[20];
        cin.get(name, 20);
        conv_name = name;
        cin >> id >> hours >> minutes >> seconds;
        participants.push_back(new Person(conv_name, id, 0, ((hours*3600)+(minutes*60)+seconds) ));
        cin.ignore(80, '\n');
    }

    cin >> _count;
    for(int i = 0; i != _count; i++){
        string currentID;
        cin >> currentID;
        for(Person* participant : participants){
            if(participant->id == currentID){
                if(participant->gender == 1){
                    int hours, minutes, seconds;
                    cin >> hours >> minutes >> seconds;
                    int points[2];
                    cin >> points[0] >> points[1];
                    participant->scoreTime = (hours*3600 + minutes*60 + seconds)-participant->startTime + (5-points[0])*60 + (5-points[1])*60;
                } else if(participant->gender == 2){
                    int hours, minutes, seconds;
                    cin >> hours >> minutes >> seconds;
                    int points[4];
                    cin >> points[0] >> points[1] >> points[2] >> points[3];
                    participant->scoreTime = (hours*3600 + minutes*60 + seconds)-participant->startTime + (5-points[0])*60 + (5-points[1])*60 + (5-points[2])*60 + (5-points[3])*60;
                }
                break;
            }
        }
    }

    sort(participants.begin(), participants.end(), sortByScore);
    writeToFile(participants);

}
