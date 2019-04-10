#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include <algorithm>
#include <climits>
#include <map>
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
    /* helpers */
    bool isStartVertex(std::string l1, std::string l2) { return (startVertex == l1 || startVertex == l2); }
    bool isStartVertex(std::string l1) { return (startVertex == l1); }
    bool isEndVertex(std::string l1, std::string l2) { return (endVertex == l1 || endVertex == l2); }
    bool isEndVertex(std::string l1) { return (endVertex == l1); }
};

class Graph : public GraphBase {
private:
    std::map<std::string, Vertex> V;      // <Vertex label, Vertex pointer>
    std::map<int, Edge> E;                // <Edge ID, Edge pointer>
    int edgeId = 0;                       // Assign an ID to each edge; this number only ever increases
public:
    /* functions inherited from abstract class */
    void addVertex(std::string label);
    void removeVertex(std::string label);
    void addEdge(std::string label1, std::string label2, unsigned long weight);
    void removeEdge(std::string label1, std::string label2);
    void removeEdge(std::string label1);
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
    /* helpers */
    void addAdjacency(std::string curr, std::string adj);                           // add vertex adjaceny
    unsigned long buildPath(std::string startLabel, std::string endLabel, std::map<std::string, std::string> visited, std::vector<std::string>& path);
    unsigned long compareDistances(std:: string curr, std::string adj, unsigned long currDistance, unsigned long oldDistance);
    int getEdgeId(std::string label1, std::string label2);                          // return edgeId of edge containing a pair of vertices
    int getEdgeId(std::string label1);                                              // return edgeId of edge containing a vertex
    std::string getMinDistanceLabel(std::map<std::string, unsigned long> vDist);    // return label of vertex w/ min distance to start vertex
    unsigned long getWeight(std::string curr, std::string adj);                     // get weight of edge, given a pair of vertices
    bool isUnvisited(std::string label,std:: map<std::string, unsigned long> unvisited);
    void printGraph(); // REMOVE
};


#endif /* GRAPH_H */
