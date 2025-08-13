#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

struct Node {
    std::string name;
    std::map<Node*, int> neighbors;
};

bool depthLimitedSearch(Node* current, Node* goal, std::vector<Node*>& path, int limit) {
    path.push_back(current);

    if (current == goal) {
        return true;
    }

    if (limit <= 0) {
        path.pop_back();
        return false;
    }

    for (auto const& pair : current->neighbors) {
        Node* neighbor = pair.first;
        
        bool is_in_path = false;
        for(Node* node_in_path : path) {
            if (node_in_path == neighbor) {
                is_in_path = true;
                break;
            }
        }

        if (!is_in_path) {
            if (depthLimitedSearch(neighbor, goal, path, limit - 1)) {
                return true;
            }
        }
    }

    path.pop_back();
    return false;
}

std::vector<Node*> iterativeDeepeningSearch(Node* start, Node* goal) {
    for (int depth = 0; ; ++depth) {
        std::vector<Node*> path;
        if (depthLimitedSearch(start, goal, path, depth)) {
            return path;
        }
        if (depth > 10) { 
            return {};
        }
    }
}

void printOptimalPath(const std::vector<Node*>& path) {
    if (path.empty()) {
        std::cout << "No path found." << std::endl;
        return;
    }
    std::cout << "Optimal solution found:" << std::endl;
    
    std::cout << "  Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i]->name;
        if (i < path.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
    std::cout << "  Nodes Visited: " << path.size() << std::endl;
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

    std::cout << "Running IDDFS (BFS+DFS Hybrid) from S to G..." << std::endl;
    
    std::vector<Node*> path = iterativeDeepeningSearch(&s_node, &g_node);
    printOptimalPath(path);

    return 0;
}
