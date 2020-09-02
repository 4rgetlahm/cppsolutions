#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>

struct Student{

    Student(std::string name, int batch){
        this->name = name;
        this->batch = batch;
    }

    int batch = 0;
    std::string name;
};

void fillInto(std::vector<Student*> &studentList, Student* student){
    for(int i = 1; i != studentList.size(); i++){
        if(studentList[i-1]->batch < student->batch && studentList[i]->batch < student->batch){
            studentList.insert(studentList.begin()+i, student);
            return;
        }
    }
    studentList.insert(studentList.end(), student);
}

int main(){
    freopen("U1.txt", "r", stdin);
    freopen("U1rez.txt", "w", stdout);

    std::vector<Student*> studentList;

    int _count;
    std::cin >> _count;
    for(int i = 0; i != _count; i++){
        int _current_count;
        std::cin >> _current_count;
        for(int j = 0; j != _current_count; j++){
            std::string curr_name;
            std::cin >> curr_name;
            if(i == 0){
                studentList.push_back(new Student(curr_name, i));
            } else{
                fillInto(studentList, new Student(curr_name, i));
            }
        }
    }
    for(Student* student : studentList){
        std::cout << student->name << " ";
    }
}
