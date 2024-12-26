#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <vector>

using namespace std;

int getYear(){
    time_t now = std::time(0);
    tm *localTime = std::localtime(&now);
    int year = localTime->tm_year + 1900; // tm_year tính từ 1900
    std::cout << "Nam hien tai: " << year << std::endl;
    return year;
}
const int YEARNOW = getYear();

struct Person {
    string id;
    string name;
    string birthYear;
};

string normalizeBirthYear(string yearStr, int yearNow = YEARNOW){
    int year = stoi(yearStr);
    if (year > yearNow) {
        yearNow = yearNow % 100;
        year = year % 100 + 1900;
        return to_string(year);
    } 
    return to_string(year);
}

void readFile(vector<Person> &people, string &header, string fileName = "employee.txt"){
    const char delimiter = ',';
    ifstream inputFile(fileName);
    string line;
    getline(inputFile, header);

    while (getline(inputFile, line)){
        vector<std::string> tokens; // Vector để lưu các chuỗi con
        string token;
        istringstream tokenStream(line); // Tạo một stream từ chuỗi

        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        Person person;
        person.id = tokens[0];
        person.name = tokens[1];
        person.birthYear = normalizeBirthYear(tokens[2]);
        people.push_back(person);
    }
    inputFile.close();
}

// insertionSort sap xep theo nguyen ly xep bai tay
void insertionSort(vector<Person> &people){
    int n = people.size();
    for (int i = 1; i < n; i++){
        int pos = i; Person x = people[i];// lay phan tu a[i] de sap xep vao mang a[0], a[i - 1]
        while (pos > 0 && x.birthYear > people[pos - 1].birthYear){
            people[pos] = people[pos - 1];
            pos -= 1;
        }
        people[pos] = x;
    }
}

// selectionSort tim phan tu nho nhat trong mang (duyet het), day len dau
void selectionSort(vector<Person> &people){
    int n = people.size();
    for (int i = 0; i < n; i++){
        int pos = i; Person now = people[i];
        for (int j = i; j < n; j++){
            if (now.birthYear <= people[j].birthYear) {
                pos = j; now = people[j];
            }
        }
        Person temp = people[i]; // swap(a[i], a[pos]);
        people[i] = people[pos];
        people[pos] = temp;
    }
}

// interchangeSort tim va ngay lap tuc day phan tu nho hon len dau
void interchangeSort(vector<Person> &people){
    int n = people.size();
    for (int i = 0; i < n; i++){
        for (int j = i; j < n; j++){
            if (people[j].birthYear > people[i].birthYear){
                Person temp = people[i]; //swap(a[i], a[j]);
                people[i] = people[j];
                people[j] = temp;
            }
        }
    }
}

void insertionSortByName(vector<Person> &people, int start, int end){
    int n = people.size();
    for (int i = start + 1; i <= end; i++){
        int pos = i; Person x = people[i];// lay phan tu a[i] de sap xep vao mang a[0], a[i - 1]
        while (pos > start && x.name < people[pos - 1].name){
            people[pos] = people[pos - 1];
            pos -= 1;
        }
        people[pos] = x;
    }
}

void sortByName(vector<Person> &people){
    int n = people.size();
    int i = 0, j = 0;
    while (i < n) {
        while (people[j + 1].birthYear == people[i].birthYear && j < n) j++;
        if (i != j) insertionSortByName(people, i, j);
        i = j + 1; j = i;
    }
}

void sortData(vector<Person> &people, int typesort){
    if (typesort == 1) insertionSort(people);
    if (typesort == 2) selectionSort(people);
    if (typesort == 3) interchangeSort(people);
    sortByName(people);
}

void writeFile(vector<Person> people, string header, string fileName = "sortedemponage.txt"){
    ofstream outputFile(fileName);
    outputFile << header << "\n";
    for (const auto &person : people) {
        outputFile << person.id << "," << person.name << "," << person.birthYear << "\n";
    }
}

int main() {
    vector<Person> people;
    string header;
    readFile(people, header);

    int typeSort = 1;
    cout << "Input type sort (1: insertion sort, 2: selection sort, 3: interchange sort): ";
    cin >> typeSort;

    sortData(people, typeSort);
    writeFile(people, header);

    cout << header << "\n";
    for (const auto &person : people) {
        cout << person.id << "," << person.name << "," << person.birthYear << "\n";
    }

    return 0;
}