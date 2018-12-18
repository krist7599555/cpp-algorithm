#include <bits/stdc++.h>
#include <iostream>
#include <cstring>
#define input() (*std::istream_iterator<int>(cin))
#define rep(i,k,n) for(int i=(k);i!=int(n);++i)
#define loop(i,n) for(int i = n; i--;)
#define all(x) (x).begin(),(x).end()
#define sz(x) (x).size()
using namespace std;

template < int N = 4, typename T = uint16_t, int B = 8 * sizeof(T) >
 struct Bitset : public std::array <T, N> {
 public:
	typedef std::array <T, N> Arr;
	Bitset(): Arr() {}
	Bitset(uint64_t b): Bitset(std::bitset<64>(b).to_string()) {}
	Bitset(const Bitset& b): Arr() { std::copy (b.begin(), b.end(), Arr::begin()); }
	Bitset(std::string s): Arr() {
		std::reverse(s.begin(), s.end());
		auto it = Arr::begin();
		while (not s.empty()){
			int mx = std::min<int>(B, s.size());
			*it++ = std::bitset<B>(std::string(s.rbegin(), s.rbegin() + mx)).to_ulong();
			s.erase (s.end() - mx, s.end());
	}}
	Bitset operator - (const Bitset& rhs) const {
		Bitset res;
		bool carry = false;
		std::transform (Arr::cbegin(), Arr::cend(), rhs.cbegin(), res.begin(), [&](T a, T b){
			if (carry){
				if (a) a -= 1, carry = false;
				else a = ~a;
			}
			if (b > a) carry = true;
			return a - b;
		});
		return res;
	}
	Bitset operator << (uint m) const {
		Bitset res;
		for (int g = m / B, k = m % B, i = 0; i != N; ++i){
			if (i >= g) res[i] |= Arr::at(i-g) << k;
			if (i >  g) res[i] |= Arr::at(i-g-1) << (B - k);
		}
		return res;
	}
	Bitset operator >> (uint m) const {
		Bitset res;
		for (int g = m / B, k = m % B, i = 0; i != N; ++i){
			if (i+g   < N) res[i] |= Arr::at(i+g) >> k;
			if (i+g+1 < N) res[i] |= Arr::at(i+g+1) << (B - k);
		}
		return res;
	}
#define __bitset_transform_operator(tk,nm) \
	Bitset operator tk (const Bitset& rhs) const { \
		Bitset res; \
		std::transform (Arr::cbegin(), Arr::cend(), \
			rhs.cbegin(), res.begin(), std::bit_ ## nm <T>()); \
		return res; \
	} 
#define __bitset_assign_operator(tk) \
	Bitset& operator tk ## = (const Bitset& rhs){\
		return *this = *this tk rhs; \
	}
	__bitset_transform_operator(&,and);
	__bitset_transform_operator(|,or);
	__bitset_transform_operator(^,xor);
	__bitset_assign_operator(&);
	__bitset_assign_operator(|);
	__bitset_assign_operator(^);
	__bitset_assign_operator(-);
	__bitset_assign_operator(>>);
	__bitset_assign_operator(<<);
	
#undef __bitset_transform_operator
#undef __bitset_assign_operator
	
	std::string to_string() const { return *this; }
	operator  std::string() const {
		std::string s;
		for (auto r = Arr::crbegin(); r != Arr::crend(); ++r) 
			s += std::bitset<B>(*r).to_string();
		return s;
	}
	template <typename R = int64_t>
	 R to_llong () const {
		R r = (Arr::back() >> (B - 1)) & 1 ? ~R() : R();
		for (auto t = Arr::rbegin(); t != Arr::rend(); ++t)
			r = r << B | *t;
		return r;
	}
	inline void toggle(int x){ Arr::at(x / B) ^= 1LL << x % B; }
	inline bool get(int x) const { return Arr::at(x/B) & (1LL<< x%B);}
	inline int count () const {
		return std::accumulate (Arr::cbegin(), Arr::cend(), 0, 
			[](int sm, T vl){ return sm + __builtin_popcountll(vl); });
	}
};


int main(){
	cin.sync_with_stdio(0);
	std::map<char, Bitset<>> mp;
	std::string s1, s2;
	cin >> s1 >> s2;
	rep(i,0,sz(s1)){
		mp[s1[i]].toggle (i + 1);
	}
	Bitset<> ans; // O(N*M/64)
	for (char c : s2){
		ans.toggle(0);
		auto all_b = ans | mp[c];
		auto nex_b = all_b ^ (all_b - (ans << 1));
		ans = all_b & nex_b;
	}
	cout << ans.count();
}
