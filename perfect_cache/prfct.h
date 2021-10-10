#include <list>
#include <unordered_map>

template <typename KeyT, typename T>
class PRFCT_
{
    public:
    size_t size_;

    std::list <std::pair<KeyT, T>> requests_;

    std::unordered_map <KeyT, T> cache_;
};
