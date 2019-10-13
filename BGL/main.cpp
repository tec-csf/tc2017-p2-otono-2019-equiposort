#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/floyd_warshall_shortest.hpp>
#include <ctime> 
 
unsigned t0, t1;
using namespace boost;
using namespace std;
struct VertexData
{
    int num;
};
int main()
{
    //Definición de la lista de adyacencia
    typedef adjacency_list< vecS, vecS, directedS,VertexData,property<edge_weight_t, int> > MyGraphType;
    typedef graph_traits < MyGraphType >::edge_descriptor Edge;
    typedef graph_traits < MyGraphType >::vertex_descriptor Vertex;
    typedef pair<int, int> E;
    typedef graph_traits<MyGraphType>::vertex_descriptor vertex_descriptor;
    typedef property_map<MyGraphType, edge_weight_t>::type EdgeWeightMap;
    //typedef DistanceProperty::matrix_type DistanceMatrix;
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
//-------------------------------Insertar vertices------------------------------
    t0=clock();
    MyGraphType G(edge_array, edge_array + num_edges, weights, num_nodes);
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "DFS execution time: " << time << "ms"<<endl;
    //Weight map
    property_map<MyGraphType, edge_weight_t>::type weightmap = get(edge_weight, G);

//--------------------------------------- DFS --------------------------------------
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
    vertex_descriptor s = vertex(1, G);
    t0=clock();
    dijkstra_shortest_paths(G, s, predecessor_map(&predecesores[0]).distance_map(&distancias[0]));
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    cout << "Dijkstra execution time: " << time << "ms"<< endl;
// //-------------------------------Algoritmo Floyd-Warshall----------------------------
    // map<vertex_descriptor, map<vertex_descriptor, float> > matrix;
    // EdgeWeightMap weight_pmap = get(edge_weight, G);
    
    // DistanceMatrix dist(num_vertices(G));
    // DistanceMatrixMap dm(dist, G);
    // t0=clock();
    // bool noNegCycles = floyd_warshall_all_pairs_shortest_paths(G, dm, weight_map(weight_pmap));
    // t1 = clock();
    // time = (double(t1-t0)/CLOCKS_PER_SEC)*1000;
    // cout << "Floyd-Warshall execution time: " << time << "ms"<< endl;
    
    //Imprimir vertices
    // write_graphviz(cout, G/*, make_label_writer(name)*/);
    return 0;
}
