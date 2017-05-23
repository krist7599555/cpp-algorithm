#include <bits/extc++.h>
#include <iostream>
#define rep(i,k,n) for(decltype(k) i=(k);i!=(n);++i)
using namespace std;
typedef std::vector<int> Vec;


struct Node {
	Node (int v): v(v), prio(rand()), sz(1), l(nullptr), r(nullptr) {}
	int v,prio,sz;
	Node *l, *r;
};

Node* root = nullptr;

inline void fixup (Node* nd){
	if(nd) nd->sz = (nd->l ? nd->l->sz : 0) + 1 + (nd->r ? nd->r->sz : 0);
}

void merge (Node*& nd, Node*&l, Node*& r){
	if (!l or !r) return void (nd = l ?: r);
	if (l->prio > r->prio)
		 merge (l->r, l->r, r), nd = l;
	else merge (r->l, l, r->l), nd = r;
	fixup (nd);
}

void split (Node*& nd, Node*& l, Node*& r, int pos){
	if (!nd)
		return void (l = r = nullptr);
	int szl = 1 + (nd->l ? nd->l->sz : 0);
	if (szl <= pos){
		l = nd;
		split (l->r, l->r, r, pos - szl);
		fixup (l);
	}else{
		r = nd;
		split (r->l, l, r->l, pos);
		fixup (r);
	}
}

void insert (Node*& nd, Node* v, int pos){
	if (!nd) return void (nd = v);
	if (nd->prio < v->prio){
		split (nd, v->l, v->r, pos);
		nd = v;
	}else{
		int szl = 1 + (nd->l ? nd->l->sz : 0);
		if (szl <= pos)
			 insert (nd->r, v, pos - szl);
		else insert (nd->l, v, pos);
	}
	fixup (nd);
}

int at (Node*& nd, int pos){
	int szl = 1 + (nd->l ? nd->l->sz : 0);
	if (szl == pos) return nd->v;
	return szl < pos ? at(nd->r, pos - szl) : at(nd->l, pos);
}

ostream& operator << (ostream& out, Node*& nd){
	return !nd ? out : out << nd->l << nd->v << ' ' << nd->r;
}

int main(){

}
