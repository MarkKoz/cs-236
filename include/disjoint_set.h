#ifndef CS_236_07_DISJOINT_SET_H
#define CS_236_07_DISJOINT_SET_H

#include <unordered_map>

template<class T>
class disjoint_set
{
public:
    T find(T element)
    {
        if (parents_[element] == element) {
            return element;
        }

        return find(parents_[element]);
    }

    void make_set(T element)
    {
        parents_[element] = element;
    }

    void unite(T a, T b)
    {
        T parent_a = find(a);
        T parent_b = find(b);
        parents_[parent_a] = parent_b;
    }

private:
    std::unordered_map<T, T> parents_ {};
};

#endif
