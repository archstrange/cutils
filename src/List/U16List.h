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
#ifndef CUTILS_U16List_H
#define CUTILS_U16List_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// U16List: a double linked list type.
typedef struct _ADT_U16List_ *U16List;

/// U16ListNode: U16List node type.
typedef struct _ADT_U16ListNode_ *U16ListNode;

/// Set the data hold by @self to @value.
void U16ListNode_set(U16ListNode self, uint16_t value);

/// Get the data hold by @self.
uint16_t U16ListNode_get(U16ListNode self);

/// Get next node. If @self is tail-node, NULL will be returned.
U16ListNode U16ListNode_getNext(U16ListNode self);

/// Get previous node. If @self is head-node, NULL will be returned.
U16ListNode U16ListNode_getPrev(U16ListNode self);

/// Create a new node that hold @value and insert it as
/// @self's previous node.
U16ListNode U16ListNode_insertPrev(U16ListNode self, uint16_t value);

/// Create a new node that hold @value and insert it as
/// @self's next node.
U16ListNode U16ListNode_insertNext(U16ListNode self, uint16_t value);

/// Delete this node from list.
size_t U16ListNode_delete(U16ListNode self);

/// Create a new empty U16List object.
U16List U16List_new();

U16List U16List_clone(U16List src);

void U16List_copy(U16List self, U16List src);

/// Free @self.
void U16List_free(U16List self);

/// Get head node.
U16ListNode U16List_getHead(U16List self);

/// Get tail node.
U16ListNode U16List_getTail(U16List self);

/// Get the number of nodes.
size_t U16List_getLength(U16List self);

size_t U16List_pushFront(U16List self, uint16_t value);

size_t U16List_pushBack(U16List self, uint16_t value);


#endif
