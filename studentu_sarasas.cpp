#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>

using namespace std;

struct Student {
        Student(char conv_name[26], char conv_social_number[12]) {
                name = conv_name;
                social_number = conv_social_number;
        }
        string name, social_number;
};
///VISISKAI NEREIKALINGAS NURODYMAS:
void addStudent(vector<Student*> &studentList, char name[26], char social_number[12]){
    studentList.push_back(new Student(name, social_number));
}

void removeStudent(vector<Student*> &studentList, char social_number[12]){
    for(int i = 0; i != studentList.size(); i++){
        if(studentList[i]->social_number == social_number){
            delete studentList[i]; ///atminties optimizacija
            studentList.erase(studentList.begin()+i);
            break;
        }
    }
}

bool sortStudents(Student* var1, Student* var2){
    if(var1->name < var2->name){
        return true;
    } else if(var1->name == var2->name){
        string date1 = (var1->social_number).substr(2,7);
        string date2 = (var2->social_number).substr(2,7);

        if(date1 < date2){
            return true;
        }
        return false;
    }
    return false;
}



int main() {
    freopen("U2.txt", "r", stdin);
    freopen("U2rez.txt", "w", stdout);
    vector<Student*> studentList;
    int _count;
    cin >> _count;
    cin.ignore(80, '\n');
    for (int i = 0; i != _count; i++) {
            char name[26];
            char social_number[12];
            cin.get(name, 26);
            cin.get(social_number, 12);
            addStudent(studentList, name, social_number);
            cin.ignore(80, '\n');
    }

    cin >> _count;

    for(int i = 0; i != _count; i++){
        char decision;
        cin >> decision;
        char name[26], social_number[12];
        cin.ignore(1);
        cin.get(name, 26);
        cin.get(social_number, 12);
        if(decision == '+'){
            addStudent(studentList, name, social_number);
        }
        else if(decision == '-'){
            removeStudent(studentList, social_number);
        }
    }
    sort(studentList.begin(), studentList.end(), sortStudents);
    for(int i = 0; i != studentList.size(); i++){
        cout << i+1 << ". " << studentList[i]->name << " " << studentList[i]->social_number << endl;
    }

}
