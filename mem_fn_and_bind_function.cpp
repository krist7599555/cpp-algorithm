#include <bits/extc++.h>
#include <iostream>
#define rep(i,k,n) for(decltype(k) i=(k);i!=(n);++i)
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) int((x).size())
#define fi first
#define se second
#define cin() ({int _; cin >> _; _;})
using namespace __gnu_pbds;
using namespace __gnu_cxx;
using namespace std;
typedef long long lli;
typedef std::vector<int> Vec;
typedef std::pair<int,int> pii;

struct Data {
	int x,y;
	void operator *(void){
		x = x * x;
		y = y * y;
	}
	
	//~ bool operator < (const Data& b) const { // 1
		//~ return tie(x,y) < tie(b.x,b.y);
	//~ }
	
	// write friend for used out side class
	// if we write in side we can not get function address
	friend bool operator < (const Data& a, const Data& b);
	friend ostream& operator << (ostream& o, const Data& i);

	void f (){
		cout << *this << ' ';
		cout << boolalpha << (*this < Data());
	}
	
};


bool operator < (const Data& a, const Data& b){ // 2
	return tie(a.x,a.y) < tie(b.x,b.y);
}
ostream& operator << (ostream& o, const Data& i){ // 3
	return o << " x " << i.x << " y " << i.y;
}

using namespace std::placeholders;

// 1.) class method
//~ using data_cmp_type = bool(Data::*)(const Data&)const; // class method
//~ auto  data_cmp = mem_fn (static_cast<data_cmp_type>(&Data::operator <));

// 2.) globle out side class
//~ using friend_cmp_type = bool(*)(const Data&,const Data&); // <---- 
//~ auto  freind_cmp_v1 = bind <friend_cmp_type>(&::operator <,_1,_2); 
//~ auto  freind_cmp_v2 = bind (static_cast<friend_cmp_type>(&::operator <),_1,_2);

// 3.) globle out side class
//~ using friend_stdout_type = ostream&(*)(ostream&, const Data&); // <---- 
//~ auto frind_1 = bind<friend_stdout_type>(&::operator<<, ref(cout), _1);
//~ auto frind_2 = bind(static_cast<friend_stdout_type>(&::operator<<), ref(cout), _1);


int main(){
	
	ref((cout.operator << (11001100) << ' ')).get().operator << (' ') << endl;
	
	Data d[10];	
	rep(i,0,10)
		i[d].x = i,
		i[d].y = i * 100;

	auto prin  = [](const int& a)->void{ cout <<setw(8)<< a << ' '; };
	for_each(d,d+10,
		bind(prin,
			bind(mem_fn(&Data::x),_1))); 
	cout << endl;
	
	auto out_char = [](ostream& o = cout, const char*& c)->ostream& {return o << c;};
	
	for_each(d,d+10,
		bind(out_char,
			bind<ostream&(ostream::*)(int)>
			(&ostream::operator <<, ref(cout), 
				bind(mem_fn(&Data::x),_1))," * ")); 
	cout << endl;
	
	copy (d, d + 10, ostream_iterator<Data>(cout,"\n")); 
	cout << endl;
	
	for_each(d,d+10,
		bind([](int&a){a=a*a;},
			bind(&Data::y,_1)));
	
	for_each (d, d + 10, bind(prin,bind(&Data::y,_1))); 		cout << endl;
	for_each (d, d + 10, bind(prin,bind(mem_fn(&Data::y),_1))); cout << endl;
	for_each (d, d + 10, bind(prin,bind(std::divides<int>(),
							bind(&Data::y,_1),
							10))); 							
	cout << endl;
	
	typedef decltype(mem_fn(&Data::x)) f_int; 
	auto do_sth = [](
		const Data& d, 
		f_int f1, 
		f_int f2, 
		std::function<int(int,int)> f3 = std::minus<int>()){
			cout << setw(8) << f3(f1(d),f2(d)) << ' ';
	};
	for_each(d,d+10,bind(do_sth,_1,mem_fn(&Data::x),mem_fn(&Data::y))); cout << endl;
	for_each(d,d+10,bind(do_sth,_1,mem_fn(&Data::y),mem_fn(&Data::x))); cout << endl;
	for_each(d,d+10,bind(do_sth,_1,mem_fn(&Data::x),mem_fn(&Data::x))); cout << endl;
	for_each(d,d+10,bind(do_sth,_1,mem_fn(&Data::x),mem_fn(&Data::x),std::plus<int>())); cout << endl;
	for_each(d,d+10,bind(do_sth,_1,mem_fn(&Data::x),mem_fn(&Data::x),__gnu_cxx::power<int,int>)); cout << endl;
	for_each(d,d+10,bind(prin,bind(
		[](int a){return a?int(1000*log2(a)):-1;},
			bind(mem_fn(&Data::x),_1)))); 
	cout << endl;
}

