2010.01.17                    RETURN TO THE ROOTS                          0.7.2
--------------------------------------------------------------------------------

A. Allgemeine Hinweise
B. Installation
   1. Windows
   2. Linux
C. Spiel
   1. Erstellen eines Spiels
   2. Multiplayer-Spiele
   3. Replays
   4. Optionen
D. Abst�rze und Fehler
E. �bersicht: Updates und �nderungen

--------------------------------------------------------------------------------

A. Allgemeine Hinweise

   Das Spiel ben�tigt eine OpenGL-f�hige Grafikkarte mit sch�tzungsweise
   mindestens 64 MiB Grafikspeicher. Ein Prozessor mit 800 MHz reicht aus.

   Weiterhin ben�tigt man eine installierte "Siedler 2 Gold-Edition" oder die
   Originalversion + Missions-CD.

--------------------------------------------------------------------------------

B. Installation

   1. Windows

      Windows 95/98/ME/Vista ist nicht offiziell unterst�tzt. Vista sollte
      aber eigentlich funktionieren.

      a) Zip-Archive
         Zum Spielen sucht man die Verzeichnisse "DATA" und "GFX" im
         Original "Die Siedler 2 Gold" Spiel (oder S2 + Mission CD) und kopiert
         diese in das Nightly-Verzeichnis (so dass s25client.exe sich auf 
         der selben Ebene wie S2.EXE befindet).

         Darin kann man dann s25client.exe zum Spielen von Siedler II.5 RTTR
         ausf�hren.
         
         (In Nightlies kann man mit RTTR.BAT updaten.)

      b) Setup
         Setup ausf�hren und als Installationsverzeichnis die installierte
         "Siedler 2 Gold-Edition" ausw�hlen.
         Alternativ kann man nat�rlich nacht�glich den Inhalt der
         Gold-Edition in den Installationsordner von S25rttr kopieren.

         Das Spiel kann man dann bequem mit der installierten
         Desktopverkn�pfung starten.

      Es werden KEINE originalen Spieldateien ver�ndert. Man kann
      weiterhin das Original ohne Beeintr�chtigung spielen.
      
   -------------------------------------------------------------------------

   2. Linux

      Zun�chst ben�tigt man folgende Pakete
      (ggf �ber Paketmanager/per Hand installieren):

      libsndfile libsamplerate libsdl1.2 libsdl-mixer1.2 gettext timidity

      Weiterhin sollte man sicherstellen, dass DirectRendering funktioniert:

      glxinfo | grep direct

      Wenn die Ausgabe "direct rendering: Yes" kommt, ist alles in Ordnung,
      ansonsten kann es sein, dass man eine miese Spielperformance hat.

      Die eigentliche Installation:

      z.B. nach /opt/s25rttr entpacken:

      mkdir -p /opt/s25rttr
      cd /opt/s25rttr
      tar -jxvf s25rttr_???.tar.bz2

      Nun muss man entweder nur noch die original "Siedler 2"-Installation
      nach /opt/s25rttr/share/s25rttr/S2

      kopieren, oder einen Symlink dorthin anlegen.

      Starten kann man das Ganze dann mit

      /opt/s25rttr/bin/rttr.sh
      
      (Nightly Versionen updaten sich selber. Wenn man rttr.sh mit der
      Option noupdate startet, wird kein Update durchgef�hrt.)

--------------------------------------------------------------------------------

C. Spiel

   1. Erstellen eines Spiels

      Einen richtigen Einzelspielermodus gibt es in dem Sinne noch nicht, man
      kann aber trotzdem folgenderma�en alleine im Multiplayermodus siedeln:

      1. Im Hauptmen� auf Mehrspieler gehen
      2. Direkte IP
      3. Spiel erstellen
      4. Im folgenden Fenster einen Namen f�r das Spiel eingeben (Passwort
         kann weggelassen werden).
      5. Im Kartenauswahl-Fenster kann oben eine Kategorie ausgew�hlt
         werden, �hnlich wie im Original.
         Alternativ kann unten �ber "Spiel laden" ein Spielstand geladen
         werden.
      6. Nach der Auswahl der Karte und einem Klick auf "Weiter" gelangt man
         ins Host-Men�, wo im oberen Teil die einzelnen Spieler samt ihrer
         Eigenschaften aufgelistet sind.
         Spielziel, Aufkl�rung und Teams sperren sind bisher noch ohne
         Bedeutung.
         Achtung: Um das Spiel starten zu k�nnen, m�ssen entweder alle Pl�tze
         mit menschlichen oder KI-Spielern besetzt werden, oder die Slots
         m�ssen geschlossen werden (mit Klick auf die Buttons unter
         "Spielername").

         Die KI-Spieler sind zur Zeit noch nicht lebendig.

   2. Multiplayer-Spiele

      a) Direktes Spielen
         Die Erstellung eines Multiplayerspiels erfolgt genauso wie bei 1. Die
         weiteren Spieler gehen bei "Direkte IP" unter "Spiel beitreten" und
         geben die IP oder den Hostnamen des Spielerstellers (Host) ein.

      b) Spielen �ber integrierte Lobby
         �ber die eingebaute Lobby kann man vorhandene Spiele einsehen,
         diese er�ffnen und auch beitreten. Weiterhin kann man sich hier
         mit anderen Spielern direkt unterhalten.

         Der Funktionsumfang der Lobby ist momentan noch sehr beschr�nkt
         und es kann zeitweise zu Datenbank-Problemen kommen.
         Ein Punktesystem ist vorgesehen, aber noch nicht implementiert.

         Alle eingegebenen Daten werden nicht weitergegeben und dienen rein
         zur Identifikation des Spielers. Die zur Registrierung notwendige
         Emailadresse ist momentan nur ggf. zum Zusenden eines neuen
         Passworts gedacht und ist nicht �ffentlich einsehbar.

      F�r das Spiel wird Port 3665 (TCP) genutzt. Dieser muss, falls man selbst
      das Spiel er�ffnen m�chte, u.a. bei Verwendung eines Routers, einer
      Firewall usw. freigegeben werden!
      Router nennen diese Einstellung "Virtual Server" oder einfach nur
      "Port Forwarding". Dort ist dann Port 3665 vom Typ TCP auf die interne IP
      des Spiel-PCs weiterzuleiten.

      Die Schneckensymbole im oberen Teil stehen f�r Lags der jeweiligen
      Spieler.

      Wenn der Host das Spiel verl�sst, k�nnen die �brigen Spieler noch nicht
      das Spiel weiter fortf�hren.

      Es sind sowohl Spiele �ber das Internet als auch �ber LAN m�glich, wenn
      die jeweilige IP bekannt ist.

      Das �bertragen der Karte geschieht immer automatisch (auch wenn die
      Spielteilnehmer die Karte des Hosts schon besitzen).

      Dr�cken der Taste "P" pausiert das Spiel (dies kann nur der Host tun),
      weiteres Dr�cken von "P" l�sst das spiel fortf�hren.

      Zum Chatten muss man "Enter" dr�cken, dann kommt ein Chatfenster.

   3. Replays

      Replays sind Aufzeichnungen von gespielten Partien. Sie k�nnen unter
      "Einzelspieler", "Replay abspielen" angesehen werden.

      Mit den Tasten [+] und [-] kann die Geschwindigkeit erh�ht bzw.
      verringert werden. Mit der Taste "J" ist es m�glich, Abschnitte im
      Replay zu �berspringen.

      Replays werden aufgezeichnet und im Verzeichnis RTTR/REPLAYS
      abgespeichert.

   4. Speichern

      Speichern ist im Spielmen� an der "originalen" Stelle m�glich.
      Speichern ist auch aus dem Replaymodus an beliebiger Stelle m�glich.
      Laden von Spielen kann man nur aus dem Kartenauswahlbildschirm.
      Mitspieler ben�tigen kein eigenes Savegame, dieses wird automatisch
      beim Verbinden �bertragen.

   5. Optionen

      Die Einstellungen im Optionsmen� sollten so weit selbsterkl�rend sein.


--------------------------------------------------------------------------------

D. Abst�rze und Fehler

   Es handelt sich selbst bei dieser Version zwar schon um eine stabilere
   Variante. Abst�rze, Asyncs, Speicherzugriffs- und sonstige Fehler
   lassen sich aber leider immer noch nicht ausschlie�en.

   Durch Replays k�nnen Fehler leicht rekonstruiert werden. Ihr k�nnt uns
   mit dem Zusenden euer Replays helfen, weitere zu finden. Bitte stellt
   aber sicher, dass ihr immer die neuste Daily-Version verwendet. Fehler
   aus m�glicherweise veralteten Releaseversionen sind mitunter schon lange
   behoben.

   Falls ein Async aufgetreten ist, findet ihr im RTTR/LOGS/-Verzeichnis
   Log-Dateien. Schickt uns diese bitte von JEDEM(!) Spieler einschlie�lich
   eines Replays (Verzeichnis RTTR/REPLAYS).
   Bitte stellt sicher, dass ihr den Async nicht absichtlich durch Spielen mit
   verschiedenen Versionen oder Cheaten herbeigef�hrt habt!

   Wenn ihr Fehler findet, bitte diese im Launchpad posten:

               http://bugs.siedler25.org/

   Das Launchpad erh�ht die �bersichtlichkeit f�r Bugs und erm�glicht euch
   zudem selber einsehen zu k�nnen, wann der Bug gefixt wurde.

   Bei weiteren Fragen bitte an
        
               bugs@siedler25.org

   wenden.

   Alternativ k�nnt ihr euch auch im Forum oder im IRC-Channel unter
   irc.freenode.net:6667/#siedler2.5 melden. Ihr k�nnt dem Chat auch �ber
   unsere Seite beitreten.

   Vielen Dank!

   Settlers Freaks
   23. November 2009

--------------------------------------------------------------------------------

E. �bersicht: Updates und �nderungen

 * 0.7.2 - 17.01.2011 *
   --------------------------------------------------------------------------
   - Kritische Fehlerkorrekturen

 * 0.7 - Seventh version - 24.12.2010 *
   --------------------------------------------------------------------------
   - OpenSource!
   - �bersetzung: Niederl�ndisch
   - �bersetzung: Russisch (Zeichensatz fehlt)
   - �bersetzung: Czech
   - �bersetzung: Estonian
   - �bersetzung: Italian
   - �bersetzung: Norwegian
   - �bersetzung: Polish
   - �bersetzung: Slovenian
   - �bersetzung: Slovak
   - Statistik
   - Post
   - Diplomatie - noch nicht fertig
   - Erste KI von jh
   - Seefahrt (noch nicht fertig)
   - Addon Men�

 * 0.6 - Sechste Version - 25.01.2009 *
   -------------------------------------------------------------------------
   - viele Bugs behoben
   - Fog of War (mit Teamview-Option)
   - Sp�hturm
   - Minimap
   - Mapvorschau im Hostmen�
   - Planierer
   - Balancing
   - Tr�geranimationen hinzugef�gt
   - Mehrsprachenunterst�tzung
   - �bersetzung: Spanisch
   - �bersetzung: Ungarisch
   - �bersetzung: Schwedisch
   - �bersetzung: Franz�sisch (nicht abgeschlossen)
   - �bersetzung: Finnisch (nicht abgeschlossen)
   - Siegesmeldungen
   - Tastaturbefehle + Readme
   - Option im Hostmen�: Abriss-Verbot
   - Geb�ude Info
   - Einige Hausanimationen hinzugef�gt
   
  * 0.5 - F�nfte Version - 27.01.2008 *
   -------------------------------------------------------------------------
   - sehr viele Bugs behoben
   - Eselstra�en, Eselz�chter
   - Bootsstra�en mit Booten und Werft (baut nur Boote)
   - Bergstra�en
   - Katapulte
   - Soldatenverhalten ver�ndert, r�cken nicht mehr so schnell nach
   - beim Abbrennen von Lagerh�usern und dem Hauptquartier fl�chten
     nun alle Leute nach drau�en wie im Original
   - Async-Logdatei
   - diverse Kleinigkeiten wie ein das Original-Abfragefenster vor dem
     Abbrennen von Geb�uden oder fehlende/falsche Tooltips
   - Sound an/aus Buttons im Spiel

   * 0.4 - Vierte Version - 09.10.2007 *
   -------------------------------------------------------------------------
   - Speichern und Laden von Spielen eingebaut, inklusive Autosave
   - zig zum Teil schwere Bugs behoben

   * 0.3 - Dritte Version Fix01 -  13.09.2007 *
   -------------------------------------------------------------------------
   - kritischen Absturz behoben

   * 0.3 - Dritte Version - 12.09.2007 *
   -------------------------------------------------------------------------
   - diverse Absturzbugs behoben
   - Siedler warten nun, falls der Platz vor ihnen besetzt ist
     (durch K�mpfe z.B.)
   - Settings unter Linux im Home-Verzeichnis untergebracht
   - Settings in lesbares Format gebracht (GER-File)
   - Build-System unter Linux von autotools auf CMake umgestellt
   - CIA-Bot f�r den IRC aktiviert
   - Lobbygrundfunktionen fertiggestellt
   - Vorbereitungen f�r Speichern und Laden getroffen

   * 0.2 - Zweite Version - 15.07.2007 *
   -------------------------------------------------------------------------
   - diverse Bugs behoben und diverse Verz�gerungsbugs unterdr�ckt
   - Men�s in variabler Aufl�sung
   - Pr�fen der Synchronit�t und Rausschmiss asynchroner Spieler
   - Inventurfenster eingebaut
   - "Nicht Einlagern"/"Auslagern" m�glich
   - Bereit-Button im Host-Men�
   - Verteilung korrigiert
   - diverse fehlende Zierobjekte (z.B Stalagmiten, Ruinen) eingebaut
   - zu allen Gebäuden kann nun gesprungen werden
   - einige Zierobjekte werden beim Wegbau nun abgerissen
   - Produktivit�tsanzeige und Namenanzeige (C, S) teilweise schon korrekt
     implementiert
   - Abrissbest�tigung eingebaut
   - RoadWindow schlie�t sich nun, wenn man woanders hinklickt

   * 0.1 - Erster Release - 01.07.2007 *
   -------------------------------------------------------------------------
   - alles ;-)

--------------------------------------------------------------------------------
http://www.siedler25.org                     Copyright (C) 2005-2009 Settlers Freaks
--------------------------------------------------------------------------------
