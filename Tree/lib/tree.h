#include <iostream>
#include <string>

namespace tree
{
    struct node_
    {
        node_ *left = nullptr, *right = nullptr, *parent = nullptr;

        int number;

        size_t lsize = 0, rsize = 0;

        size_t lheight = 0, rheight = 0;

        node_ () = default;

        ~node_ () = default;

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

        void help_print (std::fstream &s, node_ *top) const;

        public:

        Tree_ () = default;

        Tree_ (const Tree_ &rhs)
        {
            top = new node_;
            size = rhs.size;

            node_ *cur = top;
            node_ *cur_p = nullptr;
            node_ *cur_rhs = rhs.top;

            while (true)
            {
                cur->number = cur_rhs->number;
                cur->lsize = cur_rhs->lsize;
                cur->rsize = cur_rhs->rsize;
                cur->parent = cur_p;
                

                if (cur_rhs->left != nullptr and cur->left == nullptr)
                {
                    cur->left = new node_;

                    cur_p = cur;

                    cur = cur->left;
                    cur_rhs = cur_rhs->left;
                }

                else if (cur_rhs->right != nullptr and cur->right == nullptr)
                {
                    cur->right = new node_;

                    cur_p = cur;

                    cur = cur->right;
                    cur_rhs = cur_rhs->right;
                }

                else
                    if (cur_rhs->parent != nullptr)
                    {
                        cur = cur->parent;
                        cur_rhs = cur_rhs->parent;
                    }

                    else
                        break;
            }
        }

        Tree_ (Tree_ &&rhs): top{rhs.top}, size{rhs.size}
        {
            rhs.top = nullptr;
        }

        Tree_ & operator = (Tree_ &rhs)
        {
            if (this == &rhs)
                return *this;

            delete top;

            top = new node_;
            size = rhs.size;

            node_ *cur = top;
            node_ *cur_p = nullptr;
            node_ *cur_rhs = rhs.top;

            while (true)
            {
                cur->number = cur_rhs->number;
                cur->lsize = cur_rhs->lsize;
                cur->rsize = cur_rhs->rsize;
                cur->parent = cur_p;
                

                if (cur_rhs->left != nullptr and cur->left == nullptr)
                {
                    cur->left = new node_;

                    cur_p = cur;

                    cur = cur->left;
                    cur_rhs = cur_rhs->left;
                }

                else if (cur_rhs->right != nullptr and cur->right == nullptr)
                {
                    cur->right = new node_;

                    cur_p = cur;

                    cur = cur->right;
                    cur_rhs = cur_rhs->right;
                }

                else
                    if (cur_rhs->parent != nullptr)
                    {
                        cur = cur->parent;
                        cur_rhs = cur_rhs->parent;
                    }

                    else
                        break;
            }

            return *this;
        }

        Tree_ & operator = (Tree_ &&rhs)
        {
            if (this == &rhs)
                return *this;

            top = rhs.top;
            size = rhs.size;

            return *this;
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