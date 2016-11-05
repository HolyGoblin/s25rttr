// $Id: list.h 9357 2014-04-25 15:35:25Z FloSoft $
//
// Copyright (c) 2005 - 2011 Settlers Freaks (sf-team at siedler25.org)
//
// This file is part of Return To The Roots.
//
// Return To The Roots is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Return To The Roots is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Return To The Roots. If not, see <http://www.gnu.org/licenses/>.
#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#pragma once

/** @class list
 *
 *  @brief dynamische doppeltverkettete Liste
 *
 *  @example
 *  Ein einfaches Beispiel f�r die Listenklasse.
 *
 *  @code
 *  // Liste definieren
 *  list<int> IntegerList;
 *
 *  // Ein paar Werte einf�gen
 *  IntegerList.push_back(4);
 *  IntegerList.push_back(5);
 *
 *  // Liste ausgeben
 *  for(list<int>::iterator it = IntegerList.begin(); it.valid(); ++it)
 *    std::cout << (*it) << std::endl;
 *
 *  // aufr�umen (wird auch im Destruktor getan)
 *  list.clear();
 *
 *  @endcode
 *
 *  @author OLiver
 *  @author FloSoft
 */

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif


template <class T>
class list
{
    private:
        /** @class item
         *
         *  @brief private Itemklasse der Liste
         *
         *  @author OLiver
         */
        class item
        {
            public:
                /** @name item
                 *
                 *  @brief Konstruktor von @p item.
                 *
                 *  @author OLiver
                 */
                item(void) : next(NULL), prev(NULL)
                {
                }

                /** @name item
                 *
                 *  @brief Konstruktor von @p item.
                 *
                 *  @param[in] data Daten des Items
                 *  @param[in] next Zeiger auf n�chsten Datensatz
                 *  @param[in] prev Zeiger auf vorherigen Datensatz
                 *
                 *  @author OLiver
                 */
                item(const T& data, item* next, item* prev) : next(next), prev(prev), data(data)
                {
                }

                item* next; ///< Zeiger auf das n�chste Element
                item* prev; ///< Zeiger auf das vorherige Element
                T data;     ///< Datensatz
        };

    public:
        /** @class iterator
         *
         *  @brief �ffentliche Iteratorklasse der Liste
         *
         *  @author OLiver
         */
        class iterator
        {
            public:
                // sind Freunde
                friend class list;

                /** @name iterator
                 *
                 *  @brief Konstruktor von @p iterator.
                 *
                 *  @author OLiver
                 */
                iterator(list<T> *liste = NULL) : data(NULL), liste(liste)
                {
                }

                /** @name iterator
                 *
                 *  @brief Konstruktor von @p iterator.
                 *
                 *  @param[in] data Das Item auf dem iteriert wird.
                 *
                 *  @author OLiver
                 */
                iterator(item* data, list<T> *liste) : data(data), liste(liste)
                {
                }

                /** @name valid
                 *
                 *  @brief pr�ft den Iterator auf G�ltigkeit
                 *
                 *  @return liefert true bei g�ltigem Item, false bei ung�ltigem.
                 *
                 *  @author FloSoft
                 */
                bool valid(void)
                {
                    return ( data != NULL );
                }

                /** @name operator *
                 *
                 *  @brief Dereferenzierungsoperator
                 *
                 *  @return liefert eine Referenz auf @p data
                 *
                 *  @bug Wenn data invalid ist -> crash
                 *
                 *  @author OLiver
                 */
                T& operator *()
                {
                    return data->data;
                }

                /** @name operator ->
                 *
                 *  @brief Member-Selection-Operator
                 *
                 *  @return liefert einem Zeiger auf @p data (oder NULL bei invalidem data)
                 *
                 *  @author OLiver
                 */
                T* operator ->()
                {
                    // Ist unser Iterator g�ltig?
                    if(valid())
                        return &data->data;

                    // nein, NULL zur�ckgeben
                    return NULL;
                }

                /** @name operator ==
                 *
                 *  @brief Gleichheitsoperator
                 *
                 *  @param[in] it Zweiter Iterator mit dem verglichen wird
                 *
                 *  @return true bei Gleichheit, false bei Ungleichheit
                 *
                 *  @author OLiver
                 */
                bool operator ==(const iterator it)
                {
                    return (data == it.data);
                }

                /** @name operator =
                 *
                 *  @brief Zuweisungsoperator
                 *
                 *  @param[in] it Zweiter Iterator von dem zugewiesen wird
                 *
                 *  @return Referenz auf diesen Iterator
                 *
                 *  @author FloSoft
                 */
                iterator& operator =(const iterator& it)
                {
                    liste = it.liste;
                    data = it.data;

                    return *this;
                }

                /** @name operator !=
                 *
                 *  @brief Ungleichheitsoperator
                 *
                 *  @param[in] it Zweiter Iterator mit dem verglichen wird
                 *
                 *  @return true bei Ungleichheit, false bei Ungleichheit
                 *
                 *  @author OLiver
                 */
                bool operator !=(const iterator it)
                {
                    return (data != it.data);
                }

                /** @name operator ++
                 *
                 *  @brief Post-Inkrement-Operator.
                 *  setzt den Iterator auf das n�chste Item
                 *
                 *  @return alter Wert des Iterators
                 *
                 *  @author OLiver
                 *  @author FloSoft
                 */
                iterator operator ++ (int)
                {
                    // aktuellen Wert sichern
                    iterator it(data);

                    // neuen Wert setzen
                    if(valid())
                        data = data->next;
                    else if (liste)
                        data = liste->head;
                    else
                        data = NULL;

                    // Alten Wert zur�ckliefern
                    return it;
                }

                /** @name operator ++
                 *
                 *  @brief Pre-Inkrement-Operator.
                 *  setzt den Iterator auf das n�chste Item
                 *
                 *  @return neuer Wert des Iterators
                 *
                 *  @author OLiver
                 *  @author FloSoft
                 */
                iterator& operator ++ (void)
                {
                    // neuen Wert setzen
                    if(valid())
                        data = data->next;
                    else if (liste)
                        data = liste->head;
                    else
                        data = NULL;

                    // Neuen Wert zur�ckliefern
                    return *this;
                }

                /** @name operator --
                 *
                 *  @brief Post-Dekrement-Operator.
                 *  setzt den Iterator auf das vorherige Item
                 *
                 *  @return alter Wert des Iterators
                 *
                 *  @author OLiver
                 *  @author FloSoft
                 */
                iterator operator -- (int)
                {
                    // aktuellen Wert sichern
                    iterator it(data);

                    // neuen Wert setzen
                    if(valid())
                        data = data->prev;
                    else if (liste)
                        data = liste->tail;
                    else
                        data = NULL;

                    // Alten Wert zur�ckliefern
                    return it;
                }

                /** @name operator --
                 *
                 *  @brief Pre-Dekrement-Operator.
                 *  setzt den Iterator auf das vorherige Item
                 *
                 *  @return neuer Wert des Iterators
                 *
                 *  @author OLiver
                 *  @author FloSoft
                 */
                iterator& operator -- (void)
                {
                    // neuen Wert setzen
                    if(valid())
                        data = data->prev;
                    else if (liste)
                        data = liste->tail;
                    else
                        data = NULL;

                    // Neuen Wert zur�ckliefern
                    return *this;
                }

                iterator GetNext() { iterator tmp(data->next, liste); return tmp; }
                iterator GetPrev() { iterator tmp(data->prev, liste); return tmp; }
            private:
                item* data;    ///< Datensatz auf den der Iterator zeigt
                list<T> *liste; ///< Zeiger auf die Liste auf der der Iterator operiert
        };

        class const_iterator
        {
            public:
                // sind Freunde
                friend class list;


                const_iterator(const list<T> *liste = NULL) : data(NULL), liste(liste)
                {
                }

                const_iterator(const item* data, const list<T> *liste) : data(data), liste(liste)
                {
                }

                bool valid(void) const
                {
                    return ( data != NULL );
                }

                const T& operator *()
                {
                    return data->data;
                }


                const T* operator ->()
                {
                    // Ist unser Iterator g�ltig?
                    if(valid())
                        return &data->data;

                    // nein, NULL zur�ckgeben
                    return NULL;
                }


                bool operator ==(const iterator it) const
                {
                    return (data == it.data);
                }

                iterator& operator =(const iterator& it)
                {
                    liste = it.liste;
                    data = it.data;

                    return *this;
                }

                bool operator !=(const iterator it) const
                {
                    return (data != it.data);
                }

                const_iterator operator ++ (int)
                {
                    // aktuellen Wert sichern
                    const_iterator it(data);

                    // neuen Wert setzen
                    if(valid())
                        data = data->next;
                    else if (liste)
                        data = liste->head;
                    else
                        data = NULL;

                    // Alten Wert zur�ckliefern
                    return it;
                }

                const_iterator& operator ++ (void)
                {
                    // neuen Wert setzen
                    if(valid())
                        data = data->next;
                    else if (liste)
                        data = liste->head;
                    else
                        data = NULL;

                    // Neuen Wert zur�ckliefern
                    return *this;
                }

                const_iterator operator -- (int)
                {
                    // aktuellen Wert sichern
                    const_iterator it(data);

                    // neuen Wert setzen
                    if(valid())
                        data = data->prev;
                    else if (liste)
                        data = liste->tail;
                    else
                        data = NULL;

                    // Alten Wert zur�ckliefern
                    return it;
                }


                const_iterator& operator -- (void)
                {
                    // neuen Wert setzen
                    if(valid())
                        data = data->prev;
                    else if (liste)
                        data = liste->tail;
                    else
                        data = NULL;

                    // Neuen Wert zur�ckliefern
                    return *this;
                }

                const_iterator GetNext() { const_iterator tmp(data->next, liste); return tmp; }
                const_iterator GetPrev() { const_iterator tmp(data->prev, liste); return tmp; }
            private:
                const item* data;    ///< Datensatz auf den der Iterator zeigt
                const list<T> *liste; ///< Zeiger auf die Liste auf der der Iterator operiert
        };

    public:
        /** @name list
         *
         *  @brief Konstruktor der Liste
         *
         *  @author OLiver
         */
        list(void)
        {
            // initialisieren
            init();
        }

        /** @name ~list
         *
         *  @brief Destruktor der Liste
         *
         *  @author OLiver
         */
        ~list(void)
        {
            // aufr�umen
            clear();
        }

        /** @name begin
         *
         *  @return liefert die Anzahl der Datens�tze der Liste
         *
         *  @author OLiver
         *  @author FloSoft
         */
        unsigned size() const
        {
            return count;
        }

        /** @name begin
         *
         *  @return liefert einen Iterator auf den Anfang der Liste
         *
         *  @author OLiver
         *  @author FloSoft
         */
        iterator begin()
        {
            return iterator(head, this);
        }

        /** @name end
         *
         *  @return liefert einen Iterator auf das Ende der Liste
         *
         *  @author OLiver
         *  @author FloSoft
         */
        iterator end()
        {
            return iterator(tail, this);
        };

        /** @name begin
         *
         *  @return liefert einen Iterator auf den Anfang der Liste
         *
         *  @author OLiver
         *  @author FloSoft
         */
        const_iterator begin() const
        {
            return const_iterator(head, this);
        }

        /** @name end
         *
         *  @return liefert einen Readonly-Iterator auf das Ende der Liste
         *
         *  @author OLiver
         *  @author FloSoft
         */
        const_iterator end() const
        {
            return const_iterator(tail, this);
        };

        /** @name init
         *
         *  @brief Initialisiert die Liste
         *
         *  @author OLiver
         *  @author FloSoft
         */
        void init()
        {
            // Zeiger zur�cksetzen
            head = NULL;
            tail = NULL;

            // Anzahl zur�cksetzen
            count = 0;
        }

        /** @name clear
         *
         *  @brief r�umt die Liste auf
         *
         *  @author OLiver
         *  @author FloSoft
         */
        void clear()
        {
            // Alle Items l�schen
            iterator it = end();
            while(it.valid())
                erase(&it);

            // zur�cksetzen
            init();
        }

        /** @name insert
         *
         *  @brief f�gt ein Item bei @p nach it ein
         *
         *  @param[in] it   Iterator (Position) an der eingef�gt werden soll
         *  @param[in] data Daten die eingef�gt werden sollen
         *
         *  @author OLiver
         *  @author FloSoft
         */
        iterator insert(iterator it, const T& data)
        {
            // Anzahl erh�hen
            ++count;

            // sind wir am Anfang der Liste?
            if( count == 1 )
            {
                // Anzahlfehler vorbeugen
                count = 1;

                // dann neuen head erzeugen, it wird logischerweise ignoriert
                head = new item(data, NULL, NULL);

                // Alles hat ein Ende :-)
                tail = head;

                return iterator(head, this);
            }
            else if (it.valid() == false) // am Beginn einf�gen?
            {
                // neues Item erzeugen
                head->prev = new item(data, head, NULL);

                // und Head korrigieren
                head = head->prev;

                return iterator(head, this);
            }
            else
            {
                // vorherige Position sichern
                item* next = it.data->next;

                // Neues Item einh�ngen
                it.data->next = new item(data, next, it.data );

                // ggf Ende neu setzen
                if( it.data == tail )
                    tail = it.data->next;
                else
                    next->prev = it.data->next;

                return iterator(it.data->next, this);

            }


        }

        /** @name push_back
         *
         *  @brief f�gt ein Item am Ende ein
         *
         *  @param[in] data Daten die angef�gt werden sollen
         *
         *  @author OLiver
         *  @author FloSoft
         */
        iterator push_back(const T& data)
        {
            // Nach dem Ende einf�gen
            return insert(end(), data);
        }

        /** @name push_front
         *
         *  @brief f�gt ein Item am Anfang ein
         *
         *  @param[in] data Daten die eingef�gt werden sollen
         *
         *  @author OLiver
         *  @author FloSoft
         */
        iterator push_front(const T& data)
        {
            // Als neuen Head einf�gen
            return insert( iterator(NULL), data);
        }

        /** @name erase
         *
         *  @brief entfernt das Item auf das it zeigt
         *
         *  @param[in] it Iterator (Position) an der gel�scht werden soll
         *
         *  @author OLiver
         *  @author FloSoft
         */
        void erase(iterator it)
        {
            // nur validen Iterator l�schen
            if(it.valid() == false)
                return;

            // vorherige und nachfolgendes Item sichern
            item* prev = it.data->prev;
            item* next = it.data->next;

            // ggf neuen Head setzen
            if(it.data == head)
                head = next;

            // ggf neuen Tail setzen
            if(it.data == tail)
                tail = prev;

            // Item l�schen
            delete it.data;

            // neu verketten
            if(prev)
                prev->next = next;

            // neu verketten
            if(next)
                next->prev = prev;

            // Anzahl verringern
            --count;
        }

        /** @name erase
         *
         *  @brief l�scht ein bestimmtes Element aus der Liste
         *
         *  @param[in] obj Objekt welches entfernt werden soll
         *
         *  @author OLiver
         *  @author FloSoft
         */
        void erase(const T& obj)
        {
            // Objekt suchen
            iterator it = search(obj);

            // und ggf. l�schen
            if(it.valid())
                erase(it);
        }

        /** @name erase
         *
         *  @brief l�scht ein bestimmtes Element aus der Liste und setzt den iterator auf das vorherige Item
         *
         *  @param[in] it Iterator (Position) an der gel�scht werden soll
         *
         *  @author OLiver
         *  @author FloSoft
         */
        void erase(iterator* it)
        {
            if(it == NULL)
                return;
            if(it->valid() == false)
                return;

            // vorheriges Item sichern
            item* prev = it->data->prev;


            // Item l�schen
            erase( (*it) );

            // und vorheriges Zuweisen (oder head)
            //if(prev)
            it->data = prev;
            /*else
                it->data = head;*/
        }

        /** @name pop_back
         *
         *  @brief entfernt ein Item am Ende
         *
         *  @author OLiver
         *  @author FloSoft
         */
        void pop_back()
        {
            // Item an Ende entfernen
            erase( end() );
        }

        /** @name pop_front
         *
         *  @brief entfernt ein Item am Anfang
         *
         *  @author OLiver
         *  @author FloSoft
         */
        void pop_front()
        {
            // Item am Anfang entfernen
            erase( begin() );
        }

        /** @name search
         *
         *  @brief ein bestimmtes Item suchen
         *
         *  @param[in]
         *
         *  @return Einen Iterator auf das Item, oder einen NULL-Iterator
         *
         *  @author OLiver
         *  @author FloSoft
         */
        iterator search(const T& data)
        {
            for(iterator it = begin(); it.valid(); ++it)
            {
                // Ist der Iterator unser Item?
                if( (*it) == data)
                    return it;
            }

            // Item nicht gefunden :-(
            return iterator(NULL);
        }

        /** @name insert_ordered
         *
         *  @brief f�gt ein Item bei sortiert ein ein
         *
         *  @param[in] data Daten die eingef�gt werden sollen
         *
         *  @author OLiver
         *  @author FloSoft
         */
        iterator insert_ordered(const T& data)
        {
            // Suchen wir die Position
            for(iterator it = end(); it.valid(); --it)
            {
                // Ist das einzuf�gende Item gr��er als das aktuelle?
                if( (*it) <= data)
                {
                    // ja dann hier einf�gen
                    return insert(it, data);
                }
            }

            // Ansonsten ganz nach vorn
            return push_front(data);
        }

        /** @name operator[]
         *
         *  @brief Array-Access-Operator.
         *  liefert das @p index-te Element als Iterator
         *
         *  @param[in] index Nummer des Items das geholt werden soll
         *
         *  @return Iterator an Stelle @p index in der Liste
         *
         *  @author FloSoft
         */
        iterator operator[] (int index)
        {
            if((unsigned int)index < count)
            {
                iterator it = begin();

                unsigned int i = -1;
                while(++i < (unsigned int)index)
                    ++it;
                return it;
            }
            return iterator(NULL);
        }

    private:
        item* head;         ///< Item f�r den Kopf der Liste
        item* tail;         ///< Item f�r das Ende der Liste
        unsigned int count; ///< Anzahl der Datens�tze
};

#endif // !LIST_H_INCLUDED
