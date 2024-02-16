#ifndef KOPIEC_HPP
#define KOPIEC_HPP

#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <algorithm>


using namespace std;

struct Node
{
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    int key;
    int degree;
    bool marked;


    Node(int val) : parent(nullptr), child(nullptr), left(nullptr), right(nullptr), key(val), degree(0), marked(false) {}
};
std::vector<Node*> nodeArray;
Node* minimum = nullptr;
int number = 0;

void link(Node* smaller, Node* larger)
{
    (smaller->left)->right = smaller->right;
    (smaller->right)->left = smaller->left;

    smaller->parent = larger;
    smaller->marked = false;

    if (larger->child == nullptr)
    {
        larger->child = smaller;
        smaller->right = smaller;
        smaller->left = smaller;
    }
    else
    {
        Node* child = larger->child;
        (child->left)->right = smaller;
        smaller->right = child;
        smaller->left = child->left;
        child->left = smaller;
    }

    larger->degree++;
}

void consolidate()
{
    int maxDegree = static_cast<int>(log2(number)) + 1;
    vector<Node*> degreeArray(maxDegree, nullptr);

    Node* current = minimum;
    vector<Node*> roots;

    do
    {
        roots.push_back(current);
        current = current->right;
    } while (current != minimum);

    for (Node* root : roots)
    {
        int degree = root->degree;

        while (degreeArray[degree] != nullptr)
        {
            Node* other = degreeArray[degree];

            if (root->key > other->key)
                swap(root, other);

            link(other, root);
            degreeArray[degree] = nullptr;
            degree++;
        }

        degreeArray[degree] = root;
    }

    minimum = nullptr;
    for (Node* root : degreeArray)
    {
        if (root != nullptr)
        {
            if (minimum == nullptr || root->key < minimum->key)
            {
                minimum = root;
            }
        }
    }
}

void push(int val)
{
    Node* new_node = new Node(val);

    if (minimum != nullptr)
    {
        (minimum->left)->right = new_node;
        new_node->right = minimum;
        new_node->left = minimum->left;
        minimum->left = new_node;
        if (new_node->key < minimum->key)
        {
            minimum = new_node;
        }
    }
    else
    {
        minimum = new_node;
        new_node->right = new_node;
        new_node->left = new_node;
    }

    number++;
    nodeArray.push_back(new_node);
}



int pop_min()
{
    if (minimum == nullptr)
        throw std::out_of_range("Heap is empty.");


    Node* minNode = minimum;
    int minValue = minNode->key;

    if (minNode->child != nullptr)
    {
        Node* child = minNode->child;
        do
        {
            Node* nextChild = child->right;
            (minimum->left)->right = child;
            child->right = minimum;
            child->left = minimum->left;
            minimum->left = child;
            child->parent = nullptr;
            child = nextChild;
        } while (child != minNode->child);
    }

    (minNode->left)->right = minNode->right;
    (minNode->right)->left = minNode->left;

    if (minNode == minNode->right)
    {
        minimum = nullptr;
    }
    else
    {
        minimum = minNode->right;
        consolidate();
    }
    auto it = find(nodeArray.begin(), nodeArray.end(), minNode);
    if (it != nodeArray.end())
    {
        nodeArray.erase(it);
    }

    delete minNode;
    number--;

    return minValue;
}

int top()
{
    if (minimum != nullptr)
    {
        return minimum->key;
    }
    else
    {
        throw std::runtime_error("Heap is empty.");

    }
}

void cut(Node* child, Node* parent)
{
    if (child->right == child)
    {
        parent->child = nullptr;
    }
    else
    {
        (child->right)->left = child->left;
        (child->left)->right = child->right;

        if (parent->child == child)
        {
            parent->child = child->right;
        }
    }

    parent->degree--;

    child->left = minimum;
    child->right = minimum->right;
    (minimum->right)->left = child;
    minimum->right = child;

    child->parent = nullptr;
    child->marked = false;
}

void cascading_cut(Node* target)
{
    Node* parent = target->parent;

    if (parent != nullptr)
    {
        if (!target->marked)
        {
            target->marked = true;
        }
        else
        {
            cut(target, parent);
            cascading_cut(parent);
        }
    }
}



void decrease_key(Node* target, int new_key)
{
    if (new_key > target->key)
    {
        throw std::runtime_error( "New key is greater than the current key.");

    }

    target->key = new_key;
    Node* parent = target->parent;

    if (parent != nullptr && target->key < parent->key)
    {
        cut(target, parent);
        cascading_cut(parent);
    }

    if (target->key < minimum->key)
    {
        minimum = target;
    }
}
int size()
{
    return number;
}
Node* find(int key, Node* start)
{
    if (start == nullptr)
    {
        return nullptr;
    }

    Node* current = start;
    do
    {
        if (current->key == key)
        {
            return current;
        }

        Node* childResult = find(key, current->child);
        if (childResult != nullptr)
        {
            return childResult;
        }

        current = current->right;
    } while (current != start);

    return nullptr;
}

void del(int key)
{
    Node* target = find(key, minimum);

    if (target == nullptr)
    {
        throw std::out_of_range( "Key not found." );

    }
    decrease_key(target, -std::numeric_limits<int>::max());
    pop_min();
}

void visualisation() {
    int size = nodeArray.size();
    for(int i = 0; i<size; i++){
        Node* current = nodeArray[i];
        std::cout << "Node " << current->key << " - Left: " << (current->left)->key << ", Right: "
                  << (current->right)->key << ", Parent: "
                  << (current->parent ? (current->parent)->key : -1) << ", Child: "
                  << (current->child ? (current->child)->key : -1) << std::endl;

    }

}




#endif

