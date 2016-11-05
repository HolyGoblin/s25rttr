// $Id: RoadSegment.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef ROADSEGMENT_H_INCLUDED
#define ROADSEGMENT_H_INCLUDED

#pragma once

#include "GameObject.h"

class nofCarrier;
class noRoadNode;
class noFlag;
class noFigure;

class RoadSegment : public GameObject
{
    public:
        enum RoadType
        {
            RT_NORMAL,  ///< Normale Stra�e bzw. Bergstra�e
            RT_DONKEY,  ///< Eselstra�e
            RT_BOAT     ///< Wasserstra�e
        };

    public:
        RoadSegment(const RoadType rt, noRoadNode* const f1, noRoadNode* const f2, const std::vector<unsigned char>& route);
        RoadSegment(SerializedGameData* sgd, const unsigned obj_id);

        /// zerst�rt das Objekt.
        void Destroy(void) { Destroy_RoadSegment(); }
        /// serialisiert das Objekt.
        void Serialize(SerializedGameData* sgd) const { Serialize_RoadSegment(sgd); }
        /// liefert den GO-Type.
        inline GO_Type GetGOT() const { return GOT_ROADSEGMENT; }
        /// Gibt die ID (0 oder 1) eines RoadNodes dieser Stra�e zur�ck (die Flagge muss zu dieser Stra�e geh�ren, sonst kommt M�ll raus!!)
        inline bool GetNodeID(const noRoadNode* rn) { return (rn == f2); }
        /// Gibt Stra�en-Typ zur�ck
        inline RoadType GetRoadType() const { return rt; }
        /// Gibt die L�nge der Sta�e zur�ck
        inline unsigned GetLength() const { return route.size(); }
        /// gibt Flagge 1 zur�ck
        inline noRoadNode* GetF1() const { return f1; }
        /// setzt Flagge 1 auf o
        inline void SetF1(noRoadNode* o) { f1 = o; }
        /// gibt Flagge 2 zur�ck
        inline noRoadNode* GetF2() const { return f2; }
        /// setzt Flagge 2 auf o
        inline void SetF2(noRoadNode* o) { f2 = o; }
        /// gibt die Route nr zur�ck
        inline unsigned char GetRoute(unsigned short nr) const { return route.at(nr); }
        /// setzt die Route nr auf r
        inline void SetRoute(unsigned short nr, unsigned char r) { route[nr] = r; }
        /// gibt den Carrier nr zur�ck
        inline nofCarrier* getCarrier(unsigned char nr) const { return carrier[nr]; }
        /// setzt den Carrier nr auf c
        inline void setCarrier(unsigned char nr, nofCarrier* c) { carrier[nr] = c; }
        /// haben wir den Carrier "nr"?
        inline bool hasCarrier(unsigned char nr) const { return (carrier[nr] != NULL); }
        /// Braucht die Stra�e einen Esel? Nur wenn sie auch einen Tr�ger schon hat!
        inline bool NeedDonkey() const { return (rt == RT_DONKEY && carrier[0] && !carrier[1]); }
        /// Hat einen Esel als Arbeiter dazubekommen.
        inline void GotDonkey(nofCarrier* donkey) { assert(!carrier[1]); carrier[1] = donkey; }

        /// haben wir �berhaupt Carrier?
        inline bool isOccupied() const
        {
            return((carrier[0]) || (carrier[1]));
        }

        inline unsigned char GetDir(const bool dir, const unsigned int id) const
        {
            if(dir)
                return (route[route.size() - id - 1] + 3) % 6;
            else
                return route[id];
        }

        /// zerteilt die Stra�e in 2 Teile.
        void SplitRoad(noFlag* splitflag);
        /// �berpr�ft ob es an den Flaggen noch Waren zu tragen gibt f�r den Tr�ger.
        bool AreWareJobs(const bool flag, unsigned int carrier_type, const bool take_ware_immediately) const;
        /// Eine Ware sagt Bescheid, dass sie �ber dem Weg getragen werden will.
        void AddWareJob(const noRoadNode* rn);
        /// Eine Ware will nicht mehr bef�rdert werden.
        void WareJobRemoved(const noFigure* const exception);
        /// Baut die Stra�e zu einer Eselstra�e aus.
        void UpgradeDonkeyRoad();
        /// Soll versuchen einen Esel zu bekommen.
        void TryGetDonkey();
        /// Ein Tr�ger muss k�ndigen, aus welchen Gr�nden auch immer.
        void CarrierAbrogated(nofCarrier* carrier);
        /// given a flag returns the other end location
        noFlag* GetOtherFlag(const noFlag* flag);
        /// given a flag returns last direction of the route towards the other flag
        unsigned char GetOtherFlagDir(const noFlag* flag);

    protected:
        /// zerst�rt das Objekt.
        void Destroy_RoadSegment(void);
        /// serialisiert das Objekt.
        void Serialize_RoadSegment(SerializedGameData* sgd) const;

    private:
        /// Stra�entyp
        RoadType rt;
        /// die 2 Roadnodes, die den Weg eingrenzen
        noRoadNode* f1, *f2;
        /// Beschreibung des Weges, ist length gro� und liegt als Beschreibung der einzelnen Richtungen vor (von f1 zu f2)
        std::vector<unsigned char> route;
        /// Tr�ger (und ggf. Esel), der auf diesem Weg arbeitet
        nofCarrier* carrier[2];
};

#endif // !ROADSEGMENT_H_INCLUDED
