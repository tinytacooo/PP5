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
    void removeAdjVertex(std::string label) { adjVertices.erase(label); }
    std::map<std::string, Vertex*> getAdjacentVertices() const { return adjVertices; }
    std::string getLabel() const { return label; }
    /* helpers, operator overloads */
    bool hasAdjVertex(std::string label);
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
    std::string getStartVertex() { return startVertex; }
    std::string getEndVertex() { return endVertex; }
    unsigned long getWeight() { return weight; }
    /* helpers, operator overloads */
    bool isStartVertex(std::string l1, std::string l2) { return (startVertex == l1 || startVertex == l2); }
    bool isStartVertex(std::string l1) { return (startVertex == l1); }
    bool isEndVertex(std::string l1, std::string l2) { return (endVertex == l1 || endVertex == l2); }
    bool isEndVertex(std::string l1) { return (endVertex == l1); }
    bool operator< (const Edge & r) const { return ( this->startVertex < r.endVertex && this->endVertex < r.startVertex && this->weight < r.weight ); }
};

class Graph : public GraphBase {
private:
    std::map<std::string, Vertex> V;      // <Vertex label, Vertex pointer>
    std::map<int, Edge> E;                // <Edge ID, Edge pointer>
    int edgeId = 0;                       // Keep track of edge ID; this does not indicate the length of the Edge map
public:
    /* functions from abstract class */
    void addVertex(std::string label);
    void removeVertex(std::string label);
    void addEdge(std::string label1, std::string label2, unsigned long weight);
    void removeEdge(std::string label1, std::string label2);
    void removeEdge(std::string label1);
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
    /* helpers */
    void addAdjacency(std::string curr, std::string adj);               // add vertex adjaceny
    int  getEdgeId(std::string label1, std::string label2);             // each edge has an id; returns this value
    int  getEdgeId(std::string label1);
    void printGraph(); // REMOVE
};


#endif /* GRAPH_H */
