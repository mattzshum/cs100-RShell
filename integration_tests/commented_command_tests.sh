#!/bin/sh
echo Changing directory to 'assignment-cs-100-darrien-christian'
cd ..
bin/assignment-cs-100-darrien-christian << EOF
echo ls #everything past is comment; ls
echo ls -a || trial && error # mkdir newfolder; ls -a || trial && error
echo df -h || ls # ls; df -h || ls
echo exit; exit
EOF
