#!/bin/sh
echo Changing directory to "assignment-cs-100-darrien-christian"
cd ..
bin/assignment-cs-100-darrien-christian << EOF
echo "ls || echo hello"; ls || echo "hello";
echo "ls -a && mkdir newfolder || echo hello"; ls -a && mkdir newfolder || echo hello;
echo "ls; ls"; ls; ls;
echo exit; exit
EOF

