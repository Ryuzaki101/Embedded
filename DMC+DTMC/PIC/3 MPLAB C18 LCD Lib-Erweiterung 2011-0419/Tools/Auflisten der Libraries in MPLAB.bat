@echo off
  rem ******************************************************************
  rem *  Listet den Inhalt der Libraries p18f452.lib und p18f452_.lib  *
  rem *  im Lib-Verzeichnis von MPLAB auf.                             *
  rem ******************************************************************

  echo.

rem  Überprüfen der Umgebung:
if not exist "%MCC_INCLUDE%\..\bin\mplib.exe"     goto falscher Pfad
if not exist "%MCC_INCLUDE%\..\Lib\p18f452?.lib"  goto keine_Lib_vorhanden

:List
  dir  "%MCC_INCLUDE%\..\Lib\p18f452?.lib"
  echo.
  echo Vorhandene LCD-Module:
  echo (erweitert, wenn lcd.o + lcdgreen.o vorhanden sind)
  echo.
  echo In p18f452.lib (aktive Library):
  if exist "%MCC_INCLUDE%\..\Lib\p18f452.lib" "%MCC_INCLUDE%\..\bin\mplib" /t "%MCC_INCLUDE%\..\Lib\p18f452.lib" |find "lcd"
  echo.
  echo In p18f452_.lib (Sicherheitskopie):
  if exist "%MCC_INCLUDE%\..\Lib\p18f452_.lib" "%MCC_INCLUDE%\..\bin\mplib" /t "%MCC_INCLUDE%\..\Lib\p18f452_.lib" |find "lcd"
  echo.
goto end

:falscher_Pfad
  echo Der C18-Compiler befindet sich nicht im Pfad
  echo %MCC_INCLUDE%\..
  echo.
  echo Ist der Compiler installiert?
  echo.
goto end

:keine_Lib_vorhanden
  echo Im Lib-Verzeichnis von MPLAB ist keine Library-Datei p18f452?.lib vorhanden.
  echo.
goto end

:end
pause
