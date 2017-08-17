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
public:
    item();
    void stampaNomeCompleto(char nome[]);
    char getIcon();
    bool getAttraversabile();
    bool getRaccoglibile();
    void setNomeCompleto (char newNomeCompleto[]);
    void setAttraversabile(bool isAttraversabile);
    void setRaccoglibile(bool isRaccoglibile);
    void setIcon(char newIcon);
};

#endif // ITEM_H
