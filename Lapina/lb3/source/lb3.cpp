#include "lb3.hpp"

void Read_inform_about_edge(Graph &G){
    char source , dest;
    float metr;
    while (std::cin >> source >> dest >> metr){
        edge g(dest, metr);
        //проверяем есть ли уже вектор с такой вершиной
        if (G.count(source) == 0) {
            std::vector<edge> d = {g};
            G[source] = d;
        } else {
            G[source].push_back(g);

            std::sort(G[source].begin(), G[source].end(), [] (edge &p1, edge &p2) { //по возрастанию
            return (p1.name() < p2.name());
            });
        }
    }


}

void dec_metric(Graph &G, std::string path, int min){

    //Уменьшаем вес у нынешних
    for (int i = 0; i != path.size() - 1; i++){
        char source = path[i];
        char dest = path[i+1];

        edge g(dest, min);
        for (int j = 0; j != G[source].size(); j++){
            if (G[source][j].name()==dest)
                G[source][j].dec(min);
        }
        
    }

}

int Search_min(std::string path, Graph G){
    //Ищем минимальный вес в пути 
    int min = 10000;
    for (int i = 0; i != path.size() - 1; i++){
        char source = path[i];
        char dest = path[i+1];
        for (int j = 0; j!= G[source].size(); j++){
            if (G[source][j].name() == dest){
                if (min>G[source][j].len())
                    min = G[source][j].len();
            }
        }
    }
    return min;
}

void create_reverse_edges(Graph &G, std::string path, int min){
    //Делаем обратные рёбра

    std::reverse(path.begin(), path.end());  //перевернули

    for (int i = 0; i != path.size() - 1; i++){
        char source = path[i];
        char dest = path[i+1];

        edge g(dest, min);
        //проверяем есть ли уже вектор с такой вершиной
        if (G.count(source) == 0) {   //если нет
            std::vector<edge> d = {g};
            G[source] = d;
        } 
        else {     //если есть
            int is_find = 0;
            for (int j = 0; j!=G[source].size(); j++){
                if (G[source][j].name() == dest){  //если есть такое ребро
                    G[source][j].inc(min);
                    is_find = 1;
                }
            }

            if (is_find==0){                           //если нет
                G[source].push_back(g);
                std::sort(G[source].begin(), G[source].end(), [] (edge &p1, edge &p2) { //по возрастанию
                return (p1.name() < p2.name());
                });
            }

        }
    }

}

std::string Search_path(Graph &G, char cur, char finish, std::string path){
    while (cur!=finish){
        char now = cur;
        for (int it=0; it!= G[cur].size(); it++){                

            int f4 = 1;
            for(int i =0; i!= path.size();i++){  //проверка, что вершина не встречалась ранее
                if (G[cur][it].name() == path[i]){
                    f4 = 0;
                }


            }

            if (f4==0){
                continue;
            }

            if ((!G[G[cur][it].name()].empty()  && G[cur][it].view == 0 && G[cur][it].len()>0) ||   (G[cur][it].name()==finish && G[cur][it].len()>0)){   //если взяли вершину
                G[cur][it].view = 1;  //отмечаем как просмотренную
                cur = G[cur][it].name();
                path.push_back(cur);
                break;
            }

            else{
                G[cur][it].view = 1;  //отмечаем как просмотренную 
                if (it == (G[cur].size() - 1)){ 
                    path.pop_back();
                    cur = path.back();
                    break; 
                }
            }
        }
        if (cur==now){
            if (path.size()<2){
                return path;
            }
            else{
                path.pop_back();
                cur = path.back();
            }
        }
    }
    return path;
}



bool Check_v(Graph G, char start){  //возвращвет 0, если нет ребер, с метрикой больше 0 из стартовой вершины
    for (int i = 0; i != G[start].size(); i++){
        if (G[start][i].len() > 0){
            return 1;
        } 
    }
    return 0;
}

std::vector <answ> for_answer(Graph G, Graph G2){
    std::vector <answ> result;
    for(auto it = G2.begin(); it != G2.end(); it++){
        int l = 0;
        int l2 = 0;        

        for(auto k = it->second.begin(); k!=it->second.end(); k++){
            char source = it->first;
            char dest = k->name();
            int l2 = k->len();
            int l = 0;
            for (int j = 0; j != G[source].size(); j++){
                if (G[source][j].name() == dest)
                    l = l2 - G[source][j].len();
            }
            if (l<0)
                l = 0;
            answ g(source, dest, l);
            result.push_back(g);
        }
    }

    std::sort(result.begin(), result.end(), [] (answ &p1, answ &p2) { //по возрастанию, берем с конца наименьший
        if (p1.source < p2.source){
            return true;
        }
        if (p1.source == p2.source){
            return (p1.dest < p2.dest);
        }
        return false;
    });
    return result;
}

int Algoritm(Graph &G, char start, char finish){
    int max_potok = 0;
    bool check = Check_v(G, start);
    char cur = start;
    std::string path;
    path.push_back(cur);
    while(check){
        path  = Search_path(G, cur, finish, path);   //ищем путь
        if (path.empty())
            break;
        int min = Search_min(path, G); //Ищем ребро с минимальным весом - максимальный поток пути
        max_potok = max_potok + min;
        dec_metric(G, path, min); //Уменьшаем вес у нынешних
        create_reverse_edges(G, path, min); //Делаем обратные рёбра

        if (path.size()>1){
            path.pop_back();
            cur = path.back();
            check = Check_v(G, start);
        }

        if (path.size()==1)
            continue;

        std::string new_path;
        char source = path[0];
        char dest = path[1];
        new_path.push_back(source);
        int f3 = 1;
        for (int j = 0; j!= path.size()-1; j++){
            for(int k = 0; k!=G[source].size(); k++){
                if(G[source][k].name() == dest){ 
                    if (G[source][k].len()>0){
                        new_path.push_back(G[source][k].name());
                        source = G[source][k].name();
                        dest = path[j+2];
                        cur = dest;
                        break;
                    }
                    else{
                        cur = new_path[new_path.size()-1];
                        f3 = 0;
                        break;
                    }
                }
            }
            if (f3==0)
                break;
        }

        for(int z = new_path.size(); z != path.size(); z++){
            source = path[z];
            dest = path[z+1];
            for (int y = 0; y!=G[source].size(); y++){
                if (G[source][y].name() == dest){
                    G[source][y].view = 0;
                }
            }
        }
        path = new_path;
        if (path.size()>=1){
            check = Check_v(G, start);
        }
        else{
            check = 0;
            break;
        }
    }
    return max_potok;
}
