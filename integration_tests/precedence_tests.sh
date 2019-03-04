#!/bin/sh
echo Changing directory to 'assignment-cs-100-darrien-christian'
cd ../bin/assignment-cs-100-darrien-christian

(echo A && echo B) || (echo C && echo D)
(echo hello world)
(echo hello world && ls -a)
echo A || (ls && ls -a)
(echo A) || (echo B)
((echo A && echo B) || (echo C && echo D)) && ls
((ls) || (ls -a)) && mkdir testdir && echo created test directory
(ls && rm -r testdir) && echo removed test directory
exit
