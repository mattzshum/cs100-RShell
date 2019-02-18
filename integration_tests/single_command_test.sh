#!/bin/sh
echo Changing directory to 'assignment-cs-100-darrien-christian'.
cd ..
bin/assignment-cs-100-darrien-christian << EOF
echo ls; ls
echo date; date
echo ls Base.h; ls Base.h
echo echo does this work?; echo does this work?
echo exit; exit
EOF
