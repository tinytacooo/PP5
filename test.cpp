/* test file */

/****** GRAPH TEST ********/

#include "Graph.hpp"
#include <iostream>
using namespace std;
int main() {
    Graph G;

    while (1) {
        int opt;
        string v1;
        string v2;
        int n;

        cin >> opt;
        if (opt == 0)
            return 0;

        switch(opt) {
            case 1: { cin >> v1; G.addVertex(v1); break; }
            case 2: { cin >> v1; G.removeVertex(v1); break; }
            case 3: { cin >> v1; cin >> v2; cin >> n; G.addEdge(v1, v2, n); }
        }

        G.printGraph();
    }

    return 0;
}

/****** GENERIC TEST ********

#include <bits/stdc++.h>
using namespace std;

class Person {
public:
    Person(string n, int a) : name(n), age(a) {};
    string getName() const { return name; }
    int getAge() const { return age; }
    bool operator< (const Person & newPerson) const { return (this->age < newPerson.age && this->name < newPerson.name); }
private:
    string name;
    int age;
};

int main() {
    std::set<Person> P;

    P.insert(Person("Amy", 21));
    P.insert(Person("Bob", 22));
    P.insert(Person("Cal", 23));

    for (auto it : P)
        cout << it.getName() << endl;

    string search = "Bob";
    set<Person>::iterator it = P.begin();

    while (++it != P.end()) {
        if (it->getName() == search) {
            P.erase(it);
            break;
        }
    }

    for (auto it : P)
        cout << it.getName() << endl;

	return 0;
}
*/
