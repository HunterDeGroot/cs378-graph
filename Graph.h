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

#include <cassert>   // assert
#include <cstddef>   // size_t
#include <utility>   // make_pair, pair
#include <vector>    // vector
#include <limits>    // used to find unique vert_desc
#include <algorithm> // sort


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

        typedef vector< vertex_descriptor>::iterator vertex_iterator;
        typedef vector< edge_descriptor>::iterator edge_iterator;
        typedef vector< vertex_descriptor>::iterator adjacency_iterator;

        typedef size_t vertices_size_type;
        typedef size_t edges_size_type;

    public:

        // sorts to keep vector (indexadble) ordered
        struct vSort {
            bool operator()(pair< vertex_descriptor, vector< edge_descriptor> > a, pair< vertex_descriptor, vector< edge_descriptor> > b) { return a.first < b.first; }};
        
        struct edgeSort{
            bool operator()(edge_descriptor a, edge_descriptor b) { return a.second < b.second; }};

        // --------
        // add_edge
        // --------

        /**
         * adds edge to src's edge list, if already present it will not duplicate
         * bool pertains to the element being added(T) or not(F)
         */
        friend pair<edge_descriptor, bool> add_edge (vertex_descriptor src, vertex_descriptor dest, Graph& x) {
        
            edge_descriptor ed = make_pair(src,dest);
			vertex_descriptor vdi = x.lookup(src);
			vertex_descriptor check_dest = x.lookup(dest);
			
			// check if vertices are in g
			if(vdi == numeric_limits<int>::max()) {
                x.g.push_back(make_pair(src,vector<edge_descriptor>()));
				sort(x.g.begin(), x.g.end(),vSort());
				
				x.verts.push_back(src);
				sort(x.verts.begin(), x.verts.end());
				
				vdi = x.lookup(src);}
			if(check_dest == numeric_limits<int>::max()) {
                x.g.push_back(make_pair(src,vector<edge_descriptor>()));
				sort(x.g.begin(), x.g.end(), vSort());
				
				x.verts.push_back(dest);
				sort(x.verts.begin(), x.verts.end());}
				
			// check if the new edge is already present
            else if(find(x.g[vdi].second.begin(), x.g[vdi].second.end(), make_pair(src,dest)) != x.g[vdi].second.end())
                return make_pair(ed,false);
                
            x.g[vdi].second.push_back(ed);
            sort(x.g[vdi].second.begin(), x.g[vdi].second.end(), edgeSort());
            
            x.edges.push_back(ed);
			sort(x.edges.begin(), x.edges.end(), edgeSort());
			
            return make_pair(ed, true);}

        // ----------
        // add_vertex
        // ----------

        /**
         * adds blank edge list to the end and 
         * returns the index (acts as vertex desc)
         */
        friend vertex_descriptor add_vertex (Graph& x) {
            vertex_descriptor rvd = x.randomvd();
            x.g.push_back(make_pair(rvd,vector<edge_descriptor>()));
	    sort(x.g.begin(), x.g.end(), vSort());
            x.verts.push_back(rvd);
            return rvd;}

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * returns the beg, end iterators of the vectors adjacent vectors
         */
        friend pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor vd, Graph& x) {
			vertex_descriptor vdi = x.lookup(vd);
			x.avs = vector< vertex_descriptor>();
			size_t i;
			for(i = 0; i < x.g[vdi].second.size(); ++i)
				x.avs.push_back(x.g[vdi].second[i].second);
            adjacency_iterator b = x.avs.begin();
            adjacency_iterator e = x.avs.end();
            return make_pair(b, e);}

        // ----
        // edge
        // ----

        /**
         * returns edge,true if the edge is their and blank edge,false if not
         */
        friend pair<edge_descriptor, bool> edge (vertex_descriptor src, vertex_descriptor dest, const Graph& x) {
            
            vertex_descriptor vdi = x.lookup(src);
            if(find(x.g[vdi].second.begin(), x.g[vdi].second.end(), make_pair(src,dest)) != x.g[vdi].second.end())
                return make_pair(make_pair(src,dest),true);
            return make_pair(make_pair(0,0),false);}

        // -----
        // edges
        // -----

        /**
         * returns a pair beginning and end iterator of all the edges
         */
        friend pair<edge_iterator, edge_iterator> edges (Graph& x) {
            return make_pair(x.edges.begin(), x.edges.end());}

        // ---------
        // num_edges
        // ---------

        /**
         * returns the number of edges in graph g
         */
        friend edges_size_type num_edges (const Graph& x) {
            return x.edges.size();}

        // ------------
        // num_vertices
        // ------------

        /**
         * returns how many vertices are in the graph
         */
        friend vertices_size_type num_vertices (const Graph& x) {
            return x.verts.size();}

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
            return ed.second;}

        // ------
        // vertex
        // ------

        /**
         * returns the nth vertex in the graph's vertex list
         */
        friend vertex_descriptor vertex (vertices_size_type n, const Graph& x) {
            return x.verts[n];}

        // --------
        // vertices
        // --------

        /**
         * returns a pair beginning and end iterator of the vertex vector
         */
        friend pair<vertex_iterator, vertex_iterator> vertices (Graph& x) {
        	return make_pair(x.verts.begin(), x.verts.end());}

    private:
        // ----
        // data
        // ----

        vector< pair< vertex_descriptor, vector< edge_descriptor> > > g;
        vector< edge_descriptor> edges;
        vector< vertex_descriptor> verts;
		
		// temp to put adj verts
		vector< vertex_descriptor> avs;

        // -----
        // valid
        // -----

        /**
         * check if valid container
         */
        bool valid () const {
            return g.size() >= 0;}
            
		// -----
        // lookup
        // -----

        /**
         * returns the index of the given vert desc
         */        
         vertex_descriptor lookup(vertex_descriptor vd) const {
         	size_t i;
         	for(i = 0; i < verts.size(); ++i)
         		if(verts[i] == vd) return i;
         	
         	return -1;}
         	
         // -----
        // randomvd
        // -----

        /**
         * returns a random unused vector_descriptor
         */
         vertex_descriptor randomvd() {
         	vertex_descriptor x;
         	for(x = 0; x < numeric_limits<int>::max(); ++x){
         		size_t i;
         		bool goodvd = true;
         		for(i = 0; i < verts.size(); ++i){
    				if(x == verts[i]) goodvd = false;}
    			if(goodvd) return x;}
    			
    		return numeric_limits<int>::max();}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * default const calls default construct of containers
         * and checks if the graph is valid
         */
        Graph () {assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

#endif // Graph_h
