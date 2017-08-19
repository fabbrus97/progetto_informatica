#ifndef ITEM_H
#define ITEM_H
#define CONST_LENGTH 100

typedef int posizione[4];
/* posizione[0] è la coordinata x rispetto alla mappa
 * posizione[1] è la coordinata y rispetto alla mappa
 * posizione[2] è la coordinata x rispetto alla stanza
 * posizione[3] è la coordinata y rispetto alla stanza
 */

class item
{
protected:
    char nomeCompleto[CONST_LENGTH];
    bool attraversabile;
    bool raccoglibile;
public:
    char icon;
    posizione pos;
    item();
    item(char carattere, bool attr, bool racc);
    void stampaNomeCompleto(char nome[]);
    char getIcon();
    bool getAttraversabile();
    bool getRaccoglibile();
    void setNomeCompleto (char newNomeCompleto[]);
    void setAttraversabile(bool isAttraversabile);
    void setRaccoglibile(bool isRaccoglibile);
    void setIcon(char newIcon);
    void get_position(int x, int y, int xx, int yy);

};

typedef item * ptr_item;

#endif // ITEM_H
