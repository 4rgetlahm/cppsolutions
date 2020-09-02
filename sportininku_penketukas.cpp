#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Sportsman{
    int id;
    string name;
    int points = 0;
};

struct Voter{
    string name;
    vector<Sportsman*> picks_ptr;
};

bool sortByPoints(Sportsman var1, Sportsman var2){
    if(var1.points == var2.points){
        if(var1.id < var2.id){
            return true;
        }
        return false;
    }
    else if(var1.points > var2.points){
        return true;
    }
    return false;
}

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    freopen("U2.txt", "r", stdin);
    freopen("U2rez.txt", "w", stdout);
    vector<Sportsman> sportsmanList;
    vector<Voter> voterList;
    int _count;
    cin >> _count;
    cin.ignore(80, '\n');
    for(int i = 0; i != _count; i++){
        Sportsman sportsman;
        getline(cin, sportsman.name);
        sportsman.id = i;
        sportsmanList.push_back(sportsman);
    }
    cin >> _count;
    cin.ignore(80, '\n');
    for(int i = 0; i != _count; i++){
        Voter voter;
        char name[26];
        cin.get(name, 26);
        voter.name = name;
        for(int j = 0; j != 5; j++){
            int current_vote;
            cin >> current_vote;
            sportsmanList[current_vote-1].points++;
            voter.picks_ptr.push_back(&(sportsmanList[current_vote-1]));
        }
        cin.ignore(80, '\n');
        voterList.push_back(voter);
    }
    vector<Sportsman> tempSportsmanList = sportsmanList;
    sort(tempSportsmanList.begin(), tempSportsmanList.end(), sortByPoints);
    tempSportsmanList.erase(tempSportsmanList.begin()+5, tempSportsmanList.end());
    cout << "GERIAUSIEJI SPORTININKAI:" << endl;
    for(Sportsman sportsman : tempSportsmanList){
        cout << sportsman.name << " " << sportsman.points << endl;
    }
    vector<Voter> winners;
    for(int i = 0; i != voterList.size(); i++){
        bool error = false;
        for(Sportsman* sportsman_ptr : voterList[i].picks_ptr){
            bool found = false;
            for(Sportsman sportsman : tempSportsmanList){
                if(sportsman.id == sportsman_ptr->id){
                    found = true;
                    break;
                }
            }
            if(!found){
                error = true;
                break;
            }
        }
        if(!error){
            winners.push_back(voterList[i]);
        }
    }
    cout << endl;
    if(winners.size() > 0){
        cout << "PENKETUKĄ ATSPĖJO:" << endl;
        for(Voter voter : winners){
            cout << voter.name << endl;
        }
    } else{
        cout << "NIEKAS NEATSPĖJO" << endl;
    }
    return 0;
}
