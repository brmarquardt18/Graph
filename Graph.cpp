#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <fstream>
#include "Graph.hpp"
#include <vector>
using namespace std;


Graph::Graph(){

}
Graph::~Graph(){

}


void Graph::addVertex(std::string cityName){
  vertex vert;
  vert.name = cityName;
  vert.visited = false;
  vertices.push_back(vert);
}



void Graph::addEdge(std::string city1, std::string city2, int distance){
  vertex *v1 = findVertex(city1);
  vertex *v2 = findVertex(city2);
  Edge newEdge;
  newEdge.v = v2;
  newEdge.distance = distance;
  v1->Edges.push_back(newEdge);
}

void Graph::displayEdges(){
  for(int i = 0; i < vertices.size(); i++){
    std::cout << vertices[i].name << "-->";
    for(auto j = vertices[i].Edges.begin(); j != vertices[i].Edges.end(); ++j){
      if(j == vertices[i].Edges.begin()){
        std::cout << j->v->name << " (" << j->distance << " miles) ";
      }else{
        std::cout << "***" << j->v->name << " (" << j->distance << " miles) ";
      }
    }
    std::cout << std::endl;
  }
}
void Graph::printDFT()
{
  setAllVerticesUnvisited();
  for(int i = 0; i < vertices.size(); i++){
    if(vertices[i].visited == false){
      DFT_traversal(&vertices[i]);
    }
  }
}

void Graph::BFT_traversal(vertex *v){
  queue<vertex*> q;
  std::string name;

  v->visited = true;
  q.push(v);

  while(!q.empty()){
    v = q.front();
    std::cout << v->name << std::endl;
    q.pop();


    for(int i = 0; i < v->Edges.size(); i++){
      if((v->Edges)[i].v->visited == false){
        (v->Edges)[i].v->visited = true;
        q.push((v->Edges)[i].v);
      }
    }
  }
}
void Graph::printBFT(){
  setAllVerticesUnvisited();
  for(int i = 0; i < vertices.size(); i++){
    if(vertices[i].visited == false){
      BFT_traversal(&vertices[i]);
    }
  }
}
void Graph::setAllVerticesUnvisited(){
  for(int i = 0; i < vertices.size(); i++){
    vertices[i].visited = false;
  }
}


vertex* Graph::findVertex(std::string name){
  for(int i = 0; vertices.size(); i++){
    if(vertices[i].name == name){
      return &vertices[i];
    }
  }
}

void Graph::DFT_traversal(vertex *v){
  std::cout << v->name << std::endl;
  v->visited = true;
  for(int i = 0; i < v->Edges.size(); i++){
    if(v->Edges[i].v->visited == false){
      DFT_traversal(v->Edges[i].v);
    }
  }
}


int main(){
  int main(int argc, char* argv[]){
    Graph g;
    ifstream inStream(argv[1]);
    string cityLine;
    string cityAdd;
    string line;
    string city;
    string cityConnected;
    string dist;
    getline(inStream, cityLine);
    stringstream cityStream(cityLine);
    getline(cityStream,cityAdd,',');
    while(getline(cityStream,cityAdd,',')){
      g.addVertex(cityAdd);
    }
    while(getline(inStream, line)){
      stringstream strStream(line);
      stringstream cityStream(cityLine);
      getline(strStream,city,',');
      getline(cityStream,cityConnected,',');
      while(getline(cityStream,cityConnected,',')){
        getline(strStream,dist,',');
        if(stoi(dist) > 0){
          cout << " ... Reading in " << city << " -- " << cityConnected << " -- " << dist << endl;
          g.addEdge(city, cityConnected, stoi(dist));
        }
      }
    }
    cout << "------------------------------ " << endl
  << "Breadth First Traversal" << endl
  << "------------------------------" << endl;
  g.printBFT();
  cout << "------------------------------ " << endl
  << "Depth First Traversal" << endl
  << "------------------------------"<< endl;
  g.printDFT();
  cout << "------------------------------ " << endl
  << "Display Edges" << endl
  << "------------------------------"<< endl;
  g.displayEdges();
  }

}
