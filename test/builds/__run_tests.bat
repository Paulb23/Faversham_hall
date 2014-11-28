@echo off
echo Starting tests!

if "%~1"=="" (
for /r %%s in (*.exe) do (
 call %%s
 cls
)
) else (
call _%1
)

echo Tests finshed!
pause
