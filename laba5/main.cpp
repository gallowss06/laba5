/* Лошкарев Тимофей ИУ8-25 ЛР5 Вариант 11
 Для класса, разработанного в ЛР4, обеспечить возможность добавления объектов в контейнер set (сортировка как указано в задании на ЛР4) и в контейнер unordered_set. Исходные данные как в ЛР4 читать из файла, вывести на печать для контроля объекты контейнеров.
 ЛР: Объект - студент (поля: ФИО, группа, номер зачетной книжки, массив 4-х оценок за сессию), Сортировка по среднему баллу, Исходный контейнер vector, копируем в deque*/
#include <iostream>
#include <fstream>
#include <set>
#include <unordered_set>
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
    
    set<Student> studentsSet;
    unordered_set<Student, StudentHash> studentsUnorderedSet;
    string fio, group, recordBook;
    int g1, g2, g3, g4;
    while (getline(input, fio)) {
        getline(input, group);
        getline(input, recordBook);
        input >> g1 >> g2 >> g3 >> g4;
        input.ignore();
        Student student(fio, group, recordBook, g1, g2, g3, g4);
        studentsSet.insert(student);
        studentsUnorderedSet.insert(student);
    }
    input.close();
    
    ofstream output("output.txt");
    
    cout << "Контейнер set (отсортирован по среднему баллу):" << endl;
    output << "Контейнер set (отсортирован по среднему баллу):" << endl;
    for (const auto& student : studentsSet) {
        cout << student << endl;
        output << student << endl;
    }
    cout << "\n" << "Контейнер unordered_set:" << endl;
    output << "\n" << "Контейнер unordered_set:" << endl;
    for (const auto& student : studentsUnorderedSet) {
        cout << student << endl;
        output << student << endl;
    }
    output.close();
}
