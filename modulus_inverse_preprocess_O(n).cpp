#include <bits/stdc++.h>
const int N = 400004;

int dp[N];
ii b[N];

int fac[N], ifac[N], inv[N];

void prencr(){

	fac[0] = ifac[0] = inv[1] = 1;

  for(int i = 2; i < N; ++i)
    inv[i] = mod - 1LL * (mod / i) * inv[mod % i] % mod; // magic ? inv[v] = pow (v,mod-2)

  for(int i = 1; i < N; ++i){
    fac[i] = 1LL * i * fac[i - 1] % mod;
    ifac[i] = 1LL * inv[i] * ifac[i - 1] % mod;
  }
}

int main(){
    
}
