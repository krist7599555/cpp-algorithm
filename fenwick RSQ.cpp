//fenwick RSQ 

int sz=20;
int pfw[100]; // plus fenwick 
int mfw[100]; // minus fenwick 

void _update(int * ar,int i,int v){
 for(;i<sz;i+=i&-i) ar[i]+=v;
} 

void update(int l,int r,int v){
 _update(pfw,l  , v); // vvvvvvvv (happen in range only)
 _update(pfw,r+1,-v); // inverse up function
 _update(mfw,l  , v*(l-1)); // vvvv----- (for del upup func)
 _update(mfw,r+1,-v*r);  // inverse up function
}

int _query(int *ar,int i){
 int sum=0;
 for(;i>0;i-=i&-i) sum += ar[i];
 return sum;
}

int query(int l,int r){ // sum 1 to idx
        //     range val * range - range that never reach in front
 int ll = _query(pfw,l-1)*(l-1) - _query(mfw,l-1);
 int rr = _query(pfw,r)  *(r)   - _query(mfw,r);
 return rr-ll;
}
