#include "graph.hpp"


Graph::Graph(char source_node_symbol, char sink_node_symbol, int edges_amount) {
    source_symbol_ = source_node_symbol;
    sink_symbol_ = sink_node_symbol;
    edges_amount_ = edges_amount;
}

bool Graph::read_edges(std::istream& in) {
    char edge_start_name, edge_end_name;
    int max_flow;
    for(int i = 0; i < edges_amount_; i++) {
        in >> edge_start_name >> edge_end_name >> max_flow;

        if(max_flow < 0) {
            return false;
        }

        graph_map_[edge_start_name].push_back({edge_end_name, {max_flow, 0, i, true}});
        graph_map_[edge_end_name].push_back({edge_start_name, {0, max_flow, i}});
    }

    return true;
}

std::string Graph::to_string() {
    std::string out;
    for (auto char_vec_pair = graph_map_.begin(); char_vec_pair != graph_map_.end(); ++char_vec_pair) {
        out += char_vec_pair->first;
        out += ": ";
        for(auto neighbour = char_vec_pair->second.begin(); neighbour != char_vec_pair->second.end(); ++neighbour) {
            out += neighbour->first;
            out += "(";
            out += std::to_string(neighbour->second.flow);
            out += "/";
            out += std::to_string(neighbour->second.usedFlow);
            out += ") ";
        }
        out += "\n";
    }
    return out;
}

bool neighbour_cmp(Neighbour a, Neighbour b) {
    return a.second.flow > b.second.flow;
}

int Graph::find_flow_path(char start_symbol, char end_symbol, std::map<char, bool> is_visited_map, int flow) {

    if (start_symbol == end_symbol) return flow;
	
    is_visited_map[start_symbol] = true;

    std::sort(graph_map_[start_symbol].begin(), graph_map_[start_symbol].end(), neighbour_cmp);

    for (auto& neighbour : graph_map_[start_symbol]) {
        neighbour.second.isVisited = false;
	if (!is_visited_map[neighbour.first] && neighbour.second.flow > 0) {
            neighbour.second.isVisited = true;
            Neighbour* ptr;
            for(auto& reverse_neighbour: graph_map_[neighbour.first]) {
                reverse_neighbour.second.isVisited = false;
                if(reverse_neighbour.first == start_symbol && reverse_neighbour.second.index == neighbour.second.index) {
                    reverse_neighbour.second.isVisited = true;
                    ptr = &reverse_neighbour;
                    break;
                }
            }

            flow = neighbour.second.flow;
	    prev_node_map_[neighbour.first] = start_symbol;
            int found_flow = find_flow_path(neighbour.first, end_symbol, is_visited_map, flow);

            if(found_flow) {
                return std::min(flow, found_flow);
            }

            neighbour.second.isVisited = false;
            ptr->second.isVisited = false;
	}
    }
    return 0;

}

int Graph::ford_fulkerson() {
    
    prev_node_map_[source_symbol_] = source_symbol_;

    std::map<char, bool> is_visited_map;
    std::vector<char> path;

    int max_flow = 0;
    int found_flow = find_flow_path(source_symbol_, sink_symbol_, is_visited_map, 0);

    while(found_flow) {

        max_flow += found_flow;
        path = get_flow_path();

        for(auto node_char = path.rbegin(); node_char != path.rend(); ++node_char) {
            for(auto& neighbour: graph_map_[*node_char]) {
                if(neighbour.first == *(node_char + 1) && neighbour.second.isVisited) {
                    neighbour.second.flow -= found_flow;
                    neighbour.second.usedFlow += found_flow;   

                    for (auto& reverse_neighbour : graph_map_[neighbour.first]) {
                        if (reverse_neighbour.first == *node_char && reverse_neighbour.second.isVisited){
                            reverse_neighbour.second.flow += found_flow;                            
                            reverse_neighbour.second.usedFlow -= found_flow;
                        }
                    }
                }
            }
        }
        
        found_flow = find_flow_path(source_symbol_, sink_symbol_, is_visited_map, 0);
    }

    return max_flow;
}

std::vector<char> Graph::get_flow_path() {
    std::vector<char> result;
	char current = sink_symbol_;
	result.push_back(current);
	while (current != source_symbol_) {
		current = prev_node_map_[current];
		result.push_back(current);
	}

    return result;
}

std::string Graph::print_res_graph() {
    auto neighbour_letter_cmp = [](Neighbour a, Neighbour b) -> bool {
        return a.first < b.first;
    };
    std::string out;
    for (auto char_vec_pair = graph_map_.begin(); char_vec_pair != graph_map_.end(); ++char_vec_pair) {
        std::sort(char_vec_pair->second.begin(), char_vec_pair->second.end(), neighbour_letter_cmp);
        for(auto neighbour = char_vec_pair->second.begin(); neighbour != char_vec_pair->second.end(); ++neighbour) {
            if(neighbour->second.isInit) {
                out += char_vec_pair->first;
                out += " ";
                out += neighbour->first;
                out += " ";
                out += std::to_string(std::max(0, neighbour->second.usedFlow));
                out += "\n";
            }
        }
    }
    return out;
}

Graph::~Graph() {
}


std::vector<char> Graph::test_find_path(char start_symbol, char end_symbol) {
    std::map<char, bool> is_visited_map;
    int res = find_flow_path(start_symbol, end_symbol, is_visited_map, 0);
    return get_flow_path();
}
