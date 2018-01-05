// josephus problem
// remove man from cycle every k step
#include <bits/stdc++.h>
#define rep(i,k,n) for(int i=(k);i!=int(n);++i)
#define loop(i,n) for(int i = n; i--;)
#define all(x) (x).begin(),(x).end()
#define len(x) (x).size()
using namespace std;
typedef std::vector<int> Vec;
typedef std::set<int> Set;

int josephus_1(int n, int k){ // O(n^2)
	Vec v(n);
	std::iota(all(v), 1);
	auto it = v.begin();
	while (len(v) != 1){
		if (it == v.end()) it = v.begin();
		loop(_,k-1){
			if (++it == v.end()){
				it = v.begin();
		}}
		it = v.erase(it);
	}
	return v.front();
}

int josephus_2(int n, int k){ // O(n log n)
	Vec fw(n + 1);
	for(int i = 1; i <= n; ++i) fw[i] = i & -i;
	auto query = [&](int x){int sm=0; for(;x!=0; x-=x&-x) sm+=fw[x]; return sm;};
	auto remov = [&](int x){for(;x<=n; x+=x&-x) --fw[x];};
	const int mlg = log2(n) + 1;
	int it = 0;
	loop(st, n){
		int fd = (query(it) + k - 1) % (st + 1);
		int x = 0;
		loop(lg, mlg){
			int nw = x + (1 << lg);
			if (nw <= n and fw[nw] <= fd){
				fd -= fw[x = nw];
		}}
		remov(it = x + 1);
	}
	return it;
}

int josephus_3(int n, int k){ // O(n) reverse thinking
	return n == 1 ? 1 : (josephus_3(n - 1, k) + k - 1) % n + 1;
}

int main(){
	cin.sync_with_stdio(0);
	srand(time(0));
	loop(_,100){
		int a = rand() % 400 + 1;
		int b = rand() % 300 + 1;
		Set s {
			josephus_1(a, b),
			josephus_2(a, b),
			josephus_3(a, b)
		};
		assert(len(s) == 1);
	}
	puts("success");
}
