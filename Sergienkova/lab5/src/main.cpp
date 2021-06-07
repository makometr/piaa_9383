#include "Node.h"
#include "Bohr.h"

#define TASK 2

int main() {
    std::string t, p;
    char j;
    std::vector<std::pair<std::string, int>> pts;
    std::vector<std::pair<int, int>> res;
    int num = 0;

    std::cin >> t;
#if TASK == 1
    std::cin >> num;
    for (int i = 0; i < num; i++) {
        std::string s;
        std::cin >> s;
        pts.push_back({ s, 0 });
    }
    MyAlgorithm(t, pts, res);
#elif TASK == 2
    std::cin >> p;
    std::cin >> j;
    preparePatterns(p, j, pts);
    MyAlgorithm(t, pts, res, p.length());
#endif

    if (res.empty()) {
        std::cout << "\nПоиск не дал результатов\n";
    }
    else {
        sort(res.begin(), res.end());
        for (auto r : res) {
            std::cout << r.first;
#if TASK == 1
            std::cout << " " << r.second;
#endif
            std::cout << "\n";
        }
    }
    return 0;
}
