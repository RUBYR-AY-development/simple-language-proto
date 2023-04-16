#pragma once
#include <iostream>
#include <vector>
#include "tree_main.h"

struct TREE_TOK
{
    std::string type;
    struct
    {
        std::string raw_value;
        // additional metadata
        std::string value_type;
    } init;
};

// i copied from my other repo
struct node
{
    TREE_TOK data;
    std::vector<node*> children;

    void add_child(TREE_TOK data)
    {
        node* child = new node(data);
        this->children.push_back(child);
    }

    node(TREE_TOK data) { this->data = data; }
    ~node()
    {
        for (node* x : children)
            delete x;
    }

    /*
    bool search(TREE_TOK request) // searches itself and children for it
    {
        if (this->data == request)
            return true;
        else
            for (node* x : children)
                return x->search(request);
    }
    */
};

namespace tree_make {
    node* create(int& line, std::vector<TOKEN>& TOKENS);
}