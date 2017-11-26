#include "Graph.h"
#include <vector>
#include <string>
#include <iostream>
#include <queue>

using namespace std;

template<typename T>
Graph<T>::Graph() {

};

template<typename T>
Graph<T>::~Graph() {

};

template<typename T>
void Graph<T>::displayEdges() {
    for(int i = 0; i < vertices.size(); i++) {
        cout<<vertices[i].district<<":"<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++) {
            cout<<vertices[i].adj[j].v->name;
            if(j != vertices[i].adj.size()-1) {
                cout<<"***";
            }
        }
        cout<<endl;
    }
};

template<typename T>
void Graph<T>::addEdge(T v1, T v2, int weight) {
    for(int i = 0; i < vertices.size(); i++) {
        if(vertices[i].name == v1) {
            for(int j = 0; j < vertices.size(); j++) {
                if(i!=j && vertices[j].name == v2) {
                    adjVertex<string> newPath;
                    newPath.v = &vertices[j];
                    newPath.weight = weight;
                    vertices[i].adj.push_back(newPath);
                }
            }
        }
    }
};

template<typename T>
void Graph<T>::addVertex(T name) {
    for(int i = 0; i < vertices.size(); i++) {
        if(vertices[i].name==name) {
            return;
        }
    }
    vertex<string> newVertex;
    newVertex.name = name;
    newVertex.district = -1;
    newVertex.visited = false;
    newVertex.distance = 0;
    newVertex.ID = -1;
    vertices.push_back(newVertex);
};

template<typename T>
void Graph<T>::assignDistricts() {
    int distNum = 1;
    for(int i = 0; i < vertices.size(); i++) {
        if(vertices[i].district==-1) {
            BFTraversalLabel(vertices[i].name, distNum);
            distNum++;
        }
    }
};

template<typename T>
void Graph<T>::BFTraversalLabel(T startingCity, int distID) {
    vertex<string> *v = findVertex(startingCity);
    v->district = distID;
    std::queue<vertex<string> *> vQueue;
    vQueue.push(v);
    while(!vQueue.empty()) {
        vertex<string> *n = vQueue.front();
        vQueue.pop();
        for(int i = 0; i < n->adj.size(); i++) {
            if(n->adj[i].v->district==-1) {
                n->adj[i].v->district = distID;
                vQueue.push(n->adj[i].v);
            }
        }
    }
};

template<typename T>
void Graph<T>::shortestPath(T startingCity, T endingCity) {
    vertex<string> *v = findVertex(startingCity);
    vertex<string> *v2 = findVertex(endingCity);
    if(v == NULL || v2 == NULL) {
        cout<<"One or more cities doesn't exist"<<endl;
        return;
    }
    if(v->district != v2->district) {
        cout<<"No safe path between cities"<<endl;
        return;
    }
    if(v->district==-1) {
        cout<<"Please identify the districts before checking distances"<<endl;
        return;
    }
    for(int i = 0; i < vertices.size(); i++) {
        vertices[i].ID = -1;
        vertices[i].visited = false;
    }
    bool found = false;
    v->visited = true;
    v->distance = 0;
    v->ID = -1;
    std::queue<vertex<string> *> vQueue;
    vQueue.push(v);
    while(!vQueue.empty()) {
        vertex<string> *n = vQueue.front();
        vQueue.pop();
        for(int i = 0; i < n->adj.size(); i++) {
            if(!n->adj[i].v->visited) {
                n->adj[i].v->distance = n->distance + 1;
                int index;
                for(int j = 0; j < vertices.size(); j++) {
                    if(vertices[j].name == n->name) {
                        index = j;
                        break;
                    }
                }
                n->adj[i].v->ID = index;
                if(n->adj[i].v->name == endingCity) {
                    v2 = n->adj[i].v;
                    found = true;
                    break;
                }
                else {
                    n->adj[i].v->visited = true;
                    vQueue.push(n->adj[i].v);
                }
            }
        }
        if(found) {
            break;
        }
    }
    cout<<v2->distance;
    vertex<string> *current = v2;
    vector<string> path;
    path.push_back(current->name);
    while(current->ID!=-1) {
        path.push_back(vertices[current->ID].name);
        current = &vertices[current->ID];
    }
    for(int i = path.size()-1; i>=0; i--) {
        cout<<","<<path[i];
    }
    cout<<endl;
};

template<typename T>
vertex<T> * Graph<T>::findVertex(T name) {
    for(int i = 0; i < vertices.size(); i++) {
        if(vertices[i].name == name) {
            return &vertices[i];
        }
    }
    return NULL;
};
