//IPST 17 10 

//fast log2 , builtin 1 : 6 cmath
  log2(n) = (sizeof(n)<< 3) - __builtin_clz(n) -1

//RMQ : make
  1.) map[i][0] = vec[i]
  2.) int k = log2(n)
  3.) for  i=0 ;  i<=k ;
  4.) for  j=0 ;  j+(1<<(i-1)) < n ;
  5.) map[j][i] = map[j][i-1] ^ map[j+(1<<(i-1))][i-1]

//RMQ : query
  1.) k = log2(b-a+1)
  2.) return map[a][k] ^ map[b+1-(1<<k)][k]

//CCLOCK
  clock_t one = clock();
  clock_t two = clock();
  double(two-one) / CLOCKS_PER_SEC;

//BIT permu bit
  f = i & -i;
  k = f + i;
  i = (((k^i)>>2) / f ) | k;
