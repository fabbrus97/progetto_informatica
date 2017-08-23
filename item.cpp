#include "item.h"
#include <cstring>

item::item(){}

item::item(char icona, bool isAttraversabile, bool isRaccoglibile){
    icon = icona;
    attraversabile = isAttraversabile;
    raccoglibile = isRaccoglibile;
}

item::item(char nome[], char icona, bool isAttraversabile, bool isRaccoglibile, int positionX, int positionY, int positionXX, int positionYY)
{
    strcpy(nomeCompleto, nome);
    icon = icona;
    attraversabile = isAttraversabile;
    raccoglibile = isRaccoglibile;
    posizioneX = positionX;
    posizioneY = positionY;
    posizioneXX = positionXX;
    posizioneYY = positionYY;
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

int item::getPositionX()
{
    return posizioneX;
}

int item::getPositionY()
{
    return posizioneY;
}

int item::getPositionXX()
{
    return posizioneXX;
}

int item::getPositionYY()
{
    return posizioneYY;
}

void item::setPositionX(int newPositionX, int newPositionY, int newPositionXX, int newPositionYY)
{
    posizioneX = newPositionX;
    posizioneY = newPositionY;
    posizioneXX = newPositionXX;
    posizioneYY = newPositionYY;
}


