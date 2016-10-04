#include<bits/stdc++.h>
using namespace std;
typedef tuple<int,int,int> T3;
#define mp(x,y) make_pair(x,y)
#define mt(x,y,z) make_tuple(x,y,z)
#define pb(x) push_back(x)

int d[101][10004];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n,m,k;
		scanf("%d%d%d",&k,&n,&m);
		vector<vector<T3> > adj(n+1);
		memset(d,0x1f,sizeof d);
		for(int i=0; i<m; ++i){
			int x,y,c,t;
			scanf("%d%d%d%d",&x,&y,&t,&c);
			adj[x].pb(mt(y,c,t));
		}
        priority_queue<T3, vector<T3>, greater<T3> > q;
        q.push(mt(0,k,1));
        d[1][k] = 0;
        int ans = 1e9+7;
        while(!q.empty()){
			int t,c,x;
			tie(t,c,x) = q.top();
			q.pop();
			if(d[x][c]!=t)	continue;
			if(x==n){
				ans = min(ans, t);
			}
			for(auto e:adj[x]){
				int nx,nc,nt;
				tie(nx,nc,nt) = e;
				if( c-nc>=0 && d[nx][c-nc] > t + nt ){
					d[nx][c-nc] = t + nt;
					q.push(mt(d[nx][c-nc],c-nc,nx));
				}
			}
        }
		if(ans > 1e9)
			ans = -1;
		printf("%d\n",ans);
	}
	return 0;
}
