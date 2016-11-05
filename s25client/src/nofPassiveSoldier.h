// $Id: nofPassiveSoldier.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef NOF_PASSIVESOLDIER_H_
#define NOF_PASSIVESOLDIER_H_

#include "nofSoldier.h"

class nofAttacker;


/// Soldaten, die nur in Milit�rgeb�ude warten bzw. vom HQ dareinkommen und noch keine spezielle Funktion
/// �bernehmen
class nofPassiveSoldier : public nofSoldier
{
    private:

        /// "Heilungs-Event"
        EventManager::EventPointer healing_event;

    private:

        /// Eventhandling
        void HandleDerivedEvent(const unsigned int id);

        // informieren, wenn ...
        void GoalReached(); // das Ziel erreicht wurde

        /// wenn man gelaufen ist
        void Walked();
        /// Pr�ft die Gesundheit des Soldaten und meldet, falls erforderlich, ein Heilungs-Event an
        void Heal();


    public:

        nofPassiveSoldier(const nofSoldier& soldier);
        nofPassiveSoldier(const unsigned short x, const unsigned short y, const unsigned char player, nobBaseMilitary* const goal, nobBaseMilitary* const home, const unsigned char rank);
        nofPassiveSoldier(SerializedGameData* sgd, const unsigned obj_id);

        ~nofPassiveSoldier();

        /// Aufr�ummethoden
    protected:  void Destroy_nofPassiveSoldier();
    public:     void Destroy() { Destroy_nofPassiveSoldier(); }

        /// Serialisierungsfunktionen
    protected:  void Serialize_nofPassiveSoldier(SerializedGameData* sgd) const;
    public:     void Serialize(SerializedGameData* sgd) const { Serialize_nofPassiveSoldier(sgd); }

        GO_Type GetGOT() const { return GOT_NOF_PASSIVESOLDIER; }

        // Zeichnet den Soldaten
        void Draw(int x, int y);

        /// wenn Milit�rgeb�ude abgerissen wurde und sich der Soldat im Geb�ude befand
        void InBuildingDestroyed();
        /// Sagt einem in einem Milit�rgeb�ude sitzenden Soldaten, dass er raus nach Hause gehen soll
        void LeaveBuilding();

        /// Bef�rdert einen Soldaten
        void Upgrade();

        /// Soldat befindet sich auf dem Hinweg zum Milit�rgeb�ude und wird nich l�nger gebraucht
        void NotNeeded();
};

#endif // !NOF_PASSIVESOLDIER_H_
