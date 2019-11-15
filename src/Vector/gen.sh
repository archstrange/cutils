#!/bin/bash

for t in h c; do
	for w in 8 16 32 64; do
		ohce Vector.${t}.ohce > I${w}Vector.${t} <<EOF
{
	Vector "I${w}Vector"
	T "int${w}_t"
}
EOF
		ohce Vector.${t}.ohce > U${w}Vector.${t} <<EOF
{
	Vector "U${w}Vector"
	T "uint${w}_t"
}
EOF
	done
done

echo '{Vector "Str" T "uint8_t"}' | ohce Vector.h.ohce > Str.h
echo '{Vector "Str" T "uint8_t"}' | ohce Vector.c.ohce > Str.c

echo '{Vector "F32Vector" T "float"}' | ohce Vector.h.ohce > F32Vector.h
echo '{Vector "F32Vector" T "float"}' | ohce Vector.c.ohce > F32Vector.c

echo '{Vector "F64Vector" T "double"}' | ohce Vector.h.ohce > F64Vector.h
echo '{Vector "F64Vector" T "double"}' | ohce Vector.c.ohce > F64Vector.c

for t in h c; do
	ohce Vector.${t}.ohce > StrVector.${t} <<EOF
{
	Vector "StrVector"
	T "Str"
	h_include '#include "Str.h"'
	T_new "Str_new"
	T_clone "Str_clone"
	T_copy "Str_copy"
	T_free "Str_free"
}
EOF
done

