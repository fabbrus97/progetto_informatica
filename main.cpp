#include <iostream>
#include "mappa.hpp"
using namespace std;

int main() {

    mappa nuova_mappa(4);
    nuova_mappa.generate_all_rooms();
    //nuova_mappa.print_list();
    //nuova_mappa.add_empty_rooms();
    //RIVEDERE FUNZIONE add_empty_roooms();
    //nuova_mappa.generate_tunnel();
    nuova_mappa.print_all_rooms();
    //nuova_mappa.print_list();

    return 0;
}