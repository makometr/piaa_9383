#include "graph.h"

void readGraph(std::vector<Node*>& graph, char start, char finish, std::istream& in)
{
    char curValue, neighbourValue;
    float edgeLength;
    Node* startNode = nullptr;
    Node* endNode = nullptr;

    while (in >> curValue >> neighbourValue >> edgeLength)
    {
        if (!isalpha(curValue) || !isalpha(neighbourValue))
        {
            continue;
        }
        if (edgeLength < 0)
        {
            continue;
        }
        int startIndex = findIndex(graph, curValue);
        int endIndex = findIndex(graph, neighbourValue);
        if (startIndex == -1)
        {
            if (curValue == start)
            {
                startNode = new Node(curValue, heuristic_func(start, finish));
            }
            else
            {
                startNode = new Node(curValue);
            }
            graph.push_back(startNode);
            startIndex = graph.size() - 1;
        }
        else
        {
            startNode = graph[startIndex];
        }
        if (endIndex == -1)
        {
            if (neighbourValue == start)
            {
                endNode = new Node(neighbourValue, heuristic_func(start, finish));
            }
            else
            {
                endNode = new Node(neighbourValue);
            }
            graph.push_back(endNode);
        }
        else
        {
            endNode = graph[endIndex];
        }
        graph[startIndex]->neighbours.push_back(std::make_pair(endNode, edgeLength));
    }
}

int heuristic_func(char start, char finish)
{
	return abs(start - finish);
}

int findIndex(std::vector<Node*>& graph, char value)
{
    for (size_t i = 0; i < graph.size(); i++)
    {
        if (graph[i]->value == value)
        {
            return i;
        }
    }
    return -1;
}

std::string Astar(std::vector<Node*>& graph, char finish)
{

    auto node_cmp = [](const Node* left, const Node* right)
    {
        if (left->priority > right->priority)
        {
            return true;
        }
        if (left->priority == right->priority && left->value < right->value)
        {
            return true;
        }
        return false;
    };

    std::make_heap(std::begin(graph), std::end(graph), node_cmp);

    std::string answer;
    while (!graph.empty())
    {
        //std::cout << vecToString(graph);
        Node* node = graph.front();
        if (node->value == finish)
        {
            while (node->prev)
            {
                answer += node->value;
                node = node->prev;
            }
            answer += node->value;
            break;
        }
        for (auto& neighbour : node->neighbours)
        {
            float temp = node->priority - heuristic_func(node->value, finish) + neighbour.second;
            if (temp < neighbour.first->priority)
            {
                neighbour.first->priority = temp + heuristic_func(neighbour.first->value, finish);
                neighbour.first->prev = node;
            }
        }
        std::swap(graph[0], graph[graph.size() - 1]);
        graph.pop_back();
        std::make_heap(std::begin(graph), std::end(graph), node_cmp);
    }
    reverse(answer.begin(), answer.end());
    if (answer.empty())
    {
        answer = "No path.";
    }
    return answer;
}

std::string greedy(std::vector<Node*>& graph, char finish)
{
    auto node_cmp = [](const Node* left, const Node* right)
    {
        if (left->priority > right->priority)
        {
            return true;
        }
        if (left->priority == right->priority && left->value > right->value)
        {
            return true;
        }
        return false;
    };

    std::make_heap(std::begin(graph), std::end(graph), node_cmp);

    std::string answer;
    while (!graph.empty())
    {
        Node* node = graph.front();
        if (node->value == finish)
        {
            while (node->prev)
            {
                answer += node->value;
                node = node->prev;
            }
            answer += node->value;
            break;
        }
        for (auto& neighbour : node->neighbours)
        {
            if (neighbour.first->priority > neighbour.second)
            {
                neighbour.first->priority = neighbour.second;
                neighbour.first->prev = node;
            }
        }
        std::swap(graph[0], graph[graph.size() - 1]);
        graph.pop_back();
        std::make_heap(std::begin(graph), std::end(graph), node_cmp);
    }
    reverse(answer.begin(), answer.end());
    if (answer.empty())
    {
        answer = "No path.";
    }
    return answer;
}

std::string vecToString(std::vector<Node*>& vec)
{
    std::string ans;
    std::string value;
    for (auto& node : vec)
    {
        value = node->value;
        ans += value + " = [";
        for (auto& neighbour : node->neighbours)
        {
            value = neighbour.first->value;
            ans += value + ", ";
        }
        ans += " ]; \n";
    }
    return ans;
}

void freeMemory(std::vector<Node*>& vec)
{
    for (auto node : vec) {
        delete node;
    }
}
