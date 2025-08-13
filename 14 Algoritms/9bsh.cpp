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

std::vector<Node*> beamSearchWithHistory(Node* start, Node* goal, int beam_width) {
    std::vector<std::vector<Node*>> beam;
    beam.push_back({start});

    std::set<Node*> visited;
    visited.insert(start);

    while (!beam.empty()) {
        std::vector<std::vector<Node*>> candidates;

        for (const auto& path : beam) {
            Node* last_node = path.back();

            if (last_node == goal) {
                return path;
            }

            for (auto const& pair : last_node->neighbors) {
                Node* neighbor = pair.first;
                
                if (visited.find(neighbor) == visited.end()) {
                    std::vector<Node*> new_path = path;
                    new_path.push_back(neighbor);
                    candidates.push_back(new_path);
                }
            }
        }

        if (candidates.empty()) {
            return {};
        }

        std::sort(candidates.begin(), candidates.end(), [](const std::vector<Node*>& a, const std::vector<Node*>& b) {
            return a.back()->heuristic < b.back()->heuristic;
        });

        beam.clear();
        for (int i = 0; i < std::min((int)candidates.size(), beam_width); ++i) {
            beam.push_back(candidates[i]);
            visited.insert(candidates[i].back());
        }
    }

    return {};
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

    std::cout << "Running Beam Search with History (w=2) from S to G..." << std::endl;
    std::vector<Node*> path = beamSearchWithHistory(&s_node, &g_node, 2);
    printPath("Beam Search w/ History", path);

    return 0;
}
