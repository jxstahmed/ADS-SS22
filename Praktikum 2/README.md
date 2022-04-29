# Ablauf:

> Für beide Aufgaben die Testcases vorzeigen.

> Das wichtigste in beiden Codes zeigen und erklären.

> Fragen für beide Aufgaben beantworten [siehe unten].

# Aufgabe 1:

> Wie arbeitet die Methode addNode? -> 3 Fälle (Wenn leer, Wenn Voll, Wenn noch platz aber nicht leer), NodeOrderID berechnen.

> Wie geht die Methode addNode vor bei vollem Ring? -> Man löscht das älteste [OldAge = 5 (anker->next->next)].

> Wie verändern wir die OldAge Attribute wenn wir einen neuen Einfügen? -> Einfach durch den Ring und aktuellest Alter + 1 (Außer der neue Knoten, weil der hat schon 0)

> Wo startet wir genau beim Ring? -> Beim anker [wenn leer = zeigt auf Ringpuffer]

> Wie sind die RingeNodes mit einander verbunden? -> Jeweils durch den Next pointer [anker->0->5->4->3->2->1->0 (Dann wieder im Kreis durch)]

# Aufgabe 2:

> Search Methode vorführen -> Findet er doppelte Einträge? [Zeigt er alle an]

> Knoten Einfügen und dann die Datei einfügen -> Ist der erste Knoten den wir manuell eingefügt haben noch in der Liste drinnen.

> Wo kann man Rinpuffer im echten leben anwenden -> Flugzeugschreiber [Nur das wichtigste wird immer gespeichert]

> Wieso geht currentNodeChronolicalID nicht als als zuweisung im Baum -> Weil dann alles nur nach rechts geht [artet in eine verkettete Liste aus]

> Was passiert wenn NodeOrderID doppelt ist? -> Eine richtige Zuweisung des knoten mit doppelter NodeOrderID wird nicht funktionieren (Programm weiß nicht richtig ob links oder rechts)
