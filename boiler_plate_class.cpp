#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

struct displayParameters {
  string shape, color, text;
};

// struct edgeParameters {
//   string shape, color, text;
// };

template <typename messageType, typename stateType>
class node
{
  ll id;
  list<ll> neighbours;
  list<messageType> inbox;
  list<messageType> outbox;
  displayParameters nodeParams;
  list<displayParameters> edgeParams;

public:
  stateType state;
  function<void()> code;
};

int main()
{
  return 0;
}
