#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <queue>
#include <map>

struct Node {
    std::string name;
    std::vector<Node*> neighbors;
};

std::vector<Node*> bfsWithHistory(Node* start, Node* goal) {
    std::queue<Node*> frontier;
    frontier.push(start);

    std::set<Node*> visited;
    visited.insert(start);

    std::map<Node*, Node*> came_from;
    came_from[start] = nullptr;

    while (!frontier.empty()) {
        Node* current = frontier.front();
        frontier.pop();

        if (current == goal) {
            break;
        }

        for (Node* neighbor : current->neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                came_from[neighbor] = current;
                frontier.push(neighbor);
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

    std::cout << "Running BFS with history from S to G..." << std::endl;
    std::vector<Node*> path = bfsWithHistory(&s_node, &g_node);
    printPath("BFS", path);

    return 0;
}
