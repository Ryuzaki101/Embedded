@echo off
  rem *********************************************************************************************
  rem *  Verschieben der erweiterten Lib vom Desktop ins MPLAB-Verzeichnis                        *
  rem *    Auszuf¸hren nach der Batchdatei "1 - LCD Lib-Erweiterung auf dem Desktop anlegen.bat"  *
  rem *  Hinweis:                                                                                 *
  rem *    Unter Windows 7 diese Batchdatei bitte als Administrator ausf¸hren.                    *
  rem *    echo (rechte Maustaste auf Batchdatei - Als Administrator ausf¸hren.)                  *
  rem *********************************************************************************************
  echo.
  cd
  echo.

rem  ‹berpr¸fen der Umgebung:
if ("%MCC_INCLUDE%"=="")                          goto kein_C18
if not exist "%MCC_INCLUDE%\..\bin\mplib.exe"     goto falscher_Pfad
if not exist "%USERPROFILE%\Desktop\p18f452.lib"  goto erweiterte_Lib_fehlt

rem  Kopien in MPLAB anlegen
if exist "%MCC_INCLUDE%\..\lib\p18f452_.lib"  goto nur_erweiterte Lib_verschieben

  echo Erstelle Sicherheitskopie der p18f452.lib im MPLAB-Programmverzeichnis ...
  copy  "%MCC_INCLUDE%\..\lib\p18f452.lib"  "%MCC_INCLUDE%\..\lib\p18f452_.lib"
if not exist "%MCC_INCLUDE%\..\lib\p18f452_.lib"  goto Zugriffsfehler_MPLAB
  echo.

:nur_erweiterte Lib_verschieben
  echo Verschiebe die erweiterte Library
  echo von  %USERPROFILE%\Desktop
  echo nach %MCC_INCLUDE%\..\lib
  move "%USERPROFILE%\Desktop\p18f452.lib"  "%MCC_INCLUDE%\..\lib\p18f452.lib"
  echo.

:List
  dir  "%MCC_INCLUDE%\..\Lib\p18f452?.lib"
  echo.
  echo Vorhandene LCD-Module:
  echo (erweitert, wenn lcd.o + lcdgreen.o vorhanden sind)
  echo.
  echo In p18f452.lib (aktive Library):
  "%MCC_INCLUDE%\..\bin\mplib" /t "%MCC_INCLUDE%\..\Lib\p18f452.lib" |find "lcd"
  echo.
  echo In p18f452_.lib (Sicherheitskopie):
  "%MCC_INCLUDE%\..\bin\mplib" /t "%MCC_INCLUDE%\..\Lib\p18f452_.lib" |find "lcd"
  echo.
goto end

rem  ***** Fehlermeldungen *****
:kein_C18
  echo Die Systemvariable MCC_INCLUDE ist nicht vorhanden.
  echo Der Compiler 'MPLAB C fÅr PIC18' ist mîglicherweise noch nicht installiert.
  echo.
  echo Installation bitte in folgender Reihenfolge ausfÅhren:
  echo 1.) MPLAB
  echo 2.) MPLAB C fÅr PIC18
  echo 3.) Library-Erweiterung fÅr LCD
  echo.
goto end

:falscher_Pfad
  echo Der C18-Compiler befindet sich nicht im Pfad
  echo %MCC_INCLUDE%\..
  echo.
  echo Ist der Compiler installiert?
  echo.
goto end

:erweiterte_Lib_fehlt
  echo Es wurde keine erweiterte Librarydatei p18f452.lib auf dem Desktop gefunden.
  echo.
  echo Nach Installation von MPLAB und MPLAB C fÅr PIC18 bitte zuerst
  echo die Batchdatei "1 - LCD Lib-Erweiterung auf dem Desktop anlegen.bat"
  echo durch Doppelklicken ausfÅhren, um die Library auf dem Desktop bereit zu stellen.
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
