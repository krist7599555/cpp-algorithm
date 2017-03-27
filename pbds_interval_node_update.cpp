#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

typedef pair<uint,uint> interval;

template<class Const_Node_Iterator,
	 class Node_Iterator,
	 class Cmp_Fn = less<int>,
	 class Allocator = allocator<char> >
struct intervals_node_update{
	
public:
	// The metadata that each node stores is the largest endpoint of an
	// interval in its subtree. In this case, this is an unsigned int.
	typedef uint metadata_type;

	// Checks whether a set of intervals contains at least one interval
	// overlapping some interval. Algorithm taken from "Introduction to
	// Algorithms" by Cormen, Leiserson, and Rivest.
	bool overlaps(const interval& r_interval){
	  
		Const_Node_Iterator nd_it  = node_begin();
		Const_Node_Iterator end_it = node_end();

		while (nd_it != end_it){
			// Check whether r_interval overlaps the current interval.
			if (r_interval.second >= (*nd_it)->first&&
				r_interval.first  <= (*nd_it)->second)
				return true;

			// Get the const node iterator of the node's left child.
			Const_Node_Iterator l_nd_it = nd_it.get_l_child();

			// Calculate the maximal endpoint of the left child. If the
			// node has no left child, then this is the node's maximal
			// endpoint.
			const uint l_max_endpoint =(l_nd_it == end_it)?  0 : l_nd_it.get_metadata();

			// Now use the endpoint to determine which child to choose.
			if (l_max_endpoint >= r_interval.first) nd_it = l_nd_it;
			else 									nd_it = nd_it.get_r_child();
			 
		}
		return false;
	}

protected:
  // Update predicate: nd_it is a node iterator to the node currently
  // updated; end_nd_it is a const node iterator to a just-after leaf
  // node.
  inline void
  operator()(Node_Iterator nd_it, Const_Node_Iterator end_nd_it){
	  
    // The left maximal endpoint is 0 if there is no left child.
    const uint l_max_endpoint =(nd_it.get_l_child() == end_nd_it)?
      0 : nd_it.get_l_child().get_metadata();

    // The right maximal endpoint is 0 if there is no right child.
    const uint r_max_endpoint =(nd_it.get_r_child() == end_nd_it)?
      0 : nd_it.get_r_child().get_metadata();

    // The maximal endpoint is the endpoint of the node's interval,
    // and the maximal endpoints of its children.
    const_cast<uint&>(nd_it.get_metadata()) =
      max((*nd_it)->second, max<uint>(l_max_endpoint, r_max_endpoint));
  }

  virtual Const_Node_Iterator node_begin() const = 0;
  virtual Const_Node_Iterator node_end()   const = 0;

  virtual ~intervals_node_update(){}
};

template <typename It>
void dfs (It nd_it, It en_it, int layer){
	if (nd_it == en_it){ return ; }
	
	dfs (nd_it.get_l_child(), en_it, layer+1);
	
	cout << layer << " : ";
	for(int i = 0; i < layer; ++i) cout << "\t";
	cout << (**nd_it).first << "," << (**nd_it).second << " => " << nd_it.get_metadata() << endl;
	
	dfs (nd_it.get_r_child(), en_it, layer+1);
}

// The following function performs some operation sequence on a
// generic associative container supporting order statistics. It
// inserts some intervals, and checks for overlap.
template<class Cntnr>
void some_op_sequence(Cntnr r_c){
  // Insert some entries.
  r_c.insert(make_pair(0, 100));
  r_c.insert(make_pair(150, 160));
  r_c.insert(make_pair(300, 1000));
  r_c.insert(make_pair(10000, 100000));
  r_c.insert(make_pair(200, 100200));
  r_c.insert(make_pair(30, 1000200));
  r_c.insert(make_pair(2, 9000000));
  r_c.insert(make_pair(20000, 100));
	
	auto nd_it = r_c.node_begin();
	auto en_it = r_c.node_end();
	
	dfs (nd_it,en_it,0);	
	puts("\n\n");
}

int main()
{
  // Test a red-black tree.
  some_op_sequence(tree<
		   interval,
		   null_type,
		   less<interval>,
		   rb_tree_tag,
		   intervals_node_update>());

  // Test an ordered-vector tree.
  some_op_sequence(tree<
		   interval,
		   null_type,
		   less<interval>,
		   ov_tree_tag,
		   intervals_node_update>());

  // Test a splay tree.
  some_op_sequence(tree<
		   interval,
		   null_type,
		   less<interval>,
		   splay_tree_tag,
		   intervals_node_update>());

  return 0;
}

