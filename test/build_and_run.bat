@echo off

if "%~1"=="" (
call build_tests.bat
call run_tests.bat
) else (
call build_tests.bat %1
call run_tests.bat %1
)