#include <bits/extc++.h>
#include <ext/hash_map>
#include <ext/hash_set>
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include <iostream>
#define rep(i,k,n) for(decltype(k) i=(k);i!=(n);++i)
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) int((x).size())
#define fi first
#define se second
#define cxx __gnu_cxx
#define pbds __gnu_pbds
using namespace std;
using namespace pbds;
using namespace cxx;

const int mxn = 500000;

int main(){
	
	using std::cout;
	
	std::vector<int> in(mxn);
	srand(time(NULL));
	generate(in.begin(),in.end(),rand);
	
	#define test(Container,command)										\
	{																	\
		clock_t s = clock();											\
		Container c;													\
		for (int i : in) command;										\
		clock_t t = clock();											\
		printf(" %.8lf ",double(t - s) / CLOCKS_PER_SEC); 				\
		cout << #Container << '\n';										\
	}
	
	cout << "TIMING TEST \n\n";
	cout << "Item : " << mxn << '\n';
	
	
	cout << "\n pririty: \n";
	
	test (__typeof( std ::priority_queue      <int> ), 	c.push(i));
	test (__typeof( pbds::priority_queue      <int> ), 	c.push(i));
	
	cout << "\n push_back: \n";
	
	test (__typeof( std ::vector      <int> ), 	c.push_back(i));
	test (__typeof( std ::deque       <int> ), 	c.push_back(i));
	test (__typeof( std ::list        <int> ), 	c.push_back(i));
	
	cout << "\n push_front: \n";
	
	test (__typeof( std ::deque       <int> ), 	c.push_front(i));
	test (__typeof( std ::list        <int> ), 	c.push_front(i));
	test (__typeof( std ::forward_list<int> ), 	c.push_front(i));
	
	cout << "\n push: \n";
	
	test (__typeof( std ::queue       <int> ), 	c.push(i));
	test (__typeof( std ::stack       <int> ), 	c.push(i));
	
	
	cout << "\n sorted 1 : \n";
	
	test (__typeof( std ::set  <int>           ), 			c.insert(i));
	test (__typeof( pbds::tree <int,null_type> ), 			c.insert(i));
	test (__typeof( pbds::tree <int,null_type,less<int>,rb_tree_tag>    ), 	c.insert(i));
	test (__typeof( pbds::tree <int,null_type,less<int>,splay_tree_tag> ), 	c.insert(i));
	test (__typeof( pbds::tree <int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ), 	c.insert(i));
	
	cout << "\n sorted 2 : \n";
	
	test (__typeof( std ::map  <int,int>                 ), 	c[i] = i);
	test (__typeof( pbds::tree <int,int>                 ), 	c[i] = i);
	
	cout << "\n sorted multi 1 : \n";
	
	test (__typeof( std ::multiset <int>                ), 	c.insert(i));
	
	cout << "\n sorted multi 2 : \n";
	
	test (__typeof( std ::multimap <int,int>            ), 	c.insert ({i,i}));
	
	cout << "\n unsorter 1: \n";
	
	test (__typeof( tr1 ::unordered_set       <int>     ), 	c.insert(i));
	test (__typeof( std ::unordered_set       <int>     ), 	c.insert(i));
	test (__typeof( cxx ::hash_set            <int>     ), 	c.insert(i));
	
	test (__typeof( tr1 ::unordered_multiset  <int>     ), 	c.insert(i));
	test (__typeof( std ::unordered_multiset  <int>     ), 	c.insert(i));
	test (__typeof( cxx ::hash_multiset       <int>     ), 	c.insert(i));
	
	cout << "\n unsorter 2: \n";
	
	test (__typeof( tr1 ::unordered_map       <int,int> ), 	c[i] = i);
	test (__typeof( std ::unordered_map       <int,int> ), 	c.insert({i,i}));
	test (__typeof( cxx ::hash_map            <int,int> ), 	c.insert({i,i}));
	
	test (__typeof( tr1 ::unordered_multimap  <int,int> ), 	c.insert({i,i}));
	test (__typeof( std ::unordered_multimap  <int,int> ), 	c.insert({i,i}));
	test (__typeof( cxx ::hash_multimap       <int,int> ), 	c.insert({i,i}));
	
	
	test (__typeof( pbds::gp_hash_table       <int,int> ), 	c[i] = i);
	test (__typeof( pbds::cc_hash_table       <int,int> ), 	c[i] = i);


	
}
