// ============================================================
// ПРОГРАМА №2 — Контейнерні класи для типу користувача
// Варіант 8: Перший контейнер — list, Другий — map, Тип — Student
// ============================================================

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <iomanip>
#include <algorithm>
#include <clocale>

using namespace std;

struct Student {
    string name;
    int    group;
    float  gpa;

    Student() : name(""), group(0), gpa(0.0f) {}
    Student(const string& n, int g, float r) : name(n), group(g), gpa(r) {}

    bool operator==(const Student& o) const {
        return name == o.name && group == o.group;
    }

    friend ostream& operator<<(ostream& os, const Student& s) {
        os << left << setw(12) << s.name
            << " гр=" << setw(4) << s.group
            << " GPA=" << fixed << setprecision(2) << s.gpa;
        return os;
    }
};

void printListS(const list<Student>& lst, const string& title) {
    cout << "\n[" << title << "] list<Student> (" << lst.size() << " елем.):\n";
    int i = 1;
    for (list<Student>::const_iterator it = lst.begin(); it != lst.end(); ++it, ++i)
        cout << "  " << i << ". " << *it << "\n";
}

void printMapS(const map<int, Student>& m, const string& title) {
    cout << "\n[" << title << "] map<int,Student> (" << m.size() << " пар):\n";
    for (map<int, Student>::const_iterator it = m.begin(); it != m.end(); ++it)
        cout << "  ключ=" << setw(3) << it->first << " -> " << it->second << "\n";
}

int main() {
    setlocale(LC_ALL, "Ukrainian");
    cout << "========================================\n";
    cout << " ПРОГРАМА 2: list<Student> + map<int,Student>\n";
    cout << "========================================\n";

    list<Student> lst1;
    lst1.push_back(Student("Ivanenko", 101, 4.5f));
    lst1.push_back(Student("Petrenko", 102, 3.8f));
    lst1.push_back(Student("Sydorenko", 101, 4.9f));
    lst1.push_back(Student("Koval", 103, 3.2f));
    lst1.push_back(Student("Melnyk", 102, 4.1f));
    lst1.push_back(Student("Boyko", 101, 2.9f));
    lst1.push_back(Student("Shevchenko", 103, 4.7f));

    cout << "\n--- Крок 1: Створено list<Student> ---";
    printListS(lst1, "lst1 початковий");

    cout << "\n--- Крок 2: Перегляд ---";
    printListS(lst1, "lst1");

    cout << "\n--- Крок 3: Видаляємо GPA < 3.5, замінюємо Petrenko ---";
    lst1.remove_if([](const Student& s) { return s.gpa < 3.5f; });
    for (list<Student>::iterator it = lst1.begin(); it != lst1.end(); ++it)
        if (it->name == "Petrenko") { it->name = "Petrenko*"; it->gpa = 4.0f; }
    printListS(lst1, "lst1 після змін");

    cout << "\n--- Крок 4: Перегляд через ітератор ---\n";
    int idx = 0;
    for (list<Student>::iterator it = lst1.begin(); it != lst1.end(); ++it, ++idx)
        cout << "  [" << idx << "] " << *it << "\n";

    cout << "\n--- Крок 5: Другий list<Student> ---";
    list<Student> lst2;
    lst2.push_back(Student("Hrytsenko", 201, 4.3f));
    lst2.push_back(Student("Khomenko", 202, 3.9f));
    lst2.push_back(Student("Yaremenko", 201, 4.8f));
    printListS(lst2, "lst2");

    cout << "\n--- Крок 6: Видаляємо 2 елементи після першого, додаємо lst2 ---";
    {
        list<Student>::iterator it = lst1.begin();
        ++it;
        int n = 2;
        for (int i = 0; i < n && it != lst1.end(); i++)
            it = lst1.erase(it);
    }
    lst1.insert(lst1.end(), lst2.begin(), lst2.end());

    cout << "\n--- Крок 7: Фінальний перегляд ---";
    printListS(lst1, "lst1 фінальний");
    printListS(lst2, "lst2 фінальний");

    cout << "\n========================================\n";
    cout << " Другий контейнер: map<int, Student>\n";
    cout << "========================================\n";

    map<int, Student> map1;
    map1[1] = Student("Ivanenko", 101, 4.5f);
    map1[2] = Student("Petrenko", 102, 3.8f);
    map1[3] = Student("Sydorenko", 101, 4.9f);
    map1[4] = Student("Koval", 103, 3.2f);
    map1[5] = Student("Melnyk", 102, 4.1f);

    cout << "\n--- Крок 1: Створено map<int,Student> ---";
    printMapS(map1, "map1 початковий");

    cout << "\n--- Крок 2: Перегляд ---";
    printMapS(map1, "map1");

    cout << "\n--- Крок 3: Видаляємо ключ 4, змінюємо студента з ключем 2 ---";
    map1.erase(4);
    map1[2] = Student("Petrenko+", 102, 4.5f);
    printMapS(map1, "map1 після змін");

    cout << "\n--- Крок 4: Ітератор ---\n";
    for (map<int, Student>::iterator it = map1.begin(); it != map1.end(); ++it)
        cout << "  ключ=" << it->first << " -> " << it->second << "\n";

    cout << "\n--- Крок 5: Другий map<int,Student> ---";
    map<int, Student> map2;
    map2[10] = Student("Hrytsenko", 201, 4.3f);
    map2[20] = Student("Khomenko", 202, 3.9f);
    printMapS(map2, "map2");

    cout << "\n--- Крок 6: Видаляємо 1 після першого, додаємо map2 ---";
    {
        map<int, Student>::iterator it = map1.begin();
        ++it;
        if (it != map1.end()) map1.erase(it);
    }
    map1.insert(map2.begin(), map2.end());

    cout << "\n--- Крок 7: Фінальний перегляд ---";
    printMapS(map1, "map1 фінальний");
    printMapS(map2, "map2 фінальний");

    return 0;
}