//
// Created by simone on 20/07/17.
//
#include <iostream>
#include "oggetti_mappa.hpp"
using namespace std;

item::item(char c, bool b){
    carattere=c;
    is_passable=b;
}

item::item(){}

void item::damage(){
    cout << "danno item: " << dam << endl;
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

