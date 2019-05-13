#pragma once
#include <assert.h>

template<typename T>
class Heap
{

    public:
    enum Type{Min,Max};
    
    public:
    Heap(Type tp = Min, int size = 100)
    : m_size(0)
    , m_root(new T[size])    
    , m_type(tp)
    , m_cap(size)
    {}

    bool insert(const T& value);
    T remove();
    private:
    void correct_up(int ind);
    void correct_down(int ind);
    int get_p(int curr)
    {
        
        return (curr>0)? (curr-1)/2: -1; 
    }
    int get_l(int curr)
    {
        return ((2*curr + 1) >= m_size)? -1: (2*curr + 1);
    }
    int get_r(int curr)
    {
        return ((2*curr + 2) >= m_size)? -1: (2*curr + 2);
    }
    private:
    
    int m_cap;
    int m_size;
    T * m_root;
    Type m_type;
};
template<typename T>
bool Heap<T>::insert(const T& value)
{
    if(m_size == m_cap)
        return false;
    m_root[m_size++] = value;
    correct_up(m_size-1);
    return true;
}

template<typename T>
void Heap<T>::correct_up(int ind)
{
    int p_idnex = get_p(ind);
    while(p_idnex != -1)
    {
        if(((m_type == Max) && (m_root[ind] > m_root[p_idnex]))  || ((m_type == Min) && (m_root[ind] < m_root[p_idnex]) ))
        {
            T tmp = m_root[ind];
            m_root[ind] = m_root[p_idnex];
            m_root[p_idnex] = tmp;
            p_idnex = get_p(p_idnex);
        }    
        else
        {
            break;
        } 
    }
}
template<typename T>
void Heap<T>::correct_down(int ind)
{
    int left = get_l(ind);
    int right = get_r(ind);
    int index_to_s = ind;

    if((m_type == Max) && (left != -1) && (m_root[index_to_s] > m_root[left]))
        index_to_s = left;
    
    if((m_type == Max) && (right != -1) && (m_root[index_to_s] > m_root[right]))
        index_to_s = right;
    
    if((m_type == Min) && (left != -1) && (m_root[index_to_s] < m_root[left]))
        index_to_s = left;
    
    if((m_type == Min) && (right != -1) && (m_root[index_to_s] < m_root[right]))
        index_to_s = right;
    
    if(index_to_s == ind)
        return;

    T tmp = m_root[ind];
    m_root[ind] = m_root[index_to_s];
    m_root[index_to_s] = tmp;

    correct_down(index_to_s);
}
template<typename T>
T Heap<T>::remove()
{
    assert(m_size != 0);
    T tmp = m_root[0];
    m_root[0] = m_root[m_size-1];
    correct_down(0);
    return tmp;
}