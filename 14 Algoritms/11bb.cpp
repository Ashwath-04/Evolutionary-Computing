#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <numeric>
#include <limits>

struct Node {
    std::string name;
    std::vector<std::pair<Node*, int>> neighbors;
};

void branchAndBoundRecursive(
    Node* current_node,
    Node* goal,
    std::vector<Node*>& current_path,
    int current_cost,
    std::vector<Node*>& best_path,
    int& upper_bound_cost
) {
    if (current_cost >= upper_bound_cost) {
        return;
    }

    current_path.push_back(current_node);

    if (current_node == goal) {
        upper_bound_cost = current_cost;
        best_path = current_path;
        current_path.pop_back();
        return;
    }

    for (auto const& pair : current_node->neighbors) {
        Node* neighbor = pair.first;
        int edge_cost = pair.second;
        
        bool is_in_path = false;
        for (Node* node_in_path : current_path) {
            if (node_in_path == neighbor) {
                is_in_path = true;
                break;
            }
        }

        if (!is_in_path) {
            branchAndBoundRecursive(neighbor, goal, current_path, current_cost + edge_cost, best_path, upper_bound_cost);
        }
    }

    current_path.pop_back();
}

int getEdgeCost(Node* from, Node* to) {
    for (const auto& pair : from->neighbors) {
        if (pair.first == to) {
            return pair.second;
        }
    }
    return 0;
}

void printOptimalPath(const std::vector<Node*>& path) {
    if (path.empty()) {
        std::cout << "No path found." << std::endl;
        return;
    }
    std::cout << "Optimal solution found:" << std::endl;
    
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

    std::cout << "Running Branch and Bound from S to G..." << std::endl;
    
    std::vector<Node*> best_path;
    std::vector<Node*> current_path;
    int upper_bound = 17;

    branchAndBoundRecursive(&s_node, &g_node, current_path, 0, best_path, upper_bound);
    printOptimalPath(best_path);

    return 0;
}
