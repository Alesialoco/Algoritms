#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>

struct Node{
    int value;
    char symbol = 0;
    bool letter;
    Node* left;
    Node* right;

    Node(char s, int val) : value(val), symbol(s), letter(1), right(nullptr), left(nullptr){}
    Node(int val) : value(val), symbol(), letter(0), right(nullptr), left(nullptr){}
};

struct comparator {
    bool operator()(Node* a, Node* b) {
        return a->value > b->value;
    }
};

void build_codes(Node* node, std::string code, std::unordered_map<char, std::string>& codes) {
    if (node == nullptr) 
        return;
    if (node->letter) {
        codes[node->symbol] = code;
        return;
    }
    build_codes(node->left, code + "0", codes);
    build_codes(node->right, code + "1", codes);
}

std::string haffmen(std::string line){
    std::unordered_map<char, int> usage;
    for (char i : line){
        usage[i]++;
    }
    std::priority_queue<Node*, std::vector<Node*>, comparator> heap;
    for (const auto& pair : usage){
        Node* node = new Node(pair.first, pair.second);
        heap.push(node);
    }
    while (heap.size() > 1){
        Node* one = heap.top();
        heap.pop();
        Node* two = heap.top();
        heap.pop();
        Node* middle = new Node(one->value + two->value);
        middle->left = one;
        middle->right = two;
        heap.push(middle);
    }
    std::unordered_map<char, std::string> codes;
    build_codes(heap.top(), "", codes);
    std::string result = "";
    for (char i : line){
        result += codes[i];
    }
    std::cout << "Получившиеся коды" << std::endl;
    for (const auto& pair : codes){
        std::cout << pair.first << " - " << pair.second << std::endl; 
    }
    return result;
}

int main(){
    std::string a;
    std::cout << "Введите строку, которую хотите защифровать" << std::endl;
    std::cin >> a;
    std::cout << haffmen(a);
    return 0;
}