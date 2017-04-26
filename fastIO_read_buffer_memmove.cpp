#include <bits/extc++.h>
#include <iostream>

namespace fastIO {
	
	int  buffer_size;
	
	char in[1<<10];
	char * end_in = in;
	char * o = in;
	
	char  out[1<<10];
	char const * const end_out = out + sizeof(out);
	char* t = out - 1;
	
	void init(){
		if (feof(stdin)) return;
		int still = end_in - o;
		memmove (in, o, still);
		still += fread (in + still, sizeof(char), sizeof(in) - 4 - still, stdin);
		o = in;
		end_in = in + still;
		if (feof(stdin)) *end_in++ = '\0';
	}
	
	void finish(){
		fwrite (out, sizeof(char), ++t - out, stdout);
		t = out - 1;
	}
	
	int getInt(){
		if (end_in - o < 30) init();
		int  res = 0;
		bool neg = false;
		while (*o < '-') ++o;
		if 	  (*o =='-') ++o, neg = true;
		while (*o >= '0') res = (res << 3) + (res << 1) + (*o++ - '0');
		return neg ? -res : res;
	}
	
	
	void writeInt(int x) { // with endl
		if (t + 30 > end_out) finish();
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

