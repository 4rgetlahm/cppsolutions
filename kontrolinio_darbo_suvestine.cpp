#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Student{
    string name;
    double points = 0;
};

bool sortByPoints(Student var1, Student var2){ /// sortinimo algoritmas pagal kuri isrikiuos didejimo tvarka
    if(var1.points > var2.points){
        return true;
    }
    return false;
}

void read(vector<double> &taskValue, vector<Student> &studentList){
    freopen("U2.txt", "r", stdin); /// atidarome faila
    int student_count, task_count;
    cin >> student_count >> task_count;
    for(int i = 0; i != task_count; i++){
        double value_read;
        cin >> value_read;
        taskValue.push_back(value_read); ///perskaitome kiekvienos uzduoties verte ir idedame ja i vektoriu
    }
    cin.ignore(80, '\n');
    for(int i = 0; i != student_count; i++){
        Student student; ///sukuriame mokini
        string name; /// perskaitome varda
        getline(cin, name);
        student.name = name; ///tikriausiai buvo galima iskarto skaityti i student.name, bet toks variantas nekelia pasitikejimo
        for(int j = 0; j != task_count; j++){
            int taskGrade;
            cin >> taskGrade;
            student.points += (taskGrade*taskValue[j]); /// pridedame taskus uz kiekviena uzduoti
        }
        cin.ignore(80, '\n');
        studentList.push_back(student); ///idedame mokini i mokiniu sarasa
    }
}

int main()
{
    freopen("U2rez.txt", "w", stdout);
    setlocale(LC_ALL, "Lithuanian"); /// LIETUVIU KALBA!!!!!
    vector<Student> studentList; /// cia saugosim mokinukus
    vector<double> taskValue; /// o cia saugosim balus, bet techniskai net nereikalingas mums sitas (bet nurodymui gali prireikti?)
    read(taskValue, studentList); /// perskaitom ir vos ne isprendziam uzdavini sioje vietoje
    sort(studentList.begin(), studentList.end(), sortByPoints); /// isrikiuojam pagal balus (nenurodyta, kad reikia rikiuoti pagal varda pavarde jei sutampa)
    double avg = 0; /// cia bus vidurkis
    for(Student student : studentList){ ///keliaujiame per kiekviena mokinuka
        cout << student.name << " " << setprecision(1) << fixed << student.points << " ";
        cout <<  setprecision(0) << fixed << (student.points/studentList[0].points)*10 << endl; ///spausdinam viska ko praso uzduotis
        avg += student.points;
    }
    avg /= studentList.size(); /// surandame vidurki
    cout << endl;
    cout << "Taškų vidurkis: " << setprecision(1) << fixed << avg; ///israsome vidurki
    return 0;
}
