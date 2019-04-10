#include "Graph.hpp"

/* GRAPH methods */

void Graph::addVertex(std::string label) {
    V.insert({label, Vertex(label)});
}

void Graph::removeVertex(std::string label) {
    for (std::map<std::string, Vertex>::iterator it = V.begin(); it != V.end(); it++)
            it->second.removeAdjVertex(label);

    V.erase(label);
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    if(getEdgeId(label1, label2) == 0) {
        E.insert({++edgeId, Edge(label1, label2, weight)});

        addVertex(label1);
        addVertex(label2);

        addAdjacency(label1, label2);
        addAdjacency(label2, label1);
    }
}

void Graph::removeEdge(std::string label1, std::string label2) {
    int id = getEdgeId(label1, label2);
    if (id != 0) {
        removeVertex(label1);
        removeVertex(label2);
        E.erase(id);
    }
    else std::cout << "EDGE NOT DELETED\n";
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {
    std::cout << "shortestPath called\n";

    return 0;
}

/* GRAPH helpers */
void Graph::addAdjacency(std::string curr, std::string adj) {
    V.at(curr).addAdjVertex(adj, &(V.at(adj)));
}

bool Graph::isAdjVertex(std::string label1, std::string label2) {
    return (hasVertex(label1) && hasVertex(label2) && V.at(label1).hasAdjVertex(label2));
}

int Graph::getEdgeId(std::string label1, std::string label2) {
    for (auto it : E) {
        if (it.second.isStartVertex(label1, label2) && it.second.isEndVertex(label1, label2))
            return it.first;
    }

    return 0;
}

/* VERTEX methods */

bool Vertex::hasAdjVertex(std::string label) {
    return (adjVertices.find(label) != adjVertices.end());
}

/* REMOVE */

void Vertex::printAdjV() {
    for (auto it : adjVertices)
        std::cout << it.first << " ";
}

void Graph::printGraph() {
/*    std::cout << "VERTICES:\n";
    for (auto it : V) {
        std::cout << it.second.getLabel() << "\t=>";
        for (auto itr : it.second.getAdjacentVertices())
            std::cout << "\t" << itr.first;
        std::cout << "\n";
    }
*/
    std::cout << "EDGES:\n";
    for (auto it : E) {
        std::cout << it.first << " " << it.second.getStartVertex() <<  "  " << it.second.getEndVertex() << "  " << it.second.getWeight() << std::endl;
    }
}
