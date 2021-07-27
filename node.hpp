#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>

template <typename messageType, typename stateType>
class Node {
// private:
public:
  std::vector<std::pair<int, messageType>> inBox, outBox, inBox_copy, outBox_copy;
  std::map<std::string, std::string> nodeParams, nodeParams_copy;
  std::vector<Node<messageType, stateType>*> neighbours;
  std::vector<std::map<std::string, std::string>> edgeParams, edgeParams_copy;
  void addNeighbour (Node<messageType, stateType> &node) {
    Node<messageType, stateType> *ptr = &node;
    neighbours.push_back(ptr);
    edgeParams.push_back(std::map<std::string, std::string>());
  }

public:
  int id, id_copy;
  stateType state, state_copy;
  Node<messageType, stateType> (int _id, stateType _state=stateType()) : id(_id), state(_state) {
    resetParams();
  }
  void setCopy() {
    id_copy = id; state_copy = state;
    edgeParams_copy = edgeParams;
    nodeParams_copy = nodeParams;
    outBox_copy = outBox;
    inBox_copy = inBox;
  }
  void swapCopy() {
    auto id_tmp=id; 
    auto nodeParams_tmp=nodeParams_copy;
    auto edgeParams_tmp=edgeParams_copy;
    auto state_tmp=state_copy;
    auto inBox_tmp=inBox_copy;
    auto outBox_tmp=outBox_copy;

    id_copy = id; state_copy = state;
    edgeParams_copy = edgeParams;
    nodeParams_copy = nodeParams;
    outBox_copy = outBox;
    inBox_copy = inBox;

    id = id_tmp; state = state_tmp;
    edgeParams = edgeParams_tmp;
    nodeParams = nodeParams_tmp;
    outBox = outBox_tmp;
    inBox = inBox_tmp;
  }
  void receive(messageType &msg, int j) {
    inBox.push_back({j, msg});
  }
  void send(messageType &msg, int j) {
    outBox.push_back({j, msg});
  }
  void flushOutBox() {
    for (auto it : outBox) {
      int j = it.first; auto msg = it.second;
      neighbours[j]->receive(msg, id);
    }
    outBox.clear();
  }
  void setNodeParam(std::string param, std::string value) {
    if (nodeParams.find(param) != nodeParams.end()) {
      nodeParams.erase(param);
    }
    nodeParams.insert({param, value});
  }
  void setEdgeParam(int i, std::string param, std::string value) {
    if (edgeParams[i].find(param) != edgeParams[i].end()) {
      edgeParams[i].erase(param);
    }
    edgeParams[i].insert({param, value});
  }
  void resetParams() {
    nodeParams.clear();
    setNodeParam("label", std::to_string(state) + "," + std::to_string(id));
    setNodeParam("shape", "circle");
    for (auto &ep : edgeParams) ep.clear();
  }
  friend std::ostream& operator<<(std::ostream &out, const Node<messageType, stateType> &node) {
    out << node.id << ' ' << node.nodeParams.size() << '\n';
    for (auto it : node.nodeParams) {
      out << it.first << ' ' << it.second << '\n';
    }
    return out;
  }
  template<typename mT, typename sT> friend class Graph;
  // template<typename mT, typename sT> friend Graph::std::ostream& operator<<(std::ostream &out, const Graph<mT, sT>);
};

template<typename messageType, typename stateType>
class Graph {
public:
  std::vector<Node<messageType, stateType>> nodes;
  std::vector<std::pair<int, int>> edges;
  int V, E, snaps;
public:
  Graph() {
    V = E = snaps = 0;
    code = [](Node<messageType, stateType> &node) {
      for (auto &it : node.inBox) {
        node.state = std::max(node.state, it.second);
      }
      node.inBox.clear();
      node.state = std::max(node.state, node.id);
      node.setNodeParam("color", "blue");
      node.setNodeParam("label", "state=" + std::to_string(node.state) + ",id=" + std::to_string(node.id));
      for (int j=0;j<node.neighbours.size();++j) {
        node.send(node.state, j);
        node.setEdgeParam(j, "label", std::to_string(node.state));
        node.setEdgeParam(j, "color", "red");
      }
    };
  }
  void addEdge(int u, int v) {
    edges.push_back({u, v});
    // std::cerr << "added " << nodes[u].id << ", " << nodes[v].id << '\n';
    nodes[u].addNeighbour(nodes[v]);
    nodes[v].addNeighbour(nodes[u]);
    E++;
  }
  void addVertex(stateType _state = stateType()) {
    nodes.push_back(Node<messageType, stateType>(V, _state));
    V++;
  }
  friend std::ostream& operator<<(std::ostream &out, const Graph &g) {
    out << g.V << " " << g.E * 2 << '\n';
    for (auto &node : g.nodes) {
      out << node;
    }
    for (auto &node : g.nodes) {
      int sz = node.neighbours.size();
      for (int i=0;i<sz;++i) {
        out << node.id << " " << node.neighbours[i]->id << ' ' << node.edgeParams[i].size() << '\n';
        for (auto it : node.edgeParams[i]) {
          // if (it.first < it.second)
          out << it.first << " " << it.second << '\n';
        }
      }
    }
    return out;
  }
  std::function<void(Node<messageType, stateType> &node)> code;
  void simulate(int rounds) {
    while (rounds--) {
      std::vector<Node<messageType, stateType>> nodes_tmp;
      for (auto &node : nodes) {
        node.setCopy();
        code(node);
        std::fstream f(("./graph_texts/" + std::to_string(snaps++) + ".txt").c_str(), std::ios::out);
        f << (*this);
        node.swapCopy();
      }
      for (auto &node : nodes) {
        node.swapCopy();
        node.flushOutBox();
        node.resetParams();
      }
    }
  }
};
