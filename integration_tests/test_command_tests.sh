#!/bin/sh
echo Changing directory to 'assignment-cs-100-darrien-christian'
cd ../bin/assignment-cs-100-darrien-christian

test -e base.h && echo base.h exists

test -d base.h || echo directory base.h does not exist

mkdir check
touch file.cpp

test -d check && echo directory check exists
test -f file.cpp && echo file file.cpp exists

rm file.cpp
rm -r check

test -f file.cpp || echo file file.cpp does not exist
exit
