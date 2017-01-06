// used sequencegenerate in " Compile Time C++14 " 

#include <bits/stdc++.h>
#include <utility>
#include <tuple>
using namespace std;

template<size_t ... arg>
void Size_tSequence( index_sequence< arg... >){
	for(size_t i : { arg... })  cout << i << ' ' << endl;
};

template<typename Type, Type ... arg > // universal because template a type ans used integer_sequence
void intSequence( integer_sequence<Type,arg...>){
	for(Type i : { arg... })  cout << i << ' ';
};

template<int T>
struct sqr{ enum { value = T*T }; }; // template class
template<int ... T>
vector<int> generateSquare( integer_sequence<int,T...>){ // spasific type [int]
	return {sqr<T>::value...}; // 0 1 4 9
	//return {T...}; // 0 1 2 3 4
};

namespace catalan {
	
	/* 
	//still OK
	template <size_t N> 		struct cata {	       enum { value = cata<N-1> + for_cata<_,_> ... }; };
	template <size_t N> 		class  cata { public : enum { value = cata<N-1> + for_cata<_,_> ... }; };
	*/
	
	template <size_t N> 	   	struct cata; // declearlation not have spasific <>
	template <>		 	struct cata<0>; // sub declear for determind case
	template <size_t L,size_t R>	struct for_cata;
	template <size_t L> 	   	struct for_cata<-1,L>;
	
	template <size_t N> 	   	struct cata 	  	: std::integral_constant<size_t, for_cata<0,N-1>::value > {};
	template <>		 	struct cata<0> 		: std::integral_constant<size_t, 1 > {};
	
	template <size_t L,size_t R>	struct for_cata 	: std::integral_constant<size_t, cata<L>::value * cata<R>::value + for_cata<L+1,R-1>::value > {};  
	template <size_t L> 	   	struct for_cata<L,-1> 	: std::integral_constant<size_t, 0LL > {};  
	
	template <size_t ... T> // variadic template
	vector<size_t> GetCatalan( integer_sequence<size_t,T...> ){
		return { catalan::cata<T>::value ... }; // apply template struct to all _va_arg_(it is tuple)
	}
};


static const vector<int> SQUARE  = move( generateSquare(make_integer_sequence<int,80>()) );

// make_integer_sequence<TYPE,SIZE> = integer_sequence<TYPE,0,1,2,3,4,5,6,7...>
// index_dequence = bind template TYPE = size_t

static const vector<size_t> CATALAN  = move( catalan::GetCatalan(make_integer_sequence<size_t,20>()) ); 
static const vector<size_t> CATALAN2 = move( catalan::GetCatalan(make_index_sequence<20>()) ); 

int main(){
	
	for(uint i=0; i<=20;i++)	cout << CATALAN[i] << " \n"[i==20];
	for(uint i=0; i<=80;i++)	cout << SQUARE [i] << " \n"[i==80];
	return 0;
}
