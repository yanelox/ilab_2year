#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <utility>

namespace tree
{
    struct node_
    {
        node_ *left = nullptr, *right = nullptr, *parent = nullptr;

        int number;

        size_t lsize = 0, rsize = 0;

        size_t lheight = 0, rheight = 0;

        bool operator == (const node_ &rhs)
        {
            if (this == &rhs)
                return true;

            bool res = true;

            if (lsize != rhs.lsize or rsize != rhs.rsize or
                lheight != rhs.lheight or rheight != rhs.rheight)
                return false;

            if (left == nullptr and rhs.left != nullptr or 
                left != nullptr and rhs.left == nullptr)
                return false;

            if (left != nullptr and rhs.left != nullptr)
                res *= ((*left) == (*rhs.left));

            if (right == nullptr and rhs.right != nullptr or
                right != nullptr and rhs.right == nullptr)
                return false;

            if (right != nullptr and rhs.right != nullptr)
                res *= ((*right) == (*rhs.right));

            return res;
        }

        node_ *balancing ();

        node_ *little_left_r ();
        node_ *big_left_r ();
        node_ *little_right_r ();
        node_ *big_right_r ();

    };

    class Tree_
    {
        node_ *top = nullptr;

        size_t size = 0;

        void help_print (std::ofstream &s, node_ *top) const;

        public:

        Tree_ () = default;

        Tree_ (const Tree_ &rhs)
        {
            top = new node_;
            size = rhs.size;

            node_ *cur = top;
            node_ *cur_rhs = rhs.top;

            while (true)
            {
                if (cur_rhs->left != nullptr and cur->left == nullptr)
                {
                    cur->left = new node_;

                    cur->left->parent = cur;

                    cur = cur->left;
                    cur_rhs = cur_rhs->left;
                }

                else if (cur_rhs->right != nullptr and cur->right == nullptr)
                {
                    cur->right = new node_;

                    cur->right->parent = cur;

                    cur = cur->right;
                    cur_rhs = cur_rhs->right;
                }

                else
                {
                    cur->lheight = cur_rhs->lheight;
                    cur->rheight = cur_rhs->rheight;
                    cur->lsize = cur_rhs->lsize;
                    cur->rsize = cur_rhs->rsize;
                    cur->number = cur_rhs->number;
                    
                    if (cur_rhs->parent != nullptr and cur->parent != nullptr)
                    {
                        cur = cur->parent;
                        cur_rhs = cur_rhs->parent;
                    }

                    else
                        break;
                }
            }
        }

        Tree_ (Tree_ &&rhs): top{rhs.top}, size{rhs.size}
        {
            rhs.top = nullptr;
        }

        Tree_ & operator = (const Tree_ &rhs)
        {
            if (this == &rhs)
                return *this;
            
            Tree_ tmp {rhs};

            *this = std::move (tmp);

            return *this;
        }

        Tree_ & operator = (Tree_ &&rhs)
        {
            if (this == &rhs)
                return *this;

            top = rhs.top;
            size = rhs.size;

            rhs.top = nullptr;

            return *this;
        }

        bool operator == (const Tree_ &rhs) const
        {
            if (this == &rhs)
                return true;

            if (top == nullptr and rhs.top == nullptr)
                return true;

            if (top == nullptr or rhs.top == nullptr)
                return false;

            return ((*top) == (*rhs.top));
        }

        ~Tree_ ()
        {
            if (top != nullptr)
            {
                node_ *cur = top;
                node_ *for_del = nullptr;

                while(true)
                {
                    if (cur->left != nullptr)
                        cur = cur->left;

                    else if (cur->right != nullptr)
                        cur = cur->right;

                    else if (cur->parent != nullptr)
                    {
                        for_del = cur;

                        cur = cur->parent;

                        if (cur->left == for_del)
                            cur->left = nullptr;

                        else if (cur->right == for_del)
                            cur->right = nullptr;

                        delete for_del;
                    }

                    else
                    {
                        delete cur;
                        break;
                    }
                }
            }
        }

        int push (int n);

        void fprint (std::string filename) const;

        int k_min (int k) const;

        size_t m_less (int m) const;

        size_t get_size () const;
    };
}