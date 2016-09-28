int BIT[MAXN];
void update(int x, int v){
	for(; x<MAXN; x+=(x&-x))
		BIT[x]+=v;
}
int query(int x){
	int r = 0;
	for(; x>0; x-=(x&-x))
		r += BIT[x];
	return r;
}
