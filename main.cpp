#include <iostream>
#include "mappa.hpp"
using namespace std;

int main() {
    mappa nuova_mappa(5);
    //nuova_mappa.generate_all_rooms();
    //nuova_mappa.print_list();
    //nuova_mappa.add_empty_rooms();

    nuova_mappa.generate_map();
    //nuova_mappa.print_list();
    nuova_mappa.print_map();
    //nuova_mappa.print_list();

    return 0;
}