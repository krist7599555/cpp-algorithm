#include <bits/extc++.h>
#include <iostream>
#include <cstring>

static char  stdinBuffer[1024];
static char* stdinDataEnd = stdinBuffer + 1024;
static const char* stdinPos = stdinDataEnd;

void readAhead(size_t amount){
    
    size_t remaining = stdinDataEnd - stdinPos;
    if (remaining < amount) { // not have enough memory still in array
		
       std::memmove (stdinBuffer, stdinPos, remaining); // copy still not readto front
       size_t sz 	= fread (stdinBuffer + remaining, 1, 1024 - remaining, stdin); // source from stdin
       stdinPos 	= stdinBuffer; 					// reset new begin
       stdinDataEnd = stdinBuffer + remaining + sz; // reset new end
       
       if (stdinDataEnd != stdinBuffer + 1024)
         *stdinDataEnd = 0;
    }
}

int readInt(){
    readAhead(16); // ahead allocate
    int x = 0;
    while (*stdinPos <  '0' || *stdinPos >  '9') ++stdinPos;   
    while (*stdinPos >= '0' && *stdinPos <= '9') {
       x += (x << 3) + (x << 1) + *stdinPos - '0';
       ++stdinPos;
    }
    return x;
}

int main(){
	int x = readInt();
}

