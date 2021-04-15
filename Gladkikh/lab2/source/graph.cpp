#include "graph.hpp"


Graph::Graph(char start_vertex, char end_vertex) {
    start_vertex_symbol_ = start_vertex;
    end_vertex_symbol_ = end_vertex;
}

bool Graph::read_edges(std::istream& in) {
    char edge_start_name, edge_end_name;
    float edge_weight;

    Vertex* first_vertex;
    Vertex* second_vertex;


    while (in >> edge_start_name >> edge_end_name >> edge_weight) {

        if(edge_weight < 0.0 || !isalpha(edge_start_name) || !isalpha(edge_end_name)) {
            utility_vector_ = vertices_arr_;
            return false;
        }

        first_vertex = get_vertex_from_vector(edge_start_name);
        if(!first_vertex) {
            first_vertex = new Vertex({edge_start_name});
            vertices_arr_.push_back(first_vertex);
        }

        second_vertex = get_vertex_from_vector(edge_end_name);
        if(!second_vertex) {
            second_vertex = new Vertex({edge_end_name});
            vertices_arr_.push_back(second_vertex);
        }


        first_vertex->edges_arr.push_back({second_vertex, edge_weight});

        if(in.eof()) {
            break;
        }

    }

    if(vertices_arr_.size() == 0) return false;

    utility_vector_ = vertices_arr_;
    return true;
}

std::string Graph::find_path_a_star() {
    if(vertices_arr_.size() < 2) return "Error";

    auto vertex_pair_cmp = [](Vertex* left, Vertex* right) -> bool {
        if (left->priority == right->priority && left->name < right->name)
            return true;
        return left->priority > right->priority;
    };


    start_vertex_ = get_vertex_from_vector(start_vertex_symbol_);
    start_vertex_->priority = 0 + heuristics(start_vertex_symbol_, end_vertex_symbol_);

    end_vertex_ = get_vertex_from_vector(end_vertex_symbol_);

    std::make_heap(vertices_arr_.begin(), vertices_arr_.end(), vertex_pair_cmp);

    Vertex* cur_vertex;

    while(!vertices_arr_.empty()) {
        cur_vertex = vertices_arr_.front();
        if (cur_vertex->name == end_vertex_symbol_) {
            while (cur_vertex->prev) {
                path_ += cur_vertex->name;
                cur_vertex = cur_vertex->prev;                
            }
            path_ += cur_vertex->name;
            break;            
        }

        for (auto& edge : cur_vertex->edges_arr) {
            float temp = cur_vertex->priority - heuristics(cur_vertex->name, end_vertex_symbol_) + edge.weight;
            if (edge.end_vertex->priority > temp) {

                edge.end_vertex->priority = temp + heuristics(edge.end_vertex->name, end_vertex_symbol_);
                edge.end_vertex->prev = cur_vertex;                
            }
        }
        vertices_arr_.erase(vertices_arr_.begin());

        std::make_heap(vertices_arr_.begin(), vertices_arr_.end(), vertex_pair_cmp);
    }
    
    reverse(path_.begin(), path_.end());

    if(vertices_arr_.empty() || path_[0] != start_vertex_symbol_)
        return "no path";

    return path_;
}

std::string Graph::find_path_greedy() {
    if(vertices_arr_.size() < 2) return "Error";

    auto vertex_pair_cmp = [](Vertex* left, Vertex* right) -> bool {
        return left->priority > right->priority;
    };

    start_vertex_ = get_vertex_from_vector(start_vertex_symbol_);
    start_vertex_->priority = 0;

    std::make_heap(vertices_arr_.begin(), vertices_arr_.end(), vertex_pair_cmp);


    Vertex* cur_vertex;

    while(!vertices_arr_.empty()) {

        cur_vertex = vertices_arr_.front();

        cur_vertex->isVisited = true;

        if (cur_vertex->name == end_vertex_symbol_) {
            while (cur_vertex->prev) {
                path_ += cur_vertex->name;
                cur_vertex = cur_vertex->prev;
            }
            path_ += cur_vertex->name;
            break;
        }

        for (auto& edge : cur_vertex->edges_arr) {
            if (edge.end_vertex->priority > edge.weight && !edge.end_vertex->isVisited) {
                edge.end_vertex->priority = edge.weight;
                edge.end_vertex->prev = cur_vertex;
            }
        }
        
        vertices_arr_.erase(vertices_arr_.begin());

        std::make_heap(vertices_arr_.begin(), vertices_arr_.end(), vertex_pair_cmp);
    }
        
    reverse(path_.begin(), path_.end());
    
    if(vertices_arr_.empty() || path_[0] != start_vertex_symbol_)
        return "no path";
    
    return path_;
}

std::string Graph::print_vector_to_string() {
    std::string out;
    for (const auto& cur_vertex : vertices_arr_) {
        out += cur_vertex->name;
        out += " = [ ";
        for(const auto& neighbour: cur_vertex->edges_arr) {
            out += neighbour.end_vertex->name;
            out += " ";
        }
        out += "]; ";
    }
    return out;
}

Graph::~Graph() {
    for(auto& vertex: utility_vector_) {
        delete vertex;
    }
}

Vertex* Graph::get_vertex_from_vector(char target_vertex_name) {
    for(auto& cur_vertex: vertices_arr_) {
        if(cur_vertex->name == target_vertex_name) {
            return cur_vertex;
        }
    }

    return nullptr;
}

float Graph::heuristics(const char& start, const char& finish) {
    return abs(start - finish);
}