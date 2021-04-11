#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <algorithm>

class rebro {
public:
    rebro(char v, float metrika){
        this->v = v;
        this->metrika = metrika;
    }
 
    char name()const{
        return this->v;
    }
 
    float len()const{
        return this->metrika;
    }

private:
    char v;
    float metrika;
};

using Graph = std::map<char, std::vector<rebro>>;

int h(char name, char finish);
void Read(Graph &G, std::vector <char> &v_for_check);
void Check_h(std::vector <char> v, char finish, int path, Graph G);
std::string Algoritm_A(float &priority, char start, char finish, Graph G);

