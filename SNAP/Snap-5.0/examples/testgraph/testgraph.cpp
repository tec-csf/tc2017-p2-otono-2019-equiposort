#include <iostream>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <ctime> 
#include "Snap.h"
 
unsigned t0, t1;
using namespace std;

#define VERT 23 
#define NODES 14

struct Edgepeso{
    int ID;
    int peso;
};
void insertaN(PNEGraph Graph) {
  for(int i = 0; i<NODES; i++){
      Graph -> AddNode(i+1);
  }
}
void deleteN(int id,PNEGraph Graph){
    Graph -> DelNode(id);
}
void insertA(PNEGraph Graph, Edgepeso arrV[], int origen, int destino, int peso){
    int id;
    Graph -> AddEdge(origen,destino,-1);
    id = Graph ->GetEId(origen,destino);
    arrV[id].ID = id;
    arrV[id].peso = peso;
}

void deleteE(int id, PNEGraph Graph){
    Graph -> DelEdge(id);
}
void insertarAristas(PNEGraph Graph, Edgepeso arrV[]){
    insertA(Graph,arrV,1,4,8);
    insertA(Graph,arrV,1,3,8);
    insertA(Graph,arrV,4,8,2);
    insertA(Graph,arrV,4,7,3);
    insertA(Graph,arrV,7,4,6);
    insertA(Graph,arrV,8,7,3);
    insertA(Graph,arrV,8,9,3);
    insertA(Graph,arrV,9,12,4);
    insertA(Graph,arrV,9,10,2);
    insertA(Graph,arrV,12,9,2);
    insertA(Graph,arrV,12,11,8);
    insertA(Graph,arrV,11,12,6);
    insertA(Graph,arrV,12,14,9);
    insertA(Graph,arrV,14,13,2);
    insertA(Graph,arrV,13,14,6);
    insertA(Graph,arrV,3,10,4);
    insertA(Graph,arrV,10,3,10);
    insertA(Graph,arrV,3,2,7);
    insertA(Graph,arrV,3,5,8);
    insertA(Graph,arrV,2,5,7);
    insertA(Graph,arrV,4,5,1);
    insertA(Graph,arrV,5,6,9);
    insertA(Graph,arrV,6,13,4);
}

void DFS( PNEGraph Graph, int source){
    bool visitado[NODES];
    stack<int> stack;
    int s, counter=0; int dfs[NODES];;

    for(int i=0; i<NODES; i++){
        visitado[0] = false;
    }
    stack.push(source);

    printStack(stack);
    while(!stack.empty()){

        s = stack.top();
        stack.pop();

        if(visitado[s-1] == false){
            visitado[s-1] = true;
            dfs[counter] = s;
            counter++;
        }

        for(int i = 0; i<NODES; i++){
            if((Graph -> IsEdge(s, i+1, true) == 1) && visitado[i]== false){
                stack.push(i+1);
            }
        }


    }
}
void BFS(PNEGraph Graph, int source){
    bool visitado [NODES];
    queue <int> que;
    int bfs[NODES];
    int front, counter = 0;

    for(int i = 0; i < M; i++){
        visitado [i] = false;
    }

    visitado[source-1] = true;
    que.push(source);

    while(!que.empty()){
        front = que.front();
        bfs[counter] = front;
        counter++;

        for(int i = 0; i<NODES; i++){
            if((Graph -> IsEdge(front, i+1, true) == 1) && visitado[i]== false){
                visitado[i] = true;
                que.push(i+1);
            }
        }

        que.pop();
    }
}

void prim(PNEGraph Graph, Edgepeso arrV[]){
    int counter = 0, id, min, destino;
    int nodos [2][NODES];
    int pesos [VERT];
    for(int i =0; i<NODES; i++){
        nodos[0][i] = i+1;
    }

    for(int x = 0; x<NODES; x++){
        destino = x+1;
        counter=0;
        for(int i = 0; i<NODES; i++){
            if(Graph -> IsEdge(i+1, destino, true) == 1){
                id = Graph ->GetEId(i+1,destino);
                pesos[counter] = arrV[id].peso;
                counter++;
            }
        }

                min = pesos[0];
                for(int k = 0; k<counter;k++){
                    if(pesos[k]<min){
                        min = pesos[k];
                    }
                }
                nodos[1][x] = min;
    }
    nodos[1][0] = NULL;
}

void kruskal(PNEGraph Graph, Edgepeso arrV[]){
    list<int> T;
    subset *subsets = new subset[VERT];
    int x, y, src, drc;

    for (int i = 0; i < VERT; i++)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

        Edgepeso VerticeOrd[VERT];
        for(int i =0; i<VERT; i++){
            VerticeOrd[i].ID = arrV[i].ID;
            VerticeOrd[i].peso = arrV[i].peso;
        }

        sort(VerticeOrd, VerticeOrd+VERT, compare);

    for(int i =0; i<VERT; i++){
        src = GetSrc(VerticeOrd[i].ID, Graph);
        drc = GetDrc(VerticeOrd[i].ID, Graph);

        x = encontrar(subsets, src);
        y = encontrar(subsets, drc);

        if(x != y){
            T.push_back(VerticeOrd[i].ID);
            unir(subsets, x, y);
        }
        else{

        }
    }
}

void dijkstra(PNEGraph Graph, Edgepeso arrV[], int source){
    int u = source-1;
    int distancia[NODES];
    bool visitado[NODES];
    for(int i =0; i<NODES; i++){
        distancia[i] = 10000;
        visitado[i] = false;
    }
    distancia[source-1] = 0;
    for(int i = 0; i<NODES; i++){
        for(int v=0; v<NODES;v++){
        if(Graph -> IsEdge(u+1, v+1, true) == 1){
        int id = Graph ->GetEId(u+1,v+1);
        int x = arrV[id].peso;
			if(!visitado[v] && distancia[u]!=10000 && distancia[u]+x<distancia[v]){
			distancia[v]=distancia[u]+x;

		    }
        }
    }
    u = minD(distancia, visitado);
        visitado[u] = true;
  }
}

void floyd(PNEGraph Graph, Edgepeso arrV[]){
    int id, temp;
    int A[NODES][NODES];
    for(int i = 0; i<NODES; i++){
        for(int j = 0; j<NODES; j++){
            if(Graph -> IsEdge(i+1, j+1, true) == 1){
                 id = Graph ->GetEId(i+1,j+1);
                 A[i][j] = arrV[id].peso;
            }
            else{
                A[i][j] = 10000;
            }
        }
    }

    for(int i = 0; i<NODES; i++){
        A[i][i] = 0;
    }


    int C[NODES][NODES];
    for(int i = 0; i<NODES; i++){
        for(int j = 0; j<NODES; j++){
            C[i][j] = A[i][j];
        }
    }

    for(int k = 0; k<NODES; k++){
        for(int i = 0; i<NODES; i++){
            for(int j = 0; j<NODES; j++){
                temp = C[i][k] + C[k][j];
                if( C[i][j] > temp){
                    C[i][j] = temp;
                }
            }
        }
    }
}


struct subset{
    int parent;
    int rank;
};

bool compare(Edgepeso a, Edgepeso b){
    return a.peso < b.peso;
}

int GetSrc(int id, PNEGraph Graph){
    int x;
    for (TNEGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++) {
        if( EI.GetId() == id){
            x = EI.GetSrcNId();
        }
    }
    return x;
}

int GetDrc(int id, PNEGraph Graph){
    int x;
    for (TNEGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++) {
        if( EI.GetId() == id){
           x = EI.GetDstNId();
        }
    }
    return x;
}

int encontrar(subset subsets[], int i){
    if (subsets[i].parent != i)
        subsets[i].parent = encontrar(subsets, subsets[i].parent);

    return subsets[i].parent;
}

void unir(subset subsets[], int x, int y)
{
    int xroot = encontrar(subsets, x);
    int yroot = encontrar(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;

    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
int minD(int *distancia, bool *visitado){
    int min = 9999;
    int index;

    for(int i = 0; i<NODES; i++){
        if(visitado[i] == false && distancia[i] <= min){
            min = distancia[i];
            index = i;
        }
    }
    return index;

}

int main(){
    PNEGraph Graph;
    Edgepeso arrV[VERT];
    Graph = TNEGraph::New();
    t0=clock();
    insertaN(Graph);
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "Insertar vertices: " << time << "ms"<<endl;

    t0=clock();
    insertarAristas(Graph, arrV);
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "Insertar aristas: " << time << "ms"<<endl;

    t0=clock();
    DFS(Graph, 1);
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "DFS: " << time << "ms"<<endl;

    t0=clock();
    BFS(Graph, 1);
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "BFS: " << time << "ms"<<endl;

    t0=clock();
    prim(Graph, arrV);
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "Prim: " << time << "ms"<<endl;
    
    t0=clock();
    kruskal(Graph, arrV);
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "Kruskal: " << time << "ms"<<endl;
        
    t0=clock();
    dijkstra(Graph, arrV, 1);
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "Dijkstra: " << time << "ms"<<endl;
            
    t0=clock();
    floyd(Graph, arrV);
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "Floyd-Warshall: " << time << "ms"<<endl;

    t0=clock();
    deleteE(1, Graph);
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "Eliminar arista: " << time << "ms"<<endl;
    
    t0=clock();
    deleteN(3, Graph);
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "Eliminar vertice: " << time << "ms"<<endl;

    return 0;
}
