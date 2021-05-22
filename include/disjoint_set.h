#ifndef CS_236_07_DISJOINT_SET_H
#define CS_236_07_DISJOINT_SET_H

#include <unordered_map>

/**
 * @brief Stores a collection of disjoint sets.
 *
 * @tparam T The type of the elements stored in the sets.
 */
template<class T>
class disjoint_set
{
public:
    /**
     * @brief Find the root element of the set to which the given element belongs.
     *
     * @param element The element for which to find the root.
     *
     * @return The root element of the set to which the given element belongs.
     */
    T find(T element)
    {
        if (parents_[element] == element) {
            return element;
        }

        return find(parents_[element]);
    }

    /**
     * @brief Make a new set containing a new element.
     *
     * @param element The new element to place in the new set.
     */
    void make_set(T element)
    {
        parents_[element] = element;
    }

    /**
     * @brief Merge the two sets which contain the given elements.
     *
     * @param a The element in the set to merge.
     * @param b The element in the other set to merge.
     */
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
