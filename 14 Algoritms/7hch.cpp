#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>

struct Node {
    std::string name;
    int heuristic;
    std::map<Node*, int> neighbors;
};

std::vector<Node*> hillClimbingWithHistory(Node* start, Node* goal) {
    std::vector<Node*> path;
    Node* current_node = start;
    
    std::set<Node*> visited;

    while (current_node != goal) {
        path.push_back(current_node);
        visited.insert(current_node);

        Node* next_node = nullptr;

        for (auto const& pair : current_node->neighbors) {
            Node* neighbor = pair.first;
            
            if (visited.find(neighbor) == visited.end()) {
                if (next_node == nullptr) {
                    next_node = neighbor;
                } else if (neighbor->heuristic < next_node->heuristic) {
                    next_node = neighbor;
                } else if (neighbor->heuristic == next_node->heuristic) {
                    if (neighbor->name < next_node->name) {
                        next_node = neighbor;
                    }
                }
            }
        }

        if (next_node == nullptr) {
            return {};
        }
        
        current_node = next_node;
    }
    
    path.push_back(goal);
    return path;
}

void printPath(const std::string& algorithm_name, const std::vector<Node*>& path) {
    std::cout << algorithm_name << " Path: ";
    if (path.empty()) {
        std::cout << "No path found (stuck or no unvisited neighbors)." << std::endl;
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
    Node s_node = {"S", 8};
    Node a_node = {"A", 7};
    Node b_node = {"B", 6};
    Node c_node = {"C", 7};
    Node d_node = {"D", 5};
    Node e_node = {"E", 9};
    Node g_node = {"G", 0};

    s_node.neighbors = { {&a_node, 3}, {&b_node, 5} };
    a_node.neighbors = { {&d_node, 3}, {&b_node, 4} };
    d_node.neighbors = { {&g_node, 5} };
    b_node.neighbors = { {&a_node, 4}, {&c_node, 5} };
    c_node.neighbors = { {&e_node, 6} };

    std::cout << "Running Hill Climbing with History from S to G..." << std::endl;
    std::vector<Node*> path = hillClimbingWithHistory(&s_node, &g_node);
    printPath("Hill Climbing w/ History", path);

    return 0;
}
