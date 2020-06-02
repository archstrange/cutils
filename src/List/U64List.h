// cutils: my c utils library
// Copyright (C) 2019  Qijian Zhang <arch.strange@foxmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// This file is generated from List.h.ohce by ohce.
#ifndef CUTILS_U64List_H
#define CUTILS_U64List_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// U64List: a double linked list type.
typedef struct _ADT_U64List_ *U64List;

/// U64ListNode: U64List node type.
typedef struct _ADT_U64ListNode_ *U64ListNode;

/// Set the data hold by @self to @value.
void U64ListNode_set(U64ListNode self, uint64_t value);

/// Get the data hold by @self.
uint64_t U64ListNode_get(U64ListNode self);

/// Get next node. If @self is tail-node, NULL will be returned.
U64ListNode U64ListNode_getNext(U64ListNode self);

/// Get previous node. If @self is head-node, NULL will be returned.
U64ListNode U64ListNode_getPrev(U64ListNode self);

/// Create a new node that hold @value and insert it as
/// @self's previous node.
U64ListNode U64ListNode_insertPrev(U64ListNode self, uint64_t value);

/// Create a new node that hold @value and insert it as
/// @self's next node.
U64ListNode U64ListNode_insertNext(U64ListNode self, uint64_t value);

/// Delete this node from list.
size_t U64ListNode_delete(U64ListNode self);

/// Create a new empty U64List object.
U64List U64List_new();

U64List U64List_clone(U64List src);

void U64List_copy(U64List self, U64List src);

/// Free @self.
void U64List_free(U64List self);

/// Get head node.
U64ListNode U64List_getHead(U64List self);

/// Get tail node.
U64ListNode U64List_getTail(U64List self);

/// Get the number of nodes.
size_t U64List_getLength(U64List self);

size_t U64List_pushFront(U64List self, uint64_t value);

size_t U64List_pushBack(U64List self, uint64_t value);


#endif
