#!/bin/bash

if [ $# -lt 1 ]; then
  echo "File number required as first argument"
  echo "./script 13 <other arguments>"
  exit 1
fi

re='^[0-9]+$'
if ! [[ $1 =~ $re ]] ; then
  echo "First argument must be a number"
  echo "./script 13 <other arguments>"
  exit 1
fi

if [ $1 -lt 10 ]; then
  f="data/tour00${1}.txt"
elif [ $1 -lt 100 ]; then
  f="data/tour0${1}.txt"
else
  f="data/tour${1}.txt"
fi

shift

args="-f $f $@"

echo "./src/main.exe $args"
./src/main.exe $args
