#ifndef ITEM_H
#define ITEM_H
#define CONST_LENGTH 100

class item
{
protected:
    char nomeCompleto[CONST_LENGTH];
    char icon;
    bool attraversabile;
    bool raccoglibile;
    int posizioneX; //coordinata x rispetto alla mappa
    int posizioneY; //coordinata y rispetto alla mappa
    int posizioneXX; //coordinata x rispetto alla stanza
    int posizioneYY; //coordinata y rispetto alla stanza
public:
    item(char nome[], char icona, bool isAttraversabile, bool isRaccoglibile, int positionX, int positionY, int positionXX, int positionYY);
    void stampaNomeCompleto(char nome[]);
    char getIcon();
    bool getAttraversabile();
    bool getRaccoglibile();
    void setNomeCompleto (char newNomeCompleto[]);
    void setAttraversabile(bool isAttraversabile);
    void setRaccoglibile(bool isRaccoglibile);
    void setIcon(char newIcon);
    int getPositionX();
    int getPositionY();
    int getPositionXX();
    int getPositionYY();
    void setPositionX(int newPositionX);
    void setPositionY(int newPositionY);
    void setPositionXX(int newPositionXX);
    void setPositionYY(int newPositionYY);
};

#endif // ITEM_H
