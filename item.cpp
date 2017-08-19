#include "item.h"
#include <cstring>


item::item()
{
}

item::item(char carattere, bool attr, bool racc){
    nomeCompleto[0]='\0';
    icon=carattere;
    attraversabile=attr;
    raccoglibile=racc;
}

bool item::getAttraversabile()
{
    return attraversabile;
}

bool item::getRaccoglibile()
{
    return raccoglibile;
}

void item::setAttraversabile(bool isAttraversabile)
{
    attraversabile = isAttraversabile;
}

void item::setRaccoglibile(bool isRaccoglibile)
{
    raccoglibile = isRaccoglibile;
}

char item::getIcon()
{
    return icon;
}

void item::setIcon(char newIcon)
{
    icon = newIcon;
}

void item::setNomeCompleto(char newNomeCompleto[])
{
    strcpy(newNomeCompleto, nomeCompleto);
}

void item::get_position(int x, int y, int xx, int yy) {
    /* x è la coordinata x della stanza rispetto alla mappa
     * y è la coordinata y della stanza rispetto alla mappa
     * xx è la coordinata x del punto rispetto alla stanza
     * yy è la coordinata y del punto rispetto alla stanza
     */
    pos[0]=x;
    pos[1]=y;
    pos[2]=xx;
    pos[3]=yy;
}


