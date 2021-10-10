#include "prfct.h"

namespace prfct
{
    template <typename Key, typename T>
    bool Cache_ <Key, T>::is_valid () const
    {
        if (map_.size() <= size_)
            return 1;

        return 0;
    }

    template <typename Key, typename T>
    int Cache_ <Key, T>::start_push (std::vector <std::pair<Key, T>> &requests_)
    {
        int res = 0;

        for (int i = 0; i < requests_.size(); ++i)
        {
            if(entries_.find (requests_[i].first) == entries_.end())
                entries_.insert ({requests_[i].first, {}});

            entries_[requests_[i].first].push_back (i);
        }

        for (int i = 0; i < requests_.size(); ++i)
            res += push (requests_[i]);

        return res;
    }

    template <typename Key, typename T>
    int Cache_ <Key, T>::push (std::pair <Key, T> &page)
    {
        int res = 0;

        if (!is_valid())
            return -1;

        if (map_.find(page.first) == map_.end())
        {
            if (map_.size() < size_)
                map_.insert (page);

            else
            {
                int tmp_max = 0;
                Key tmp_key {};

                for (auto i = map_.begin(); i != map_.end(); ++i)
                {
                    if (entries_.find(i->first) == entries_.end())
                    {
                        tmp_key = i->first;
                        break;
                    }

                    if (entries_[i->first].front() > tmp_max)
                    {
                        tmp_max = entries_[i->first].front();
                        tmp_key = i->first;
                    }
                }

                map_.erase (tmp_key);
                
                map_.insert (page);
            }
        }

        else
            res = 1;

        entries_[page.first].pop_front();

        if (entries_[page.first].empty())
            entries_.erase (page.first);

        return res;
    }

    template <typename Key, typename T>
    int Cache_ <Key, T>::print () const
    {
        std::cout << "map_\n{\n";

        for (auto i = map_.begin(); i != map_.end(); ++i)
        {
            std::cout << "{" << i->first << ", " << i->second << "}\n";
        }

        std::cout << "}\n\nentries\n{\n";

        for (auto i = entries_.begin(); i != entries_.end(); ++i)
        {
            std::cout << "{" << i->first << ", {";

            for (auto j = i->second.begin(); j != i->second.end(); ++j)
            {
                std::cout << *j << " ";
            }

            std::cout << "}}\n";
        }

        std::cout << "}\n";

        return 0;
    }
}