#include "lab4_2.h"


void KMP::Read() {
    std::cout << "Введите первую строку А:\n";
    std::cin >> A;
    std::cout << "Введите вторую строку В:\n";
    std::cin >> B;
}


void KMP::PrintAnswer() {
    std::cout << "\n\n_Ответ_:\n";
    if (answer == -1) {
        std::cout << "A Не является циклическим сдвигом B.\n";
        std::cout << answer << '\n';
    }
    else {
        std::cout << "A является циклическим сдвигом B.\n";
        std::cout << "Индекс начала строки B в А: " << answer << '\n';
    }
}


void KMP::Prefix() {   //префикс-функция
    std::cout << "\n_Подсчет префикс-функции_:\n\n";
    int bLength = B.length();
    arrPrefix = std::vector<int>(bLength);
    arrPrefix[0] = 0;
    std::cout << "Значение префикс-функции для символа " << B[0] << " под номером " << 0 << " равна " << 0 << '\n';
    for (int i = 1; i < bLength; i++) {
        int curLength = arrPrefix[i - 1];
        std::cout << "Вычисление значения префикс-функции для символа " << B[i] << " под номером " << i << "\n\n";

        while (curLength > 0 && (B[curLength] != B[i])) {   // если предыдущий суффикс нельзя расширить, то рассматриваем суффикс меньшего размера
            std::cout << "Предыдущий суффикс размера " << curLength << " нельзя расширить.\n";
            curLength = arrPrefix[curLength - 1];
            std::cout << "Рассмотрим новый суффикс меньшего размера: " << curLength << '\n';
        }

        if (B[curLength] == B[i]) {    // проверка на расширение
            std::cout << "Суффикс длинны " << curLength << " можно расширить.\n";
            curLength++;
            std::cout << "Новый размер суффикса: " << curLength << '\n';
        }

        std::cout << "Значение префикс-функции равно " << curLength << '\n';
        arrPrefix[i] = curLength;
    }

    std::cout << "\nЗначения префикс-функции:\n";
    for (auto j : B) {
        std::cout << j << ' ';
    }
    std::cout << '\n';
    for (auto i : arrPrefix) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}


void KMP::CyclicShift() {
    if (A.length() != B.length()) {
        std::cout << "Длинны строк не равны, значит это не циклический сдвиг.\n";
        answer = -1;
        return;
    }

    Prefix();
    std::cout << "\n\n_Определение, является ли А циклическим сдвигом B_:\n\n";
    int aLength = A.length();
    int curBLength = 0;
    for (int i = 0; i < aLength * 2; i++) { //поиск по удовоенной первой строке
        int j = i % aLength;
        if (B[curBLength] != A[j]) //если символы не равны
            std::cout << "Несовпадение " << j << " символа строки А " << '(' << A[j] << ')' << " и " << curBLength << " символа строки В "  << '(' << B[curBLength] << ")";
        while (curBLength > 0 && B[curBLength] != A[j]) {
            curBLength =arrPrefix[curBLength - 1];
        }
        std::cout << '\n';
        if (B[curBLength] == A[j]) { //если символы равны
            std::cout << "Найдено совпадение " << j << " символа строки А " << '(' << A[j] << ')' << " и " << curBLength << " символа строки В " << '(' << B[curBLength] << ")";
            curBLength++;
        }

        if (curBLength == aLength) {  //если нашлось вхождение
            answer = i - curBLength + 1;
            std::cout << "\n\nВхождение нашлось. Индекс равен " << answer << '\n';
            return;
        }
    }

    answer = -1;
    return;
}


int main() {
    setlocale(LC_ALL, "Russian");
    KMP k;
    k = KMP();
    k.Read();
    k.CyclicShift();
    k.PrintAnswer();
    return 0;
}