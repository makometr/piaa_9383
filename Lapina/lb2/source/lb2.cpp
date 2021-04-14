#include "lb2.hpp"

int h(char name, char finish) {    //эврист ф-ция
        return abs(finish - name);
    };

void Read(Graph &G, std::vector <char> &v_for_check){
    char source , dest;
    float metr;
while (std::cin >> source >> dest >> metr){
        rebro g(dest, metr);
        //проверяем есть ли уже вектор с такой вершиной
        if (G.count(source) == 0) {
            std::vector<rebro> d = {g};
            G[source] = d;
        } else {
            G[source].push_back(g);
        }
        auto is_not_find =std::find(v_for_check.begin(), v_for_check.end(), dest);
        if (is_not_find==v_for_check.end())
            v_for_check.push_back(dest);
    }
}

void Check_h(std::vector <char> v, char finish, int path, Graph G){
    std::cout << "Проверка эвристики на допустимость:\n";
    bool check_dop = true;
    for (int i = 0; i!=v.size();i++){
        if(h(v[i], finish)<=path){
            std::cout << "\tВершина " <<v[i] << " удовлеворяет условию допустимости\n";
        }
        else {
            std::cout << "\tВершина " <<v[i] << " не удовлеворяет условию допустимости\n";
            check_dop = false;
        }
    }
    if (check_dop)
        std::cout << "Эвристическая функция допустима\n";
    else
        std::cout << "Эвристическая функция не допустима\n";

    std::cout << "\nПроверка эвристики на монотонность\n";
    bool check_mon = true;
    for (auto it = G.begin(); it!=G.end();it++){
        auto source = it->first;
        for (auto i = it->second.begin();i!=it->second.end(); i++){
            if (abs(h(source, finish) - h(i->name(), finish)) <= i->len()){
                std::cout << "\tРебро " << source << i->name() << " не нарушает мотонность\n";
            }
            else{
                std::cout << "\tРебро " << source << i->name() << " нарушает мотонность\n";
                check_mon = false;
            }
        }
    }
    if (check_mon && ( h(finish, finish) == 0))
        std::cout << "Эвристическая функция монотонна\n";
    else
        std::cout << "Эвристическая функция не монотонна\n";
} 

std::string Algoritm_A(float &priority, char start, char finish, Graph G){
     
    std::vector<std::tuple<char, char, float>> past; //вектор кортежей пройденных ребер (float = путь до вершины)
    std::vector<std::tuple<char, char, float>> queue; //в.к. очереди с приоритетом (float = путь до вершины+эвристика)
    char cur = start;
    while (cur != finish){
        for(auto it = G[cur].begin(); it != G[cur].end(); it++){
            queue.push_back(std::make_tuple(cur, it->name(), priority + it->len() + h(it->name(), finish)));
        }
        std::sort(queue.begin(), queue.end(), [] (const std::tuple<char, char, float> &p1, const std::tuple<char, char, float> &p2) { //по убыванию, берем с конца наименьший
            if (std::get<2>(p1) > std::get<2>(p2)){
                return true;
            }
            return false;
        });
        bool check = false;
        char prev;
        while(!queue.empty()){
            prev = std::get<0>(queue.back());   //предыдущий
            cur = std::get<1>(queue.back());    //нынешний
            priority = std::get<2>(queue.back()) - h(cur, finish);  //путь
            queue.pop_back();
            int flag = 0;
            for(auto it = past.begin(); it != past.end(); it++){
                if (std::get<1>(*it) == cur){
                    if(std::get<2>(*it) <= priority){
                        flag = -1;
                        break;
                    }else{
                        past.erase(it);
                        break;
                    }
                }
            }
            if (flag == -1){ //если есть путь короче, то берет следующий
                continue;
            }
            check = true;
            break;
        }
        if(!check){
            std::cout << "Пути нет!\n";
            return 0;
        }
        past.push_back(std::make_tuple(prev, cur, priority));
    }
    std::string result = "";
    cur = finish;
    result.push_back(cur);
    while(cur != start){
        for (auto it = past.begin(); it != past.end(); it++){
            
            if(std::get<1>(*it) == cur){ //для поиска результата 
                cur = std::get<0>(*it);
                break;
            }
        }
        result.push_back(cur);
    }

    std::reverse(result.begin(), result.end());  //перевернули
    return result;
}
