#!/bin/bash

echo 'Queue "I8Queue" T "int8_t"' | ohce Queue.h.ohce > I8Queue.h
echo 'Queue "I8Queue" T "int8_t"' | ohce Queue.c.ohce > I8Queue.c

echo 'Queue "I16Queue" T "int16_t"' | ohce Queue.h.ohce > I16Queue.h
echo 'Queue "I16Queue" T "int16_t"' | ohce Queue.c.ohce > I16Queue.c

echo 'Queue "I32Queue" T "int32_t"' | ohce Queue.h.ohce > I32Queue.h
echo 'Queue "I32Queue" T "int32_t"' | ohce Queue.c.ohce > I32Queue.c

echo 'Queue "I64Queue" T "int64_t"' | ohce Queue.h.ohce > I64Queue.h
echo 'Queue "I64Queue" T "int64_t"' | ohce Queue.c.ohce > I64Queue.c

echo 'Queue "U8Queue" T "uint8_t"' | ohce Queue.h.ohce > U8Queue.h
echo 'Queue "U8Queue" T "uint8_t"' | ohce Queue.c.ohce > U8Queue.c

echo 'Queue "U16Queue" T "uint16_t"' | ohce Queue.h.ohce > U16Queue.h
echo 'Queue "U16Queue" T "uint16_t"' | ohce Queue.c.ohce > U16Queue.c

echo 'Queue "U32Queue" T "uint32_t"' | ohce Queue.h.ohce > U32Queue.h
echo 'Queue "U32Queue" T "uint32_t"' | ohce Queue.c.ohce > U32Queue.c

echo 'Queue "U64Queue" T "uint64_t"' | ohce Queue.h.ohce > U64Queue.h
echo 'Queue "U64Queue" T "uint64_t"' | ohce Queue.c.ohce > U64Queue.c

echo 'Queue "F32Queue" T "float"' | ohce Queue.h.ohce > F32Queue.h
echo 'Queue "F32Queue" T "float"' | ohce Queue.c.ohce > F32Queue.c

echo 'Queue "F64Queue" T "double"' | ohce Queue.h.ohce > F64Queue.h
echo 'Queue "F64Queue" T "double"' | ohce Queue.c.ohce > F64Queue.c

echo 'Queue "PtrQueue" T "void *"' | ohce Queue.h.ohce > PtrQueue.h
echo 'Queue "PtrQueue" T "void *"' | ohce Queue.c.ohce > PtrQueue.c
