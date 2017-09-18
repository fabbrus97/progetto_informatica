#ifndef ITEM_H
#define ITEM_H
#define MAX_NOME_COMPLETO_LENGTH 100

// NB, l'icona identifica anche il tipo di item

class item
{
protected:
    char nomeCompleto[MAX_NOME_COMPLETO_LENGTH];
    char icon;
    /* Se un Item é attraversabile NON puó essere anche raccoglibile,
     * questo perché se é attraversabile allora l'item verrá cancellato
     * quando il personaggio ci andrá sopra poiché nelle stanze ogni punto
     * puó contenere solo 1 item (ricordo che il personaggio é un item)
     */
    bool attraversabile;
    bool raccoglibile;
    int posizioneX; //coordinata x rispetto alla mappa
    int posizioneY; //coordinata y rispetto alla mappa
    int posizioneXX; //coordinata x rispetto alla stanza
    int posizioneYY; //coordinata y rispetto alla stanza

    int teletrasporto[4];

public:
    item();
    item(char icon, bool isAttraversabile, bool isRaccoglibile);
    item(char icon, bool isAttraversabile, bool isRaccoglibile, char nome[]);
    item(char icona, bool isAttraversabile, bool isRaccoglibile, char nome[], int positionX, int positionY, int positionXX, int positionYY);
    char getIcon();
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
    void setPosition(int newPositionX, int newPositionY, int newPositionXX, int newPositionYY);
};

typedef item * ptr_item;

#endif // ITEM_H