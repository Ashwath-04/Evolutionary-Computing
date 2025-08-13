#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>

struct Node {
    std::string name;
    int heuristic;
    std::map<Node*, int> neighbors;
};

struct State {
    Node* node;
    int cost_g;
    int cost_f;

    bool operator>(const State& other) const {
        return cost_f > other.cost_f;
    }
};

std::vector<Node*> aStarSearch(Node* start, Node* goal) {
    std::priority_queue<State, std::vector<State>, std::greater<State>> frontier;
    frontier.push({start, 0, start->heuristic});

    std::map<Node*, Node*> came_from;
    came_from[start] = nullptr;

    std::map<Node*, int> cost_so_far;
    cost_so_far[start] = 0;

    while (!frontier.empty()) {
        State current_state = frontier.top();
        frontier.pop();

        Node* current_node = current_state.node;

        if (current_node == goal) {
            break;
        }

        for (auto const& pair : current_node->neighbors) {
            Node* neighbor = pair.first;
            int edge_cost = pair.second;
            int new_cost_g = cost_so_far[current_node] + edge_cost;

            if (cost_so_far.find(neighbor) == cost_so_far.end() || new_cost_g < cost_so_far[neighbor]) {
                cost_so_far[neighbor] = new_cost_g;
                int new_cost_f = new_cost_g + neighbor->heuristic;
                frontier.push({neighbor, new_cost_g, new_cost_f});
                came_from[neighbor] = current_node;
            }
        }
    }

    std::vector<Node*> path;
    if (came_from.count(goal)) {
        Node* current = goal;
        while (current != nullptr) {
            path.push_back(current);
            current = came_from[current];
        }
        std::reverse(path.begin(), path.end());
    }
    return path;
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
            int cost = 0;
            for(auto const& pair : path[i]->neighbors) {
                if(pair.first == path[i+1]) {
                    cost = pair.second;
                    break;
                }
            }
            total_cost += cost;
        }
    }
    std::cout << std::endl;
    std::cout << "  Nodes Visited: " << path.size() << std::endl;
    std::cout << "  Path Cost: " << total_cost << std::endl;
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

    std::cout << "Running A* Search from S to G..." << std::endl;
    
    std::vector<Node*> path = aStarSearch(&s_node, &g_node);
    printOptimalPath(path);

    return 0;
}
