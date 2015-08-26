@ECHO OFF

set gamedir=".\..\"

echo This will DELETE ALL BAK FILES IN %gamedir%. 
pause
del  /s /f  %gamedir%*.bak
pause