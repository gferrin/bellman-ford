# bellman-ford 

bellman-ford allows you to run the [bellman ford algorithm](https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm) in node.js.

It is written in C++ and ported to node.js. It uses a directed graph
as it's underlying data structure. 

## Install

`npm install bellman-ford`

## Examples

### Create Graph
```js
var graph = new bellman-ford();
``` 

### Add Nodes
```js
graph.add_node("a");
graph.add_node("b");
graph.add_node("c");
graph.add_node("d");
graph.add_node("e");
``` 

### Add Edges 
```js
graph.add_edge("a", "b", -0.1);
graph.add_edge("b", "a", 0.2);
graph.add_edge("a", "c", 0.9);
graph.add_edge("c", "e", -0.1);
graph.add_edge("e", "c", 0.2);
graph.add_edge("e", "d", 0.2);
graph.add_edge("d", "e", 0.1);
graph.add_edge("d", "a", 0.4);
graph.add_edge("b", "d", 0.3);
``` 

### Run Bellman-Ford
```js
console.log(graph.bellmanford("c"));
``` 
which will output

```js
[ [ 'a', '0.5' ],
  [ 'b', '0.4' ],
  [ 'd', '0.1' ],
  [ 'e', '-0.1' ],
  [ 'c', '0' ] ]
``` 

where each subarray contains a value in the graph say `a` and 
the distance to the source node `c` whcich in this case is `0.5`

## Functions

### add_node

This function adds a node to directed graph.
It takes one parameter `add_node(node_name)` 
If a node with `node_name` already exists then nothing wil happen

### add_edge

This function adds edges to directed graph.
It takes three parameters `add_edge(node_from, node_to, edge_weight)` 
If `node_from` or `node_to` has not yet beed added to the graph then
the function call will fail

### update_edge

This function updates edge weights between nodes
It takes three parameters `update_edge(node_from, node_to, edge_weight)`

### print

This function prints out the current graph

```js
graph.print();
```
for the given example will output 
```
a:
	weight: -0.1 to: b
	weight: 0.9 to: c
b:
	weight: 0.2 to: a
	weight: 0.3 to: d
d:
	weight: 0.1 to: e
	weight: 0.4 to: a
e:
	weight: 0.2 to: c
	weight: 0.2 to: d
c:
	weight: -0.1 to: e
```

### trim 

This function removes all nodes with less then two edges as well
as removing all associated edges.

### bellmanford

This is the main function which will run the bellman ford algorithm on
the current graph. It will return a 2d array of the form 
`[node_name, distance_from_source]`

If the graph contains negative weight cycles then it will return an empty array

## Compiling from Source

To compile the code from source you must have `python` `gcc` and `node-gyp` 
installed on your machine.

Then run 

`node-gyp configure`

and

`node-gyp build`

## Notes

So fare I have only tested this on OS X. I would appricate any and all feedback 
and suggestions on how this could be improved. 




