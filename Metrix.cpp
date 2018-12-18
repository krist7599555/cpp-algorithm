#include <bits/stdc++.h>
using namespace std;

template<typename T>
class Matrix{
	
	static const long long modd = 1000000007;
	
	protected :
	
		int row,col;
		vector<vector<T>> vec;
	
	public :
	
	// initiation
	
		Matrix(int r,int c){
			row = r;
			col = c;
			vec.resize(r);
			for(auto& v : vec) v.resize(c);
		}
		
		Matrix(int r,int c,const initializer_list<initializer_list<T>>& lis){
			row = r;
			col = c;
			vec.resize(r);
			move(lis.begin(),lis.end(),vec.begin());
			for(auto& v : vec) v.resize(c);
		}
		
		Matrix(const initializer_list<initializer_list<T>>& lis){
			move(lis.begin(),lis.end(),back_inserter(vec));
			row = vec.size();
			col = max_element(vec.begin(),vec.end(),[](const vector<T>& a, const vector<T>& b){ return a.size() < b.size(); }) -> size();
			for(vector<T>& v : vec) v.resize(col);
		}
		
		Matrix<T> operator * (void){ return *this;}
	
	// return scope
		
		inline vector<vector<T>> & 	operator ()()			 { return this->vec; }
		inline vector<T> & 			operator [](int r)		 { return this->vec[r]; }
		inline T & 					operator ()(int r,int c) { return this->vec[r][c]; }
		
		inline const vector<vector<T>> & 	operator ()()			 const { return this->vec; }
		inline const vector<T> & 			operator [](int r) 		 const { return this->vec[r]; }
		inline const T& 					operator ()(int r,int c) const { return this->vec[r][c]; }
		
	// multiply
	
		template<typename T2>
		friend Matrix<T> operator * (const Matrix<T>& a, const Matrix<T2>& b){
			
			Matrix<T> ret(a.row,b.col);
			if(a.col!=b.row) return ret;
			
			for(int i=0; i<a.row; i++){
			for(int j=0; j<b.col; j++){
				for(int k=0;k<a.col;k++){
					ret[i][j] += a[i][k] * b[k][j];	
					ret[i][j] %= modd;
				}
			}}
			return ret;
		}
	
	// power
	
		Matrix<T> pow(int factor){
			if(factor==0) return Matrix<T>::baseMatrix(row);
			if(factor==1) return *this;
			Matrix<T> ret(this->pow(factor/2));
			return ret * ret * (factor&1 ?  *this : Matrix<T>::baseMatrix(row) );
		}
	
	// erase
	
		void erase(int r,int c){
			for(vector<T>& v : (*this)() ) 
				v.erase(v.begin()+c);
			(*this)().erase((*this)().begin()+r);
			this->row--;
			this->col--;
		}
	
	// determinant
	
		int det(){
			if(this->row==1 && this->col==1) return (*this)(0,0);
			int ret = 0;
			for(int i=0;i<this->row;i++){
				Matrix<int> temp(*this);
				int init = i&1? -temp[i][0] : temp[i][0];
				ret += init * ( temp.erase(i,0), temp.det() );
			}
			return ret;
		};
	
	// ostream out
	
		friend ostream& operator << (ostream& out,const Matrix<T>& m){
			for(const vector<T>& v : m()){
				for(const T& i :  v)
				out << i << ' ';
				out << endl;
			}return out;
		}
		
	// fill
	
		void fill(T around, T middle){
			this->fillAround(around);
			this->fillMiddle(middle);
		}
	
		void fillAround(T around){
			for(auto& v : vec)
				for(T& i : v)
					i = around;
		}
		
		void fillMiddle(T middle){
			for(int i=0;i<row;i++)
				vec[i][i] = middle;
		}

		
	// baseMatrix
	
		static Matrix<T> baseMatrix(int sz){
			Matrix<T> ret(sz,sz);
			ret.fill(0,1);
			return ret;
		}
		
	// accumulate
		
		T accumulate(){
			T ret{};
			for(auto& v : vec)
				for(T& i : v)
					ret += i;
			return ret;
		}
		
	// isSquare
		
		bool isSquare(){
			return row == col;
		}
		
	// transpote
		
		void transpote(){
			for(int i=0; i<row; i++){
			for(int j=0; j< i ; j++){
				swap(this->vec[i][j],this->vec[j][i]);
			}}
		}
	
};


int main(){}
