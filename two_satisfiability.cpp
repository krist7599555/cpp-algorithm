#include <vector>
#include <algorithm>
#include <string>
/**
 * Two_Satisfiability can solve in polynimoal time
 * implement : covert closure to implies operator
 * and solve by strongly connected component
 * proof by contradic a -> ... -> !a -> ... -> a
 * is unable to solve is a and !a is on same component
 */
template <int N>
 class Two_Satisfiability {
 public:
	Two_Satisfiability(){ clear(); }
	static inline int eval(int i){ return std::max(i,~i) << 1 | (i < 0); }
	[[maybe_unused]] static inline int invl(int i){ return i & 1 ? ~(i/2) : i/2; }
	[[maybe_unused]] static inline Str tstr(int i){ return (i & 1 ? "-" : "+") + to_string(i/2); }
	[[maybe_unused]] void _is_true(int i){ _implies(i^1, i); };
	[[maybe_unused]] void _is_fals(int i){ _implies(i, i^1); };
	#define make_func(name,...) \
	inline void _##name(int i,int j){__VA_ARGS__;} \
	inline void    name(int i,int j){return _##name(eval(i),eval(j));}
	#define im(i,j) _implies(i,j)
	make_func(implies, if(i != j) edge[i].push_back(j));		// impl ->
	make_func(equivla, im(i,j),   im(j,i)); 			// eq  ==
	make_func(conjunc, im(i^1,j), im(j^1,i)); 			// or  |
	make_func(nequivl, im(i^1,j), im(j^1,i), im(i,j^1), im(j,i^1)); // xor ^
	#undef im
	#undef make_func
	typedef std::vector<int> Vec;
	Vec edge[N * 2];
	bool vis[N * 2];
	int  low[N * 2];
	int  num[N * 2];
	[[maybe_unused]] Vec head;
	[[maybe_unused]] Vec comp[N * 2];
	[[maybe_unused]] int  dep[N * 2];
	int  tim = 0;
	int tarjan (int u, int pa = -1){
		if(!vis[u]){
			vis[u] = true;
			dep[u] = ~pa ? dep[pa] + 1 : 0;
			low[u] = num[u] = tim++;
			for (int v : edge[u]){
				low[u] = std::min(low[u], vis[v] ? num[v] : tarjan(v, u));
		}}
		if (low[u] == num[u]) 
			head.push_back(low[u]);
		comp[low[u]].push_back(u);
		return low[u];
	}
	void clear(){
		tim = 0;
		head.clear();
		std::fill(vis, vis + N * 2, false);
		std::for_each(edge, edge + N * 2, std::mem_fn(&Vec::clear));
		std::for_each(comp, comp + N * 2, std::mem_fn(&Vec::clear));
	}
	bool solve(){
		for (int i = 0; i != N; ++i){
			if (tarjan(eval(i)) == tarjan(eval(~i))){
				return false;
		}}
		return true;
	}
	[[maybe_unused]] 
	 std::vector<bool> backtracking(){
		if(!solve()) return "";
		std::vector<bool> res(N);
		std::string dp(N * 2, '-');
		std::sort (head.begin(), head.end(), [&](int i, int j){
			return dep[comp[i].back()] > dep[comp[j].back()];
		});
		for (int i : head){
			assert (num[i] == low[i]);
			std::string str;
			for (int j : comp[i]){
				if (dp[j] != '-') str += dp[j];
				for (int k : edge[j]){
					if (dp[k] != '-'){
						str += dp[k] ^ 'T' ^ 'F';
			}}}
			char c = str.empty() ? 'T' : ~str.find('F') ? 'F' : 'T';
			for (int j : comp[i]){
				dp [j]   = c;
				dp [j^1] = c ^ 'T' ^ 'F';
				res[j/2] = dp[j&-2] == 'T';
		}}
		return res;
	}
};
