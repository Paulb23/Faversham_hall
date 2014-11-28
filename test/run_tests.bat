@echo off
cd %~dp0/builds
if "%~1"=="" (
call __run_tests.bat
) else (
call __run_tests.bat %1
)
cd..