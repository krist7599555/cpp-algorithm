#include <bits/extc++.h>
#include <iostream>

namespace fastIO {
	
	int  buffer_size;
	
	char in[1<<21];
	char const * o = in;
	
	char  out[1<<22];
	char* t = out - 1;
	
	void init(){
		in [ buffer_size = fread (in, sizeof(char), sizeof(in) - 4, stdin) ] = '\0';
	}
	
	void finish(){
		fwrite (out, sizeof(char), ++t - out, stdout);
	}
	
	int getChar(){
		while (*o < 'A'|| *o > 'z' || ('Z' < *o && *o < 'A')) ++o;
		return *o++;
	}
	
	int getInt(){
		int  res = 0;
		bool neg = false;
		while (*o < '-') ++o;
		if 	  (*o =='-') ++o, neg = true;
		while (*o >= '0') res = (res << 3) + (res << 1) + (*o++ - '0');
		return neg ? -res : res;
	}
	
	
	void writeInt(int x) { // with endl
		static char  stk[10];
		static char* c = stk;
		if (x == 0) *++t = '0';
		if (x <  0) *++t = '-', x = -x;
		while (x) *c++ = x % 10 + '0', x /= 10;
		while (c != stk) *++t = *--c;
		*++t = '\n';
	}
	
};

int main(){

}

