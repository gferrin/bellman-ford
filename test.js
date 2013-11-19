var graph_constructor = require('./build/Release/graph');
var graph = new graph_constructor.Graph();


graph.add_node("a");
graph.add_node("b");
graph.add_node("d");
graph.add_node("e");
graph.add_node("c");

graph.add_edge("a", "b", 0.1);
graph.add_edge("b", "a", 0.2);
graph.add_edge("a", "c", 0.9);
graph.add_edge("c", "e", 0.1);
graph.add_edge("e", "c", 0.2);
graph.add_edge("e", "d", 0.2);
graph.add_edge("d", "e", 0.1);
graph.add_edge("d", "a", 0.4);
graph.add_edge("b", "d", 0.3);

graph.print();

console.log(graph.bellmanford("a"));