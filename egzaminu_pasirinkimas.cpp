#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>

using namespace std;

struct Student{
    string name;
    int worst_grade = 2147483647;
    map<int, int> subjectData;
};


struct Subject{
    string title;
    int id;
    vector<Student> subjectStudents;
};

bool sortByGrade(Student var1, Student var2){
    if(var1.worst_grade == var2.worst_grade){
        if(var1.name < var2.name){
            return true;
        }
        return false;
    } else if(var1.worst_grade < var2.worst_grade){
        return true;
    }
    return false;
}

bool sortByName(Subject var1, Subject var2){
    if(var1.title < var2.title){
        return true;
    }
    return false;
}

int main()
{
    vector<Subject> subjectList;
    vector<Student> studentList;
    setlocale(LC_ALL, "Lithuanian");
    freopen("U2.txt", "r", stdin);
    freopen("U2rez.txt", "w", stdout);
    int _count;
    cin >> _count;
    cin.ignore(80, '\n');
    for(int i = 0; i != _count; i++){
        Subject subject;
        char title[30];
        cin.get(title, 30);
        subject.title = title;
        cin >> subject.id;
        subjectList.push_back(subject);
        cin.ignore(80, '\n');
    }
    cin >> _count;
    cin.ignore(80, '\n');
    for(int i = 0; i != _count; i++){
        Student student;
        char name[25];
        cin.get(name, 25);
        student.name = name;
        int subject_count;
        cin >> subject_count;
        for(int j = 0; j != subject_count; j++){
            int id, grade;
            cin >> id >> grade;
            student.worst_grade = min(grade, student.worst_grade);
            student.subjectData[id] = grade;
        }
        studentList.push_back(student);
        cin.ignore(80, '\n');
    }
    for(Student &student : studentList){
        for(auto const &x : student.subjectData){
            if(x.second == student.worst_grade){
                for(Subject &subject : subjectList){
                    if(subject.id == x.first){
                        subject.subjectStudents.push_back(student);
                    }
                }
            }
        }
    }
    for(Subject &subject : subjectList){
        sort(subject.subjectStudents.begin(), subject.subjectStudents.end(), sortByGrade);
    }
    sort(subjectList.begin(), subjectList.end(), sortByName);
    for(Subject &subject : subjectList){
        if(subject.subjectStudents.size() > 0){
            cout << subject.title << endl;
                for(int i = 0; i != subject.subjectStudents.size(); i++){
                    cout << i+1 << ". " << subject.subjectStudents[i].name << " " << subject.subjectStudents[i].worst_grade << endl;
                }
        }
    }
}
