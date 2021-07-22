#include <vector>
#include <string>

struct displayParameters {
  std::string shape, color, text;
};

template <typename messageType, typename stateType>
class Node {
public:
  std::vector<Node<messageType, stateType>*> neighbours;
  std::vector<messageType> inbox, outbox;
  displayParameters nodeParams;
  std::vector<displayParameters> edgeParams;

  Node<messageType, stateType> (stateType _state, int _id) : id(_id), state(_state) {}

  void addNeighbour (Node<messageType, stateType> &node) {
    Node<messageType, stateType> *ptr = node;
    neighbours.push_back(node);
  }

  int id;
  stateType state;
  void receive (messageType &msg) {
    inbox.push_back(msg);
  }
};

template<typename messageType, typename stateType>
class Graph {
public:
  std::vector<Node<messageType, stateType>> nodes;
  std::vector<pair<int, int>> edges;
  displayParameters graphParams;
  int V, E;
  bool isDirected;
  void simulateRound() {
    for (auto &node : nodes) {
      code(node);
    }
  }
  function<void(Node<messageType, stateType> &n)> code;
  Graph(bool _isDirected = true, displayParameters _graphParams = displayParameters()) : isDirected(_isDirected), graphParams(_graphParams) {
    V = E = 0;
    
  }
  void addNode() {
    Node<messageType, stateType> newNode();
  }
  void addEdge(int u, int v) {

  }
  void print(ostream &out) {
    
  }
};

int main() {

}
