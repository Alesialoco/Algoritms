#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

struct Node{
    int value;
    Node* left;
    Node* right;
    int priority;
    int subtree;

    Node(int val): value(val), left(nullptr), right(nullptr), subtree(1){
        static std::random_device rd;  
        static std::mt19937 gen(rd()); 
        static std::uniform_int_distribution<int> distrib(1, 1000000); 
        priority = distrib(gen);
    }
};

class CartesianTree{
    Node* root;
public:
    CartesianTree() : root(nullptr) {
    }

    ~CartesianTree() {
        clear(root);
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    void count_subtrees(Node* node){
        if (node) {
            node->subtree = 1;
            if (node->left) {
                node->subtree += node->left->subtree;
            }
            if (node->right) {
                node->subtree += node->right->subtree;
            }
        }
    }

    std::pair<Node*, Node*> split(Node* node, int value){
        if (!node)
            return {nullptr, nullptr};
        if (node->value < value){
            auto [left_sub, right_sub] = split(node->right, value);
            node->right = left_sub;
            count_subtrees(node);
            return {node, right_sub};
        }
        else{
            auto [left_sub, right_sub] = split(node->left, value);
            node->left = right_sub;
            count_subtrees(node);
            return {left_sub, node};
        }
    }

    Node* merge(Node* left, Node* right){
        if (!left) 
            return right;
        if (!right) 
            return left;
        if (left->priority > right-> priority){
            left->right = merge(left->right, right);
            count_subtrees(left);
            return left;
        }
        else{
            right->left = merge(left, right->left);
            count_subtrees(right);
            return right;
        }
    }

    void insert(int value){
        Node* new_one = new Node(value);
        auto [left_sub, right_sub] = split(root, value);
        root = merge(merge(left_sub, new_one), right_sub);
    }

    void remove(int value){
        auto [less, right] = split(root, value);
        auto [equal, greater] = split(right, value + 1);
        if (equal){
            Node* del_one = equal;
            equal = merge(equal->left, equal->right);
            delete del_one;
        }
        root = merge(merge(less, equal), greater);
    }

    int size(){
        if (root)
            return root->subtree;
        else 
            return 0;
    }

};



int main() {
    CartesianTree tree;
    std::vector<int> test_data = {5, 3, 7, 5, 5, 2, 5, 8};

    std::cout << "Вставляем элементы:" << std::endl;
    for (int x : test_data) {
        std::cout << x;
        tree.insert(x);
        std::cout << ", размер: " << tree.size() << std::endl;
    }

    
    std::cout << "Проверка поиска:" << std::endl;
    std::vector<int> search_values = {5, 3, 9, 2};
    for (int val : search_values) {
        int count = 0;
        CartesianTree temp;
        for (int x : test_data) {
            if (x == val) {
                temp.insert(x);
                count++;
            }
        }
        std::cout << "Значение " << val << " - ожидается: " << count 
                  << ", в дереве: " << temp.size() << std::endl;
    }

    std::cout << "Тест удаления:" << std::endl;
    std::vector<std::pair<int, int>> to_remove = {{5, 2}, {3, 1}, {10, 1}};
    for (auto [val, times] : to_remove) {
        int initial_size = tree.size();
        for (int i = 0; i < times; ++i) {
            tree.remove(val);
        }
        std::cout << "Удалено " << times << " вхождений " << val
                  << ". Размер был: " << initial_size
                  << ", стал: " << tree.size() << std::endl;
    }

    std::vector<int> expected_remaining = {5, 5, 7, 2, 8};
    std::cout << "Ожидается элементов: " << expected_remaining.size()
              << ", в дереве: " << tree.size() << std::endl;

    return 0;
}