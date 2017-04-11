#include <bits/stdc++.h>

/**
 * 	concept : lazy add, find sum of [1..b] by
 *  SiNGle >> if we cut in middle we get  sum value to multiply
 * 	GRouP  >> if mid -> cancle of single else look to another
 *  (v * a-1) - (v * b) = v * (b - a - 1) = v * len
 */

template <typename T>
class Fenwick { // tag : range update, range query
private:
	
	int n;
	T* sng; // single
	T* grp; // group
	
	void update (T fw[], int x, T v){
		for (; 1 <= x and x <= n; x += x & -x)
			fw[x] += v;
	}
	
	T query (T fw[], int x){
		T res = T();
		for (; 1 <= x and x <= n; x -= x & -x)
			res += fw[x];
		return res;
	}

public:

	Fenwick(int n): n(n), sng(new T[n+1]()), grp(new T[n+1]()) {}
	
	void update (int l,int r, T v){
		update (sng, l  ,  v);
		update (sng, r+1, -v);
		update (grp, l  ,  v * (l - 1));
		update (grp, r+1, -v * (r    ));
	}
	
	T query (int l, int r){
		l--;
		int suml = query(sng,l) * l - query(grp,l);
		int sumr = query(sng,r) * r - query(grp,r);
		return sumr - suml;
	}
	
	void debug (){
		for (int i = 1; i <= n; ++i)
		std::cout << query(i,i) << " \n"[i==n];
	}
	
};

int main(){
	
	int n;
	std::cin >> n;
	Fenwick<int> fw(n);
	while (true){
		int l,r,v;
		std::cin >> l >> r >> v;
		fw.update (l,r,v);
		fw.debug();
	}
}
