#include <iostream>
#include <algorithm>
#include <queue>
#include <ctime>
#include <cassert>
using namespace std;

template <typename T, typename Cmp = std::less<T>>
class leftist_heap {
	class node {
	public:
		T vl;
		int dis;
		node *l, *r;
		node(T _vl, int _dis = 0): vl(_vl), dis(_dis), l(0), r(0) {}
	};
protected:
	node* root;
	const Cmp op;
	node* merge (node* nl, node* nr){
		if (!nl or !nr) return nl ?: nr;
		if (this->op(nl->vl, nr->vl))
			std::swap(nl, nr);
		if (nl->l){ // nl is root
			nl->r = merge(nl->r, nr);
			if (nl->l->dis < nl->r->dis)
				std::swap(nl->l, nl->r);
			nl->dis = nl->r->dis + 1;
		}else nl->l = nr;
		return nl;
 	}
public:
	typedef node* point_iterator;
	leftist_heap (Cmp _op = Cmp()): root(0), op(_op) {}
	inline const T& top() { return root->vl; }
	inline bool empty() { return !root; }
	inline node* push (const T& vl){ root = merge(root, new node(vl)); }
	inline void pop (){
		node* p = root;
		root = merge(root->l, root->r);
		delete p;
	}
	inline void join (leftist_heap& rhs){
		root = merge(root, rhs.root);
		rhs.root = nullptr;
	}
};

int main(){
	leftist_heap<int> hp;
	std::priority_queue<int> pq;
	#define method(...) hp.__VA_ARGS__, pq.__VA_ARGS__
	#define compare() pq.empty() ?: hp.top() == pq.top()
	std::srand(time(0));
	for (int i = 0; i < 1000000; ++i){
		if (std::rand() % 5 > 1){
			int vl = std::rand();
			method(push(vl));
		}else if (!pq.empty()) method(pop());
		assert(compare());
	}
}
