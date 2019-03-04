#!/bin/sh
echo Changing directory to 'assignment-cs-100-darrien-christian'
cd ../bin/assignment-cs-100-darrien-christian

[-e base.h] && echo Base.h exists

[-d base.h] || echo directory base.h does not exist

mkdir check
touch file.cpp

[-d check] && echo directory check exists
[-f file.cpp] && echo file file.cpp exists

rm file.cpp
rm -r check

[-f file.cpp] || echo file file.cpp does not exist
exit
