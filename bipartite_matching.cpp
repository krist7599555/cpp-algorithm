#include <functional>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

template <int N, int M>
 class hopcroft_karp_bipartite_matching { // O(sqrt(V) * E)
 public:
	typedef std::vector<int> Vec;
	bool used[N];
	int level[N];
	int match[M];
	Vec edge[N];
	Vec::const_iterator edge_it[N];
	hopcroft_karp_bipartite_matching(){}
	void clear(){
		std::for_each (edge, edge + N, std::mem_fn(&Vec::clear));
	}
	void bfs(){
		std::queue<int> q;
		std::fill (level, level + N, -1);
		for (int i = 0; i != N; ++i){
			if (!used[i]){
				level[i] = 0;
				q.emplace(i);
		}}
		while (!q.empty()){
			int u = q.front(); q.pop();
			for (int v : edge[u]){
				int w = match[v];
				if (w != -1 and level[w] == -1){
					level[w] = level[u] + 1;
					q.emplace(w);
		}}}
	}
	bool dfs(int u){
		for(auto& it = edge_it[u]; it != edge[u].end(); ++it){ // optimize
			int v = *it;
			int w = match[v];
			if (w == -1 or (level[w] == level[u] + 1 and dfs(w))){
				return match[v] = u,
						used[u] = true;
		}}
		return false;
	}
	int run(){
		std::fill (used, used + N, false);
		std::fill (match, match + M, -1);
		bool ok = true;
		int res = 0;
		while (ok){
			ok = false;
			bfs();
			std::transform (edge, edge + N, edge_it, std::mem_fn(&Vec::cbegin));
			for (int i = 0; i != N; ++i){
				if (!used[i] and dfs(i)){
					ok = true;
					res++;
		}}}
		return res;
	}
	inline void add_edge(int i, int j){ 
		edge[i].emplace_back(j); 
	}
	std::vector<std::pair<int, int>> backtracking() const {
		std::vector<std::pair<int, int>> res;
		for (int i = 0; i != M; ++i){
			if (~match[i]){
				res.emplace_back(match[i], i);
		}}
		std::sort (res.begin(), res.end());
		return res;
	}
};
#include <iostream>
int main(){
	auto input = []{ int i; std::cin >> i; return i; };
	hopcroft_karp_bipartite_matching<50000,50000> b;
	[[maybe_unused]] int n = input(); 
	[[maybe_unused]] int m = input();
	for (int e = input(); e--;){
		int i = input() - 1;
		int j = input() - 1;
		b.add_edge(i, j);
	}
	std::cout << b.run() << '\n';
	for (auto p : b.backtracking()){
	  std::cout << p.first << ' ' << p.second << '\n';
	}
}
