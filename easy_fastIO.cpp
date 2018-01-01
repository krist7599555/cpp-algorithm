#ifdef input
#undef input
inline extern int input(){
	static const int  sz = 1 << 15;
	static char _o[sz+1], *o = _o + sz;
	#define getchar(c) {if(o == _o + sz){_o[fread(o = _o, 1, sz, stdin)] = '\0';} c = *o++;}
	int rs = 0;
	char c = 0;
	while (c < '0' || c > '9') getchar(c);
	while (c >= '0'&& c <='9'){
		rs = (rs << 1) + (rs << 3) + c - '0';
		getchar(c);
	}
	return rs;
};
#endif
