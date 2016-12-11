#include <bits/stdc++.h>
#define rep(i,n) for(int i=1;i<=n;i++)
#define fi first
#define se second
#define SZ(x) int(x.size())
#define ALL(x) x.begin(), x.end()
using namespace std;
typedef pair<int,int> pii;
typedef long long lli;

class MyString : public std::string{
public :
	MyString(const string& s) : std::string(s) {}
};

template<typename T>
class MyQueue : public std::queue<T,std::deque<T>> {
public :
	
	template <typename It>
	MyQueue(It beg, It en){ this->c.assigned(beg,en); }
	
	template <typename Con>
	MyQueue(Con con){ copy(con.begin(),con.end(),back_inserter(this->c)); }
	
	typename std::deque<T>::iterator begin(){ return this->c.begin(); }
	typename std::deque<T>::iterator end  (){ return this->c.end(); }
	
	void clear(){ this->c.clear(); }
	
};

template<typename T,typename V = vector<T>, typename Cmp = less<T> >
class MyPriorityQueue : public std::priority_queue<T,V,Cmp> {
public :

	reference_wrapper< std::priority_queue<T,V,Cmp> > ref = ref( this->c );
	
	template <typename It>
	MyPriorityQueue(It beg, It en){ this->c.assigned(beg,en); }
	
	template <typename Con>
	MyPriorityQueue(Con con){ copy(con.begin(),con.end(),back_inserter(this->c)); }
	
	typename std::deque<T>::iterator begin(){ return this->c.begin(); }
	typename std::deque<T>::iterator end  (){ return this->c.end(); }
	
	void clear(){ this->c.clear(); }
	
};


template<typename T, typename Cmp = function<bool(T,T)>, typename Allo = std::allocator<T> >
class MySet : public std::set<T,Cmp,Allo> {
public :
	
	MySet(Cmp cmp = less<T>()): std::set<T,Cmp,Allo>(cmp) {};
	
	typename set<T,Cmp,Allo>::iterator begin(){ return std::set<T,Cmp,Allo>::begin(); }
	typename set<T,Cmp,Allo>::iterator end  (){ return std::set<T,Cmp,Allo>::end(); }
	
	void clear(){
		for_each(this->begin(),this->end(),[](int *x){ delete x; });
		set<T,Cmp,Allo>::clear();
	}

};

template<typename T>
class MyList : public std::list<T> {
public :
	_List_node<T> N;
	
};


int main(){
	
	function<bool(int*,int*)> poiterless = [](const int* a, const int* b){ return *a < *b; };
	MySet<int*> s (poiterless); // OK work with out Key_Compare
	
	s.insert(new int(123));
	s.insert(new int(12));
	s.insert(new int(13));
	s.insert(new int(1));
	s.insert(new int(1123));
	
	for(auto* x : s)
		cout << *x << ' ';	
	cout << endl;
	
	s.clear();
}
	
