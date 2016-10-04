#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
#define mp(x,y) make_pair(x,y)
#define pb(x) push_back(x)

struct Node{
	int c=0;
	int next[26]={0};
};
vector<Node> tr;

bool ans = 1;
void add(char s[]){
	int cur = 0;
	for(int i=0; s[i]; ++i){
		if(tr[cur].next[s[i]-'a']==0){
			tr[cur].next[s[i]-'a'] = tr.size();
			tr.pb(Node());
		}
		cur = tr[cur].next[s[i]-'a'];
	}
	tr[cur].c++;
}

int query(char s[]){
	int cur = 0;
	for(int i=0; s[i]!='\0'; ++i){
		int nx = tr[cur].next[s[i]-'a'];
		if(nx==0)
			return 0;
		cur = nx;
	}
	return tr[cur].c;
}

char s[2000006];
int main() {
	int T;
	scanf("%d",&T);
	while(T--){
		tr.clear();
		tr.push_back(Node());
		int n;
		scanf("%d",&n);
		for(int i=0; i<n; ++i){
			scanf("%s",s);
			add(s);
		}
	}
	return 0;
}
