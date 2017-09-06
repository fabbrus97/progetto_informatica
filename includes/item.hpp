#ifndef ITEM_H
#define ITEM_H
#define MAX_NOME_COMPLETO_LENGTH 100

class item
{
protected:
    char nomeCompleto[MAX_NOME_COMPLETO_LENGTH];
    char icon;
    int colore; //0-8
    bool attraversabile;
    bool raccoglibile;
    int posizioneX; //coordinata x rispetto alla mappa
    int posizioneY; //coordinata y rispetto alla mappa
    int posizioneXX; //coordinata x rispetto alla stanza
    int posizioneYY; //coordinata y rispetto alla stanza
public:
    item();
    item(char icon, bool isAttraversabile, bool isRaccoglibile);
    item(char icon, bool isAttraversabile, bool isRaccoglibile, int colore);
    item(char icon, bool isAttraversabile, bool isRaccoglibile, int colore, char nome[]);
    item(char icona, bool isAttraversabile, bool isRaccoglibile, int colore, char nome[], int positionX, int positionY, int positionXX, int positionYY);
    char getIcon();
    int getColore();
    bool getAttraversabile();
    bool getRaccoglibile();
    void setNomeCompleto (char newNomeCompleto[]);
    void getNomeCompleto(char *buff);
    void setAttraversabile(bool isAttraversabile);
    void setRaccoglibile(bool isRaccoglibile);
    void setIcon(char newIcon);
    int getPositionX();
    int getPositionY();
    int getPositionXX();
    int getPositionYY();
    void setPositionX(int newPositionX, int newPositionY, int newPositionXX, int newPositionYY);
    /*void setPositionY(int newPositionY);
    void setPositionXX(int newPositionXX);
    void setPositionYY(int newPositionYY);*/
};

typedef item * ptr_item;

#endif // ITEM_H