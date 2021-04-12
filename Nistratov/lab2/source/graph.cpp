#include "graph.h"

void Graph::inputNode(char first, char second, float weight){
    Node* firstNode = nullptr;
    Node* secondNode = nullptr;

    firstNode = getNodeByName(first);
    if (!firstNode) {
        firstNode = new Node(first);
        nodes.push_back(firstNode);
    }

    secondNode = getNodeByName(second);
    if (!secondNode) {
        secondNode = new Node(second);
        nodes.push_back(secondNode);
    }

    firstNode->neighbours.push_back(new Neighbour(secondNode, weight));      
}

std::vector<Node *> Graph::getNodes(){
    return nodes;
}


/* WORKS ONLY ON WINDOWS!!!!! std::cin.clear() ???? 
void Graph::setHeuristic(){
    std::cout << "Set Heuristics: " << std::endl;
    for (auto& node : nodes){
        //node->heuristic = abs((int)end - (int)node->name);   

        std::cout << node->name << ": ";
        std::cin >> node->heuristic;
        std::cout << std::endl;
        if (node->heuristic < 0){
            node->heuristic = abs(node->heuristic);
        }
    } 
}*/

Node* Graph::getNodeByName(char name){
    for (auto& elem: nodes){
        if (elem->name == name){
            return elem;
        }
    }
    return nullptr;
}

int Graph::getIndexByNode(Node* node){
    for (int i = 0; i < nodes.size(); i++){
        if (node->name == nodes[i]->name){
            return i;
        }
    }
    return -1;
}

Node* Graph::getMinNode(){
    Node* temp = nullptr;
    for (auto& node : nodes){
        if (!temp){
            temp = node;
            continue;
        }
        if (node->cost == temp->cost && node->name > temp->name){
            temp = node;
        }
        else if (node->cost < temp->cost){
            temp = node;
        }
    }
    return temp;
}

void Graph::printGraph(){
    for (auto& elem : nodes){
        std::cout << "Node : " << elem->name << " Heuristic: " << elem->heuristic << std::endl;
        for (auto& neighbour_in : elem->neighbours){
            std::cout << "Neigbour : " << neighbour_in->nodeName->name << " Weight: " << neighbour_in->weight << \
            " Cost: " <<  neighbour_in->weight + neighbour_in->nodeName->heuristic << std::endl;
        }
    }
}
void Graph::printNodes(){
    for (auto& a : nodes){
        std::cout << a->name << std::endl;
    }
}

void Graph::printAnswer(){
    std::string answer;
    while (endNode->cameFrom){
        answer += endNode->name;
        endNode = endNode->cameFrom;
    }
    answer += endNode->name;
    std::reverse(answer.begin(), answer.end());
    std::cout << answer << std::endl;
}

std::string Graph::getAnswer(){
    std::string answer;
    while (endNode->cameFrom){
        answer += endNode->name;
        endNode = endNode->cameFrom;
    }
    answer += endNode->name;
    std::reverse(answer.begin(), answer.end()); 
    return answer;
}

void Graph::AStar(){
    startNode = getNodeByName(start);
    startNode->cost = startNode->heuristic;
    Node* currNode;

    while (!nodes.empty()){
        currNode = getMinNode(); 
        nodes.erase(nodes.begin() + getIndexByNode(currNode)); 

        if (currNode->name == end){
                endNode = currNode;
                break;
            }

        for (auto& node : currNode->neighbours){

            float newCost = currNode->cost - currNode->heuristic + node->weight;

            if (node->nodeName->cost > newCost){
                node->nodeName->cost = newCost + node->nodeName->heuristic;
                node->nodeName->cameFrom = currNode;
            }
        }
    }    
}