#include "graph.h"

int yyFlexLexer::yywrap ()
{
    return 1;
}

namespace graph
{
    //graph

    template <typename T, typename U>
    int graph_ <T, U>::input ()
    {
        std::vector <int> edges_info_;
        std::vector <std::pair <int, int>> data_;

        FlexLexer* lexer = new yyFlexLexer;

        int a = 0;
        int first = 0, second = 0, info = 0;

        while ((a = lexer->yylex()) != 0) //TODO: may be delete copypaste ?
        {
            if (a <= 0) //not a node number
            {
                std::cout << "Incorrect input\n";

                return 0;
            }

            first = a;

            a = lexer->yylex();

            if (a != tokens::edge)
            {
                std::cout << "Incorrect input\n";

                return 0;
            }

            a = lexer->yylex();

            if (a <= 0) //not a node number
            {
                std::cout << "Incorrect input\n";

                return 0;
            }

            second = a;

            a = lexer->yylex();

            if (a != tokens::comma)
            {
                std::cout << "Incorrect input\n";

                return 0;
            }

            a = lexer->yylex();

            if (a <= 0) //not a edge info
            {
                std::cout << "Incorrect input\n";

                return 0;
            }

            info = a;

            data_.push_back ({first, second});
            edges_info_.push_back (info);
        }

        fill (data_.begin(), data_.end());
        fill_edges_info (edges_info_.begin(), edges_info_.end());

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
                out << i + 1 << " " << nodes_colors[i] << " ";

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

        int cur_node = data[data[0].next ^ 1].start - 1;
        prev_nodes[cur_node] = 0;

        int next_node = 0;
        int next_edge = 0;

        nodes_colors[0] = 'b';

        while (true)
        {
            nodes_colors[cur_node] = prev_color ^ 16;

            next_edge = data[cur_node].next;
            next_node = data[next_edge ^ 1].start - 1;

            while (next_edge != cur_node and nodes_colors[next_node] != '\0')
            {
                if (nodes_colors[next_node] != prev_color)
                {
                    nodes_colors.clear();

                    return 0;
                }

                next_edge = data[next_edge].next;
                next_node = data[next_edge ^ 1].start - 1;
            }

            if (next_edge == cur_node)
            {
                if (cur_node == 0)
                {
                    colorized = 1;
                    return 1;
                }

                cur_node = prev_nodes[cur_node];
            }

            else
            {
                prev_nodes[next_node] = cur_node;
                cur_node = next_node;
            }

            prev_color ^= 16;
        }
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
                nodes_colors[j] ^= 16;

            for (auto&& j:queue[i])
            {
                int cur_edge = data[j].next;
                int cur_node = data[cur_edge ^ 1].start - 1;

                while (cur_edge != j)
                {
                    if (!recolorized[cur_node])
                    {
                        queue[i ^ 1].push_back (cur_node);
                        recolorized[cur_node] = true;
                    }

                    cur_edge = data[cur_edge].next;
                    cur_node = data[cur_edge ^ 1].start - 1;
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
