#include "Graph.hpp"

void Graph::addVertex(std::string label) {
    V.insert({label, Vertex(label)});
}

void Graph::removeVertex(std::string label) {
    Vertex* v = &(V.at(label));

    std::cout << "FOUND VERTEX: " << v->getLabel() << std::endl;

    for (std::map<std::string, Vertex>::iterator it = V.begin(); it != V.end(); it++) {
        bool b = it->second.hasAdjVertex(label);
        std::cout << (b ? "HAS VERTEX" : "DOES NOT HAVE VERTEX") << std::endl;

        if(v != nullptr) {
            std::cout << "FROM " << it->first << " REMOVING " << v->getLabel() << std::endl;
            std::cout << "REMOVED " << it->second.removeAdjVertex(label) << " RECORDS\n";
        }
    }

//    V.erase(label);
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    E.insert(Edge(label1, label2, weight));

    addVertex(label1);
    addVertex(label2);

    addAdjacency(label1, label2);
    addAdjacency(label2, label1);

//    std::cout << "VERTEX AT LABEL1: " << V.at(label1).getLabel() << std::endl;
}

void Graph::removeEdge(std::string label1, std::string label2) {
    std::cout << "removeEdge called\n";
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {
    std::cout << "shortestPath called\n";

    return 0;
}

/* helpers */

bool Vertex::hasAdjVertex(std::string label) {
    if (adjVertices.find(label) != adjVertices.end())
        return true;
    else
        return false;
}

void Graph::addAdjacency(std::string curr, std::string adj) {
    V.at(curr).addAdjVertex(adj, &(V.at(adj)));
}

void Vertex::printAdjV() {
    for (auto it : adjVertices)
        std::cout << it.first << " ";
}

void Graph::printGraph() {
    std::cout << "VERTICES:\n";
    for (auto it : V) {
        std::cout << it.second.getLabel() << "\t=>";
        for (auto itr : it.second.getAdjacentVertices())
            std::cout << "\t" << itr.first;
        std::cout << "\n";
    }
}
