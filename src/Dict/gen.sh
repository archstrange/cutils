#!/bin/bash

for t in h c; do
	ohce Dict.${t}.ohce > StrStrDict.${t} <<EOF
{
	Dict "StrStrDict"
	K "Str"
	V "Str"
	h_include '#include "../Str.h"'
	K_clone "Str_clone"
	K_copy "Str_copy"
	K_free "Str_free"
	K_hash "Str_hash"
	K_equal "Str_equal"
	V_clone "Str_clone"
	V_copy "Str_copy"
	V_free "Str_free"
}
EOF
done
