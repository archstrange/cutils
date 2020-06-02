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
#ifndef CUTILS_U32List_H
#define CUTILS_U32List_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// U32List: a double linked list type.
typedef struct _ADT_U32List_ *U32List;

/// U32ListNode: U32List node type.
typedef struct _ADT_U32ListNode_ *U32ListNode;

/// Set the data hold by @self to @value.
void U32ListNode_set(U32ListNode self, uint32_t value);

/// Get the data hold by @self.
uint32_t U32ListNode_get(U32ListNode self);

/// Get next node. If @self is tail-node, NULL will be returned.
U32ListNode U32ListNode_getNext(U32ListNode self);

/// Get previous node. If @self is head-node, NULL will be returned.
U32ListNode U32ListNode_getPrev(U32ListNode self);

/// Create a new node that hold @value and insert it as
/// @self's previous node.
U32ListNode U32ListNode_insertPrev(U32ListNode self, uint32_t value);

/// Create a new node that hold @value and insert it as
/// @self's next node.
U32ListNode U32ListNode_insertNext(U32ListNode self, uint32_t value);

/// Delete this node from list.
size_t U32ListNode_delete(U32ListNode self);

/// Create a new empty U32List object.
U32List U32List_new();

U32List U32List_clone(U32List src);

void U32List_copy(U32List self, U32List src);

/// Free @self.
void U32List_free(U32List self);

/// Get head node.
U32ListNode U32List_getHead(U32List self);

/// Get tail node.
U32ListNode U32List_getTail(U32List self);

/// Get the number of nodes.
size_t U32List_getLength(U32List self);

size_t U32List_pushFront(U32List self, uint32_t value);

size_t U32List_pushBack(U32List self, uint32_t value);


#endif
