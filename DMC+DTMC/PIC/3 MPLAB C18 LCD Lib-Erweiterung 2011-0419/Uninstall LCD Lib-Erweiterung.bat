@echo off
  rem *****************************************************************************
  rem *  Deinstallation der LCD-Lib-Erweiterung:                                  *
  rem *    Wiederherstellen der Original-Library p18f452.lib                      *
  rem *    aus der Sicherheitskopie p18f452_.lib                                  *
  rem *  Hinweis:                                                                 *
  rem *    Unter Windows 7 diese Batchdatei bitte als Administrator ausf¸hren.    *
  rem *    echo (rechte Maustaste auf Batchdatei - Als Administrator ausf¸hren.)  *
  rem *****************************************************************************

  echo.

rem  ‹berpr¸fen der Umgebung:
if ("%MCC_INCLUDE%"=="")                          goto kein_C18
if not exist "%MCC_INCLUDE%\..\lib\p18f452?.lib"  goto keine_Libs_vorhanden
if not exist "%MCC_INCLUDE%\..\lib\p18f452_.lib"  goto keine_Sicherheitskopie_vorhanden

rem  Lib wiederherstellen
  echo Wiederherstellen der Original-Library p18f452.lib
  echo aus der Sicherheitskopie p18f452_.lib
  echo im Pfad  %MCC_INCLUDE%\..\lib\
  echo.
  echo Vor Wiederherstellung:
  dir  "%MCC_INCLUDE%\..\Lib\p18f452?.lib"
  echo.
  echo Jetzt wiederherstellen (Abbruch mit Strg-C)?
pause

  move "%MCC_INCLUDE%\..\lib\p18f452_.lib"  "%MCC_INCLUDE%\..\lib\p18f452.lib"
if exist "%MCC_INCLUDE%\..\lib\p18f452_.lib"  goto Zugriffsfehler_MPLAB
  echo Library wiederhergestellt.
  echo.
  echo Nach Wiederherstellung:

:List
  dir  "%MCC_INCLUDE%\..\Lib\p18f452?.lib"
  echo.
  echo Vorhandene LCD-Module:
  echo (erweitert, wenn lcd.o + lcdgreen.o vorhanden sind)
  echo.
  echo In p18f452.lib (aktive Library):
  "%MCC_INCLUDE%\..\bin\mplib" /t "%MCC_INCLUDE%\..\Lib\p18f452.lib" |find "lcd"
  echo.
goto end

rem  ***** Fehlermeldungen *****
:kein_C18
  echo Die Systemvariable MCC_INCLUDE ist nicht vorhanden.
  echo Der Compiler 'MPLAB C fÅr PIC18' ist mîglicherweise gar nicht installiert.
  echo.
goto end

:keine_Libs_vorhanden
  echo Im Pfad
  echo %MCC_INCLUDE%\..
  echo wurden keine Libraries p18f452?.lib gefunden.
  echo.
goto end

:keine_Sicherheitskopie_vorhanden
  echo Im Pfad
  echo %MCC_INCLUDE%\..
  echo wurde keine Kopie p18f452_.lib der Original-Library p18f452.lib gefunden.
  echo Eine Deinstallation ist deshalb nicht mîglich.
  echo Kopieren Sie die p18f452.lib am besten von einem anderen PC
  echo oder installieren Sie den C-Compiler neu.
  echo.
goto end

:Zugriffsfehler_MPLAB
  echo.
  echo Fehler bei Dateizugriff. Im MPLAB-Programmverzeichnis
  echo %MCC_INCLUDE%\..
  echo muss Schreibzugriff mîglich sein.
  echo.
  echo Hinweis:
  echo.  Unter Windows 7 diese Batchdatei bitte als Administrator ausfÅhren.
  echo.  (rechte Maustaste auf Batchdatei - Als Administrator ausfÅhren.)
  echo.
goto end

:end
pause
