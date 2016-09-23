vector<vector<int> > adj;
stack<int> S;
int num[MAXN], low[MAXN], cnt, timer;
int scc[MAXN], sz[MAXN];
bool vis[MAXN];
void scc_dfs(int x) {
	num[x] = ++timer;
	low[x] = num[x];
	vis[x] = true;
	S.push(x);
	for (int j = 0; j < adj[x].size(); j++) {
		int nxt = adj[x][j];
		if (num[nxt] == 0) {
			scc_dfs(nxt);
			low[x] = min(low[x], low[nxt]);
		} else if (vis[nxt])
			low[x] = min(low[x], num[nxt]);
	}
	if (low[x] == num[x]) {
		++cnt;
		while (1) {
			int nxt = S.top();
			S.pop();
			vis[nxt] = false;
			scc[nxt] = cnt;
			sz[cnt]++;
			if (nxt == x)
				break;
		}
	}
}
