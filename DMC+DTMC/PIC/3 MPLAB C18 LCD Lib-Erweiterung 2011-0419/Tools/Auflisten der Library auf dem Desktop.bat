@echo off
  rem ********************************************************************
  rem *  Listet den Inhalt der Library p18f452.lib auf dem Desktop auf.  *
  rem ********************************************************************

  echo.

rem  Überprüfen der Umgebung:
if not exist "%USERPROFILE%\Desktop\p18f452.lib"  goto keine_Lib_vorhanden
if not exist "%MCC_INCLUDE%\..\bin\mplib.exe"     goto falscher_Pfad

:List
  dir  "%USERPROFILE%\Desktop\p18f452.lib"
  echo.
  echo Vorhandene LCD-Module:
  echo (erweitert, wenn lcd.o + lcdgreen.o vorhanden sind)
  echo.
  "%MCC_INCLUDE%\..\bin\mplib" /t "%USERPROFILE%\Desktop\p18f452.lib" |find "lcd"
  echo.
goto end

rem  ***** Fehlermeldungen *****
:falscher_Pfad
  echo Der C18-Compiler befindet sich nicht im Pfad
  echo %MCC_INCLUDE%\..
  echo.
  echo Ist der Compiler installiert?
  echo.
goto end

:keine_Lib_vorhanden
  echo Auf dem Desktop ist keine Library-Datei p18f452.lib vorhanden.
  echo.
  echo Die Library generieren lassen durch Doppelklicken der Batchdatei
  echo "1 - LCD Lib-Erweiterung auf dem Desktop anlegen.bat"
  echo.
goto end

:end
pause
