#include <iostream>
using namespace std;

class Range {
public:
	const int s, t;
	Range(int s, int t): s(s), t(t) {}
	class iterator: public std::iterator<
				std::input_iterator_tag,  // iterator_category
				int,                      // value_type
				int,                      // difference_type
				const int*,               // pointer
				int>{                     // reference
		private:
			int num;
		public:
			explicit iterator (long _num = 0) : num(_num) {}
			iterator& operator++() {++num; return *this;}
			iterator operator++(int) {iterator retval = *this; ++(*this); return retval;}
			bool operator==(iterator other) const {return num == other.num;}
			bool operator!=(iterator other) const {return num != other.num;}
			reference operator*() const {return num;}
	};
	iterator begin() {return iterator(s);}
	iterator end()   {return iterator(t);}
};
 
int main() {
    for (int l : Range(3, 5)) {
        std::cout << l << ' ';
    }
}
