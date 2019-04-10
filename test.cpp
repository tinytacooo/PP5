/* test file */

/****** TDD GRAPH TEST **********/

#include "Graph.hpp"
#include <iostream>
using namespace std;

struct EdgeStruct { std::string a; std::string b; unsigned long w; };

int main() {
    Graph g;

    std::vector<std::string> vertices1 { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12" };
    std::vector<EdgeStruct> edges1 {
      {"0", "1", 1}, {"0", "4", 1}, {"1", "2", 2}, {"1", "5", 2}, {"2", "6", 1}, {"2", "3", 1},
      {"3", "7", 2}, {"4", "8", 2}, {"5", "6", 1}, {"5", "10", 4}, {"6", "11", 2}, {"7", "12", 1},
      {"8", "9", 3}, {"9", "10", 1}, {"10", "11", 2}, {"11", "12", 5}
    };
    std::vector<std::string> path;

    for (const auto label : vertices1) g.addVertex(label);
    for (const auto &e : edges1) g.addEdge(e.a, e.b, e.w);

    g.printGraph();
    g.shortestPath("1", "12", path);

    return 0;
}

/****** USER INPUT GRAPH TEST *******

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
            case 3: { cin >> v1; cin >> v2; cin >> n; G.addEdge(v1, v2, n); break; }
            case 4: { cin >> v1; cin >> v2; G.removeEdge(v1, v2); break; }
        }

        G.printGraph();
    }

    return 0;
}
*/

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
