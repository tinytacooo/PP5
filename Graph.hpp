#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include <algorithm>
#include <map>
#include <set>
#include <iostream> // REMOVE

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

public:
    class Vertex {
    public:
        /* data members */
        std::string label;
        std::set<Vertex*> adjVertices;
        /* functions */
        Vertex(std::string l) : label(l) {};
        void addAdjVertex(Vertex* v) { adjVertices.insert(v); }
        void removeAdjVertex(Vertex* v);
        Vertex* findVertex(std::string label);
        std::set<Vertex*> getAdjacentVertices() const { return adjVertices; }
        std::string getLabel() const { return label; }
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

private:
    std::map<std::string, Vertex> V;
    std::set<Edge> E;

};


#endif /* GRAPH_H */
