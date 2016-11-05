// $Id: Minimap.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef MINIMAP_H_
#define MINIMAP_H_

struct MapNode;
class GameWorldViewer;

#include "Loader.h"
#include "glArchivItem_Bitmap_Direct.h"
#include "MapConsts.h"
#include <vector>


class Minimap
{
        ///// Breite und H�he (Pixel) der Bounding Box, in die die Map zentriert wird
        //unsigned short width,height;
        ///// Breite und H�he (Pixel) der angezeigten Map
        //unsigned short width_show, height_show;
    protected:
        /// Breite und H�he der Map (in Knoten)
        unsigned short map_width, map_height;

        /// Textur f�r die Map
        glArchivItem_Bitmap_Direct map;

        //struct PlayerColor
        //{
        //  PlayerColor() { color = 0; }
        //  unsigned color;
        //} players_color[MAX_PLAYERS];

    protected:

        /// Zus�tzliche Dinge, die die einzelnen Maps vor dem Zeichenvorgang zu tun haben
        virtual void BeforeDrawing();
        /// Variiert die �bergebene Farbe zuf�llig in der Helligkeit
        unsigned VaryBrightness(const unsigned color, const int range) const;

    public:

        Minimap() { };
        Minimap(const unsigned short map_width, const unsigned short map_height);
        virtual ~Minimap() {}

        void SetMap(glArchivItem_Map* s2map);

        /// Zeichnet die Minimap zentriert in die entsprechende Bounding-Box
        /// (x und y bezieht sich auf obere linke Ecke der Bounding Box)
        void Draw(const unsigned short x, const unsigned short y, const unsigned short width, const unsigned short height);

        /// Gibt Gr��e der Map zur�ck
        unsigned short GetMapWidth() const { return map_width; }
        unsigned short GetMapHeight() const { return map_height; }

    protected:

        /// Erstellt die Textur
        void CreateMapTexture(const void* param);

        /// Berechnet einen bestimmten Punkt neu
        void RecalcNode(const void* param, const MapCoord x, const MapCoord y);
        /// Berechnet die Farbe eines Pixels
        virtual unsigned CalcPixelColor(const void* param, const MapCoord x, const MapCoord y, const unsigned t) = 0;
};

class PreviewMinimap : public Minimap
{
    public:
        PreviewMinimap(glArchivItem_Map* s2map);

    protected:

        /// Berechnet die Farbe f�r einen bestimmten Pixel der Minimap (t = Terrain1 oder 2)
        unsigned CalcPixelColor(const void* param, const MapCoord x, const MapCoord y, const unsigned t);
};

class IngameMinimap : public Minimap
{
        /// Referenz auf den GameWorldViewer
        const GameWorldViewer& gwv;
        /// Speichert die einzelnen Ver�nderungen eines jeden Mappunktes, damit nicht unn�tigerweise
        /// in einem GF mehrmals der Mappunkt ver�ndert wird
        std::vector<bool> nodes_updated;
        /// Liste mit allen Punkten, die ge�ndert werden m�ssen
        struct Node { MapCoord x, y; };
        list<Node> nodes_updated_list;


        /// F�r jeden einzelnen Knoten speichern, welches Objekt hier dominiert, also wessen Pixel angezeigt wird
        enum DrawnObject
        {
            DO_INVALID = 0,
            DO_INVISIBLE, /// im im vollst�ndigem Dunklen
            DO_TERRAIN, /// Nur Terrain oder Baum und Granit ohne irgendwas
            DO_PLAYER, /// Nur Terrain oder Baum und Granit mit Spielerterritorium dazu
            DO_BUILDING, /// Geb�ude
            DO_ROAD /// Stra�e
        };

        std::vector<DrawnObject> dos;

        /// Einzelne Dinge anzeigen oder nicht anzeigen
        bool territory; /// L�nder der Spieler
        bool houses; /// H�user
        bool roads; /// Stra�en

    public:
        IngameMinimap(const GameWorldViewer& gwv);


        /// Merkt, vor dass ein bestimmter Punkt aktualisiert werden soll
        void UpdateNode(const MapCoord x, const MapCoord y);

        /// Updatet die gesamte Minimap
        void UpdateAll();



        /// Die einzelnen Dinge umschalten
        void ToggleTerritory();
        void ToggleHouses();
        void ToggleRoads();

    protected:

        /// Berechnet die Farbe f�r einen bestimmten Pixel der Minimap (t = Terrain1 oder 2)
        unsigned CalcPixelColor(const void* param, const MapCoord x, const MapCoord y, const unsigned t);
        /// Berechnet f�r einen bestimmten Punkt und ein Dreieck die normale Terrainfarbe
        unsigned CalcTerrainColor(const MapCoord x, const MapCoord y, const unsigned t);
        /// Pr�ft ob an einer Stelle eine Stra�e gezeichnet werden muss
        bool IsRoad(const MapCoord x, const MapCoord y, const Visibility visibility);
        /// Berechnet Spielerfarbe mit in eine gegebene Farbe mit ein (player muss mit +1 gegeben sein!)
        unsigned CombineWithPlayerColor(const unsigned color, const unsigned char player) const;
        /// Zus�tzliche Dinge, die die einzelnen Maps vor dem Zeichenvorgang zu tun haben
        /// in dem Falle: Karte aktualisieren
        void BeforeDrawing();
        /// Alle Punkte Updaten, bei denen das DrawnObject gleich dem �bergebenen drawn_object ist
        void UpdateAll(const DrawnObject drawn_object);
};



#endif

