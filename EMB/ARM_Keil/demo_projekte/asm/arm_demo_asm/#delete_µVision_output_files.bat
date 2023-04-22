@echo off
 rem  F¸r Keil µVision-Projekte zum
 rem  Lˆschen der von µVision erzeugten Ausgabedateien:
 rem  Diese Batchdatei ins aktuelle Projektverzeichnis kopieren
 rem  und dort per Doppelklick ausf¸hren.

 rem  Version f¸r Quelldateien .c und .s im selben Verzeichnis

 rem  B.Pohlner (EMB) 20.11.09 / 20.04.11 / 25.05.12 / 6.06.12

 echo.
 echo.
 echo Lîschen der von ÊVision erzeugten Ausgabedateien in diesem Projektverzeichnis
 echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 echo.        Alle fÅr die Erstellung des Projekts wichtigen Dateien
 echo.                 und Quelldateien bleiben erhalten:
 echo.

if not exist *.uv2  if not exist *.uvproj  goto Fehler
pause

 rem  Backup-Dateien
 if exist *.bak  del *.bak
 rem  µVision Build Log
 if exist *.plg  del *.plg
 rem  Dependencies
 if exist *.dep  del *.dep
 rem  (Bin‰rdatei)
 if exist *.crf  del *.crf
 rem  Compiler Protokoll
 if exist *.d    del *.d
 rem  Assembler-Listing
 if exist *.lst  del *.lst
 rem  ARM Executable and Linking Format (ELF)
 if exist *.axf  del *.axf
 rem  Invocation Parameters
 if exist *.__i  del *.__i
 rem  Static Call Graph for image *.axf
 if exist *.htm  del *.htm
 rem  Linker Protokoll
 if exist *.lnp  del *.lnp
 rem  Map-Datei des Linkers
 if exist *.map  del *.map
 rem  Scatter-Loading Description File
 if exist *.sct  del *.sct
 rem  Trace Output File
 if exist *.tra  del *.tra
 rem  plg File
 if exist *.plg  del *.plg
 rem  iex File
 if exist *.iex  del *.iex
 rem  µVision Graphical User Interface File (Editor-Dateien)
 rem  if exist *.uvgui.*  del *.uvgui.*


 rem  Objektdateien von Assembler-Quelltexten
 for %%I in (*.o) do  if exist %%~nI.s  del %%~nI.o
 rem  Objektdateien von C-Quelltexten
 for %%I in (*.o) do  if exist %%~nI.c  del %%~nI.o

goto end

:Fehler
 echo.
 echo Kein ÊVision-Projekt in diesem Verzeichnis vorhanden:
 echo.
 echo Die Batchdatei muss im Projektverzeichnis liegen, das die
 echo .uv2-Datei oder .uvproj-Datei enthÑlt.
 echo.
pause

:end
