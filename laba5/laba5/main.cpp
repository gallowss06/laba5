#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <set>
#include <unordered_set>
#include <algorithm>
using namespace std;
class Student {
public:
    string fio;
    string group;
    string zachetka;
    int grades[4];
    
    Student(string f = "", string g = "", string r = "", int g1 = 0, int g2 = 0, int g3 = 0, int g4 = 0) {
        fio = f;
        group = g;
        zachetka = r;
        grades[0] = g1;
        grades[1] = g2;
        grades[2] = g3;
        grades[3] = g4;
    }
    double getAverage() const {
        double sum = 0;
        for (int i = 0; i < 4; i++) {
            sum += grades[i];
        }
        return sum / 4;
    }
    bool operator<(const Student& other) const {
        return this->getAverage() < other.getAverage();
    }
    bool operator==(const Student& other) const {
        return this->fio == other.fio && this->group == other.group && this->zachetka == other.zachetka;
    }
};
ostream& operator<<(ostream& os, const Student& student) {
    os << "ФИО: " << student.fio << ", Группа: " << student.group
       << ", Зачетка: " << student.zachetka << ", Оценки: ";
    for (int i = 0; i < 4; i++) {
        os << student.grades[i] << " ";
    }
    os << ", Средний балл: " << student.getAverage();
    return os;
}
struct StudentHash {
    size_t operator()(const Student& student) const {
        size_t h1 = hash<string>()(student.fio);
        size_t h2 = hash<string>()(student.group);
        size_t h3 = hash<string>()(student.zachetka);
        return h1 ^ h2 ^ h3; // Просто XOR, ничего сложного
    }
};
int main() {
    ifstream input("input.txt");
    if (!input.is_open()) {
        cout << "Ошибка открытия файла input.txt" << endl;
        return 1;
    }
    vector<Student> students;
    string fio, group, recordBook;
    int g1, g2, g3, g4;
    while (getline(input, fio)) {
        getline(input, group);
        getline(input, recordBook);
        input >> g1 >> g2 >> g3 >> g4;
        input.ignore(); // Чтобы не было проблем с getline
        students.push_back(Student(fio, group, recordBook, g1, g2, g3, g4));
    }
    input.close();
           
    ofstream output("output.txt");
    if (!output.is_open()) {
        cout << "Ошибка открытия файла output.txt" << endl;
        return 1;
    }
    output << "Исходный контейнер (vector):" << endl;
    for (const auto& student : students) {
        output << student << endl;
    }
    sort(students.begin(), students.end());
    output << "\nКонтейнер после сортировки (vector):" << endl;
    for (const auto& student : students) {
        output << student << endl;
    }
    deque<Student> studentsDeque;
    for (const auto& student : students) {
        studentsDeque.push_back(student);
    }
    output << "\nСкопированный контейнер (deque):" << endl;
    for (const auto& student : studentsDeque) {
        output << student << endl;
    }
    set<Student> studentsSet;
    for (const auto& student : students) {
        studentsSet.insert(student);
    }
    output << "\nКонтейнер set:" << endl;
    for (const auto& student : studentsSet) {
        output << student << endl;
    }
    unordered_set<Student, StudentHash> studentsUnorderedSet;
    for (const auto& student : students) {
        studentsUnorderedSet.insert(student);
    }
    output << "\nКонтейнер unordered_set:" << endl;
    for (const auto& student : studentsUnorderedSet) {
        output << student << endl;
    }
    output.close();
}
