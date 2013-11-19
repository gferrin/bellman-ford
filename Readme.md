# bellman-ford 

bellman-ford allows you to run the bellman ford algorithm in node.js.

It is written in C++ and ported to node.js and uses a directed graph
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





