// dynamic convec hull trick
// by krist7599555
#include <bits/extc++.h>
#include <iostream>
#define rep(i,k,n) for(int i=(k);i<=int(n);++i)
#define loop(i,n) for(int i = n; i--;)
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
using namespace std;
typedef long long lli;
typedef std::pair<lli,lli> pii;
typedef std::vector<int> Vec;

class ConvecHull : public __gnu_pbds::tree<pii,__gnu_pbds::null_type,std::greater<pii>> {
	
	protected:

		typedef __gnu_pbds::tree<pii,null_type,std::greater<pii>> tree_type;
		typedef ConvecHull this_type;
		
		inline bool bad (iterator it){
			if (it == begin() or next(it) == end()) return false;
			auto prv = prev(it);
			auto nex = next(it);
			return nex->fi == it->fi or cross(*prv,*nex) <= cross(*prv,*it);
		}
		
	public:
	
		static const lli inf = 1e16;
		
		static inline lli get (const pii& p, int x){
			return p.fi * x + p.se;
		}
		static inline double cross (const pii& p1, const pii& p2){
			// mx + c == nx + d, x == (d - c) / m - n
			return double(p2.se - p1.se) / (p1.fi - p2.fi);
		}

		inline bool insert (pii p){
			iterator it; bool b;
			tie(it,b) = tree_type::insert(p);
			if (not b)   return false; // duplicate
			if (bad(it)) return erase(it), false; // bad one
			while (it != begin()     and bad(prev(it)))	erase(prev(it)); // bad left
			while (next(it) != end() and bad(next(it)))	erase(next(it)); // bad right
			return true;
		}
		inline iterator get_best (int x){
			auto nd = node_begin();
			auto en = node_end();
			iterator res = end();
			while (nd != en){
				if (res == end() or get(**nd, x) < get(*res, x)) res = *nd;
				double left_x = *nd == begin() ? -inf : ConvecHull::cross(*prev(*nd), **nd);
				nd = double(x) < left_x ? nd.get_l_child() : nd.get_r_child();
			}
			return res;
		}
		
		ConvecHull (){}
};

int main(){
	
}
