#include <bits/stdc++.h>
using namespace std;
struct node {
  node* child[26];
  node* fail;
  vector<int> pat;
};
node* head;
queue<node*> Q;
void insert_(char* str, int idx) {
  node* it = head;
  int sz = strlen(str), letter;
  for (int j = 0; j < sz; j++) {
    letter = int(str[j]) - 'A';
    if (!it->child[letter]) it->child[letter] = new node();
    it = it->child[letter];
  }
  it->pat.push_back(idx);
}
void build() {
  head->fail = head;
  node *it, *fail;
  for (int j = 0; j < 30; j++) {
    if (head->child[j]) {
      head->child[j]->fail = head;
      Q.push(head->child[j]);
    }
  }
  while (!Q.empty()) {
    it = Q.front();
    Q.pop();
    for (int j = 0; j < 30; j++) {
      if (!it->child[j]) continue;
      fail = it->fail;
      it->child[j]->fail = head;
      // if(fail==NULL) cout<<"ijda3ni ya wad\n";
      while (1) {
        if (fail->child[j]) {
          it->child[j]->fail = fail->child[j];
          break;
        }
        if (fail == head) break;
        fail = fail->fail;
      }
      Q.push(it->child[j]);
      it->child[j]->pat.insert(it->child[j]->pat.end(),
                               it->child[j]->fail->pat.begin(),
                               it->child[j]->fail->pat.end());
    }
  }
}
void Aho_Corasick(char* str) {
  int sz = strlen(str), letter, szo;
  node* it = head;
  for (int j = 0; j < sz; j++) {
    letter = str[j] - 'A';
    if (it->child[letter])
      it = it->child[letter];
    else {
      it = it->fail;
      while (1) {
        if (it->child[letter]) {
          it = it->child[letter];
          break;
        }
        if (it == head) break;
        it = it->fail;
      }
    }
  }
}