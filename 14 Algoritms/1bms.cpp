#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

struct Node{
    std::string name;
    std::vector<Node*> neighbours;
};

void BritishMuseumSearch(Node* currentNode, Node* goal,std::vector<Node*>& path, std::vector<std::vector<Node*>>& all_paths){
    path.push_back(currentNode);
    if (currentNode == goal){
        all_paths.push_back(path);
        path.pop_back();
        return;
    }
    for (Node* neighbour : currentNode->neighbours){
        if(std::find(path.begin(), path.end(), neighbour)==path.end()){
            BritishMuseumSearch(neighbour, goal, path, all_paths);
        }
    }
    path.pop_back();
}

int main(){
    Node s_node= {"S"};
    Node a_node= {"A"};
    Node b_node= {"B"};
    Node c_node= {"C"};
    Node d_node= {"D"};
    Node e_node= {"E"};
    Node g_node= {"G"};

    s_node.neighbours={&a_node, &b_node};
    a_node.neighbours={&d_node, &b_node};
    b_node.neighbours={&a_node, &c_node};
    c_node.neighbours={&e_node};
    d_node.neighbours={&g_node};

    std::cout<<"British Museum Search from Node S to G"<<std::endl;
    std::vector<std::vector<Node*>> all_path;
    std::vector<Node*> path;
    BritishMuseumSearch(&s_node, &g_node, path, all_path);

    std::cout<<"--------------------------------------";
    if (all_path.empty()){
        std::cout<<"No path found!"<<std::endl;
    }
    else{
        std::cout<<"Path is found:"<<std::endl;
        int path_count=1;
        for (const auto& p : all_path){
            std::cout<<"Path "<<path_count++<<": ";
            for (size_t i=0; i < p.size(); i++){
                std::cout<<p[i]->name;
                if(i<p.size()-1){
                    std::cout<<"->";
                }
            }
            std::cout<<std::endl;
        }
    }
    return 0;
}
