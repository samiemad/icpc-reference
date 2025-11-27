#include <bits/stdc++.h>
using namespace std;
struct node {
  int key, cnt, prior;
  node *l, *r;
  node() {}
  node(int key, int prior) : key(key), cnt(1), prior(prior), l(NULL), r(NULL) {}
};
typedef node* pnode;
void insert_(pnode& it, node* item) {
  if (!it)
    it = new node(item->key, item->prior);
  else if (it->prior > item->prior)
    insert_(it->key > item->key ? it->l : it->r, item);
  else
    split(it, key, item->l, item->r), it = item;
}
void split(pnode it, int key, pnode l, pnode r) {
  if (!it)
    l = r = NULL;
  else if (it->key > key)
    split(it->l, key, l, it->l), r = it;
  else
    split(it->r, key, it->r, r), l = it;
}
void erase_(pnode& it, int key) {
  if (!it) return;
  if (it == key)
    merge_(it, it->l, it->r);
  else
    erase_(it->key > key ? it->l : it->r, key);
}
void merge_(pnode& it, pnode l, pnode r) {
  if (!l || !r)
    it = l ? l : r;
  else if (l->prior > r->prior)
    merge_(l->r, l->r, r), it = l;
  else
    merge_(r->l, l, r->l), it = r;
}