@echo off

REM %1 is the message you want with the commit

git add . 
git commit -m "%1"
git push