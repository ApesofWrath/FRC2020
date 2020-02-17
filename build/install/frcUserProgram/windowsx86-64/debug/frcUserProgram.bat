
@echo off
SETLOCAL

CALL "%~dp0lib\frcUserProgram.exe" %*
EXIT /B %ERRORLEVEL%
ENDLOCAL
