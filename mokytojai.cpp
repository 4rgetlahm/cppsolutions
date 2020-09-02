#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


struct Teacher{

    Teacher(string first_name, string last_name, vector<string> groups){
        this->first_name = first_name;
        this->last_name = last_name;
        this->groups = groups;
    }

    string first_name, last_name;
    vector<string> groups;
};

vector<Teacher*> getDayOffList(vector<Teacher*> teacherList, vector<string> workingGroups){
    vector<Teacher*> returnVector;
    for(Teacher* teacher : teacherList){ // einame per kiekviena mokytoja
        bool isWorking = false;
        for(string currentGroup : workingGroups){
            if(find(teacher->groups.begin(), teacher->groups.end(), currentGroup) != teacher->groups.end()){ // tikriname ar mokytojo bent viena grupe sutampa, jei taip - jis dirba
                isWorking = true;
                break;
            }
        }
        if(!isWorking){
            returnVector.push_back(teacher); // jeigu grupiu sutapimu nerado, jis nedirba, pridedame i sarasa
        }
    }
    return returnVector;
}

int main(){
    vector<Teacher*> teacherList;
    freopen("U2.txt", "r", stdin);
        freopen("U2rez.txt", "w", stdout);

    int _count, max_groups = -21474836487;

    Teacher* max_groups_teacher;
    cin >> _count;

    for(int i = 0; i != _count; i++){
        string first_name, last_name;
        cin >> last_name >> first_name;
        int group_count;
        cin >> group_count;

        vector<string> groups;
        for(int j = 0; j != group_count; j++){
            string curr_group;
            cin >> curr_group;
            groups.push_back(curr_group);
        }
        Teacher* teacher = new Teacher(first_name, last_name, groups); // susikuriame mokytojo rodykle
        teacherList.push_back(teacher); // idedame ja i sarasa
        if(group_count > max_groups){
            max_groups = group_count;
            max_groups_teacher = teacher; // paruosiame daugiausia pamoku turinti mokytoja
        }
    }

    cout << max_groups_teacher->last_name << " " << max_groups_teacher->first_name << endl << endl; // daugiausia pamoku turinti mokytoja israsome

    vector<string> workingGroupList;
    int working_groups;
    cin >> working_groups;
    for(int i = 0; i != working_groups; i++){ // surasome visas dirbancias grupes i sarasa, ji perduosime funkcijai
        string group;
        cin >> group;
        workingGroupList.push_back(group);
    }

    for(Teacher* teacher : getDayOffList(teacherList, workingGroupList)){  //israsome visus mokytojus kurie siandien nedirba
        cout << teacher->last_name << " " << teacher->first_name << endl;
    }
}
