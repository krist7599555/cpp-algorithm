typedef long long lli;
lli pow(lli num, lli factor, lli modd = 1e9+7){
	
	// 	1	0 	0 	1 	0 	0 	1 	1 	1
	// 	n^9	n^8 	n^7	n^6	n^5	n^4	n^3	n^2	n^1	
	
	lli result = 1;
	lli nownum = 1;
	
	while (factor != 0){
		
		nownum = nownum * num % modd;
		
		if(factor&1){
			result = result * nownum % modd;
		}
		
		factor >>= 1;
		
	}
	
	return result;
	
}
