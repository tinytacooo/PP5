#include "Graph.hpp"

void Graph::addVertex(std::string label) {
    V.insert({label, Vertex(label)});
}

void Graph::removeVertex(std::string label) {
    Vertex* v = &(V.at(label));

    std::cout << "FOUND VERTEX: " << v->getLabel() << std::endl;
/*
    for (auto it : V) {
        if(it.first != label && it.second.getAdjacentVertices().find(label) != it.second.getAdjacentVertices().end())
            std::cout << "AT VERTEX " << it.first << " FOUND " << it.second.getAdjacentVertices().find(label)->first << std::endl;
    }
*/

    for (auto it : V) {
        for (std::set<Vertex*>::iterator itr = it.second.getAdjacentVertices().begin(); itr != it.second.getAdjacentVertices().end(); itr++) {
            std::cout << *itr << std::endl;
        }
        Vertex* v = it.second.findVertex(label);
    }

    V.erase(label);
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

Vertex* Graph::Vertex::findVertex(std::string label) {
    for (auto it : adjVertices) {
        if (label == it->getLabel())
            return it;
    }

    return nullptr;
}

void Graph::addAdjacency(std::string curr, std::string adj) {
//    Vertex* v = &(V.at(adj));
    V.at(curr).addAdjVertex(&(V.at(adj)));
}

void Graph::printGraph() {
    std::cout << "VERTICES:\n";
    for (auto it : V) {
        std::cout << it.second.getLabel() << "\t=>";
        for (auto itr : it.second.getAdjacentVertices())
            std::cout << "\t" << itr->getLabel();
        std::cout << "\n";
    }
}
