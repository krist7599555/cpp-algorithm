
vector<vector<int>> ans;
vector<vector<int>> conec;
vector<vector<int>> revconec;


bool visited[1010];

stack<int> stk;

void dfs1(int now){
	visited[now]=true;
	for(int nex : revconec[now])
		if(!visited[nex])
			dfs1(nex);
	stk.push(now);
}

void dfs2(int now){
	ans.back().pb(now);
	visited[now]=true;
	for(int nex : conec[now])
		if( ! visited[nex] ) dfs2(nex);	
}


void Kosaraju(){
	
	fill(visited,visited+1010,false);
	
	rep(i,many)
		if(! visited[i])
			dfs1(i);
	
	fill(visited,visited+1010,false);
	
	while(!stk.empty()){
		int now = stk.top(); stk.pop();
		if( ! visited[now] ){
			ans.pb({});
			dfs2(now);		
		}
	}
	
}
