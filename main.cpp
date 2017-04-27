#include <iostream>
#include "mappa.hpp"
using namespace std;

int main() {
    mappa nuova_mappa(9);
    nuova_mappa.generate_map();
    nuova_mappa.print_map();

    return 0;
}