// ----------------------
// projects/graph/Graph.h
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------

#ifndef Graph_h
#define Graph_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <vector>  // vector

using namespace std;

// -----
// Graph
// -----

class Graph {
    public:
        // --------
        // typedefs
        // --------

        typedef int vertex_descriptor;
        typedef pair<vertex_descriptor,vertex_descriptor> edge_descriptor;

        typedef vector<vector<edge_descriptor>>::iterator vertex_iterator;
        typedef vector<edge_descriptor>::iterator edge_iterator;
        typedef int* adjacency_iterator;

        typedef size_t vertices_size_type;
        typedef size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

        /**
         * adds edge to src's edge list, if already present it will not duplicate
         * bool pertains to the element being added(T) or not(F)
         */
        friend pair<edge_descriptor, bool> add_edge (vertex_descriptor src, vertex_descriptor dest, Graph& x) {
            bool b;
            edge_descriptor ed = make_pair(src,dest);

            if(find(x.g[src].begin(), x.g[src].end(), make_pair(src,dest)) != x.g[src].end())
                b = false;
            else {
                x.g[src].push_back(ed);
                x.edges.push_back(ed);}
            
            return make_pair(ed, b);}

        // ----------
        // add_vertex
        // ----------

        /**
         * adds blank edge list to the end and 
         * returns the index (acts as vertex desc)
         */
        friend vertex_descriptor add_vertex (Graph& x) {
            vertex_descriptor v = x.g.size();
            x.g.push_back(vector<edge_descriptor>());
            return v;}

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * <your documentation>
         */
        friend pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor, const Graph&) {
            // <your code>
            static int a [] = {0, 0};     // dummy data
            adjacency_iterator b = a;
            adjacency_iterator e = a + 2;
            return make_pair(b, e);}

        // ----
        // edge
        // ----

        /**
         * returns edge,true if the edge is their and blank edge,false if not
         */
        friend pair<edge_descriptor, bool> edge (vertex_descriptor src, vertex_descriptor dest, const Graph& x) {
            pair<edge_descriptor, bool> r;
            if(find(x.g[src].begin(), x.g[src].end(), make_pair(src,dest)) != x.g[src].end())
                r = make_pair(make_pair(src,dest),true);
            else 
                r = make_pair(make_pair(0,0),false);

            return r;}

        // -----
        // edges
        // -----

        /**
         * returns the returns a pair beginning and end iterator of a vertex's edge vector
         */
        friend pair<edge_iterator, edge_iterator> edges (Graph& x) {
            edge_iterator b = x.edges.begin();
            edge_iterator e = x.edges.end();
            return make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * returns the number of edges in graph g
         */
        friend edges_size_type num_edges (const Graph& x) {
            edges_size_type est;
            est = x.edges.size();
            return est;}

        // ------------
        // num_vertices
        // ------------

        /**
         * returns how many vertices are in the graph
         */
        friend vertices_size_type num_vertices (const Graph& x) {
            vertices_size_type vst;
            vst = x.g.size();
            return vst;}

        // ------
        // source
        // ------

        /**
         * returns the source of the edge
         */
        friend vertex_descriptor source (edge_descriptor ed, const Graph& x) {
            return ed.first;}

        // ------
        // target
        // ------

        /**
         * returns the target of an edge
         */
        friend vertex_descriptor target (edge_descriptor ed, const Graph&) {
            vertex_descriptor vd;
            vd = ed.second;
            return vd;}

        // ------
        // vertex
        // ------

        /**
         * returns the nth vertex in the graph's vertex list
         */
        friend vertex_descriptor vertex (vertices_size_type n, const Graph& x) {
            vertex_descriptor v = 0+n;
            return v;}

        // --------
        // vertices
        // --------

        /**
         * returns a pair beginning and end iterator of the vertex vector
         */
        friend pair<vertex_iterator, vertex_iterator> vertices (Graph& x) {
            vertex_iterator b = x.g.begin();
            vertex_iterator e = x.g.end();
            return make_pair(b, e);}

    private:
        // ----
        // data
        // ----

        vector< vector< edge_descriptor> > g;
        vector< edge_descriptor> edges;

        // -----
        // valid
        // -----

        /**
         * <your documentation>
         */
        bool valid () const {
            // <your code>
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Graph () :
	    g(vector< vector< edge_descriptor> >()),
	    edges(vector< edge_descriptor>())	
	    {
             assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

#endif // Graph_h
