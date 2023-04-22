@echo off
 rem  F¸r Microchip MPLAB-Projekte zum
 rem  Lˆschen der von MPLAB erzeugten Ausgabedateien:
 rem  Diese Batchdatei ins aktuelle Projektverzeichnis kopieren
 rem  und dort per Doppelklick ausf¸hren.

 rem  Version f¸r Quelldateien .c und .asm im selben Verzeichnis

 rem  B.Pohlner (EMB) 14.04.11 / 02.05.11  f¸r ASM- und C-Projekte

 echo.
 echo.
 echo Lîschen der von MPLAB erzeugten Ausgabedateien in diesem Projektverzeichnis
 echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 echo.        Alle fÅr die Erstellung des Projekts wichtigen Dateien
 echo.                 und Quelldateien bleiben erhalten:
 echo.

 if not exist *.mcp  goto Fehler
pause

 rem  Backup-Dateien
 if exist *.bak  del *.bak
 rem  Common Object File
 if exist *.cof  del *.cof
 rem  Error-Dateien (Fehlermeldungen)
 if exist *.err  del *.err
 rem  Hex-Dateien (ladbare Datei)
 if exist *.hex  del *.hex
 rem  List-Dateien (Assembler-Listing)
 if exist *.lst  del *.lst
 rem  Map-Dateien (Linker-Ausgabe)
 if exist *.map  del *.map
 rem  mptags-Dateien
 if exist *.mptags  del *.mptags
 rem  Microchip Build-State File
 if exist *.mcs  del *.mcs
 rem  tagsrc-Dateien
 if exist *.tagsrc  del *.tagsrc

 rem  Objektdateien von Assembler-Quelltexten
 for %%I in (*.o) do  if exist %%~nI.asm  del %%~nI.o
 rem  Objektdateien von C-Quelltexten
 for %%I in (*.o) do  if exist %%~nI.c  del %%~nI.o

 rem  Nicht lˆschen:
 rem  .mcp = Microchip Project File
 rem  .mcw = Microchip Workspace File

goto end

:Fehler
 echo.
 echo Kein MPLAB-Projekt in diesem Verzeichnis vorhanden:
 echo.
 echo Die Batchdatei muss im Projektverzeichnis liegen, das die
 echo .mcp-Datei enthÑlt.
 echo.
pause

:end
