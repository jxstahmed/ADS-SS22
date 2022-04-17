#ifndef _LIST_H
#define _LIST_H
#include "Node.h"
#include <iostream>
#include <string>

template <class T>
class List
{
    /*
    Die Klasse List dient zur Verwaltung von Knoten (Node). Mit Hilfe der Klasse
    List kann ein Stapel oder Warteschlange realisiert werden.
    */
private:
    struct form
    {
        std::string start    = "<< ";
        std::string zwischen = ", ";
        std::string ende     = " >>\n";
    } list_form;
    Node<T>* head_tail; // Zeiger auf Kopf- und End-Element -> next der 1. Knoten;
                     // -> prev der letzte Knoten
    int  list_size;  // Länge der Kette
    bool temp; // normalerweise false; ist true, wenn es sich um eine temor�re
               // Liste handelt die innerhalb der überladenen Operatoren
               // angelegt wird
public:
    List();
    List(const List<T>& _List); // Kopie Konstruktor
    ~List();
    void insertFront(T value);     // Einfügen eines Knotens am Anfang
    void insertFront(List& _List); // Einfügen einer vorhandenen Liste am Anfang
    void insertBack(T value);      // Einfügen eines Knotesn am Ende
    void insertBack(List<T>& _List);  // Einfügen einer vorhandenen Liste am Ende
    bool getFront(T& value);       // Entnehmen eines Knoten am Anfang
    bool getBack(T& value);        // Entnehmen eines Knoten am Ende
    bool del(T value);             // löschen eines Knotens [key]
    bool search(T value);          // Suchen eines Knoten
    bool swap(T value1, T value2); // Knoten in der Liste vertauschen
    int  size(void);               // Größe der Lise (Anzahl der Knoten)
    bool test(void);               // Überprüfen der Zeigerstruktur der Liste
    void format(const std::string& start,
                const std::string& zwischen,
                const std::string& ende);
    // Mit der format-Methode kann die Ausgabe gesteuert werden: operator <<
    // start: stirng vor der Ausgabe der Liste
    // zwischen: string zwischen Listenknoten
    // ende: string am Ende der Liste
    List<T>& operator=(const List<T>& _List); // Zuweisungsoperator definieren
    List<T>&
    operator+(const List<T>& List_Append); // Listen zusammenführen zu einer Liste
    template <typename Tf>   
    friend std::ostream&
    operator<<(std::ostream& stream,
               List<Tf> const&   Liste); // Ausgabeoperator überladen
    template <typename Tf>
    friend Node<T>* get_anker(List<Tf>& l);
    template <typename Tf>
    friend int   get_AnzahlNodes(List<Tf>& l);
};

#endif

template <class T>
List<T>::List()
{
    /*
        Konstruktor für eine leere Liste
    */
    head_tail = new Node<T>;
    list_size = 0;
    temp = false;
    head_tail->next = head_tail;
    head_tail->prev = head_tail;
}

template <class T>
List<T>::List(const List<T>& _List)
{
    /*
        Konstruktor mit Übergabe einer Liste, die dann kopiert wird.
        in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden
        sollen.
    */
    list_form = _List.list_form;
    head_tail = new Node<T>;
    list_size = 0;
    temp = _List.temp;
    head_tail->next = head_tail;
    head_tail->prev = head_tail;
    Node<T>* tmp_node;
    tmp_node = _List.head_tail->next;
    while (tmp_node != _List.head_tail)
    {
        head_tail->prev =
            new Node<T>(tmp_node->value, head_tail->prev->next, head_tail->prev);
        head_tail->prev->prev->next = head_tail->prev;
        list_size++;
        tmp_node = tmp_node->next;
    }
    /*
        Ist die übergebene Liste eine temporäre Liste? -> aus Operator +
    */
    if (_List.temp)
        delete& _List;
}

template <class T>
List<T>::~List()
{
    Node<T>* loeschen = head_tail->next;
    Node<T>* temp = nullptr;

    while (loeschen != head_tail)
    {
        temp = loeschen;
        loeschen = loeschen->next;
        delete temp;
    }
}

template <class T>
void List<T>::insertFront(T value)
{
    //ToDo
/*
    Einfuegen eines neuen Knotens am Anfang der Liste
    Einen neuen Knoten mit dem Wert value wird am Anfang der Liste einfügen
*/

    Node<T>* neu = new Node<T>(value, head_tail, head_tail);

    if (head_tail->next == head_tail && head_tail->prev == head_tail) // Liste Leer
    {
        head_tail->next = neu;
        head_tail->prev = neu;
    }
    else
    {
        head_tail->next->prev = neu; //Der erste Zeige der Liste zeigt dann auf den neuen
        neu->prev = head_tail;
        neu->next = head_tail->next;
        head_tail->next = neu;
    }
    list_size++;

}

template <class T>
void List<T>::insertFront(List<T>& _List)
{
    //ToDo
/*
    Einfuegen der Liste _List am Anfang an einer vorhandenen Liste
    Die einzufuegenden Knoten werden uebernommen (nicht kopiert)
    Die einzufuegende Liste _List ist anschließend leer.
    Es darf keine Schleife und kein new benutzt werden.
*/

/*
    gleiches Objekt -> keine Aktion
*/
    if (head_tail == _List.head_tail) return;

    /*
        Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
        Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) übertragen ohne sie zu kopieren!
        Die Liste _List ist danach leer, aber vorhanden.
    */

    if (_List.head_tail == _List.head_tail->next)
    {
        return;
    }


    Node<T>* anfang1 = head_tail->next;     // Zeiger auf Anfang der Hinteren Liste

    Node<T>* anfang2 = _List.head_tail->next;   // Zeiger auf Anfang der vorderen Liste
    list_size += 1;                            // Hochzählen damit listen Größe stimmt
    Node<T>* letzter2 = anfang2;               // Zeiger auf den Zeiger des Anfangs zum hochzählen im nächsten Schritt

    //Hochzählen der neuen Liste und list_size erweitern
    while (letzter2->next != _List.head_tail)
    {
        letzter2 = letzter2->next;
        list_size += 1;
    }

    head_tail->next->prev = letzter2;       // Verbinden des ersten Knotens der hinteren Liste, mit dem letzten der neuen Liste.
    letzter2->next = anfang1;               // Letzter Zeiger der neuen/vorderen Liste, zeigt auf den ersten der alten/hinteren Liste

    // Neue Liste mit dem "Anker" verbinden [Beide Richtungen]
    anfang2->prev = head_tail;
    head_tail->next = anfang2;

    _List.head_tail->next = _List.head_tail;
    _List.head_tail->prev = _List.head_tail;

}

template <class T>
void List<T>::insertBack(T value)
{
    //ToDo
/*
    Einfuegen eines neuen Knotens am Ende der Liste
    Einen neuen Knoten mit dem Wert value wird am Ende der Liste einfügen
*/

    Node<T>* neu = new Node<T>(value, head_tail, head_tail);

    if (head_tail->next == head_tail && head_tail->prev == head_tail) // Liste Leer
    {
        head_tail->next = neu;
        head_tail->prev = neu;
    }
    else
    {
        head_tail->prev->next = neu; //Der alte letzte Knoten zeigt dann auf den neuen letzten.
        neu->prev = head_tail->prev;
        head_tail->prev = neu;
        neu->next = head_tail;

    }
    list_size++;

}

template <class T>
void List<T>::insertBack(List<T>& _List)
{
    //ToDo
/*
    Einfuegen der Liste _List am Ende einer vorhandenen Liste
    Die einzufuegenden Knoten werden uebernommen (nicht kopiert)
    Die einzufuegende Liste _List ist anschließend leer.
    Es darf keine Schleife und kein new benutzt werden.
*/

/*
    gleiches Objekt -> keine Aktion
*/

/*
    Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
    Diese Knoten (koplette Kette) werden an den Ende der Liste (this) übertragen ohne sie zu kopieren!
    Die Liste _List ist danach leer, aber vorhanden.
*/


    if (head_tail == _List.head_tail) return;

    if (_List.head_tail == _List.head_tail->next)
    {
        return;
    }

    Node<T>* ende1 = head_tail->prev;
    Node<T>* anfang2 = _List.head_tail->next;
    list_size += 1;

    ende1->next = anfang2;
    anfang2->prev = ende1;

    while (anfang2->next != _List.head_tail)
    {
        anfang2 = anfang2->next;
        list_size += 1;
    }

    anfang2->next = head_tail;
    head_tail->prev = anfang2;

    _List.head_tail->next = _List.head_tail;
    _List.head_tail->prev = _List.head_tail;

}

template <class T>
bool List<T>::getFront(T& value)
{
    //ToDo
/*
    entnehmen des Knotens am Anfang der Liste
    der Wert wird als Parameter zurueckgegeben
    der Knoten wird entnommen
    im Fehlerfall wird false zurückgegeben
*/

/*
    gleiches Objekt -> keine Aktion
*/
    if (!list_size) return false;

    /*
        Der Wert des vorderen Knotens wird rückgegeben und der Knoten gelöscht.
        Die Methode del(value) darf nicht zum löschen benutzt werden.
    */

    if (head_tail->next == head_tail && head_tail->prev == head_tail) // Liste Leer
    {
        return false;
    }
    else
    {
        Node<T>* ausgabe = head_tail->next;
        value = ausgabe->value;
        head_tail->next->next->prev = head_tail->prev;
        head_tail->next = head_tail->next->next;
        delete ausgabe;
    }
    return true;
}

template <class T>
bool List<T>::getBack(T& value)
{
    //ToDo
/*
    entnehmen des Knotens am Ende der Liste
    der Wert wird als Parameter zurueckgegeben
    der Knoten wird entnommen
    im Fehlerfall wird false zurückgegeben
*/

/*
    gleiches Objekt -> keine Aktion
*/
    if (!list_size) return false;

    /*
        Der Wert des letzten Knotens wird rückgegeben und der Knoten gelöscht.
        Die Methode del(value) darf nicht zum löschen benutzt werden.
    */
    if (head_tail->next == head_tail && head_tail->prev == head_tail) // Liste Leer
    {
        return false;
    }
    else
    {
        Node<T>* ausgabe = head_tail->prev;
        value = ausgabe->value;
        head_tail->prev->prev->next = head_tail;
        head_tail->prev = head_tail->prev->prev;
        delete ausgabe;
    }
    return true;
}

template <class T>
bool List<T>::del(T value)
{
    //ToDo
/*
    Loeschen eines gegebenen Knotens
    im Fehlerfall wird false zurückgegeben
*/

/*
    gleiches Objekt -> keine Aktion
*/
    if (!list_size) return false;

    /*
        Löschen des Knotens mit dem Wert value
    */

    Node<T>* suchen = head_tail->next;

    while (suchen->value != value && suchen != head_tail)
    {
        suchen = suchen->next;
    }

    if (suchen->value == value)
    {
        if (suchen->next == head_tail) // Falls es das letzte ist
        {
            head_tail->prev = suchen->prev;
            suchen->prev->next = head_tail;
            delete suchen;
        }
        else if (suchen->prev == head_tail) // Falls das erste ist
        {
            head_tail->next = suchen->next;
            suchen->next->prev = head_tail;
            delete suchen;
        }
        else // Falls irgendwo
        {
            suchen->prev->next = suchen->next;
            suchen->next->prev = suchen->prev;
            delete suchen;
        }
        list_size--;        // Runterzählen damit die größe am ende Stimmt
        return true;
    }
    return false;
}

template <class T>
bool List<T>::search(T value)
{
    //ToDo
/*
    suchen eines Knotens
    nicht gefunden -> Rueckgabe: false
*/

/*
    leere Liste -> keine Aktion
*/
    if (!list_size) return false;

    /*
        suchen ob ein Knoten mit dem Wert value existiert.
    */

    Node<T>* suchen = head_tail->next;

    while (suchen->value != value && suchen != head_tail)
    {
        suchen = suchen->next;
    }

    if (suchen->value == value)
    {
        return true;
    }
    return false;
}

template <class T>
bool List<T>::swap(T value1, T value2)
{
    //ToDo
/*
    Vertauschen von zwei Knoten
    Dabei werden die Zeiger der Knoten und deren Nachbarn veraendert.
    im Fehlerfall wird false zurueckgegeben
*/

/*
    Wenn Liste Leer oder weniger als 2 Knoten besitzt -> Keine Aktion
*/
    if (list_size < 2) return false;

    /*
        Vertauschen von zwei Knoten mit dem Wert value1 und dem Wert value2.
        Es duerfen nicht nur einfach die Werte in den Knoten getauscht werden!
        Die Knoten sind in der Kette umzuhaengen.
    */

    if (head_tail->next == head_tail && head_tail->prev == head_tail)
    {
        return false;
    }
    else
    {
        Node<T>* suchen1 = head_tail->next;
        Node<T>* suchen2 = head_tail->next;

        while (suchen1->value != value1 && suchen1 != head_tail)
        {
            suchen1 = suchen1->next;
        }

        while (suchen2->value != value2 && suchen2 != head_tail)
        {
            suchen2 = suchen2->next;
        }

        if (suchen1->value == value1 && suchen2->value == value2)
        {
            Node<T>* s1next = suchen1->next;
            Node<T>* s2next = suchen2->next;

            Node<T>* s1prev = suchen1->prev;
            Node<T>* s2prev = suchen2->prev;


            if (suchen1->prev == suchen2 || suchen2->next == suchen1)
            {
                suchen1->prev = s2prev;
                suchen1->next = suchen2;
                suchen2->prev = suchen1;
                suchen2->next = s1next;

                s1next->prev = suchen2;
                s2prev->next = suchen1;
            }
            else if (suchen2->prev == suchen1 || suchen1->next == suchen2)
            {
                suchen2->prev = s1prev;
                suchen2->next = suchen1;
                suchen1->prev = suchen2;
                suchen1->next = s2next;

                s2next->prev = suchen1;
                s1prev->next = suchen2;
            }
            else
            {
                suchen1->prev = s2prev;
                s2prev->next = suchen1;
                suchen1->next = s2next;
                s2next->prev = suchen1;

                suchen2->prev = s1prev;
                s1prev->next = suchen2;
                suchen2->next = s1next;
                s1next->prev = suchen2;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}

template <class T>
int List<T>::size(void)
{
    //ToDo
/*
    Rueckgabe der Anzahl der Knoten in der Liste mit O(1)
    d.h. die Liste darf NICHT traversiert werden um die Größe zu bestimmen.

    Anzahl der Knoten in der Liste zurückgeben.
    Hier richtiges Ergebnis zurückgeben
*/

    Node<T>* zaehlen = head_tail;
    int laenge = 0;

    while (zaehlen->next != head_tail)
    {
        zaehlen = zaehlen->next;
        laenge++;
    }

    return laenge;

    // Oder einfach: return list_size;
}

template <class T>
bool List<T>::test(void)
{
    // Testmethode: die Methode durchläuft die Liste vom Anfang bis zum Ende und
    // zurück Es werden dabei die Anzahl der Knoten gezahlt. Stimmt die Anzahl
    // der Knoten überein liefert die Methode true
    Node<T>* tmp = head_tail->next;
    int   i_next = 0, i_prev = 0;
    while (tmp != head_tail)
    {
        tmp = tmp->next;
        if (i_next > list_size)
            return false;
        i_next++;
    }
    if (i_next != list_size)
        return false;
    tmp = head_tail->prev;
    while (tmp != head_tail)
    {
        tmp = tmp->prev;
        if (i_prev > list_size)
            return false;
        i_prev++;
    }
    return i_prev == i_next;
}

template <class T>
List<T>& List<T>::operator=(const List<T>& _List)
{
    // in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden
    // sollen. Kopiert wird in das Objekt "this"
    if (this == &_List)
        return *this; //  !! keine Aktion notwendig
    list_form = _List.list_form;
    Node<T>* tmp_node;
    if (list_size)
    {
        Node<T>* tmp_del;
        tmp_node = head_tail->next;
        while (tmp_node !=
            head_tail) // Alle eventuell vorhandenen Knoten in this löschen
        {
            tmp_del = tmp_node;
            tmp_node = tmp_node->next;
            delete tmp_del;
        }
        list_size = 0;
        head_tail->next = head_tail;
        head_tail->prev = head_tail;
    }
    tmp_node = _List.head_tail->next; // Die Listen-Knotenwerte werden kopiert
    while (tmp_node != _List.head_tail)
    {
        insertBack(tmp_node->value);
        tmp_node = tmp_node->next;
    }
    if (_List.temp)
        delete& _List; // ist die übergebene Liste eine temporäre Liste? -> aus
                       // Operator +
    return *this;
}

template <class T>
List<T>& List<T>::operator+(const List<T>& List_Append)
{
    // Die Methode +
    // Es werden zwei Listen aneinander gehangen.
    // Dabei werden beide Ursprungslisten nicht verändert. Es entsteht eine neue
    // Ergebnisliste.
    Node<T>* tmp_node;
    List<T>* tmp;
    if (temp)
    { // this ist eine temporäre Liste und kann verändert werden
        tmp = this;
    }
    else
    {
        tmp =
            new List<T>(*this); // this ist keine temporäre Liste -> Kopie erzeugen
        tmp->temp = true;    // Merker setzten, dass es sich um eine temporäre
                             // Liste handelt
    }
    if (List_Append.list_size)
    { // anhängen der übergebenen Liste an tmp
        tmp_node = List_Append.head_tail->next;
        while (tmp_node != List_Append.head_tail)
        {
            tmp->insertBack(tmp_node->value);
            tmp_node = tmp_node->next;
        }
    }
    if (List_Append.temp)
        delete& List_Append; // wurde eine temporäre Liste übergeben, dann wird
                             // diese gelöscht
    return *tmp;
}

template <class T>
void List<T>::format(const std::string& start,
    const std::string& zwischen,
    const std::string& ende)
{
    // Setzen des Formates für die Ausgabesteuerung der Liste bei cout
    // das Format wird für den überladenen Operator << verwendet
    list_form.start = start;
    list_form.zwischen = zwischen;
    list_form.ende = ende;
}

template <typename Tf>
std::ostream& operator<<(std::ostream& stream, List<Tf> const& Liste)
{
    // Ausgabe der Liste mit cout
    stream << Liste.list_form.start;
    for (Node<Tf>* tmp = Liste.head_tail->next; tmp != Liste.head_tail;
        tmp = tmp->next)
        stream << tmp->value
        << (tmp->next == Liste.head_tail ? Liste.list_form.ende :
            Liste.list_form.zwischen);
    if (Liste.temp)
        delete& Liste; // wurde eine temporäre Liste übergeben, dann wird diese
                       // gelöscht
    return stream;
}