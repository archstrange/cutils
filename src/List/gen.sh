#!/bin/bash

echo 'List "I8List" T "int8_t"' | ohce List.h.ohce > I8List.h
echo 'List "I8List" T "int8_t"' | ohce List.c.ohce > I8List.c

echo 'List "I16List" T "int16_t"' | ohce List.h.ohce > I16List.h
echo 'List "I16List" T "int16_t"' | ohce List.c.ohce > I16List.c

echo 'List "I32List" T "int32_t"' | ohce List.h.ohce > I32List.h
echo 'List "I32List" T "int32_t"' | ohce List.c.ohce > I32List.c

echo 'List "I64List" T "int64_t"' | ohce List.h.ohce > I64List.h
echo 'List "I64List" T "int64_t"' | ohce List.c.ohce > I64List.c

echo 'List "U8List" T "uint8_t"' | ohce List.h.ohce > U8List.h
echo 'List "U8List" T "uint8_t"' | ohce List.c.ohce > U8List.c

echo 'List "U16List" T "uint16_t"' | ohce List.h.ohce > U16List.h
echo 'List "U16List" T "uint16_t"' | ohce List.c.ohce > U16List.c

echo 'List "U32List" T "uint32_t"' | ohce List.h.ohce > U32List.h
echo 'List "U32List" T "uint32_t"' | ohce List.c.ohce > U32List.c

echo 'List "U64List" T "uint64_t"' | ohce List.h.ohce > U64List.h
echo 'List "U64List" T "uint64_t"' | ohce List.c.ohce > U64List.c

echo 'List "F32List" T "float"' | ohce List.h.ohce > F32List.h
echo 'List "F32List" T "float"' | ohce List.c.ohce > F32List.c

echo 'List "F64List" T "double"' | ohce List.h.ohce > F64List.h
echo 'List "F64List" T "double"' | ohce List.c.ohce > F64List.c

echo 'List "PtrList" T "void *"' | ohce List.h.ohce > PtrList.h
echo 'List "PtrList" T "void *"' | ohce List.c.ohce > PtrList.c
