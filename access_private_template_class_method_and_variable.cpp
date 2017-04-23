#include <bits/extc++.h>
#include <iostream>
using namespace std;

template<typename Tag>
struct result {
  /* export it ... */
  typedef typename Tag::type type;
  static type ptr;
};

template<typename Tag>
typename result<Tag>::type result<Tag>::ptr;

template<typename Tag, typename Tag::type p>
struct rob : result<Tag> {
  /* fill it ... */
  struct filler {
    filler() { result<Tag>::ptr = p; }
  };
  static filler filler_obj;
};

template<typename Tag, typename Tag::type p>
typename rob<Tag, p>::filler rob<Tag, p>::filler_obj;

template <typename T>
struct A {
public:
	int p_val = 0;
private:
	int val = 0;
	void f() {
		std::cout << "proof! " << " private: "<< val << "  public: " << p_val << std::endl;
	}
};

typedef  int A<int>::*poiter_member_type_int;
typedef  void(A<int>::*poiter_method_type)(void);

template <typename T>
struct Af { typedef void(A<T>::*type)(); };

template <typename T>
struct Am { typedef int A<T>::*type; };

template class rob<Af<int>, &A<int>::f  >;
template class rob<Am<int>, &A<int>::val>;

int main() {
  A<int> a;
  int A<int>::*      poi_member  = &A<int>::p_val;
  poiter_member_type_int poi_member2 = &A<int>::p_val;
  (a.*poi_member) = 13;
  (a.*result<Af<int>>::ptr)();
  (a.*poi_member2) = 23;
  (a.*result<Am<int>>::ptr) = 999;
  (a.*result<Af<int>>::ptr)();
}
