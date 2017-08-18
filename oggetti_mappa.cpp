//
// Created by simone on 20/07/17.
//
#include <iostream>
#include "oggetti_mappa.hpp"
using namespace std;

item::item(char c, bool b){
    dam=0;
    carattere=c;
    is_passable=b;
    /*pos[0]=x;
    pos[1]=y;
    pos[2]=xx;
    pos[3]=yy;*/
}

item::item(){}

void item::damage(){
    cout << "danno item: " << dam << endl;
}

void item::get_position(int x, int y, int xx, int yy) {
    /* x è la coordinata x della stanza rispetto alla mappa
     * y è la coordinata y della stanza rispetto alla mappa
     * xx è la coordinata x del punto rispetto alla stanza
     * yy è la coordinata y del punto rispetto alla stanza
     */

}

//SWORD

sword::sword(int d, char c, bool b){
    dam=d;
    carattere=c;
    is_passable=b;
}

void sword::damage() {
    cout << "danno spada: " << dam << endl;
}

//BOW

bow::bow(int d, char c, bool b){
    dam=d;
    carattere=c;
    is_passable=b;
}

void bow::damage(){
    cout << "danno arco: " << dam << endl;
}
