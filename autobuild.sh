#!/bin/bash

set -e

if [ ! -d `pwd`/build ]; then
    mkdir `pwd`/build
fi

rm -rf `pwd`/build/*

cd `pwd`/build &&
    cmake .. &&
    make

cd ..

if [ ! -d /usr/include/cgmuduo ]; then
    mkdir /usr/include/cgmuduo
fi

for header in `ls *.h`
do
    cp $header /usr/include/cgmuduo
done

cp `pwd`/lib/libcgmuduo.so /usr/lib

ldconfig