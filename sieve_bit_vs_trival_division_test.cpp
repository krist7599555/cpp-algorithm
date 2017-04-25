#include <bits/extc++.h>
#include <iostream>
using namespace std;
typedef long long lli;

const int mxsz = 2'000'000;
typedef bitset<mxsz> Bitset;

struct Cmp {
	int cnt = 0;
	inline bool operator ()(int a,int b){
		++cnt;
		return a < b;
	}
};

Bitset normal_sieve_bit(){
	
	Bitset res = ~Bitset();
	Cmp cmp;
	for (int i = 2; cmp(i,mxsz); ++i){
		if (res[i] == true){
			for (int j = i + i; cmp(j,mxsz); j += i){
				assert(j != 5);
				res[j] = false;
			}
		}
	}
	cout << "normal cmp = \t" << cmp.cnt << endl;
	return res;
}

Bitset optimize_sieve_bit_full(){
	
	Bitset res = ~Bitset();
	
	//#define is_t(i) (_sieve[i>>5] &   (1<<(i&31)))
	//#define mk_f(i) (_sieve[i>>5] &= ~(1<<(i&31)))
	//uint _sieve [mxsz>>5]; fill_n(_sieve, mxsz>>5, ~0);
	
	Cmp cmp;
	for (int i = 4; cmp(i,mxsz); i += 2)
		res[i] = false;
	for (int i = 3; cmp(i,mxsz); i+= 2)
		if (res[i] and lli(i) * i < mxsz)	
			for (int j = i * i; cmp(j,mxsz); j += i + i)
				res[j] = false;
	cout << "opt_full cmp = \t" << cmp.cnt << endl;
	return res;
}

Bitset optimize_sieve_bit_half(){
	
	Bitset res = ~Bitset();
	
	// half sive
	//#define is_t(i) (_sieve[i>>6] &   (1<<(i>>1&31)))
	//#define mk_f(i) (_sieve[i>>6] &= ~(1<<(i>>1&31)))
	//uint _sieve [mxsz>>6]; fill_n(_sieve, mxsz>>6, ~0);
	
	Cmp cmp;
	for (int i = 3; cmp(i,mxsz); i+= 2)
		if (res[i] and lli(i) * i < mxsz)	
			for (int j = i * i; cmp(j,mxsz); j += i + i)
				res[j] = false;
	cout << "opt_half cmp = \t" << cmp.cnt << endl;
	return res;
}

void trival_div (){
	Cmp cmp;
	for (int val = 1; val < mxsz; ++val){
		for (int fac = 2, root = sqrt(val) + 1; cmp(fac,root); ++fac)
			if (val % fac == 0) break;
	}
	cout << "triv_div cmp = \t" << cmp.cnt << endl;
}

int main(){
	
	trival_div();
	normal_sieve_bit();
	optimize_sieve_bit_full();
	optimize_sieve_bit_half();
	
}
