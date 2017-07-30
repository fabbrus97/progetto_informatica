//#include "mappa.hpp"

//item

class item{
protected:
    bool is_passable; //determina se si può passare attraverso l'oggetto
public:
    char carattere; //elemento fondamentale, è il carattere associato all'oggetto (cioè quello che verrà stampato sulla mappa)
    item(char c, bool b);
    item();

    //weapons:
    int dam=0;
    virtual void damage();
};

typedef item * ptr_item;

/*
 * oggetti stanza
 *
 */

/*
 * Ogni sottoclasse può avere nuovi metodi, ma tutti i metodi vanno specificati in item (con il prefisso virtual)
 * inoltre tutti i campi di ogni sottoclasse vanno specificati nella superclasse item
 *
 */

//LE SEGUENTI CLASSI DI ARMI SONO UNA PROVA

class sword:public item{
public:
    sword(int d, char c, bool b);
    void damage();
};

class bow:public item{
public:
    bow(int d, char c, bool b);
    void damage();
};