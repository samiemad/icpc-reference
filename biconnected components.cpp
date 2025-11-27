#include<vector>
#include <cstdio>
using namespace std;
/*Don’t forget to resize the vectors*/
vector<int> dfs_low, dfs_num, dfs_parent;
vector<bool> articulation_vertex;
int dfsNumberCounter, dfsRoot, rootChildren;
vector<vector<int> > AdjList;
void articulationPointAndBridge(int u) {
  dfs_low[u] = dfs_num[u] = dfsNumberCounter++;  // dfs_low[u] <= dfs_num[u]
  for (int i = 0; i < AdjList[u].size(); i++) {
    int v = AdjList[u][i];
    if (dfs_num[v] == -1) {  // a tree edge
      dfs_parent[v] = u;     // parent of this children is me
      if (u == dfsRoot)      // special case special case
        rootChildren++;      // count children of root
      articulationPointAndBridge(v);
      if (dfs_low[v] >=
          dfs_num[u])  // for articulation point for articulation point
        articulation_vertex[u] = true;  // store this information first
      if (dfs_low[v] > dfs_num[u])      // for bridge
        printf(" Edge (%d, %d) is a bridge\n", u, v);
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);
      // update dfs_low[u]
    } else if (v != dfs_parent[u])  // a back edge and not direct cycle
      dfs_low[u] = min(dfs_low[u], dfs_num[v]);  // update dfs_low[u]
  }
}