#!/bin/bash

for t in h c; do
	for w in 8 16 32 64; do
		ohce List.${t}.ohce > I${w}List.${t} <<EOF
{
	List "I${w}List"
	T "int${w}_t"
}
EOF
		ohce List.${t}.ohce > U${w}List.${t} <<EOF
{
	List "U${w}List"
	T "uint${w}_t"
}
EOF
	done
	ohce List.${t}.ohce > F32List.${t} <<EOF
{
	List "F32List"
	T "float"
}
EOF
	ohce List.${t}.ohce > F64List.${t} <<EOF
{
	List "F64List"
	T "double"
}
EOF
done

for t in h c; do
	ohce List.${t}.ohce > StrList.${t} <<EOF
{
	List "StrList"
	T "Str"
	h_include '#include "../Vector/Str.h"'
	T_new "Str_new"
	T_clone "Str_clone"
	T_copy "Str_copy"
	T_free "Str_free"
}
EOF
done

