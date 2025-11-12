#include <stdio.h>
#include <stdbool.h>

#define V 5
#define MAX 100

void SCCUtil(int u, int disc[], int low[], int st[], bool inStack[], int *top, int graph[V][V]) {
    static int time = 0;
    disc[u] = low[u] = ++time;
    st[++(*top)] = u; inStack[u] = true;

    for (int v = 0; v < V; v++) if (graph[u][v]) {
        if (disc[v] == -1) {
            SCCUtil(v, disc, low, st, inStack, top, graph);
            if (low[v] < low[u]) low[u] = low[v];
        } else if (inStack[v] && disc[v] < low[u]) low[u] = disc[v];
    }

    if (low[u] == disc[u]) {
        printf("SCC: ");
        while (st[*top] != u) { printf("%d ", st[*top]); inStack[st[*top]--] = false; }
        printf("%d\n", st[*top]); inStack[st[*top]--] = false;
    }
}
void findSCCs(int graph[V][V]) {
    int disc[V], low[V], st[MAX], top=-1; bool inStack[V]={0};
    for(int i=0;i<V;i++) disc[i]=-1;
    for(int i=0;i<V;i++) if(disc[i]==-1) SCCUtil(i,disc,low,st,inStack,&top,graph);
}

void APBUtil(int u,bool vis[],int disc[],int low[],int parent[],bool ap[],int graph[V][V]){
    static int time=0; vis[u]=true; disc[u]=low[u]=++time; int children=0;
    for(int v=0;v<V;v++) if(graph[u][v]){
        if(!vis[v]){ children++; parent[v]=u; APBUtil(v,vis,disc,low,parent,ap,graph);
            if(low[v]<low[u]) low[u]=low[v];
            if(parent[u]==-1&&children>1) ap[u]=true;
            if(parent[u]!=-1&&low[v]>=disc[u]) ap[u]=true;
            if(low[v]>disc[u]) printf("Bridge: %d-%d\n",u,v);
        } else if(v!=parent[u]&&disc[v]<low[u]) low[u]=disc[v];
    }
}
void findAPsAndBridges(int graph[V][V]){
    bool vis[V]={0},ap[V]={0}; int disc[V],low[V],parent[V]; for(int i=0;i<V;i++)parent[i]=-1;
    for(int i=0;i<V;i++) if(!vis[i]) APBUtil(i,vis,disc,low,parent,ap,graph);
    printf("Articulation Points: "); for(int i=0;i<V;i++) if(ap[i]) printf("%d ",i); printf("\n");
}

typedef struct{int u,v;}Edge;
void BCCUtil(int u,bool vis[],int disc[],int low[],int parent[],Edge st[],int *top,int graph[V][V]){
    static int time=0; vis[u]=true; disc[u]=low[u]=++time; int children=0;
    for(int v=0;v<V;v++) if(graph[u][v]){
        if(disc[v]==-1){ children++; parent[v]=u; st[++(*top)]={u,v};
            BCCUtil(v,vis,disc,low,parent,st,top,graph); if(low[v]<low[u]) low[u]=low[v];
            if((parent[u]==-1&&children>1)||(parent[u]!=-1&&low[v]>=disc[u])){
                printf("BCC: "); while(st[*top].u!=u||st[*top].v!=v){printf("(%d-%d) ",st[*top].u,st[*top].v);(*top)--;}
                printf("(%d-%d)\n",st[*top].u,st[*top].v);(*top)--;
            }
        } else if(v!=parent[u]&&disc[v]<disc[u]){ if(disc[v]<low[u]) low[u]=disc[v]; st[++(*top)]={u,v}; }
    }
}
void findBCCs(int graph[V][V]){
    bool vis[V]={0}; int disc[V],low[V],parent[V]; for(int i=0;i<V;i++)disc[i]=low[i]=-1,parent[i]=-1;
    Edge st[MAX]; int top=-1; for(int i=0;i<V;i++) if(disc[i]==-1) BCCUtil(i,vis,disc,low,parent,st,&top,graph);
    if(top!=-1){ printf("BCC: "); while(top>=0){printf("(%d-%d) ",st[top].u,st[top].v);top--;} printf("\n"); }
}

int main(){
    int graph1[V][V]={ 
        {0,1,0,0,0},{0,0,1,0,0},{1,0,0,1,0},{0,0,0,0,1},{0,0,0,0,0}};
    int graph2[V][V]={ 
        {0,1,1,0,0},{1,0,1,1,0},{1,1,0,1,1},{0,1,1,0,1},{0,0,1,1,0}};
    printf("=== SCCs (Directed) ===\n"); findSCCs(graph1);
    printf("\n=== APs & Bridges (Undirected) ===\n"); findAPsAndBridges(graph2);
    printf("\n=== BCCs (Undirected) ===\n"); findBCCs(graph2);
}
