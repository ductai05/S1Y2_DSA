#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath> // std::round
using namespace std;

struct student{
    string name;
    double firstPoint;
    double secondPoint;
    double avgPoint; // average of firstPoint and secondPoint
    int* options; // array of m options, sort by priority
    bool selected = false; // check if student is selected
};

double roundToTwoDecimals(double value) {
    return round(value * 100.0) / 100.0;
}

void readFile(string fileName, vector<student> &students, pair<int, int>* &option_slot, int &m){
    ifstream file(fileName);
    string line;
    getline(file, line); // get m
    m = stoi(line);

    pair<int, int>* optionSlot = new pair<int, int> [m];
    for (int i = 0; i < m; i++){
        getline(file, line);
        stringstream ss(line);
        string part;
        getline(ss, part, ' ');
        optionSlot[i].first = stoi(part);
        getline(ss, part, ' ');
        optionSlot[i].second = stoi(part);
    }
    swap(option_slot, optionSlot);  // get option_slot

    int studentID = 0;
    while(getline(file, line)){
        // line = "Doe John",9.30,9.80,4,2,1,3
        string part;
        stringstream ss(line);

        student studentNow;

        getline(ss, part, ',');
        studentNow.name = part.substr(1, part.size() - 2);
        getline(ss, part, ',');
        studentNow.firstPoint = stod(part);
        getline(ss, part, ',');
        studentNow.secondPoint = stod(part);
        studentNow.avgPoint = roundToTwoDecimals((studentNow.firstPoint + studentNow.secondPoint) / 2);

        int i = 0;
        studentNow.options = new int [m];
        while(getline(ss, part, ',') && i < m){
            studentNow.options[i] = stoi(part);
            i++;
        }
        students.push_back(studentNow);
    } // get students
}

void sortStudents(vector<student> &students){
    int n = students.size();

    // bubble sort (stable): secondPoint -> firstPoint -> avgPoint
    // alternative: mergesort, insertionsort
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - 1 - i; j++){
            if (students[j + 1].secondPoint > students[j].secondPoint){
                swap(students[j + 1], students[j]);
            }
        }
    }
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - 1 - i; j++){
            if (students[j + 1].firstPoint > students[j].firstPoint){
                swap(students[j + 1], students[j]);
            }
        }
    }
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - 1 - i; j++){
            if (students[j + 1].avgPoint > students[j].avgPoint){
                swap(students[j + 1], students[j]);
            }
        }
    }

}

void selectStudents(vector<student> &students, pair<int, int>* &option_slot, int m, vector<vector<student>> &options){
    int n = students.size();
    vector<student>* option = new vector<student> [m];
    for (int i = 0; i < n; i++){ // each student
        for (int j = 0; j < m; j++){ // each option of student
            if (students[i].selected) break; // if student is selected, break (uncessary)
            int curOpt = students[i].options[j];
            int idOpt = -1;
            for (int k = 0; k < m; k++){
                if (option_slot[k].first == curOpt){
                    idOpt = k;
                    break;
                }
            }
            if (option[idOpt].size() < option_slot[idOpt].second){
                option[idOpt].push_back(students[i]);
                students[i].selected = true;
                break;
            } else if (option[idOpt].size() == option_slot[idOpt].second){
                if (students[i].avgPoint == option[idOpt][option[idOpt].size() - 1].avgPoint
                && students[i].firstPoint == option[idOpt][option[idOpt].size() - 1].firstPoint
                && students[i].secondPoint == option[idOpt][option[idOpt].size() - 1].secondPoint){
                    option[idOpt].push_back(students[i]);
                    option_slot[idOpt].second++;
                    students[i].selected = true;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < m; i++){
        options.push_back(option[i]);
    }
}

void printAllStudents(vector<student> students, int m){
    // for (int i = 0; i < students.size(); i++){
    //     cout << students[i].name << " " << students[i].avgPoint << " " << students[i].firstPoint << " " << students[i].secondPoint << " ";
    //     for (int j = 0; j < m; j++){
    //         cout << students[i].options[j] << " ";
    //     }
    //     cout << "\n";
    // }
    ofstream file("Exercise_3_AllStudents.txt");
    for (int i = 0; i < students.size(); i++){
        file << students[i].name << " " << students[i].avgPoint << " " << students[i].firstPoint << " " << students[i].secondPoint << " ";
        for (int j = 0; j < m; j++){
            file << students[i].options[j] << " ";
        }
        file << "\n";
    }
    file.close();
}

void printOptionCandidates(vector<vector<student>> options, vector<student> students, pair<int, int>* option_slot, int m){
    ofstream file("Exercise_3_Output.txt");
    for (int i = 0; i < m; i++){
        file << "Successful candidates for option " << option_slot[i].first << ":\n";
        cout << "Successful candidates for option " << option_slot[i].first << ":\n";
        for (int j = 0; j < options[i].size(); j++){
            file << j + 1 << ". " << options[i][j].name << " " << options[i][j].avgPoint << "\n";
            cout << j + 1 << ". " << options[i][j].name << " " << options[i][j].avgPoint << "\n";
        }
    }

    file << "Unsuccessful candidates:\n";
    cout << "Unsuccessful candidates:\n";
    int j = 1;
    for (int i = 0; i < students.size(); i++){
        if (!students[i].selected){
            file << j << ". " << students[i].name << " " << students[i].avgPoint << "\n";
            cout << j << ". " << students[i].name << " " << students[i].avgPoint << "\n";
            j++;
        }
    }
    file.close();
}

int main(){
    vector<student> students;
    pair<int, int>* option_slot;
    int m;
    readFile("Exercise_3.txt", students, option_slot, m);
    sortStudents(students);
    printAllStudents(students, m);

    vector<vector<student>> optionCandidates;
    selectStudents(students, option_slot, m, optionCandidates);
    printOptionCandidates(optionCandidates, students, option_slot, m);
    return 0;
}
