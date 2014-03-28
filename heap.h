#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <algorithm>
#include "node.h"
class HeapCompare_f
{
public:
    bool operator() ( const Node *x, const Node *y ) const
    {
        return x->getF() > y->getF();
    }
};

class Heap
{
public:
    Heap();
    void push(const Node* node){
        m_list.push_back(node);
        push_heap(m_list.begin(), m_list.end(),HeapCompare_f());
    }
    const Node* pop(){
        const Node *n = m_list.front(); // get pointer to the node
        pop_heap( m_list.begin(), m_list.end(), HeapCompare_f() );
        m_list.pop_back();
        return n;
    }
    bool empty(){return m_list.empty();}
    bool has(const Node* node){return std::find(m_list.begin(), m_list.end(), node) != m_list.end();}
    void sort(){make_heap(m_list.begin(), m_list.end(),HeapCompare_f());}
protected:
    std::vector<const Node*> m_list;
};

#endif // HEAP_H
