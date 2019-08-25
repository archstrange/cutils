#!/bin/bash

echo 'Vector "I8Vector" T "int8_t"' | ohce Vector.h.ohce > I8Vector.h
echo 'Vector "I8Vector" T "int8_t"' | ohce Vector.c.ohce > I8Vector.c

echo 'Vector "I16Vector" T "int16_t"' | ohce Vector.h.ohce > I16Vector.h
echo 'Vector "I16Vector" T "int16_t"' | ohce Vector.c.ohce > I16Vector.c

echo 'Vector "I32Vector" T "int32_t"' | ohce Vector.h.ohce > I32Vector.h
echo 'Vector "I32Vector" T "int32_t"' | ohce Vector.c.ohce > I32Vector.c

echo 'Vector "I64Vector" T "int64_t"' | ohce Vector.h.ohce > I64Vector.h
echo 'Vector "I64Vector" T "int64_t"' | ohce Vector.c.ohce > I64Vector.c

echo 'Vector "Str" T "uint8_t"' | ohce Vector.h.ohce > Str.h
echo 'Vector "Str" T "uint8_t"' | ohce Vector.c.ohce > Str.c

echo 'Vector "U16Vector" T "uint16_t"' | ohce Vector.h.ohce > U16Vector.h
echo 'Vector "U16Vector" T "uint16_t"' | ohce Vector.c.ohce > U16Vector.c

echo 'Vector "U32Vector" T "uint32_t"' | ohce Vector.h.ohce > U32Vector.h
echo 'Vector "U32Vector" T "uint32_t"' | ohce Vector.c.ohce > U32Vector.c

echo 'Vector "U64Vector" T "uint64_t"' | ohce Vector.h.ohce > U64Vector.h
echo 'Vector "U64Vector" T "uint64_t"' | ohce Vector.c.ohce > U64Vector.c

echo 'Vector "F32Vector" T "float"' | ohce Vector.h.ohce > F32Vector.h
echo 'Vector "F32Vector" T "float"' | ohce Vector.c.ohce > F32Vector.c

echo 'Vector "F64Vector" T "double"' | ohce Vector.h.ohce > F64Vector.h
echo 'Vector "F64Vector" T "double"' | ohce Vector.c.ohce > F64Vector.c

echo 'Vector "PtrVector" T "void *"' | ohce Vector.h.ohce > PtrVector.h
echo 'Vector "PtrVector" T "void *"' | ohce Vector.c.ohce > PtrVector.c
