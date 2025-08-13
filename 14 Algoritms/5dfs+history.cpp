#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

struct Node {
    std::string name;
    std::vector<Node*> neighbors;
};

bool dfsWithHistory(Node* current_node, Node* goal, std::vector<Node*>& path, std::set<Node*>& visited) {
    path.push_back(current_node);
    visited.insert(current_node);

    if (current_node == goal) {
        return true;
    }

    for (Node* neighbor : current_node->neighbors) {
        if (visited.find(neighbor) == visited.end()) {
            if (dfsWithHistory(neighbor, goal, path, visited)) {
                return true;
            }
        }
    }

    path.pop_back();
    return false;
}

void printPath(const std::string& algorithm_name, const std::vector<Node*>& path) {
    std::cout << algorithm_name << " Path: ";
    if (path.empty()) {
        std::cout << "No path found." << std::endl;
        return;
    }
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i]->name;
        if (i < path.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
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

    std::cout << "Running DFS with history from S to G..." << std::endl;
    std::vector<Node*> path;
    std::set<Node*> visited_nodes;
    
    if (dfsWithHistory(&s_node, &g_node, path, visited_nodes)) {
        printPath("DFS", path);
    } else {
        printPath("DFS", {});
    }

    return 0;
}
