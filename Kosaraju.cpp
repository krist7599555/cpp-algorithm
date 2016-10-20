// https://gist.github.com/thinkphp/b8cc6ed784a7323acd08

int n, m;
struct Node{
    vector<int> adj; // point to nex
    vector<int> rev_adj; // nex point to me
};
Node graf[MAX_N];

stack<int> S;
bool visited[MAX_N];

int component[MAX_N];
vector<int> components[MAX_N];
int numComponents;

void kosaraju_dfs_1(int x)
{
    visited[x] = true;
    for(int nex : graf[x].adj)
        if (!visited[nex]) kosaraju_dfs_1(nex);
    
    S.push(x);
}

void kosaraju_dfs_2(int x)
{
    printf("%d ", x);
    component[x] = numComponents;
    components[numComponents].push_back(x);
    visited[x] = true;
    
    for(int nex : graf[x].rev_adj)
        if (!visited[nex]) kosaraju_dfs_2(nex);

}

void Kosaraju()
{
    for (int i=0;i<n;i++)
        if (!visited[i]) kosaraju_dfs_1(i);
    
    fill(visited,visited+n,false);
    
    while (!S.empty()){
        int v = S.top(); S.pop();
        if (!visited[v]){
            printf("Component %d: ", numComponents);
            kosaraju_dfs_2(v);
            numComponents++;
            printf("\n");
        }
    }
}
