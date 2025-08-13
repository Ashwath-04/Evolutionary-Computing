#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <numeric>

struct Node {
    std::string name;
    std::vector<std::pair<Node*, int>> neighbors;
};

void findAllPathsRecursive(Node* current_node, Node* goal, std::vector<Node*>& path, std::vector<std::vector<Node*>>& all_paths) {
    path.push_back(current_node);

    if (current_node == goal) {
        all_paths.push_back(path);
        path.pop_back();
        return;
    }

    for (auto const& pair : current_node->neighbors) {
        Node* neighbor = pair.first;
        bool is_in_path = false;
        for (Node* node_in_path : path) {
            if (node_in_path == neighbor) {
                is_in_path = true;
                break;
            }
        }

        if (!is_in_path) {
            findAllPathsRecursive(neighbor, goal, path, all_paths);
        }
    }

    path.pop_back();
}

int getEdgeCost(Node* from, Node* to) {
    for (const auto& pair : from->neighbors) {
        if (pair.first == to) {
            return pair.second;
        }
    }
    return 0;
}

void printAllPathsWithDetails(const std::vector<std::vector<Node*>>& all_paths) {
    if (all_paths.empty()) {
        std::cout << "No paths found." << std::endl;
        return;
    }
    std::cout << "Found " << all_paths.size() << " possible paths:" << std::endl;
    int path_num = 1;
    for (const auto& path : all_paths) {
        std::cout << "\nSolution " << path_num++ << ":" << std::endl;
        
        std::cout << "  Path: ";
        int total_cost = 0;
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i]->name;
            if (i < path.size() - 1) {
                std::cout << " -> ";
                total_cost += getEdgeCost(path[i], path[i+1]);
            }
        }
        std::cout << std::endl;
        std::cout << "  Nodes Visited: " << path.size() << std::endl;
        std::cout << "  Path Cost: " << total_cost << std::endl;
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

    s_node.neighbors = { {&a_node, 3}, {&b_node, 5} };
    a_node.neighbors = { {&d_node, 3}, {&b_node, 4} };
    d_node.neighbors = { {&g_node, 5} };
    b_node.neighbors = { {&a_node, 4}, {&c_node, 5} };
    c_node.neighbors = { {&e_node, 6} };

    std::cout << "Finding all paths from S to G..." << std::endl;
    std::vector<std::vector<Node*>> all_paths;
    std::vector<Node*> current_path;
    findAllPathsRecursive(&s_node, &g_node, current_path, all_paths);
    printAllPathsWithDetails(all_paths);

    return 0;
}
