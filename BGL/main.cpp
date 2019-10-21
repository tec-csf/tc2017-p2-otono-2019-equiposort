#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/floyd_warshall_shortest.hpp>
#include <boost/graph/exterior_property.hpp>
#include <ctime> 
 
unsigned t0, t1;
using namespace boost;
using namespace std;
struct VertexData
{
    int num;
};
typedef adjacency_list< vecS, vecS, directedS,VertexData,property<edge_weight_t, int> > MyGraphType;//Definición de la lista de adyacencia
typedef graph_traits < MyGraphType >::edge_descriptor Edge;
typedef graph_traits < MyGraphType >::vertex_descriptor Vertex;
typedef pair<int, int> E;
typedef graph_traits<MyGraphType>::vertex_descriptor vertex_descriptor;
typedef property_map<MyGraphType, edge_weight_t>::type EdgeWeightMap;
// typedef DistanceDistanceProperty::matrix_type DistanceMatrix;
// typedef DistanceProperty::matrix_map_type DistanceMatrixMap;
void insertV(MyGraphType G);
void insertE(MyGraphType G);
void deleteV(MyGraphType G);
void delteE(MyGraphType G);
void dfs(MyGraphType G);
void bfs(MyGraphType G);
void prim(MyGraphType G);
void kruskal(MyGraphType G);
void dijkstra(MyGraphType G);
void floyd(MyGraphType G);
bool empty(MyGraphType G);
void addVertex(int num, MyGraphType G);

void insertV(MyGraphType G){

}
void insertE(MyGraphType G){

}
void deleteV(MyGraphType G){

}
void delteE(MyGraphType G){

}
void dfs(MyGraphType G){
    default_dfs_visitor vis;
    depth_first_search(G, visitor(vis));
        cout << "DFS execution time: " << time << "ms"<<endl;
}
void bfs(MyGraphType G){
    default_bfs_visitor vis2;
    breadth_first_search(G, vertex(0,G),visitor(vis2));
}
void prim(MyGraphType G){
    vector <vertex_descriptor> p(num_vertices(G));
    prim_minimum_spanning_tree(G, &p[0]);
}
void kruskal(MyGraphType G){
    property_map < MyGraphType, edge_weight_t >::type weight = get(edge_weight, G);
    vector < Edge > spanning_tree;
    kruskal_minimum_spanning_tree(G, back_inserter(spanning_tree));
}
void dijkstra(MyGraphType G){
    vector<vertex_descriptor> predecesores(num_vertices(G));
    vector<int> distancias(num_vertices(G));
    vertex_descriptor s = vertex(0, G);
    dijkstra_shortest_paths(G, s, predecessor_map(&predecesores[0]).distance_map(&distancias[0]));
}
void floyd(MyGraphType G){
    map<vertex_descriptor, map<vertex_descriptor, float> > matrix;
    EdgeWeightMap weight_pmap = get(edge_weight, G);
    
    DistanceMatrix dist(num_vertices(G));
    DistanceMatrixMap dm(dist, G);
    bool result = floyd_warshall_all_pairs_shortest_paths (G, dm, weight_map(weight_pmap));

}
bool empty(MyGraphType G){
        if(num_vertices(G) == 0)
        return true;
    else
        return false;
}
void addVertex(int num, MyGraphType G){
    auto v = add_vertex(G);
    //G[v] = num;
}

void tiempos(MyGraphType G){

//-------------------------------- Insertar vertice --------------------------------------
    t0=clock();
    auto v1 = add_vertex(G);
    t1 = clock();
    auto v2 = add_vertex(G);
    double time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "Vertex v1 insertion execution time: " << time << "ms"<<endl;
//--------------------------------- Insertar arista -------------------------------
    t0=clock();
    add_edge(v1,v2,8,G);
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "Edge v1 to v2 with weight 8 insertion execution time: " << time << "ms"<<endl;
    //--------------------------------- Eliminar arista -------------------------------
    t0=clock();
    remove_edge(v1,v2,G);
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "Edge v1 to v2 with weight 8 removal execution time: " << time << "ms"<<endl;
//--------------------------------- Eliminar vertice -------------------------------
    t0=clock();
    remove_vertex(v1, G);
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "Vertex v1 deletion execution time: " << time << "ms"<<endl;

//-------------------------------------- DFS ----------------------------------------

    default_dfs_visitor vis;
    t0=clock();
    depth_first_search(G, visitor(vis));
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "DFS execution time: " << time << "ms"<<endl;

//--------------------------------------- BFS --------------------------------------

    default_bfs_visitor vis2;
    t0=clock();
    breadth_first_search(G, vertex(0,G),visitor(vis2));
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "BFS execution time: " << time << "ms"<< endl;

//-----------------------------------Algoritmo Prim---------------------------------

    vector <vertex_descriptor> p(num_vertices(G));
    t0=clock();
    prim_minimum_spanning_tree(G, &p[0]);
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "Prim execution time: " << time << "ms"<< endl;

// //----------------------------------Algoritmo Kruskal-------------------------------

    property_map < MyGraphType, edge_weight_t >::type weight = get(edge_weight, G);
    vector < Edge > spanning_tree;
    t0=clock();
    kruskal_minimum_spanning_tree(G, back_inserter(spanning_tree));
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "Kruskal execution time: " << time << "ms"<< endl;

// //---------------------------------Algoritmo Dijkstra-------------------------------

    vector<vertex_descriptor> predecesores(num_vertices(G));
    vector<int> distancias(num_vertices(G));
    vertex_descriptor s = vertex(0, G);
    t0=clock();
    dijkstra_shortest_paths(G, s, predecessor_map(&predecesores[0]).distance_map(&distancias[0]));
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "Dijkstra execution time: " << time << "ms"<< endl;

// //-------------------------------Algoritmo Floyd-Warshall----------------------------
    map<vertex_descriptor, map<vertex_descriptor, float> > matrix;
    EdgeWeightMap weight_pmap = get(edge_weight, G);
    
    DistanceMatrix dist(num_vertices(G));
    DistanceMatrixMap dm(dist, G);
    t0=clock();
    bool result = floyd_warshall_all_pairs_shortest_paths (G, dm, weight_map(weight_pmap));
    cout <<endl<< "Distance matrix: " << endl;
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "Floyd-Warshall execution time: " << time << "ms"<< endl;
}
int main()
{
    int menu = 0;
    int num,ver1,ver2,peso;
    const int num_nodes = 14;
    E edge_array[] = { 
    E(1, 4), E(1, 3), E(2, 5), E(3, 2), E(3, 5),
    E(3, 10), E(4, 5), E(4, 7),
    E(4, 8), E(5, 6), E(6, 13),
    E(7, 4), E(8, 7), E(8, 9),
    E(9, 10), E(9, 12), E(10, 3),
    E(10, 6), E(11, 12), E(12, 9),
    E(12, 11), E(12, 14), E(13, 14), E(14, 13)
    };
    int weights[] = { 8, 8, 7, 7, 8, 4, 1, 3, 2, 9, 4, 6, 3, 3, 2, 4, 10, 6, 6, 2, 8, 9, 6, 2 };
    size_t num_edges = sizeof(edge_array) / sizeof(E);
    MyGraphType G(edge_array, edge_array + num_edges, weights, num_nodes);//Creacion del G
        
    //Imprimir vertices
    //write_graphviz(cout, G/*, make_label_writer(name)*/);
    tiempos(G);
    while(menu != 11){
        cout << "1) Insertar vértice"<< endl;
        cout << "2) Insertar arista"<< endl;
        cout << "3) Eliminar vértice" << endl;
        cout << "4) Eliminar arista" << endl;
        cout << "5) Algoritmo DFS" << endl;
        cout << "6) Algoritmo BFS" << endl;
        cout << "7) Obtener arbol con Prim" << endl;
        cout << "8) Obtener arbol con Kruskal" << endl;
        cout << "9) Obtener ruta minima con Dijkstra" << endl;
        cout << "10) Obtener ruta minima con Floyd-Warshall" << endl;
        cout << "11) Salir" << endl;
        cin >> menu;
        switch (menu) {
            case 1:
                cout << "Numero de vertice: ";
                cin >> num;
                addVertex(num, G);
                break;
            case 2:
                cout << "De vertice: ";
                cin >> ver1;
                cout << "A vertice: ";
                cin >> ver2;
                cout << "Peso: ";
                cin >> peso;
                add_edge(ver1,ver2,peso,G);
                break;
            case 3:
                cout << "Numero de vertice: ";
                cin >> num;
                remove_vertex(num, G);
                break;
            case 4:
                cout << "De vertice: ";
                cin >> ver1;
                cout << "A vertice: ";
                cin >> ver2;
                cout << "Peso: ";
                cin >> peso;
                remove_edge(ver1, ver2, G);
                break;
            case 5:
                if(!empty(G))
                    dfs(G);
                break;
            case 6:
                if(!empty(G))
                    bfs(G);
                break;
            case 7:
                if(!empty(G))
                    prim(G);
                break;
            case 8:
                if(!empty(G))
                    kruskal(G);
                break;
            case 9:
                if(!empty(G))
                    dijkstra(G);
                break;
            case 10:
                if(!empty(G))
                    floyd(G);
                break;
            case 11:
                break;
            default:
                cout << "Opcion no valida" << endl;
                break;
        }
    }
    return 0;
}