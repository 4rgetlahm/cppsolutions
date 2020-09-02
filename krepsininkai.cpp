#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

template <class T>
vector<T> readToArray(int x){ /// int x kiek duomenu perskaityti i masyva
    vector<T> returnVector;
    T read;
    for(int i = 0; i != x; i++){ /// perskaito duomenis
        cin >> read;
        returnVector.push_back(read); ///iraso i masyva
    }
    return returnVector; /// grazina uzpildyta masyva
}

int main(){
    freopen("U1.txt", "r", stdin);
    freopen("U1rez.txt", "w", stdout);
    vector<int> startFive;
    int _count;
    cin >> _count;
    int minTime = 2147483647, maxTime = -2147483647, minID, maxID;
    for(int i = 0; i != _count; i++){
        int playerID, playCount, firstPlay, playTimePositive = 0, playTimeNegative = 0;
        cin >> playerID >> playCount;
        cin >> firstPlay;

        if(firstPlay > 0){
            startFive.push_back(playerID);
            playTimePositive += firstPlay;
        } else if(firstPlay < 0){
            playTimeNegative += firstPlay;
        }

        for(int j = 1; j != playCount; j++){
            int currentTime;
            cin >> currentTime;
            if(currentTime > 0){
                playTimePositive += currentTime;
            } else if(currentTime < 0){
                playTimeNegative += currentTime;
            }
        }

        if(playTimePositive > maxTime){
            maxTime = playTimePositive;
            maxID = playerID;
        } else if(playTimePositive == maxTime){
            if(playerID < maxID){
                maxID = playerID;
            }
        }

        if(playTimeNegative < minTime){
            minTime = playTimeNegative;
            minID = playerID;
        } else if(playTimeNegative == minTime){
            if(playerID < minID){
                minID = playerID;
            }
        }
    }
    sort(startFive.begin(), startFive.end());
    for(auto x : startFive){
        cout << x << " ";
    }
    cout << endl << maxID << " " << maxTime << endl << minID << " " << abs(minTime);
    return 0;
}
