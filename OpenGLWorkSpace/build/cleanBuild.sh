#!bin/bash

find . -type f ! -name 'cleanBuild.sh' -exec rm -rf {} \;
find . -type d ! -name 'cleanBuild.sh' -exec rm -rf {} \;
