#!/bin/bash

if [ -z "$1" ]; then
	install_dir=/usr/local
else
	install_dir=$1
fi

include=$install_dir/include/cutils
lib=$install_dir/lib

mkdir -p $lib

sub_dirs="Vector List Queue"

for sub_dir in $sub_dirs; do
	mkdir -p $include/$sub_dir
	cp -v src/$sub_dir/*.h $include/$sub_dir/
done

cp -v src/*.h $include/

cp -v build/src/libcutils.a $lib/
