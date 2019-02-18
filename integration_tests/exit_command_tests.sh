#!/bin/sh
echo Changing directory to 'assignment-cs-100-darrien-christian'
cd ..

echo "ls && exit";
bin/assignment-cs-100-darrien-christian << EOF
ls && exit
EOF

echo "mkdir newFolder || exit"
bin/assignment-cs-100-darrien-christian << EOF
mkdir newFolder || exit
EOF

echo "echo hello; exit"
bin/assignment-cs-100-darrien-christian << EOF
echo hello; exit
EOF

