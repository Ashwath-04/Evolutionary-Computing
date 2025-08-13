#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

struct Node {
    std::string name;
    std::vector<Node*> neighbors;
};

void BreadthFirstSearch(Node* start, Node* goal, std::vector<std::vector<Node*>>& all_paths) {
    std::queue<std::vector<Node*>> frontier;

    frontier.push({start});

    while (!frontier.empty()) {
        std::vector<Node*> current_path = frontier.front();
        frontier.pop();

        Node* last_node = current_path.back();

        if (last_node == goal) {
            all_paths.push_back(current_path);
            continue;
        }

        for (Node* neighbor : last_node->neighbors) {
            bool is_in_path = false;
            for (Node* node_in_path : current_path) {
                if (node_in_path == neighbor) {
                    is_in_path = true;
                    break;
                }
            }

            if (!is_in_path) {
                std::vector<Node*> new_path = current_path;
                new_path.push_back(neighbor);
                frontier.push(new_path);
            }
        }
    }
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

    std::cout << "Running BFS to find all paths from S to G..." << std::endl;
    std::vector<std::vector<Node*>> all_paths;
    BreadthFirstSearch(&s_node, &g_node, all_paths);
    printAllPaths(all_paths);

    return 0;
}
