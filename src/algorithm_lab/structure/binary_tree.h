#pragma once

#include <iostream>
#include <vector>
namespace yyds {
template <typename T>
class BinaryTree
{
private:
    struct Node
    {
        T val;
        Node* parent;
        Node* left;
        Node* right;
        Node(T val, Node* left = nullptr, Node* right = nullptr,
             Node* parent = nullptr)
            : val(val), left(left), right(right), parent(parent)
        {
        }
    };

public:
    void insert(T val)
    {
        auto new_node = new Node(val);
        auto cur = m_root;
        Node* parent = nullptr;
        while (cur)
        {
            parent = cur;
            if (val < cur->val)
                cur = cur->left;
            else
                cur = cur->right;
        }
        if (parent == nullptr)
        {
            m_root = new_node;
        }
        else if (parent->val > val)
        {
            parent->left = new_node;
        }
        else
        {
            parent->right = new_node;
        }
    }

    Node* search(T val)
    {
        auto node = m_root;
        while (node)
        {
            if (val < node->val) node = node->left;
            if (val > node->val)
                node = node->right;
            else
                return node;
        }
        return nullptr;
    }

    void remove(T val)
    {
        auto cur = search(val);
        if (cur != nullptr)
        {
            if (cur->left == nullptr && cur->right != nullptr)
                transplant(cur, cur->right);
            else if (cur->right == nullptr)
                transplant(cur, cur->left);
            else
            {
                auto successor = min(cur->right);
                if (successor != cur->right)
                {
                    transplant(successor, successor->right);
                    successor->right = cur->right;
                    successor->right->parent = successor;
                }
                transplant(cur, successor);
                successor->left = cur->left;
                successor->left->parent = successor;
            }
            delete cur;
        }
    }

    void inorder_walk(Node* cur)
    {
        if (cur != nullptr)
        {
            inorder_walk(cur->left);
            std::cout << cur->val << ' ';
            inorder_walk(cur->right);
        }
    }

    void inorder_walk()
    {
        inorder_walk(m_root);
        std::cout << "\n";
    }

    Node* max() { return max(m_root); }

    Node* min() { return min(m_root); }

protected:
    void transplant(Node* u, Node* v)
    {
        if (u->parent == nullptr)
            m_root = v;
        else if (u->parent->left == u)
            u->parent->left = v;
        else if (u->parent->right == u)
            u->parent->right = v;
        if (v != nullptr)
        {
            v->parent = u->parent;
        }
    }

private:
    Node* m_root = nullptr;

    Node* max(Node* root)
    {
        while (root && root->right)
        {
            root = root->right;
        }
        return root;
    }

    Node* min(Node* root)
    {
        while (root && root->left)
        {
            root = root->left;
        }
        return root;
    }
};
} // namespace yyds