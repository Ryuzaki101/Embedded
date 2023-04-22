@echo off
  rem *********************************************************************************************
  rem *  >> Erstellen einer mit LCD-Befehlen erweiterten PIC18 Library-Datei auf dem Desktop <<   *
  rem *  Ist nach Installation von MPLAB und MPLAB C für PIC18 per Doppelklick auszuführen.       *
  rem *  Hinweis: Unter Windows 7 diese Batchdatei nicht "Als Administrator ausführen"            *
  rem *********************************************************************************************
  echo.
  cd
  echo.

rem  Überprüfen der Umgebung:
if ("%MCC_INCLUDE%"=="")                       goto kein_C18
if not exist "%MCC_INCLUDE%\..\bin\mplib.exe"  goto falscher_Pfad
if not exist obj\lcd.o                         goto obj_nicht_vorhanden

rem  Willkommen
  echo Erstellung der erweiterten Library p18f452.lib auf dem Desktop
  echo zur Anpassung der LCD-Funktionen fr das EMB-Labor:
  echo.
pause
  echo.
if not exist "%USERPROFILE%\Desktop\p18f452.lib"  goto  Lib_anlegen

  echo Die Library p18f452.lib wurde bereits am Desktop angelegt.
  echo šberschreiben? (Abbruch mit Strg-C)
  echo.
pause
  echo.

:Lib_anlegen
  echo Kopiere die Library p18f452.lib auf den Desktop ...
  copy  "%MCC_INCLUDE%\..\lib\p18f452.lib"  "%USERPROFILE%\Desktop"
  echo.
if not exist "%USERPROFILE%\Desktop\p18f452.lib" goto Zugriffsfehler

  echo "%USERPROFILE%\Desktop\p18f452.lib" wird erweitert ...
  cd obj
  for %%i in (*.o) do "%MCC_INCLUDE%\..\bin\mplib" /r  "%USERPROFILE%\Desktop\p18f452.lib" %%i
  cd ..
  echo.

:List
  dir "%USERPROFILE%\Desktop\p18f452.lib"
  echo.
  echo Vorhandene LCD-Module (erweitert, wenn lcd.o + lcdgreen.o vorhanden sind):
  "%MCC_INCLUDE%\..\bin\mplib" /t "%USERPROFILE%\Desktop\p18f452.lib" |find "lcd"
  echo.
if exist "%MCC_INCLUDE%\..\Lib\p18f452_.lib"  goto end
  echo Zur Vervollst„ndigung jetzt folgende Batchdatei ausfhren:
  echo "2 - erweiterte Lib vom Desktop nach MPLAB verschieben (Administrator).bat"
  echo.
goto end

rem  ***** Fehlermeldungen *****
:kein_C18
  echo Die Systemvariable MCC_INCLUDE ist nicht vorhanden.
  echo.  MCC_INCLUDE="%MCC_INCLUDE%"
  echo.
  echo Der Compiler 'MPLAB C fr PIC18' ist m”glicherweise noch nicht installiert.
  echo.
  echo Installation bitte in folgender Reihenfolge ausfhren:
  echo 1.) MPLAB
  echo 2.) MPLAB C fr PIC18
  echo 3.) Library-Erweiterung fr LCD
  echo.
goto end

:falscher_Pfad
  echo Der Compiler 'MPLAB C fr PIC18' ist m”glicherweise noch nicht installiert.
  echo Er befindet sich nicht im Pfad
  echo.  %MCC_INCLUDE%\..
  echo.
  echo Installation bitte in folgender Reihenfolge ausfhren:
  echo 1.) MPLAB
  echo 2.) MPLAB C fr PIC18
  echo 3.) Library-Erweiterung fr LCD
  echo.
goto end

:obj_nicht_vorhanden
  echo Die die fr das LCD notwendigen Objektdateien sind nicht
  echo im Unterverzeichnis "obj" gefunden worden.
  echo.
  echo Das aktuelle Verzeichnis zur Ausfhrung der Batchdatei ist:
  cd
  echo.
 if not exist cmd.exe  goto end
  echo Hinweis:
  echo.  Unter Windows 7 diese Batchdatei nicht "Als Administrator ausfhren",
  echo.  sondern nur durch Doppelklick starten.
  echo.
goto end

:Zugriffsfehler_Desktop
  echo.
  echo Fehler bei Dateizugriff. Im Desktopverzeichnis
  echo "%USERPROFILE%\Desktop\
  echo muss Schreibzugriff m”glich sein.
  echo.
goto end

:end
pause
