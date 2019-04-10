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
    if (getEdgeId(label1) != 0)
        E.erase(getEdgeId(label1));
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {
    std::map<std::string, unsigned long> unvisited;    // contains unvisited vertices: <label, distance_to_vertex>
    std::map<std::string, std::string> visited;        // contains visited vertices:   <label, adjacent_vertex_with_shortest_distance>
    unsigned long shortestDistance = 0;                // return this value as the distance of the shortest possible path

    // set all vertices in "unvisited" to have an initial distance of 'infinity' from the start vtx (except start vtx, which has an initial distance of 0)
    // set initial shortest path to each vertex as itself (eventually replace these values using Djikstra's algorithm)
    for (auto it : V) {
        (it.first == startLabel) ? unvisited.insert({it.first, 0}) : unvisited.insert({it.first, LONG_MAX});
        visited.insert({it.first, it.first});
    }

    // For each vertex, determine which of its adjacent vertices grants the shortest route to the start vertex.
    while (!unvisited.empty()) {
        std::string currLabel = getMinDistanceLabel(unvisited);     // get label of next vertex w/ shortest distance to start vertex
        unsigned long currDistance = unvisited.at(currLabel);       // get distance associated with current vertex

        for (auto it : V.at(currLabel).getAdjacentVertices()) {             // iterate through list of vertices adjacent to the current vertex
            if (isUnvisited(it.first, unvisited)) {                         // if adjacent vertex is unvisited
                // temporarily store value of distance associated with the adjecent vertex
                unsigned long oldDistance = unvisited.at(it.first);
                // compare the adjecent vertex's distance (oldDistance) with potential new distance (current vertex distance + weight of edge (curr, adj))
                unvisited.at(it.first) = compareDistances(currLabel, it.first, currDistance, oldDistance);
                // if oldDistance was replaced with newDistance, update shortest path to adjacent vertex with current vertex
                if (oldDistance != unvisited.at(it.first)) { visited.at(it.first) = currLabel; }
            }
        }

        unvisited.erase(currLabel);         // remove vertex from "unvisited" list
    }

    shortestDistance = buildPath(startLabel, endLabel, visited, path);

    return shortestDistance;
}

/* GRAPH helpers */
void Graph::addAdjacency(std::string curr, std::string adj) {
    V.at(curr).addAdjVertex(adj, &(V.at(adj)));
}

unsigned long Graph::buildPath(std::string startLabel, std::string endLabel, std::map<std::string, std::string> visited, std::vector<std::string>& path) {
    std::string currLabel = endLabel;
    unsigned long sum = 0;

    path.emplace(path.begin(), endLabel);
    while (currLabel != startLabel) {
        path.emplace(path.begin(), visited.at(currLabel));
        sum += getWeight(currLabel, visited.at(currLabel));
        currLabel = visited.at(currLabel);
    }

    return sum;
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

bool Graph::isUnvisited(std::string label, std::map<std::string, unsigned long> unvisited) {
    return (unvisited.find(label) != unvisited.end());
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
