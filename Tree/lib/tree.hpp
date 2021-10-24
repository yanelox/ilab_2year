#include "tree.h"
#include <iostream>
#include <fstream>
#include <string>

namespace tree
{
    int Tree_::push (int n)
    {
        node_ *cur;

        if (top == nullptr)
        {
            top = new node_;
            
            top->number = n;

            return 0;
        }

        cur = top;

        while (true)
        {
            if (n < cur->number and cur->left != nullptr)
            {
                ++cur->lsize;

                cur = cur->left;
            }

            else if (n > cur->number and cur->right != nullptr)
            {
                ++cur->rsize;

                cur = cur->right;
            }

            else
                break;
        }

        if (n < cur->number)
        {
            ++cur->lsize;

            cur->left = new node_;

            cur->left->number = n;
            cur->left->parent = cur;
        }

        else if (n > cur->number)
        {
            ++cur->rsize;

            cur->right = new node_;

            cur->right->number = n;
            cur->right->parent = cur;
        }

        return 0;
    }

    void Tree_::help_print (std::fstream &s, node_ *top) const
    {
        if (top->left != nullptr)
        {
            s << top->number << " -> " << top->left->number << ";";
            help_print (s, top->left);
        }

        if (top->right != nullptr)
        {
            s << top->number << " -> " << top->right->number << ";";
            help_print (s, top->right);
        }
    }

    void Tree_::fprint (std::string filename) const
    {
        std::fstream s (filename, s.binary | s.trunc | s.in | s.out);

        s << "digraph graphname {" << std::endl;

        help_print (s, top);

        s << "}";
    }
}