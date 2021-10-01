@echo off
:loop
gen
my  
std
fc /A std.out my.out
if not errorlevel 1 goto loop
pause
:end