#include "main.h"

int main() {

    // Aufgabe 1:
    std::cout << "\nAufgabe 1:\n--------------\n";
    std::cout << "Unsere Gruppe:\n\n";
    print_info_nils_weberruss();





    // Aufgabe 2:
    std::cout << "\nAufgabe 2:\n--------------\n";
    assert(analyze(0) == 1);
    assert(analyze(9) == 1);
    assert(analyze(-1) == 2);
    assert(analyze(1234) == 4);
    assert(analyze(-90) == 3);
    assert(analyze("Hello World") == 11);
    assert(analyze("ABC") == 3);



    return 0;
}
