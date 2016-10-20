
typedef pair<int,int> pii;

class Graph{
	int V;
	list<pii> *adj;
public:
	Graph(int V);
	void addEdge(int u, int v, int w);
	void bellmanFord(int s);
};

Graph::Graph(int V){
	this->V = V;
	adj = new list<pii> [V];
}

void Graph::addEdge(int u, int v, int w){
	adj[u].push_back(make_pair(v,w));
}

void Graph::bellmanFord(int s){

	int dist[V];
	fill(dist,dist+v,INT_MAX);
	
	dist[s]=0;

	for(int i=0;i<V;i++){
		for(const iPair & pi : adj[i]){
			if(dist[i]!=INT_MAX && dist[pi.fi] > dist[i]+pi.se){
				dist[pi.fi]=dist[i]+pi.se;
			}
		}
	}

	for(int i=0;i<V;i++){	
		for(const iPair & pi : adj[i]){
			if(dist[i]!=INT_MAX && dist[i]+pi.se < dist[pi.fi]){
				cout<<"Negative cycle exists\n";
				return ;
			}
		}
	}
	
	cout<<"Negative cycle does not exist\n";
	for(int i = 0 ;i<V; i++)cout<<i<<" "<<dist[i]<<endl;
	
}
