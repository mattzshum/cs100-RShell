#!/bin/sh
echo Changing directory to 'assignment-cs-100-darrien-christian'
cd ../bin/assignment-cs-100-darrien-christian

ls > OutputRedirection1
ps > OutputRedirection2
echo Check this > OutputRedirection3
echo Check the words | wc > OutputRedirection4
echo hello > OutputRedirection2
cat < OutputRedirection5 > OutputTest1
echo test > OutputRedirection6
cat < OutputRedirection4
ls > OutputRedirection1
rm OutputTest1
rm OutputTest2
rm OutputTest3
rm OutputTest4
rm OutputTest5
rm OutputTest6
exit
