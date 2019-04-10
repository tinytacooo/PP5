#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include <algorithm>
#include <map>
#include <set>
#include <iostream> // REMOVE

class Vertex {
public:
    /* data members */
    std::string label;
    std::map<std::string, Vertex*> adjVertices;
    /* functions */
    Vertex(std::string l) : label(l) {};
    void addAdjVertex(std::string l, Vertex* v) { adjVertices.insert({l, v}); }
    int removeAdjVertex(std::string label) { return adjVertices.erase(label); } ;
    bool hasAdjVertex(std::string label);
    std::map<std::string, Vertex*> getAdjacentVertices() const { return adjVertices; }
    std::string getLabel() const { return label; }
    void printAdjV(); // REMOVE
    /* operator overloads */
    bool operator< (const Vertex & r) const { return ( this->label < r.label ); }
};

class Edge {
public:
    /* data members */
    std::string startVertex;
    std::string endVertex;
    unsigned long weight;
    /* functions */
    Edge(std::string sv, std::string ev, unsigned long w) : startVertex(sv), endVertex(ev), weight(w) {};
    /* operator overloads */
    bool operator< (const Edge & r) const { return ( this->startVertex < r.endVertex && this->endVertex < r.startVertex && this->weight < r.weight ); }
};

class Graph : public GraphBase {
public:
    void addVertex(std::string label);
    void removeVertex(std::string label);
    void addEdge(std::string label1, std::string label2, unsigned long weight);
    void removeEdge(std::string label1, std::string label2);
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
    /* helpers */
    void addAdjacency(std::string curr, std::string adj);   // to add vertex adjaceny
    void printGraph(); // REMOVE
private:
    std::map<std::string, Vertex> V;
    std::set<Edge> E;

};


#endif /* GRAPH_H */
