#!/bin/sh
echo Changing directory to 'assignment-cs-100-darrien-christian'
cd ../bin/assignment-cs-100-darrien-christian

ls | cat
ls | wc
ls -a | cat
ls -a | wc
ls -a | grep src
ls | cat | wc
ls | grep src
ps | wc
cat < tests/InputRedirection1 | tr A-Z a-z | wc > tests/OutputRedirection1
cat < tests/InputRedirection2 | tr C-X c-x
echo Check this test | wc
exit
