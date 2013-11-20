/*
	Description: Directed Graph container designed to facilitate bellman-ford algorithm.

	Author: Gabriel Ferrin
	Date: May 7th 2013
*/
#define BUILDING_NODE_EXTENSION
#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <node.h>

class Graph : public node::ObjectWrap {
public:

	Graph();
	Graph( std::string & );
	~Graph();

	static void Init(v8::Handle<v8::Object> target);

	void print();
	void trim();
	void add_node( std::string & name );
	void add_edge( std::string &, std::string &, double );
	void update_edge( std::string &, std::string &, double );
	bool search( std::string & name );
	bool bellman_ford( std::string & name, std::vector<std::vector<std::string> > & );

private:
	/* Structs */
	struct GEdge;

	struct GNode
	{
		std::string name;
		std::vector<GEdge> edges;
		int key;

		GNode( std::string name, int k ) : name( name ), key( k ) {}
	};

	struct GEdge
	{
		double weight;
		GNode * node; // node that the edge is pointed towards

		GEdge( double weight, GNode *& n ) : weight( weight ), node( n ) {}
	};

	/* Variables */ 

	GNode *source;
	std::vector<GNode> nodes;
	
	/* V8 binding functions */
	static v8::Handle<v8::Value> New(const v8::Arguments& args);
	static v8::Handle<v8::Value> add_node(const v8::Arguments& args);
	static v8::Handle<v8::Value> add_edge(const v8::Arguments& args);
	static v8::Handle<v8::Value> update_edge(const v8::Arguments& args);
	static v8::Handle<v8::Value> print(const v8::Arguments& args);
	static v8::Handle<v8::Value> trim(const v8::Arguments& args);
	static v8::Handle<v8::Value> bellmanford(const v8::Arguments& args);

	/* Functions */ 
	void add_edge( GNode *& origin, GNode *& destination, double weight );
	bool bellman_ford( GNode *& origin, std::vector<std::vector<std::string> > & );
	GNode * get_node( std::string & name )
	{
		for( unsigned long int i = 0; i < nodes.size(); ++i ){
			if( name == nodes.at(i).name ){
				return &nodes.at(i);
			}
		}
		// this should be fixed to an empty node
		return &nodes.at(0);
	}	 
};

#endif
