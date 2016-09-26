#include <bits/stdc++.h>
using namespace std;

deque<int> mq;
void push(int x){
	while(!mq.empty() && mq.back()>x)
		mq.pop_back();
	mq.push_back(x);
}
void pop(){
	mq.pop_front();
}
int mq_min(){
	return mq.front();
}

int main() {
	char c;
	int x;
	while(cin>>c){
		if(c=='+'){
			cin>>x;
			push(x);
		}else
			pop();
		cout<<mq_min()<<"\n";
	}

	return 0;
}
