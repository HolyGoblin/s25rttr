// $Id: noFigure.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef NOFIGURE_H_INCLUDED
#define NOFIGURE_H_INCLUDED

#include "noMovable.h"
#include "GlobalGameSettings.h"
#include "MapConsts.h"
#include "VideoDriverWrapper.h"

class RoadSegment;
class noRoadNode;
class glArchivItem_Bob;

// Enumforwarddeklaration bei VC nutzen
#ifdef _MSC_VER
enum Job;
#else
#include "GameConsts.h"
#endif

enum FigureState
{
    FS_GOTOGOAL = 0,
    FS_GOHOME,
    FS_WANDER,
    FS_JOB
};

class glSmartBitmap;

// Stellt einen Menschen dar
class noFigure : public noMovable
{
    protected:
        FigureState fs; // aktueller Status
        Job job; // Beruf(sart)
        unsigned char player;

        // Stra�enlaufzeug: (nur genutzt beim Laufen im Stra�ennetz!)

        const RoadSegment* cur_rs;  /// Stra�e, auf der er gerade l�uft
        unsigned short rs_pos; /// Position auf der aktuellen Stra�e (Wegst�ck)
        bool rs_dir; /// von welcher Seite er auf die Stra�e l�uft

        // Befindet sich die Figur gerade auf einem Schiff?
        bool on_ship;

        /// zu welcher Flagge er laufen soll
        noRoadNode* goal;
        /// ist der Platz davor besetzt (z.B. durch Kampf), muss er warten (Stehen bleiben), sowohl genau auf einem
        /// Wegpunkt, also auch beliebig dazwischen!
        bool waiting_for_free_node;

        // nur bei FS_WANDER von Bedeutung:
        /// Restlicher Weg f�r das Rumirren (0xFFFF wenn schon auf dem Weg zu einer Flagge!)
        unsigned short wander_way;
        /// Wieviel (erfolglose) Rumirr-Flaggensuch-Versuche hat es schon gegeben (nach bestimmter Zahl Figur sterben lassen)
        unsigned short wander_tryings;
        /// Falls eine Flagge gefunden wurde, Zielpunkt, der Flagge
        unsigned short flag_x, flag_y;
        /// Obj-ID der (damaligen) Flagge, (evtl wurde sie zwischendurch abgerissen)
        unsigned flag_obj_id;
        /// Wenn der Typ aus einem Lagerhaus geflohen ist, Obj-ID des abbrennenden Lagerhauses zur
        /// Kommunikation mit anderen Kollegen, die ebenfalls fl�chten --> "Kollektivwegfindung", ansonsten ist das 0xFFFFFFFF
        unsigned burned_wh_id;


        static const RoadSegment emulated_wanderroad;

        /// Speichert letzten Animationsframes (zum Abspielen von Sounds)
        unsigned last_id;

    private:

        /// abgeleitete Klassen informieren, wenn ...
        virtual void GoalReached() = 0; // das Ziel erreicht wurde
        virtual void Walked() = 0; // man gelaufen ist

        /// F�r alle restlichen Events, die nicht von noFigure behandelt werden
        virtual void HandleDerivedEvent(const unsigned int id) = 0;

        /// Gibt den Sichtradius dieser Figur zur�ck (0, falls nicht-sp�hend)
        virtual unsigned GetVisualRange() const;

        /// Unterfunktion von Wander --> zur Flagge irren
        void WanderToFlag();
        /// Unterfunktion von Wander --> zur Flagge irren
        //void WanderToFlagFailedTrade();

        /// Sichtbarkeiten berechnen f�r Figuren mit Sichtradius (Soldaten, Erkunder) vor dem Laufen
        void CalcVisibilities(const MapCoord x, const MapCoord y);

    protected:

        /// In aktueller Richtung ein St�ck zurcklegen
        void WalkFigure();
        /// Schatten der Figur malen
        void DrawShadow(const int x, const int y, const unsigned char anistep, unsigned char dir);

        /// Herumirren
        void Wander();
        /// Herumirren after failed traderoute
        void WanderFailedTrade();

        virtual void AbrogateWorkplace() = 0;

    public:

        /// Konstruktor f�r Figuren, die auf dem Wegenetz starten
        noFigure(const Job job, const unsigned short x, const unsigned short y, const unsigned char player, noRoadNode* const goal);
        /// Konstruktor f�r Figuren, die im Job-Modus starten
        noFigure(const Job job, const unsigned short x, const unsigned short y, const unsigned char player);

        noFigure(SerializedGameData* sgd, const unsigned obj_id);


        /// Aufr�ummethoden
    protected:  void Destroy_noFigure();
    public:     void Destroy() { Destroy_noFigure(); }

        /// Serialisierungsfunktionen
    protected:  void Serialize_noFigure(SerializedGameData* sgd) const;
    public:     void Serialize(SerializedGameData* sgd) const { Serialize_noFigure(sgd); }

        void HandleEvent(const unsigned int id);

        /// Ziel setzen
        void SetGoalToNULL() { goal = NULL; }
        /// Ziel zur�ckgeben
        noRoadNode* GetGoal() const { return goal; }

        /// Getter
        bool GetRoadDir() const { return rs_dir; }
        const RoadSegment* GetCurrentRoad() const { return cur_rs; }

        /// Tut was, nachdem er rausgehen soll
        void ActAtFirst();
        /// Legt die Anfangsdaten f�r das Laufen auf Wegen fest
        void InitializeRoadWalking(const RoadSegment* const road, const unsigned short rs_pos, const bool rs_dir);
        /// Gibt Job-Typ zur�ck
        Job GetJobType() const { return job; }
        /// Zeichnet eine Figur aus "carrier.bob" beim Laufen.
        void DrawWalkingBobCarrier(int x, int y, unsigned int ware, bool fat);
        /// Zeichnet eine Figur aus "jobs.bob", wenn sie l�uft.
        void DrawWalkingBobJobs(int x, int y, unsigned int id);
        /// Zeichnet standardm��ig die Figur, wenn sie l�uft
        void DrawWalking(int x, int y, glArchivItem_Bob* file, unsigned int item, bool fat, bool waitingsoldier = false);
        /// Zeichnet standardm��ig die Figur, wenn sie l�uft aus einem bestimmten normalen LST Archiv
        void DrawWalking(int x, int y, const char* const file, unsigned int id);
        /// Zeichnet standardm��ig die Figur, wenn sie l�uft, nimmt automatisch richtige Job-ID/Datei
        void DrawWalking(int x, int y);
        /// Interpoliert die Positon zwischen zwei Knotenpunkten
        bool CalcFigurRelative(int& x, int& y);
        /// Anfangen zu laufen (Event anmelden, T�r aufmachen ggf)
        void StartWalking(const unsigned char dir);
        /// Anfangen zu laufen (Event anmelden, T�r aufmachen ggf)
        //void StartWalkingFailedTrade(const unsigned char dir);
        /// Umherirren starten (frei rumlaufen)
        void StartWandering(const unsigned burned_wh_id = 0xFFFFFFFF);
        /// Umherirren starten (frei rumlaufen - nach fehlgeschlagener handelsroute)
        //void StartWanderingFailedTrade(const unsigned burned_wh_id = 0xFFFFFFFF);
        /// Auf Stra�en(!) nach Hause laufen
        void GoHome(noRoadNode* goal = NULL);
        /// Aktuellen Weg, auf dem er l�uft, fr ung�ltig erkl�ren
        void CutCurrentRoad() { cur_rs = 0; }
        /// Auf Stra�en zur Zielflagge laufen
        void WalkToGoal();
        /// Auf Stra�en zur Zielflagge laufen
        //void WalkToGoalFailedTrade();
        /// Gibt die Stra�e zur�ck, auf der man gerade l�uft
        const RoadSegment* GetCurrentRoad() { return cur_rs; }
        /// Wird aufgerufen, wenn die Stra�e unter der Figur geteilt wurde, setzt vorraus, dass die Figur auf der geteilten Stra�e l�uft!
        void CorrectSplitData(const RoadSegment* const rs2);
        /// Wird aufgerufen, wenn die Stra�e unter der Figur geteilt wurde (f�r abgeleitete Klassen)
        virtual void CorrectSplitData_Derived();
        /// L�sst die Figur sterben (l�st sich auf und hinterl�sst ggf. Leiche)
        void Die();
        /// L�sst die Figur sterben (l�st sich auf und hinterl�sst ggf. Leiche) - does not reduce good counts because for trade routes they have been reduced already.
        void DieFailedTrade();
        /// Mitglied von nem Lagerhaus(Lagerhausarbeiter, die die Tr�ger-Best�nde nicht beeinflussen?)
        /// Kann au�er bei WarehouseWorker die Default-Definition gelassen werden
        virtual bool MemberOfWarehouse() const { return false; }

        /// Ein Punkt neben der Figur wurde freigegeben --> wenn sie deswegen angehalten ist, kann sie weiterlaufen
        void NodeFreed(const unsigned short x, const unsigned short y);

        /// Wartet sie auf einen freien Platz?
        bool IsWaitingForFreeNode() const { return waiting_for_free_node; }
        /// Stoppt, wenn er auf diesen Punkt zul�uft
        void StopIfNecessary(const unsigned short x, const unsigned short y);


        unsigned char GetDir() const { return dir; }

        unsigned char GetPlayer() const { return player; }

        /// Macht die Figur Job-Arbeiten?
        bool DoJobWorks() const { return (fs == FS_JOB); }

        void Abrogate(); // beim Arbeitsplatz "k�ndigen" soll, man das Laufen zum Ziel unterbrechen muss (warum auch immer)

        /// Informiert die Figur, dass f�r sie eine Schiffsreise beginnt
        void StartShipJourney(const Point<MapCoord> goal);
        /// Informiert die Figur, wenn Kreuzfahrt beendet ist
        void ShipJourneyEnded();
        /// Gibt zur�ck, ob die Figur kein Ziel mehr hat und damit nach einer Schifffahrt im
        /// Lagerhaus interniert werden muss
        bool HasNoGoal() const { return (goal ==  NULL); }
        /// Gibt zur�ck, ob die Figur auf Stra�en l�uft zu ihrem Arbeitsplatz o.�.
        bool IsWalkingOnRoad() const
        {
            // Nur Tr�ger arbeiten richtig auf Stra�en
            if(fs == FS_JOB) return (GetGOT() == GOT_NOF_CARRIER);
            else if(fs == FS_GOHOME || fs == FS_GOTOGOAL) return true;
            else return false;
        }

        /// Examines the route (maybe harbor, road destroyed?) before start shipping
        /// Returns (maybe new) destination harbor ((0,0) if he doesn't go by ship)
        Point<MapCoord> ExamineRouteBeforeShipping();
};


// Erstellt Job anhand der job-id
noFigure* CreateJob(const Job job_id, const unsigned short x, const unsigned short y, const unsigned char player, noRoadNode* const goal);


#endif
