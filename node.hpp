#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <map>

template <typename messageType, typename stateType>
class Node {
private:
  std::vector<messageType> inBox, outBox;
  std::map<std::string, std::string> nodeParams;
  std::vector<Node<messageType, stateType>*> neighbours;
  std::vector<std::map<std::string, std::string>> edgeParams;
  void addNeighbour (Node<messageType, stateType> &node) {
    Node<messageType, stateType> *ptr = node;
    neighbours.push_back(ptr);
    edgeParams.push_back(std::map<std::string, std::string>());
  }

public:
  int id;
  stateType state;
  Node<messageType, stateType> (int _id, stateType _state=stateType()) : id(_id), state(_state) {}
  void receive(messageType &msg) {
    inBox.push_back(msg);
  }
  void send(messageType &msg, int j) {
    outBox.push_back(msg);
    neighbours[j]->receive(msg);
  }
  void setNodeParam(std::string &param, std::string &value) {
    if (nodeParams.find(param) != nodeParams.end()) {
      nodeParams.erase(param);
    }
    nodeParams.insert({param, value});
  }
  void setEdgeParam(int i, std::string &param, std::string &value) {
    if (edgeParams[i].find(param) != edgeParams[i].end()) {
      edgeParams[i].erase(param);
    }
    edgeParams[i].insert({param, value});
  }
  friend std::ostream& operator<<(std::ostream &out, const Node<messageType, stateType> &node) {
    out << node.id << ' ' << node.nodeParams.size() << '\n';
    for (auto it : node.nodeParams) {
      out << it.first << ' ' << it.second << '\n';
    }
    return out;
  }
  template<typename mT, typename sT> friend class Graph;
};

template<typename messageType, typename stateType>
class Graph {
  std::vector<Node<messageType, stateType>> nodes;
  std::vector<std::pair<int, int>> edges;
  int V, E;
public:
  Graph() {
    V = E = 0;
  }
  void addEdge(int u, int v) {
    edges.push_back({u, v});
    nodes[u].addNeighbour(nodes[u]);
    nodes[v].addNeighbour(nodes[v]);
    E++;
  }
  void addVertex(stateType _state = stateType()) {
    nodes.push_back(Node<messageType, stateType>(V, _state));
    V++;
  }
  friend std::ostream& operator<<(std::ostream &out, const Graph &g) {
    out << g.V << " " << g.E << '\n';
    for (auto &node : g.nodes) {
      out << node;
    }
    for (auto &node : g.nodes) {
      int sz = node.neighbours.size();
      for (int i=0;i<sz;++i) {
        out << node.id << " " << node.neighbour[i].id << ' ' << node.edgeParam[i].size() << '\n';
        for (auto it : node.edgeParam[i]) {
          out << it.first << " " << it.second << '\n';
        }
      }
    }
    return out;
  }
};

// template<typename messageType, typename stateType>
// class Graph {
// public:
//   std::vector<Node<messageType, stateType>> nodes;
//   std::vector<pair<int, int>> edges;
//   displayParameters graphParams;
//   int V, E;
//   bool isDirected;
//   void simulateRound() {
//     for (auto &node : nodes) {
//       code(node);
//     }
//   }
//   function<void(Node<messageType, stateType> &n)> code;
//   Graph(bool _isDirected = true, displayParameters _graphParams = displayParameters()) : isDirected(_isDirected), graphParams(_graphParams) {
//     V = E = 0;
//   }
//   void addNode() {
//     Node<messageType, stateType> newNode();
//   }
//   void addEdge(int u, int v) {

//   }
//   void print(std::ostream &out) {
    
//   }
// };
