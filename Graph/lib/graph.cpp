#include "graph.h"
#include "driver.h"

namespace graph
{
    //graph

    template <typename T, typename U>
    int graph_ <T, U>::input ()
    {
        yy::Driver driver;

        driver.parse();

        fill (driver.data_.begin(), driver.data_.end());
        fill_edges_info (driver.edges_info_.begin(), driver.edges_info_.end());

        return 1;
    }

    template <typename T, typename U>
    std::ostream& graph_ <T, U>::print (std::ostream& out) const
    {
        if (data.empty())
        {
            out << "Empty graph\n";

            return out;
        }

        for (int i = 0; i < data.size(); ++i)
            out << i << "\t";

        out << std::endl;

        for (auto&& i:data)
            out << i.start << "\t";

        out << std::endl;

        for (auto&& i:data)
            out << i.next << "\t";

        out << std::endl;

        for (auto&& i:data)
            out << i.prev << "\t";

        out << std::endl;

        if (!nodes_info.empty())
        {
            for (auto&& i:nodes_info)
                out << i << "\t";
        }

        else if (!edges_info.empty())
        {
            for (int i = 0; i < nodes_count; ++i)
                out << "\t";

            for (auto&& i:edges_info)
                out << i << "\t";

            out << std::endl;
        }

        return out;
    }

    template <typename T, typename U>
    std::ostream& graph_ <T, U>::print_colors (std::ostream& out) const
    {
        if (colorized != 0)
        {
            for (int i = 0; i < nodes_count; ++i)
            {
                out << i + 1 << " " << nodes_colors[i];

                if (i + 1 != nodes_count)

                out << " ";
            }

            out << std::endl;
        }

        else
            out << "Not colorized\n";

        return out;
    }

    template <typename T, typename U>
    int graph_ <T, U>::colorize ()
    {
        nodes_colors.resize(nodes_count);

        std::vector <int> prev_nodes(nodes_count);
        
        int prev_node = 0;
        char prev_color = 'b';

        int next_node = 0;
        int next_edge = 0;

        int cur_node = 0;

        int start_node = 0;

        for (; start_node < nodes_count; ++start_node)
        {
            prev_node = start_node;

            if (nodes_colors[prev_node] != '\0')
                continue;

            prev_color = 'b';

            cur_node = data[get_connected_edge (data[prev_node].next)].start - 1;
        
            prev_nodes[cur_node] = prev_node;

            nodes_colors[0] = 'b';
        
            while (true)
            {
                nodes_colors[cur_node] = prev_color ^ bitmask;  

                next_edge = data[cur_node].next;
                next_node = data[get_connected_edge (next_edge)].start - 1;

                while (next_edge != cur_node and nodes_colors[next_node] != '\0')
                {
                    if (nodes_colors[next_node] != prev_color)
                    {
                        nodes_colors.clear();

                        return 0;
                    }

                    next_edge = data[next_edge].next;
                    next_node = data[get_connected_edge (next_edge)].start - 1;
                }

                if (next_edge == cur_node)
                {
                    if (cur_node == start_node)
                        break;

                    cur_node = prev_nodes[cur_node];
                }

                else
                {
                    prev_nodes[next_node] = cur_node;
                    cur_node = next_node;
                }

                prev_color ^= bitmask;
            }
        }

        colorized = 1;
        return 1;
    }

    template <typename T, typename U>
    int graph_ <T, U>::recolorize ()
    {
        if (colorized == 0)
            return 0;

        std::vector <int> queue[2];
        std::vector <bool> recolorized(nodes_count);
        recolorized[0] = true;

        queue[0].push_back(0);

        int i = 0;

        while (true)
        {
            i = (queue[0].empty()) ? 1 : 0;

            for (auto&& j:queue[i])
                nodes_colors[j] ^= bitmask;

            for (auto&& j:queue[i])
            {
                int cur_edge = data[j].next;
                int cur_node = data[get_connected_edge (cur_edge)].start - 1;

                while (cur_edge != j)
                {
                    if (!recolorized[cur_node])
                    {
                        queue[i ^ 1].push_back (cur_node);
                        recolorized[cur_node] = true;
                    }

                    cur_edge = data[cur_edge].next;
                    cur_node = data[get_connected_edge (cur_edge)].start - 1;
                }
            }

            if (queue[i ^ 1].empty())
            {
                return 1;
            }

            queue[i].clear();
        }
    }
}
