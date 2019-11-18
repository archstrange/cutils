#!/bin/bash

for t in h c; do
	for w in 8 16 32 64; do
		ohce Queue.${t}.ohce > I${w}Queue.${t} <<EOF
{
	Queue "I${w}Queue"
	T "int${w}_t"
}
EOF
		ohce Queue.${t}.ohce > U${w}Queue.${t} <<EOF
{
	Queue "U${w}Queue"
	T "uint${w}_t"
}
EOF
	done
	ohce Queue.${t}.ohce > F32Queue.${t} <<EOF
{
	Queue "F32Queue"
	T "float"
}
EOF
	ohce Queue.${t}.ohce > F64Queue.${t} <<EOF
{
	Queue "F64Queue"
	T "double"
}
EOF
done

for t in h c; do
	ohce Queue.${t}.ohce > StrQueue.${t} <<EOF
{
	Queue "StrQueue"
	T "Str"
	h_include '#include "../Vector/Str.h"'
	T_new "Str_new"
	T_clone "Str_clone"
	T_copy "Str_copy"
	T_free "Str_free"
}
EOF
done

