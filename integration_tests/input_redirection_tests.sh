#!/bin/sh
echo Changing directory to 'assignment-cs-100-darrien-christian'
cd ../bin/assignment-cs-100-darrien-christian

cat < tests/InputRedirection1
cat < tests/InputRedirection2
wc < tests/InputRedirection3
tr A-Z a-z < tests/InputRedirection4
tr C-X c-x < tests/InputRedirection5
grep check < tests/InputRedirection6
cat < tests/InputRedirection3 > TestOutput
cat < tests/InputRedirection4 | tr A-Z a-z
grep 1 < tests/InputRedirection5
grep 2 < tests/InputRedirection4 | wc
exit
