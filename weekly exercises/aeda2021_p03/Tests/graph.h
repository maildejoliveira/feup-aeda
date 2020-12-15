#include <iostream>
#include <vector>

using namespace std;


template <class N, class E> class Edge;
template <class N, class E> class Node;

template <class N, class E>
class Node {
public:
    N info;
    vector< Edge<N,E> > edges;
    Node(N inf) {
        info = inf;
    }
};

template <class N, class E>
class Edge {
public:
    E value;
    Node<N,E> *destination;
    Edge(Node<N,E> *dest, E val) {
        value = val;
        destination = dest;
    }
};

template <class N, class E>
class Graph {
    vector< Node<N,E> *> nodes;
public:
    Graph() {};
    ~Graph() {};
    Graph & addNode(const N &inf);
    Graph & addEdge(const N &begin, const N &end, const E &val);
    Graph & removeEdge(const N &begin, const N &end);
    E & edgeValue(const N &begin, const N &end);
    unsigned numEdges(void) const ;
    unsigned numNodes(void) const ;
    void print(std::ostream &os) const;
};

template <class N, class E>
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g){
    g.print(out);
    return out;
}


// exception NodeAlreadyExists
template <class N>
class NodeAlreadyExists
{
public:
    N info;
    NodeAlreadyExists(N inf) { info=inf; }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeAlreadyExists<N> &no)
{ out << "Node already exists: " << no.info; return out; }


// exception NodeDoesNotExist
template <class N>
class NodeDoesNotExist {
public:
    N info;
    NodeDoesNotExist(N inf) {
        info = inf;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeDoesNotExist<N> &no)
{ out << "Node does not exist: " << no.info; return out; }

//exception EdgeAlreadyExists
template <class N>
class EdgeAlreadyExists
{
public:
    N begin, end;
    EdgeAlreadyExists(N beg, N en){
        begin=beg;
        end=en;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const EdgeAlreadyExists<N> &ed) {
    out << "Edge already exists: " << ed.begin << " , " << ed.end; return out;
}

//Exception EdgeDoesNotExist
template <class N>
class EdgeDoesNotExist
{
public:
    N begin, end;
    EdgeDoesNotExist(N beg, N en){
        begin=beg;
        end=en;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const EdgeDoesNotExist<N> &ed) {
    out << "Edge does not exist: " << ed.begin << " , " << ed.end; return out;
}

template<class N, class E>
Graph<N,E> &Graph<N, E>::addNode(const N &inf) {
    for (auto it=nodes.begin(); it!=nodes.end(); ++it){
        if((*it)->info==inf) {
            NodeAlreadyExists<N> exc(inf);
            throw (exc);
        }
    }
    this->nodes.push_back(new Node<N,E>(inf));
    return *this;
}

template<class N, class E>
unsigned Graph<N, E>::numEdges(void) const {
    unsigned numE=0;
    for (auto it=nodes.begin(); it!=nodes.end(); ++it) {
        numE += (*it)->edges.size();
    }
    return numE;
}

template<class N, class E>
unsigned Graph<N, E>::numNodes(void) const {
    return nodes.size();
}

template<class N, class E>
Graph<N,E> &Graph<N, E>::addEdge(const N &begin, const N &end, const E &val) {
    for (int i=0; i<nodes.size(); i++){
        if (nodes[i]->info==begin){
            for (int j=0; j<nodes.size(); j++){
                if (nodes[j]->info==end){
                    for (int e=0; e<nodes[i]->edges.size(); e++){
                        if (nodes[i]->edges[e].destination->info==end){
                            EdgeAlreadyExists<N> exc(begin, end);
                            throw exc;
                        }
                    }
                    nodes[i]->edges.push_back(Edge<N,E>(nodes[j], val));
                    return *this;
                }
            }
            NodeDoesNotExist<N> exc(end);
            throw (exc);
        }
    }
    NodeDoesNotExist<N> exc(begin);
    throw (exc);
}

template<class N, class E>
E &Graph<N, E>::edgeValue(const N &begin, const N &end) {
    for (int i=0; i<nodes.size(); i++) {
        if (nodes[i]->info == begin) {
            for (int j=0; j<nodes[i]->edges.size(); j++){
                if (nodes[i]->edges[j].destination->info==end){
                    return nodes[i]->edges[j].value;
                }
            }
            EdgeDoesNotExist<N> exc(begin, end);
            throw exc;
            NodeDoesNotExist<N> exc1(end);
            throw (exc1);
        }
    }
    NodeDoesNotExist<N> exc(begin);
    throw (exc);

}

template<class N, class E>
Graph<N,E> &Graph<N, E>::removeEdge(const N &begin, const N &end) {
    for (auto it=nodes.begin(); it!=nodes.end(); ++it){
        if ((*it)->info == begin) {
            for (auto ite=(*it)->edges.begin(); ite!=(*it)->edges.end(); ++ite){
                if ((*ite).destination->info==end){
                    (*it)->edges.erase(ite);
                    return *this;
                }
            }
            EdgeDoesNotExist<N> exc(begin, end);
            throw exc;
            NodeDoesNotExist<N> exc1(end);
            throw (exc1);
        }
    }
    NodeDoesNotExist<N> exc(begin);
    throw (exc);
}

template<class N, class E>
void Graph<N, E>::print(ostream &os) const {
    for (int i=0; i<nodes.size(); i++){
        os << "( " << nodes[i]->info;
        for (int j=0; j<nodes[i]->edges.size(); j++){
            os << "[ " << nodes[i]->edges[j].destination->info << " " << nodes[i]->edges[j].value << "] ";
        }
        os << ") ";
    }
}
