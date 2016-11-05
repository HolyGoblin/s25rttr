// $Id: noTree.h 9357 2014-04-25 15:35:25Z FloSoft $
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

#ifndef NO_TREE_H_
#define NO_TREE_H_

#include "noCoordBase.h"
#include "EventManager.h"

class nofWoodcutter;

/// Stellt einen Baum dar
/*

B�ume k�nnen ausgewachsen sein oder noch wachsen in 3 Schritten, das gibt size an.
Wenn ein Baum gef�llt wird, wird er vom Holzf�ller gezeichnet.
Das Wachsen von B�umen sieht so aus:

_______________|__|_________________|_| ...
  Warten      Wachsen   Warten    Wachsen

Es wird eine l�ngere Zeit gewartet, dann w�chst der Baum, dabei wird die n�chste Stufe langsam eingeblendet.

*/
class noTree : public noCoordBase
{
        /// Der Holzf�ller ist Experte in Sachen Baum :)
        friend class nofWoodcutter;
        friend class AIPlayerJH;
        friend class AIInterface;

        /// Typ des Baumes (also welche Baumart)
        unsigned char type;
        /// Gr��e des Baumes (0-2, 3 = aufgewachsen!)
        unsigned char size;
        enum State
        {
            STATE_NOTHING, // Baum steht einfach nur rum
            STATE_GROWING_WAIT, // Baum ist noch im Wachsstadium, hat aber gerade keinen "Wachstumsschub"
            STATE_GROWING_GROW, // Baum hat gerade den Wachstumsschub
            STATE_FALLING_WAIT, // Baum wartet noch bis er umf�llt
            STATE_FALLING_FALL, // Baum f�llt gerade um
            STATE_FALLING_FALLEN // Baum ist schon umgefallen und liegt noch ne Weile da bis er abtransportiert wird
        } state;

        /// Wachsevent
        EventManager::EventPointer event;
        /// Tier-Produier-Event
        EventManager::EventPointer produce_animal_event;


        /// Produziert dieser Baum Tiere?
        bool produce_animals;
        /// Z�hlt Instanzen der B�ume (jeder so und so vielte Baum produziert Tiere)
        static unsigned INSTANCE_COUNTER;
        /// Z�hlt gezeichnete B�ume innerhalb eines Zeichenvorgangs (so und soviel Vogelgezwitscher muss dann abgespielt werden)
        static unsigned short DRAW_COUNTER;

        /// Gibt Warte- und Wachsdauer der B�ume an
        static const unsigned WAIT_LENGTH = 835;
        static const unsigned GROWING_LENGTH = 15;

    private:

        /// Vom Holzf�ller aufgerufen: Wenn der Holzf�ller anf�ngt und der Baum dann in einer bestimmten Zeit umfallen soll
        void FallSoon();
        /// Vom Holzf�ller aufgerufen: Der Holzf�ller hat seine Arbeit unterbrochen und der Baum soll doch nicht umfallen
        void DontFall();
        /// "Produziert" ein Tier
        void ProduceAnimal();

    public:

        noTree(const unsigned short x, const unsigned short y, const unsigned char type, const unsigned char size);
        noTree(SerializedGameData* sgd, const unsigned obj_id);

        ~noTree();

        /// Aufr�ummethoden
    protected:  void Destroy_noTree();
    public:     void Destroy() { Destroy_noTree(); }

        /// Serialisierungsfunktionen
    protected:  void Serialize_noTree(SerializedGameData* sgd) const;
    public:     void Serialize(SerializedGameData* sgd) const { Serialize_noTree(sgd); }

        GO_Type GetGOT() const { return GOT_TREE; }


        void Draw( int x,   int y);

        void HandleEvent(const unsigned int id);

        BlockingManner GetBM() const { return BM_TREE; }

        /// Erzeugt von ihnen selbst ein FOW Objekt als visuelle "Erinnerung" f�r den Fog of War
        FOWObject* CreateFOWObject() const;

        /// Setzt Instance-Counter auf 0
        static void ResetInstanceCounter() { INSTANCE_COUNTER = 0; }
        /// Setzt Draw-Counter auf 0
        static void ResetDrawCounter() { DRAW_COUNTER = 0; }
        /// Liest Draw-Counter aus
        static unsigned short QueryDrawCounter() { return DRAW_COUNTER; }
};


#endif
