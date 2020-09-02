#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

struct Order{
    string location_name;
    int x, y;
};

vector<Order> read(int &_count, int &maxDistance){
    freopen("U1.txt", "r", stdin);
    cin >> _count >> maxDistance;

    vector<Order> returnOrders;
    for(int i = 0; i != _count; i++){
        cin.ignore(80, '\n');
        Order order;
        // skaitome 11 raidziu, iskaitom ir tarpa
        char location_name[11];
        cin.get(location_name, 11);
        order.location_name = location_name;
        cin >> order.x >> order.y;
        //idedame i uzsakymu sarasa
        returnOrders.push_back(order);
    }

    return returnOrders;
}

int distance(Order order){
    // atstumas bus modulio x ir y suma padauginus is 2
    return (abs(order.x) + abs(order.y))*2;
}

void write(vector<Order> failedOrders, int currentDistance, string lastLocation){
    freopen("U1rez.txt", "w", stdout);
    cout << failedOrders.size() << " " << currentDistance << " " << lastLocation << endl;
}

int main()
{
    int _count, maxDistance, currentDistance = 0;
    vector<Order> orderList = read(_count, maxDistance);
    vector<Order> failedOrders;
    string lastLocation;
    for(Order order : orderList){
        int orderDistance = distance(order); // kad nereiktu 2 kartus skaiciuoti
        if(currentDistance <= maxDistance){
            currentDistance += orderDistance;
            lastLocation = order.location_name;
        } else{
            failedOrders.push_back(order);
        }
    }

    write(failedOrders, currentDistance, lastLocation);

    return 0;
}
