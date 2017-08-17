#include "item.h"
#include <cstring>


item::item()
{
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


