#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>

namespace prfct
{
template <typename Key, typename T>
class Cache_
{
    size_t size_;

    std::unordered_map <Key, T> map_;

    std::unordered_map <Key, std::list <int>> entries_;

    public:

    Cache_ () {};

    Cache_ (size_t Size): size_(Size) {};

    bool is_valid () const;

    int start_push (std::vector <std::pair<Key, T>> &requests_);

    int push (std::pair <Key, T> &page);

    int print () const;
};
}