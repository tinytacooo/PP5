#include "Graph.hpp"

/* GRAPH methods */

void Graph::addVertex(std::string label) {
    V.insert({label, Vertex(label)});
}

void Graph::removeVertex(std::string label) {
    for (std::map<int, Edge>::iterator it = E.begin(); it != E.end(); it++)
        removeEdge(label);

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
}

void Graph::removeEdge(std::string label1) {
    int id = getEdgeId(label1);
    if (id != 0)
        E.erase(id);
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {
    std::map<std::string, unsigned long> vertexDistance;
    std::map<std::string, std::string> minDistances;
    for (auto it : V) {
        vertexDistance.insert({it.first, LONG_MAX});    // all vertices have an initial distance of 'infinity'
        minDistances.insert({it.first, it.first});         // initial shortest path in direction of start vertex from each vertex is unknown
    }

    vertexDistance.at(startLabel) = 0;      // distance from start vertex to itself is 0

    while (!vertexDistance.empty()) {
        std::string currLabel = getMinDistanceLabel(vertexDistance);
        Vertex curr = V.at(currLabel);
        unsigned long currDistance = vertexDistance.at(currLabel);

        for (auto it : curr.getAdjacentVertices()) {
            if (vertexDistance.find(it.first) != vertexDistance.end()) {
                unsigned long oldDistance = vertexDistance.at(it.first);
                vertexDistance.at(it.first) = compareDistances(currLabel, it.first, currDistance, oldDistance);
                (oldDistance != vertexDistance.at(it.first)) ? minDistances.at(it.first) = currLabel : it.first;
            }
        }

        vertexDistance.erase(currLabel);
    }

    std::string currLabel = endLabel;
    unsigned int sum = 0;
    path.emplace(path.begin(), endLabel);
    while (currLabel != startLabel) {
        path.emplace(path.begin(), minDistances.at(currLabel));
        sum += getWeight(currLabel, minDistances.at(currLabel));
        currLabel = minDistances.at(currLabel);
    }

    return sum;
}

/* GRAPH helpers */
void Graph::addAdjacency(std::string curr, std::string adj) {
    V.at(curr).addAdjVertex(adj, &(V.at(adj)));
}

unsigned long Graph::compareDistances(std:: string curr, std::string adj, unsigned long currDistance, unsigned long oldDistance) {
    unsigned long newDistance = currDistance + getWeight(curr, adj);
    if (newDistance < oldDistance)
        return newDistance;
    else
        return oldDistance;
}

int Graph::getEdgeId(std::string label1, std::string label2) {
    for (auto it : E) {
        if (it.second.isStartVertex(label1, label2) && it.second.isEndVertex(label1, label2))
            return it.first;
    }
    return 0;
}

int Graph::getEdgeId(std::string label1) {
    for (auto it : E) {
        if (it.second.isStartVertex(label1) || it.second.isEndVertex(label1))
            return it.first;
    }
    return 0;
}

std::string Graph::getMinDistanceLabel(std::map<std::string, unsigned long> vDist) {
    std::string ret;
    unsigned long min = LONG_MAX;
    for (auto it : vDist) {
        if (it.second < min) {
            ret = it.first;
            min = it.second;
        }
    }
    return ret;
}

unsigned long Graph::getWeight(std::string curr, std::string adj) {
    return E.at(getEdgeId(curr, adj)).getWeight();
}

/* REMOVE */

void Graph::printGraph() {
    std::cout << "VERTICES:\n";
    for (auto it : V) {
        std::cout << it.second.getLabel() << "  =>";
        for (auto itr : it.second.getAdjacentVertices())
            std::cout << "  " << itr.first;
        std::cout << "\n";
    }

    std::cout << "EDGES:\n";
    for (auto it : E) {
        std::cout << it.first << ":  " << it.second.getStartVertex() <<  "  " << it.second.getEndVertex() << "  " << it.second.getWeight() << std::endl;
    }
}
