#include "lab4_1.h"


void KMP::Read() {
	std::cout << "Введите первую строку P:\n";
	std::cin >> P;
	std::cout << "Введите вторую строку T:\n";
	std::cin >> T;
}

void KMP::PrintAnswer() {
    std::cout << "\n_Ответ_:\n";
    if (!answer.size()) {
        std::cout << "P не входит в T\n";
        std::cout << -1;
    }
    else {
        std::cout << "Индексы начал вхождений P в T:\n";
        for (auto a : answer) {
            if (a == answer.front())
                std::cout << a;
            else
                std::cout << "," << a;
        }
    }
    std::cout << '\n';
}

void KMP::Prefix() {   //префикс-функция
	std::cout << "\n_Подсчет префикс-функции_:\n\n";
	int pLength = P.length();
    arrPrefix = std::vector<int>(pLength);
    arrPrefix[0] = 0;
    std::cout << "Значение префикс-функции для символа "<< P[0] << " под номером " << 0  << " равна " << 0 << '\n';
    for (int i = 1; i < pLength; i++) {
        int curLength = arrPrefix[i - 1];
        std::cout << "Вычисление значения префикс-функции для символа " << P[i] << " под номером " << i << "\n\n";

        while (curLength > 0 && (P[curLength] != P[i])) {   // если предыдущий суффикс нельзя расширить, то рассматриваем суффикс меньшего размера
            std::cout << "Предыдущий суффикс размера " << curLength << " нельзя расширить.\n";
            curLength = arrPrefix[curLength - 1];
            std::cout << "Рассмотрим новый суффикс меньшего размера: " << curLength << '\n';
        }

        if (P[curLength] == P[i]) {    // проверка на расширение
            std::cout << "Суффикс длинны " << curLength << " можно расширить.\n";
            curLength++;
            std::cout << "Новый размер суффикса: " << curLength << '\n';
        }

        std::cout << "Значения префикс-функции равно " << curLength << '\n';
        arrPrefix[i] = curLength;
    }

    std::cout << "\nЗначения префикс-функции:\n";
    for (auto j : P) { 
        std::cout << j << ' ';
    }
    std::cout << '\n';
    for (auto i : arrPrefix) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}


void KMP::AlgorithmKMP(){
    Prefix();
    std::cout << "\n\n_Алгоритм Кнута-Морриса-Пратта_:\n\n";
    int tSize = T.size();
    int pSize = P.size();
    int pIndex = 0;
    int tIndex = 0;
    while (tIndex < tSize) {
        if (P[pIndex] == T[tIndex]) {  //если символы равны
            std::cout << "Найдено совпадение " << pIndex << " символа образца " << P[pIndex]  << " и " << tIndex << " символа текста " << T[tIndex] << '\n';
            pIndex++;
            tIndex++;
            if (pIndex == pSize) {  //если вхождение найдено
                std::cout << "Вхождение найдено, индекс равен " << tIndex - pIndex << "\n\n";
                answer.push_back(tIndex - pIndex);
                pIndex = arrPrefix[pIndex - 1]; //переход на позицию равную предпоследнему значению префикс-функции
            }
        }
        else if (pIndex == 0) // если сравнение с первым символом
            tIndex++;
        else  //если же по образцу продвинулись
            pIndex = arrPrefix[pIndex - 1];
    }
}


int main() {
    setlocale(LC_ALL, "Russian");
    KMP k;
    k = KMP();
    k.Read();
    k.AlgorithmKMP();
    k.PrintAnswer();
    return 0;
}