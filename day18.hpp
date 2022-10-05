#include "day.hpp"
#include <cmath>

class Day18 : public Day {

public:
    Day18() : Day{"input/day18.txt"} {}
    ~Day18() override = default;
    
    struct Node {
        Node* left;
        Node* right;
        Node* parent;
        int number = -1;
    };

    void run() override {
        // Part 1
        auto numbers = readNumbers();
        Node* lastNumber{};
        for (const auto& number : numbers) {
            if (!lastNumber) {
                lastNumber = number;
                continue;
            }

            Node* newRoot = addNumbers(lastNumber, number);
            reduceNumber(newRoot);
            lastNumber = newRoot;
        }

        printNumber(lastNumber);
        std::cout << getMagnitude(lastNumber) << std::endl;
        deleteNumber(lastNumber);

        // Part 2
        int maxMagnitude{};
        for (int i{}; i < lines.size(); ++i) {
            for (int j{}; j < lines.size(); ++j) {
                if (i == j)
                    continue;

                Node* root = addNumbers(getNumberFromLine(i), getNumberFromLine(j));
                reduceNumber(root);
                maxMagnitude = std::max(getMagnitude(root), maxMagnitude);
                deleteNumber(root);
                root = addNumbers(getNumberFromLine(j), getNumberFromLine(i));
                reduceNumber(root);
                maxMagnitude = std::max(getMagnitude(root), maxMagnitude);
                deleteNumber(root);
            }
        }

        std::cout << maxMagnitude;
    }

    void deleteNumber(Node* node) {
        if (!node)
            return;

        deleteNumber(node->left);
        deleteNumber(node->right);
        delete node;
    }

    void printNumber(Node* root) {
        std::vector<Node*> nodes{};
        listNodes(nodes, root);
        for (const auto& node : nodes) {
            std::cout << node->number << " ";
        }
        std::cout << std::endl;
    }

    Node* addNumbers(Node* left, Node* right) {
        Node* newRoot = new Node{};
        newRoot->left = left;
        newRoot->right = right;
        return newRoot;
    }

    int getMagnitude(Node* node) {
        if (!node)
            return 0;

        if (node->number != -1)
            return node->number;

        return 3 * getMagnitude(node->left) + 2 * getMagnitude(node->right);
    }

    void reduceNumber(Node* root) {
        do {
            while (explodeNumber(root, root, 0));
        } while (splitNumber(root));
    }

    bool splitNumber(Node* root) {
        std::vector<Node*> nodes{};
        listNodes(nodes, root);
        for (const auto& node : nodes) {
            if (node->number >= 10) {
                Node* child = new Node{};
                child->number = node->number/2;
                child->parent = node;
                node->left = child;
                child = new Node{};
                child->number = std::ceil(node->number/2.0);
                child->parent = node;
                node->right = child;
                node->number = -1;
                return true;
            }
        }

        return false;
    }

    bool explodeNumber(Node* root, Node* node, int level) {
        if (!node)
            return false;

        if (level > 3 && node->number == -1) {
            std::vector<Node*> nodes{};
            listNodes(nodes, root);
            int i{};
            for (i = 0; i < nodes.size(); ++i) {
                if (nodes[i] == node->left) {
                    if (i - 1 >= 0)
                        nodes[i - 1]->number += node->left->number;

                    delete node->left;
                    node->left = nullptr;
                }

                if (nodes[i] == node->right) {
                    if (i + 1 < nodes.size())
                        nodes[i + 1]->number += node->right->number;

                    delete node->right;
                    node->right = nullptr;
                }
                
                node->number = 0;
            }
            
            return true;
        }

        return explodeNumber(root, node->left, level + 1) || explodeNumber(root, node->right, level + 1);
    }

    void listNodes(std::vector<Node*>& nodes, Node* node) {
        if (!node)
            return;

        if (node->number == -1) {
            listNodes(nodes, node->left);
            listNodes(nodes, node->right);
        } else {
            nodes.emplace_back(node);
        }
    }

    Node* getNumberFromLine(int line) {
        Node* root = new Node{};
        Node* currentNode{root};
        bool left{true};
        for (const auto& c : lines[line].substr(1, lines[line].size() - 2)) {
            if (c == '[') {
                Node* child = new Node{};
                if (left)
                    currentNode->left = child;
                else
                    currentNode->right = child;

                left = true;
                child->parent = currentNode;
                currentNode = child;
            } else if (c == ']') {
                currentNode = currentNode->parent;
            } else if (c == ',') {
                left = false;
            } else {
                Node* child = new Node{};
                child->number = std::stoi(std::string{c});
                child->parent = currentNode;
                if (left)
                    currentNode->left = child;
                else
                    currentNode->right = child;
            }
        }

        return root;
    }

    std::vector<Node*> readNumbers() {
        std::vector<Node*> numbers{};
        for (int i{}; i < lines.size(); ++i)
            numbers.emplace_back(getNumberFromLine(i));

        return numbers;
    }

};