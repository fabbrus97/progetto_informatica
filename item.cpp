#include "item.h"
#include <cstring>


item::item(char nome[], char icona, bool isAttraversabile, bool isRaccoglibile, int positionX, int positionY, int positionXX, int positionYY)
{
    strcpy(nomeCompleto, nome);
    item::icon = icona;
    item::attraversabile = isAttraversabile;
    item::raccoglibile = isRaccoglibile;
    item::posizioneX = positionX;
    item::posizioneY = positionY;
    item::posizioneXX = positionXX;
    item::posizioneYY = positionYY;
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

void item::setPositionX(int newPositionX)
{
    posizioneX = newPositionX;
}

void item::setPositionY(int newPositionY)
{
    posizioneY = newPositionY;
}

void item::setPositionXX(int newPositionXX)
{
    posizioneXX = newPositionXX;
}

void item::setPositionYY(int newPositionYY)
{
    posizioneYY = newPositionYY;
}

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


