@echo off
echo Starting compile

setlocal enabledelayedexpansion enableextensions
set params=
for /R ..\Faversham_hall\src\ %%f in (*.o) do (
 if not "%%~nf"=="Faversham_hall" (
 @set params=!params! "%%f"
 )
)

if "%~1"=="" (

for /r %%s in (tests\*.c) do (
 gcc -O0 -g3 -Wall -c -fmessage-length=0 -o "tests\objects\%%~ns.o" "tests\%%~ns.c"
 gcc -o builds\\_%%~ns.exe "tests\\objects\\%%~ns.o" %params% -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lzlib1
)
) else (
 gcc -O0 -g3 -Wall -c -fmessage-length=0 -o "tests\objects\%1.o" "tests\%1.c"
 gcc -o builds\\_%1.exe "tests\\objects\\%1.o" %params% -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lzlib1
)

echo Complie complete
pause