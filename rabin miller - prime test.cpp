typedef unsigned long long lli;

lli mulmod(lli num, lli mul, lli modd){
	lli ans = 0;
	num %= modd;
	mul %= modd;
	while(mul){
		if(mul&1) 
		ans = (ans + num) % modd;
		num = (num * 2  ) % modd;
		mul >>= 1;
	}
	return ans;
}

lli powmod(lli num, lli expo, lli modd){
	lli ans = 1;
	num %= modd;
	while(expo){
		if(expo&1) 
		ans = mulmod(ans,num,modd);
		num = mulmod(num,num,modd);
		expo >>= 1;
	}
	return ans;
}

bool miller(lli num)
{
	if(num<=1) 	return false;
	if(num==2) 	return true;
	if(num%2==0)	return false;
	
	lli k = __builtin_ctz(num-1);
	lli m = (num-1) >> k;
	
	lli b0 = powmod (2, m, num); // 2^m % num
	if (b0 == 1 || b0 == num-1) return true;
	
	while (k--){
		b0 = mulmod(b0, b0, num); // b0^2 % num
		if(b0 == 1) 	return false;
		if(b0 == num-1)	return true;
	}
	return false;

}
