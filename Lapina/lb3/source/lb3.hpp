#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <algorithm>

class edge {
public:
    edge(char v, float metrika){
        this->v = v;
        this->metrika = metrika;
        this->view = 0;
    }
 
    char name()const{
        return this->v;
    }
 
    float len()const{
        return this->metrika;
    }
    void inc(int min){
        this->metrika = this->metrika+min;
    }

    void dec(int min){
        this->metrika = this->metrika-min;
    }

private:
    char v;
    float metrika;
public:
    int view;
};

class answ{
    public:
        answ(char source, char dest, int metrika){
            this->source = source;
            this->dest = dest;
            this->metrika = metrika;
        }
 
    public:
        char source;
        char dest;
        int metrika;
};

using Graph = std::map<char, std::vector<edge>>;

int Search_min(std::string path, Graph G);
void Read_inform_about_edge(Graph &G);
void dec_metric(Graph &G, std::string path, int min);
void create_reverse_edges(Graph &G, std::string path, int min);
std::string Search_path(Graph &G, char cur, char finish, std::string path);
bool Check_v(Graph G, char start);
std::vector <answ> for_answer(Graph G, Graph G2);
int Algoritm(Graph &G, char start, char finish);

