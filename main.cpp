#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif
#include "src/Menu.h"

int main() {
#ifdef _WIN32
    // Bật chế độ UTF-8 cho Windows Console để hiển thị tiếng Việt mượt mà
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    std::cout << "==================================================================\n";
    std::cout << "        KHOA CONG NGHE THONG TIN - DAI HOC GIAO THONG VAN TAI     \n";
    std::cout << "                  TP. HO CHI MINH (UTH)                           \n";
    std::cout << "             BOC CAO BAI TAP DU AN MON CTDL & GT                  \n";
    std::cout << "==================================================================\n";

    Menu menu("candidates.txt");
    menu.run();

    return 0;
}
