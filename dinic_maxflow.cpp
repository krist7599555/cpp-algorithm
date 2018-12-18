#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <numeric>

template <size_t mxn, typename typ>
 class dinic_maxflow { // O(V^2 * E)
	struct node {
		const int nd;
		const typ cap;
		typ flw;
		node(){}
		node(int _nd, typ _cp): nd(_nd), cap(_cp), flw(0) {}
		inline void reset(){ flw = 0; };
	};
	typedef const node& cnod;
	int lyr[mxn];
	std::vector<node> edge_ls;
	std::vector<int>  edge[mxn];
	std::vector<int>::const_iterator edge_it[mxn];
	
	bool bfs (int s, int t){
		std::fill (lyr, lyr + mxn, 0);
		std::queue<int> q;
		q.push((lyr[s] = 1, s));
		while (!q.empty()){
			int nw = q.front(); q.pop();
			for (int ix : edge[nw]){
				cnod nx = edge_ls[ix];
				if (!lyr[nx.nd] and nx.flw != nx.cap){
					q.push((lyr[nx.nd] = lyr[nw] + 1, nx.nd));	
		}}}
		return lyr[t];
	}
	int dfs (int nw, int ds, typ fl = std::numeric_limits<typ>::max()){
		if (nw == ds) return fl;
		for (auto& it = edge_it[nw]; it != edge[nw].end(); ++it){
			cnod nx = edge_ls[*it];
			if (nx.flw != nx.cap and lyr[nx.nd] == lyr[nw] + 1){
				if (typ mnfl = dfs(nx.nd, ds, std::min(fl, nx.cap - nx.flw))){
					edge_ls[*it ^ 0].flw += mnfl;
					edge_ls[*it ^ 1].flw -= mnfl;
					return mnfl;
		}}}
		return 0;
	}
public:
	typedef typ value_type;
	inline void add_edge (int s, int t, typ cp, bool dir = false){
		edge[s].emplace_back(edge_ls.size());
		edge_ls.emplace_back(t, cp);
		edge[t].emplace_back(edge_ls.size());
		edge_ls.emplace_back(s, dir ? 0 : cp);
	}
	typ run (int s, int t){
		typ res = 0;
		std::for_each (edge_ls.begin(), edge_ls.end(), std::mem_fun_ref(&node::reset));
		while (bfs(s, t)){
			std::transform (edge, edge + mxn, edge_it, std::mem_fun_ref(&std::vector<int>::cbegin));
			while (typ tmp = dfs(s, t)){
				res += tmp;
		}}
		return res;
	}
};
