// #ifndef BUILDING_NODE_EXTENSION
#define BUILDING_NODE_EXTENSION

#include "directed_graph.h"

using namespace v8;

void Graph::Init(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New); // this calls the New member function
  tpl->SetClassName(String::NewSymbol("Graph"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // Prototype
  
  tpl->PrototypeTemplate()->Set(String::NewSymbol("add_node"),
      FunctionTemplate::New(add_node)->GetFunction());
  
  tpl->PrototypeTemplate()->Set(String::NewSymbol("add_edge"),
  	  FunctionTemplate::New(add_edge)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("update_edge"),
      FunctionTemplate::New(update_edge)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("print"),
      FunctionTemplate::New(print)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("trim"),
      FunctionTemplate::New(trim)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("bellmanford"),
      FunctionTemplate::New(bellmanford)->GetFunction());

  Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("Graph"), constructor);
}
// this is the "New member function"
Handle<Value> Graph::New(const Arguments& args) {
  HandleScope scope;

  Graph* obj = new Graph();
  obj->Wrap(args.This());
  return args.This();
}

Handle<Value> Graph::add_node(const v8::Arguments& args)
{
  HandleScope scope;

  if (args.Length() != 1 ) {
    ThrowException(Exception::TypeError(String::New("add_node: wrong number of arguments")));
    return scope.Close(Undefined());
  }

  Graph* graph = ObjectWrap::Unwrap<Graph>(args.This());

  v8::String::Utf8Value param(args[0]->ToString());
  std::string name = std::string(*param);  

  graph->add_node( name );
  return scope.Close(Boolean::New(true));
}

Handle<Value> Graph::add_edge(const v8::Arguments& args)
{
  HandleScope scope;

  Graph* graph = ObjectWrap::Unwrap<Graph>(args.This());

  if( args.Length() == 3 ){
    v8::String::Utf8Value param1(args[0]->ToString());
    v8::String::Utf8Value param2(args[1]->ToString());

    std::string from = std::string(*param1);
    std::string to = std::string(*param2);
    double weight = args[2]->NumberValue();

    graph->add_edge( from, to, weight );
    return scope.Close(Boolean::New(true));

  } else {
    ThrowException(Exception::TypeError(String::New("add_edge: wrong number of arguments")));
    return scope.Close(Undefined()); 
  }
}

Handle<Value> Graph::update_edge(const v8::Arguments& args)
{
  HandleScope scope;

  Graph* graph = ObjectWrap::Unwrap<Graph>(args.This());
  if( args.Length() == 3 ){
    v8::String::Utf8Value param1(args[0]->ToString());
    v8::String::Utf8Value param2(args[1]->ToString());

    std::string from = std::string(*param1);
    std::string to = std::string(*param2);
    double weight = args[2]->NumberValue();

    graph->update_edge( from, to, weight );
    return scope.Close(Boolean::New(true));

  } else {
    ThrowException(Exception::TypeError(String::New("update_edge: wrong number of arguments")));
    return scope.Close(Undefined()); 
  }
}

Handle<Value> Graph::print(const v8::Arguments& args)
{
  HandleScope scope;

  Graph* graph = ObjectWrap::Unwrap<Graph>(args.This());
  graph->print();

  return scope.Close(Boolean::New(true));
}

Handle<Value> Graph::trim(const v8::Arguments& args)
{
  HandleScope scope;

  Graph* graph = ObjectWrap::Unwrap<Graph>(args.This());
  graph->trim();

  return scope.Close(Boolean::New(true));
}

Handle<Value> Graph::bellmanford(const v8::Arguments& args)
{
  HandleScope scope;
  std::vector<std::vector<std::string> > path;

  if( args.Length() != 1 ) {
    ThrowException(Exception::TypeError(String::New("bellmanford(source_node): wrong number of arguments")));
    return scope.Close(Undefined()); 
  }
  Graph* graph = ObjectWrap::Unwrap<Graph>(args.This());
  v8::String::Utf8Value param1(args[0]->ToString());
  std::string source = std::string(*param1);

  graph->bellman_ford(source, path);

  Handle<Array> result = Array::New(path.size());
  
  for(unsigned long int i = 0; i < path.size(); ++i){
    Handle<Array> keyvalue = Array::New(2);

    keyvalue->Set(0, String::New(path.at(i).at(0).c_str()));
    keyvalue->Set(1, String::New(path.at(i).at(1).c_str()));

    result->Set(i, keyvalue);
  }

  return scope.Close( result );
  
}

// #endif
