#include <iostream>
#include <string>

namespace tree
{
    struct node_
    {
        node_ *left = nullptr, *right = nullptr, *parent = nullptr;

        int number;

        size_t lsize = 0, rsize = 0;

        node_ () = default;

        ~node_ () = default;
    };

    class Tree_
    {public:
        node_ *top = nullptr;

        void help_print (std::fstream &s, node_ *top) const;

        public:

        Tree_ () = default;

        Tree_ (int n)
        {
            top = new node_;

            top->number = n;
        }

        ~Tree_ ()
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

        int push (int n);

        void fprint (std::string filename) const;
    };
}