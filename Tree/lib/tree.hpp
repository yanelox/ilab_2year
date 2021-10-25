#include "tree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

namespace tree
{
    //node

    node_ * node_::balancing ()
    {
        node_ *res = nullptr;
        node_ *tmp = nullptr;

        if (rheight == (lheight + 2) and right->lheight <= right->rheight)
        {
            res = right;

            right = right->left;    

            if (right != nullptr)
            {
                right->parent = this;
                rsize = right->lsize + right->rsize + 1;
                rheight = 1 + std::max (right->rheight, right->lheight);
            }
            else
            {
                rheight = 0;
                rsize = 0;
            }
        
            res->left = this;
            res->parent = parent;
            
            parent = res;
        
            res->lsize = lsize + rsize + 1;
            res->lheight = 1 + std::max (lheight, rheight);
        }

        else if (rheight == (lheight + 2) and right->lheight > right->rheight)
        {
            res = right->left; 

            tmp = right; 

            right = right->left->left; 

            if (right != nullptr)
            {
                right->parent = this;
                rsize = right->lsize + right->rsize + 1;
                rheight = 1 + std::max (right->rheight, right->lheight);
            }

            else
            {
                rsize = 0;
                rheight = 0;
            }

            tmp->left = res->right;

            if (tmp->left != nullptr)
            {
                tmp->left->parent = tmp;
                tmp->lsize = tmp->left->lsize + tmp->left->rsize + 1;
                tmp->lheight = 1 + std::max (tmp->left->lheight, tmp->left->rheight);
            }

            else
            {
                tmp->lsize = 0;
                tmp->lheight = 0;
            }

            res->parent = parent;

            res->left = this;
            res->right = tmp;

            parent = res;
            tmp->parent = res;
        }

        else if (lheight == (rheight + 2) and left->rheight <= left->lheight)
        {
            res = left;

            left = left->right;

            if (left != nullptr)
            {
                left->parent = this;
                lsize = left->lsize + left->rsize + 1;
                lheight = 1 + std::max (left->lheight, left->rheight);
            }

            else
            {
                lheight = 0;
                lsize = 0;
            }

            res->right = this;
            res->parent = parent;

            parent = res;

            res->rsize = lsize + rsize + 1;
            res->rheight = 1 + std::max (lheight, rheight);
        }

        else if (lheight == (rheight + 2) and left->rheight > left->lheight)
        {
            res = left->right; //c

            tmp = left; //b

            left = left->right->right;

            if (left != nullptr)
            {
                left->parent = this;
                lsize = left->lsize + left->rsize + 1;
                lheight = 1 + std::max (left->lheight, left->rheight);
            }

            else
            {
                lsize = 0;
                lheight = 0;
            }

            tmp->right = res->left;

            if (tmp->right != nullptr)
            {
                tmp->right->parent = tmp;
                tmp->rsize = tmp->right->lsize + tmp->right->rsize + 1;
                tmp->rheight = 1 + std::max (tmp->right->lheight, tmp->right->rheight);
            }

            else
            {
                tmp->rsize = 0;
                tmp->rheight = 0;
            }

            res->parent = parent;

            res->left = tmp;
            res->right = this;

            parent = res;
            tmp->parent = res;
        }
        
        return res;
    }

    //Tree

    int Tree_::push (int n)
    {
        node_ *cur = nullptr;
        node_ *res = nullptr;

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
            ++cur->lheight;

            cur->left = new node_;

            cur->left->number = n;
            cur->left->parent = cur;
        }

        else if (n > cur->number)
        {
            ++cur->rsize;
            ++cur->rheight;

            cur->right = new node_;

            cur->right->number = n;
            cur->right->parent = cur;
        }

        cur = cur->parent;
        
        while (cur != nullptr)
        {
            if (cur->left != nullptr)
                cur->lheight = 1 + std::max (cur->left->lheight, cur->left->rheight);

            else
                cur->lheight = 0;

            if (cur->right != nullptr)
                cur->rheight = 1 + std::max (cur->right->lheight, cur->right->rheight);

            else
                cur->rheight = 0;

            res = cur->balancing ();
            
            if (res != nullptr and res->parent != nullptr)
                if (res->parent->left == cur)
                    res->parent->left = res;

                else if (res->parent->right == cur)
                    res->parent->right = res;
        
            if (res != nullptr)
                cur = res->parent;

            else
                cur = cur->parent;
        }

        if (res != nullptr)
            top = res;

        return 0;
    }

    void Tree_::help_print (std::fstream &s, node_ *top) const
    {
        char label[256];
        label[0] = '\0';

        sprintf (label, "number = %d\nlsize = %zu\nrsize = %zu\nlheight = %zu\nrheight = %zu\n", top->number, top->lsize, top->rsize, top->lheight, top->rheight);

        s << top->number << " [label=\"" << label << "\"]\n";

        if (top->left != nullptr)
        {
            s << top->number << " -> " << top->left->number << ";\n";
            help_print (s, top->left);
        }

        if (top->right != nullptr)
        {
            s << top->number << " -> " << top->right->number << ";\n";
            help_print (s, top->right);
        }
    }

    void Tree_::fprint (std::string filename) const
    {
        if (top == nullptr)
            return;

        std::fstream s (filename, s.binary | s.trunc | s.in | s.out);

        s << "digraph graphname {" << std::endl;

        help_print (s, top);

        s << "}";
    }

    int Tree_::k_min (int k) const
    {
        if (top == nullptr)
            return poison;

        node_ *cur = top;
        int res = top->number;

        while (true)
        {
            if (k <= cur->lsize and cur->left != nullptr)
                cur = cur->left;

            else if (k == (cur->lsize + 1))
                return cur->number;

            else if (k > cur->lsize + 1 and cur->right != nullptr)
            {
                k -= cur->lsize + 1;
                cur = cur->right;
            }

            else
                break;
        }

        return poison;
    }

    size_t Tree_::m_less (int m) const
    {
        if (top == nullptr)
            return poison;

        size_t res = 0;
        node_ *cur = top;

        while (true)
        {
            if (m < cur->number)
                if (cur->left != nullptr)
                    cur = cur->left;
                
                else
                    break;

            else if (m == cur->number)
            {
                res += cur->lsize;
                break;
            }

            else if (m > cur->number)
                if (cur->right != nullptr)
                {
                    res += cur->lsize + 1;
                    cur = cur->right;
                }

                else
                {
                    res += 1;
                    break;
                }
        }

        return res;
    }
}