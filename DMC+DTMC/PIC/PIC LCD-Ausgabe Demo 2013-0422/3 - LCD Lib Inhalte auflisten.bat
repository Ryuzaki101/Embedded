@echo off
  rem *********************************************************************************************
  rem *  Auflisten der C18 Library-Inhalte f¸r PIC18F452                                          * 
  rem *********************************************************************************************
  echo.
  cd
  echo.

rem  ‹berpr¸fen der Umgebung:
if ("%MCC_INCLUDE%"=="")                          goto kein_C18
if not exist "%MCC_INCLUDE%\..\bin\mplib.exe"     goto falscher_Pfad

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
