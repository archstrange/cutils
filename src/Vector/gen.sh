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
	ohce Vector.${t}.ohce > F32Vector.${t} <<EOF
{
	Vector "F32Vector"
	T "float"
}
EOF
	ohce Vector.${t}.ohce > F64Vector.${t} <<EOF
{
	Vector "F64Vector"
	T "double"
}
EOF
	ohce Vector.${t}.ohce > Str.${t} <<EOF
{
	Vector "Str"
	T "uint8_t"
}
EOF
done

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
	T_hash "Str_hash"
	T_cmp "Str_cmp"
	T_equal "Str_equal"
}
EOF
done

