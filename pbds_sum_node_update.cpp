#include <bits/extc++.h>
#include <iostream>
using namespace __gnu_pbds;
using namespace std;

template<
	 class Const_Node_Iterator,
	 class Node_Iterator,
	 class Cmp_Fn,
	 class Allocator>
struct sum_node_update {
public:
	
	virtual Node_Iterator node_begin() = 0;
	virtual Node_Iterator node_end  () = 0;

	typedef int metadata_type;
	
	int get_sum (const int& key){
		
		Const_Node_Iterator nd_it = node_begin();
		Const_Node_Iterator en_it = node_end();
		
		int res = 0;
		
		while (nd_it != en_it){
			
			if (key < **nd_it){
				nd_it = nd_it.get_l_child();
				
			}else{
				res += nd_it.get_metadata() 
					- (nd_it.get_r_child() != en_it ? nd_it.get_r_child().get_metadata() : 0);
				if (key > **nd_it)
					 nd_it = nd_it.get_r_child();
				else nd_it = en_it;
			}
		}
		return res;
	}
	
	void operator () (Node_Iterator nd_it, Const_Node_Iterator en_it){
		int vl = nd_it.get_l_child() != en_it ? nd_it.get_l_child().get_metadata() : 0;
		int vr = nd_it.get_r_child() != en_it ? nd_it.get_r_child().get_metadata() : 0;
		const_cast<int&>(nd_it.get_metadata()) = (**nd_it) + vl + vr;
	}
	
};

vector<int> v{1,2,3,5,6,7,8};
tree  <int,null_type,less<int>,rb_tree_tag,sum_node_update> t;

int main(){

    cin.sync_with_stdio(0);
	t.copy_from_range(begin(v),end(v));
	for (int i : t)
		printf("%d sum = %d\n",i,t.get_sum(i));
}

