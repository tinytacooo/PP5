#include "Graph.hpp"

/* GRAPH methods */

void Graph::addVertex(std::string label) {
    V.insert({label, Vertex(label)});       // add new Vertex object (and its label) to the vector map in Graph
}

void Graph::removeVertex(std::string label) {
    removeEdge(label);          // remove edges associated with this vertex
    removeAdjacencies(label);   // remove references to this vertex from adjacency list in other vertices
    V.erase(label);             // erase Vertex entry in map
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    if(getEdgeId(label1, label2) == 0) {
        E.insert({++edgeId, Edge(label1, label2, weight)});     // add unique edgeId and Edge to map in Graph

        addVertex(label1);              // if needed, add starting vertex to Vector map
        addVertex(label2);              // if needed, add ending vertex to Vector map

        addAdjacency(label1, label2);   // add reference to end vertex to start vertex's adjacency list
        addAdjacency(label2, label1);   // (and vice versa)
    }
}

void Graph::removeEdge(std::string label1, std::string label2) {
    int id = getEdgeId(label1, label2);           // find unique edgeId associated with this vertex pair
    if (id != 0) {                                // if there is a nonzero edgeId for the pair
        removeAdjacencies(label1, label2);        // remove references to each vertex from the other's adjacency list
        E.erase(id);                              // erase entry in Edge map
    }
}

void Graph::removeEdge(std::string label) {
    for (std::map<int, Edge>::iterator it = E.begin(); it != E.end(); it++)
        removeEdge(label, it->second.getOtherVertex(label));               // remove any edges containing the specified vertex
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {
    std::map<std::string, unsigned long> unvisited;    // contains unvisited vertices: <label, distance_to_vertex>
    std::map<std::string, std::string> visited;        // contains visited vertices:   <label, adjacent_vertex_with_shortest_distance>

    // set all vertices in "unvisited" to have an initial distance of 'infinity' from the start vertex (except start vertex, which has an initial distance of 0)
    // set initial shortest path to each vertex as itself (eventually replace these values using Djikstra's algorithm)
    for (auto it : V) {
        (it.first == startLabel) ? unvisited.insert({it.first, 0}) : unvisited.insert({it.first, LONG_MAX});
        visited.insert({it.first, it.first});
    }

    // For each vertex, determine which of its adjacent vertices grants the shortest route to the start vertex.
    while (!unvisited.empty()) {
        std::string currLabel = getMinDistanceLabel(unvisited);     // get label of next vertex w/ shortest distance to start vertex
        unsigned long currDistance = unvisited.at(currLabel);       // get distance associated with current vertex

        for (auto it : V.at(currLabel).getAdjacentVertices()) {                                             // iterate through list of vertices adjacent to the current vertex
            if (isUnvisited(it.first, unvisited)) {                                                         // if adjacent vertex is unvisited:
                unsigned long oldDistance = unvisited.at(it.first);                                         // temporarily store value of distance associated with the adjacent vertex
                unvisited.at(it.first) = shorterDistance(currLabel, it.first, currDistance, oldDistance);   // compare the adjacent vertex's distance (oldDistance) with potential new distance (current_vertex_distance + weight_of_edge(curr, adj))
                if (oldDistance != unvisited.at(it.first)) { visited.at(it.first) = currLabel; }            // if oldDistance was replaced with newDistance (ie newDistance is shorter), update shortest path to adjacent vertex with current vertex
            }
        }

        unvisited.erase(currLabel);                             // remove (now visited) vertex from "unvisited" list
    }

    return buildPath(startLabel, endLabel, visited, path);      // build the path and return the shortest distance calculated
}

/* billy cobham - glass menagerie */

/* GRAPH helpers */

void Graph::addAdjacency(std::string curr, std::string adj) {
    V.at(curr).addAdjVertex(adj, &(V.at(adj)));
}

unsigned long Graph::buildPath(std::string startLabel, std::string endLabel, std::map<std::string, std::string> visited, std::vector<std::string>& path) {
    std::string currLabel = endLabel;
    unsigned long sum = 0;                  // shortest path; return this number
    path.emplace(path.begin(), endLabel);   // add ending vertex to the beginning of the path

    while (currLabel != startLabel) {
        path.emplace(path.begin(), visited.at(currLabel));      // add current vertex to beginning of path
        sum += getWeight(currLabel, visited.at(currLabel));     // add edge weight bewteen current and next vertex to the shortest path
        currLabel = visited.at(currLabel);                      // go to next vertex in the path
    }

    return sum;
}

int Graph::getEdgeId(std::string label1, std::string label2) {
    for (auto it : E) {
        if (it.second.isStartVertex(label1, label2) && it.second.isEndVertex(label1, label2))
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

void Graph::removeAdjacencies(std::string label) {
    for (std::map<std::string, Vertex>::iterator it = V.begin(); it != V.end(); it++)
        it->second.removeAdjacency(label);
}

void Graph::removeAdjacencies(std::string label1, std::string label2) {
    V.at(label1).removeAdjacency(label2);
    V.at(label2).removeAdjacency(label1);
}

unsigned long Graph::shorterDistance(std:: string curr, std::string adj, unsigned long currDistance, unsigned long oldDistance) {
    unsigned long newDistance = currDistance + getWeight(curr, adj);
    return ((newDistance < oldDistance) ? newDistance : oldDistance);
}

/* EDGE methods */

std::string Edge::getOtherVertex(std::string label) {
    if (isStartVertex(label))
        return endVertex;
    else if (isEndVertex(label))
        return startVertex;
    else
        return "";
}
