#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

#include <FlexLexer.h>

namespace graph
{
    enum tokens
    {
        comma       = -3,
        edge        = -1
    };

    bool comp (const std::pair <int, int> &a, const std::pair <int, int> &b)
    {
        int a1 = std::max (a.first, a.second);
        int b1 = std::max (b.first, b.second);

        return a1 < b1;
    }

    struct data_
    {
        int prev = 0;
        int next = 0;
        int start = 0;
    };

    template <typename T = bool, typename U = bool>
    class graph_
    {
        std::vector <data_> data;

        size_t nodes_count = 0;
        size_t edges_count = 0;

        std::vector <U> nodes_info;
        std::vector <T> edges_info;

        std::vector <char> nodes_colors; //may be i should use nodes_info to store colors
                                         // but i create special vector for this if user want
                                         // to store colors and other information of nodes
                                         // at the same time

        int colorized = 0;

        public:

        template <typename It, typename = std::void_t <decltype (*std::declval <It&>()), 
                                                       decltype (++std::declval <It&>()),
                                                       decltype (std::declval <It&>()->first),
                                                       decltype (std::declval <It&>()->second)>>
        int fill (It begin, It end)
        {
            auto res_find = std::max_element (begin, end, comp);
            
            if (res_find == end)
            {
                return 0;
            }

            std::pair <int, int> res = *res_find;

            int max_node = std::max (res.first, res.second);
            
            data.resize (max_node);

            for (auto i = begin; i != end; ++i)
            {
                if (data[i->first - 1].prev == 0)
                {
                    data.push_back ({i->first - 1, i->first - 1, i->first});

                    data[i->first - 1].prev = data[i->first - 1].next = data.size() - 1;
                }

                else
                {
                    data.push_back ({data[i->first - 1].prev, i->first - 1, i->first});
                    
                    data[i->first - 1].prev = data[data[i->first - 1].prev].next = data.size() - 1;
                }

                if (data[i->second - 1].prev == 0)
                {
                    data.push_back ({i->second - 1, i->second - 1, i->second});
                    data[i->second - 1].prev = data[i->second - 1].next = data.size() - 1;
                }

                else
                {
                    data.push_back ({data[i->second - 1].prev, i->second - 1, i->second});
                
                    data[i->second - 1].prev = data[data[i->second - 1].prev].next = data.size() - 1;
                }
            }

            nodes_count = max_node;
            edges_count = std::distance (begin, end);

            nodes_info.clear();
            edges_info.clear();

            nodes_colors.clear();

            colorized = 0;

            return 1;
        }

        graph_ () = default;

        graph_ (std::initializer_list <std::pair <int, int>> l)
        {
            std::cout << "jopa\n";
            fill (l.begin(), l.end());
        }

        template <typename It, typename = std::void_t <decltype (*std::declval <It&>()), 
                                                       decltype (++std::declval <It&>())>>
        void fill_edges_info (It begin, It end)
        {
            int i = 0;

            for (; begin != end and i < edges_count; ++i, ++begin)
            {
                edges_info.push_back (*begin);
                edges_info.push_back (*begin);
            }

            for (; i < edges_count; ++i)
            {
                edges_info.push_back (0);
                edges_info.push_back (0);
            }
        }

        template <typename It, typename = std::void_t <decltype (*std::declval <It&>()), 
                                                       decltype (++std::declval <It&>())>>
        void fill_nodes_info (It begin, It end)
        {
            int i = 0;

            for (; begin != end and i < nodes_count; ++i, ++begin)
            {
                nodes_info.push_back (*begin);
                nodes_info.push_back (*begin);
            }

            for (; i < nodes_count; ++i)
            {
                nodes_info.push_back (0);
                nodes_info.push_back (0);
            }
        }

        int get_connected_edge (int edge) const
        {
            if (nodes_count % 2 ^ edge % 2)
                return edge - 1;

            return edge + 1;
        }

        int input ();

        std::ostream& print (std::ostream &out) const;

        std::ostream& print_colors (std::ostream& out) const;

        int colorize (); //Depth-first search

        int recolorize (); //Breadth-first search
    };

    template <typename T, typename U>
    std::ostream& operator << (std::ostream &out, const graph_ <T, U> &G)
    {
        G.print (out);

        return out;
    }
}
