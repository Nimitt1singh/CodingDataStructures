#include<bits/stdc++.h>

using namespace std;

class Edge{
    public:
        int v=0;
        int w=0;
    Edge(int v,int w){
        this->v = v;
        this->w = w;
    }
};
int N=7;

vector<vector<Edge>> graph(N , vector<Edge>());

void addEdge(int u,int v,int w){
    graph[u].push_back(Edge(v,w));
    graph[v].push_back(Edge(u,w));
}

void display(){
    for(int i=0;i<N;i++){
        cout<<i;
        for(auto e: graph[i]){
            cout<<"-> ("<<e.v<<","<<e.w<<")";
        }
        cout<<endl;
    }
}

bool hasPath(int src,int des,bool visited[]){
    if(src==des)
        return true;
    visited[src] = true;
    bool res = false;
    for(auto e: graph[src]){
        if(!visited[e.v])
            res = res || hasPath(e.v,des,visited); 
    }
    return res;
}

int searchVertex(int u,int v){
    for(int i=0;i<graph[u].size();i++){
        if(graph[u][i].v == v)
            return i; 
    }
    return -1;
}

void removeEdge(int u,int v){
    int l1 = searchVertex(u,v);
    graph[u].erase(graph[u].begin()+l1);

    int l2 = searchVertex(v,u);
    graph[v].erase(graph[v].begin()+l2);
}

void removeAllEdges(int u){
    for(int i= graph[u].size()-1;i>=0;i--){
        Edge e  = graph[u][i];
        removeEdge(u , e.v);        
    }
}




int allPaths(int src,int des,bool visited[],string psf,int wsf){
    if(src == des){
        cout<<psf<<" @"<<wsf<<endl;
        return 1;
    }
    visited[src] = true;
    int count=0;
    for(Edge e: graph[src]){
        if(!visited[e.v])
        count+= allPaths(e.v,des,visited,psf+" "+to_string(e.v),wsf+e.w);
    }
    visited[src] = false;
    return count;
}

int hamiltonianPath(int src,int oscr,int edgeCount,bool visited[],string psf){
    //psf.length() is wrong kyonki vetex 10 ,11,tony kuch bhi ho sakte hai
    //hence edge count = N-1 is best

    if(edgeCount==N-1){
        // psf+=to_string(src);
        int idx = searchVertex(src,oscr);

        if(idx!= -1){
            psf+=to_string(oscr);
            cout<<"Cycle:"<<psf<<endl;
        }
        else
            cout<<"Path:"<<psf<<endl;
        return 1;
    }
    visited[src] = true;
    int count =0;
    for(auto e: graph[src]){
        if(!visited[e.v])
        count+= hamiltonianPath(e.v,oscr,edgeCount+1,visited, psf+" "+to_string(e.v));
    }
    visited[src] = false;
    return count;
}

void constructGraph(){
    addEdge(0, 1, 10);
    addEdge(0, 3, 10);
    addEdge(1, 2, 10);
    addEdge(2, 3, 40);
    addEdge(3, 4, 2);
    addEdge(4, 5, 2);
    addEdge(4, 6, 8);
    addEdge(5, 6, 3);
    addEdge(2, 5, 3);

    // display();
    bool visited[N] = {0};
    //cout<<hasPath(1,10,visited);
    // cout<<allPaths(0,6,visited,"0",0);
    //display();
    //removeEdge(0,3);
    //removeAllEdges(3);
    
    //display();

    cout<<hamiltonianPath(0,0,0, visited , "0");
}

void solve(){
    constructGraph();
}

int main(){
    solve();
    return 0;
}