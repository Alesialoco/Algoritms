#include <iostream>
#include <algorithm>

struct Node {
    int value;
    int height;
    int l_count;
    Node* left;
    Node* right;

    Node(int val) : value(val), height(1), l_count(0), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    Node* root;

    int get_height(Node* node){
        if (node)
            return node->height;
        else 
            return 0;
    }

    int get_delta_h(Node* node){
        if (node)
            return get_height(node->right) - get_height(node->left);
        else
            return 0;
    }

    void update(Node* node){
        if (node){
            node->height = 1 + std::max(get_height(node->left), get_height(node->right));
            node->l_count = count_nodes(node->left);
        }
        else
            return;
    }

    int count_nodes(Node* node){
        if (node)
            return 1 + count_nodes(node->left) + count_nodes(node->right);
        else
            return 0;
    }

    Node* turn_left(Node* node){
        Node* temp = node->right;
        node->right = temp->left;
        temp->left = node;
        update(node);
        update(temp);
        return temp;
    }

    Node* turn_right(Node* node){
        Node* temp = node->left;
        node->left = temp->right;
        temp->right = node;
        update(node);
        update(temp);
        return temp;
    }

    Node* balance(Node* node){
        update(node);
        int delta_h = get_delta_h(node);
        if (delta_h < -1) {
            if (get_delta_h(node->left) > 0)
                node->left = turn_left(node->left);
            return turn_right(node);
        }
        if (delta_h > 1) {
            if (get_delta_h(node->right) < 0)
                node->right = turn_right(node->right);
            return turn_left(node);
        }
        return node;
    }

    Node* insert(Node* node, int value){
        if (!node)
            return new Node(value);
        if (value < node->value)
            node->left = insert(node->left, value);
        else
            node->right = insert(node->right, value);
        return balance(node);
    }

    Node* find_min(Node* node){
        if (node->left)
            return find_min(node->left);
        else
            return node;
    }


    Node* remove(Node* node, int value) {
        if (!node) 
            return nullptr;
        if (value < node->value) {
            node->left = remove(node->left, value);
        } else if (value > node->value) {
            node->right = remove(node->right, value);
        } else {
            if (node->left && node->right) {
                Node* parent = node;
                Node* min = node->right;
                while (min->left) {
                    parent = min;
                    min = min->left;
                }
                node->value = min->value;
                if (parent == node)
                    parent->right = min->right;
                else
                    parent->left = min->right;
                delete min;
            } else {
                Node* child = node->left ? node->left : node->right;
                delete node;
                return child;
            }
        }
        return balance(node);
    }

    int find_k(Node* node, int k){
        if (!node) throw std::invalid_argument("Invalid k");

        int left_count = node->l_count;
        if (k == left_count + 1)
            return node->value;
        else if (k <= left_count)
            return find_k(node->left, k);
        else
            return find_k(node->right, k - left_count - 1);
    }

    void destroy(Node* node){
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    AVLTree() : root(nullptr){} 

    ~AVLTree(){                 
        destroy(root);
    }

    void insert(int value){     
        root = insert(root, value);
    }

    void remove(int value){
        root = remove(root, value);
    }

    int k_statistic(int k){
        return find_k(root, k);
    }
};

int main() {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);
    tree.insert(7);

    std::cout << tree.k_statistic(1) << std::endl;
    std::cout << tree.k_statistic(2) << std::endl;
    std::cout << tree.k_statistic(3) << std::endl;
    std::cout << tree.k_statistic(4) << std::endl;
    std::cout << tree.k_statistic(5) << std::endl;

    tree.remove(7);

    std::cout << tree.k_statistic(2) << std::endl;

    return 0;
}