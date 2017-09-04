//#include <iostream>
#include "mappa.hpp"
using namespace std;
    struct lista_mappe{
        mappa* map;
        lista_mappe * next;
    };
int main() {

    mappa nuova_mappa(5);
    nuova_mappa.generate_map();

    lista_mappe * head=NULL;
    head = new lista_mappe;
    head->map = new mappa;
    head->map = &nuova_mappa;

    head->map->print_map();

    nuova_mappa.print_map();

    return 0;
}