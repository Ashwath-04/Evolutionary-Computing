#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Node {
    std::string name;
    std::vector<Node*> neighbors;
};

void DepthFirstSearch(Node* current_node, Node* goal, std::vector<Node*>& current_path, std::vector<std::vector<Node*>>& all_paths) {
    current_path.push_back(current_node);

    if (current_node == goal) {
        all_paths.push_back(current_path);
        current_path.pop_back();
        return;
    }

    for (Node* neighbor : current_node->neighbors) {
        bool is_in_path = false;
        for (Node* node_in_path : current_path) {
            if (node_in_path == neighbor) {
                is_in_path = true;
                break;
            }
        }

        if (!is_in_path) {
            DepthFirstSearch(neighbor, goal, current_path, all_paths);
        }
    }

    current_path.pop_back();
}

void printAllPaths(const std::vector<std::vector<Node*>>& all_paths) {
    if (all_paths.empty()) {
        std::cout << "No paths found." << std::endl;
        return;
    }
    std::cout << "Found " << all_paths.size() << " possible paths:" << std::endl;
    int path_num = 1;
    for (const auto& path : all_paths) {
        std::cout << "Path " << path_num++ << ": ";
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i]->name;
            if (i < path.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    Node s_node = {"S"};
    Node a_node = {"A"};
    Node b_node = {"B"};
    Node c_node = {"C"};
    Node d_node = {"D"};
    Node e_node = {"E"};
    Node g_node = {"G"};

    s_node.neighbors = {&a_node, &b_node};
    a_node.neighbors = {&d_node, &b_node};
    d_node.neighbors = {&g_node};
    b_node.neighbors = {&a_node, &c_node};
    c_node.neighbors = {&e_node};

    std::cout << "Running DFS to find all paths from S to G..." << std::endl;
    std::vector<std::vector<Node*>> all_paths;
    std::vector<Node*> current_path;
    DepthFirstSearch(&s_node, &g_node, current_path, all_paths);
    printAllPaths(all_paths);

    return 0;
}
