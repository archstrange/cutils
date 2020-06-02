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
#ifndef CUTILS_U8List_H
#define CUTILS_U8List_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// U8List: a double linked list type.
typedef struct _ADT_U8List_ *U8List;

/// U8ListNode: U8List node type.
typedef struct _ADT_U8ListNode_ *U8ListNode;

/// Set the data hold by @self to @value.
void U8ListNode_set(U8ListNode self, uint8_t value);

/// Get the data hold by @self.
uint8_t U8ListNode_get(U8ListNode self);

/// Get next node. If @self is tail-node, NULL will be returned.
U8ListNode U8ListNode_getNext(U8ListNode self);

/// Get previous node. If @self is head-node, NULL will be returned.
U8ListNode U8ListNode_getPrev(U8ListNode self);

/// Create a new node that hold @value and insert it as
/// @self's previous node.
U8ListNode U8ListNode_insertPrev(U8ListNode self, uint8_t value);

/// Create a new node that hold @value and insert it as
/// @self's next node.
U8ListNode U8ListNode_insertNext(U8ListNode self, uint8_t value);

/// Delete this node from list.
size_t U8ListNode_delete(U8ListNode self);

/// Create a new empty U8List object.
U8List U8List_new();

U8List U8List_clone(U8List src);

void U8List_copy(U8List self, U8List src);

/// Free @self.
void U8List_free(U8List self);

/// Get head node.
U8ListNode U8List_getHead(U8List self);

/// Get tail node.
U8ListNode U8List_getTail(U8List self);

/// Get the number of nodes.
size_t U8List_getLength(U8List self);

size_t U8List_pushFront(U8List self, uint8_t value);

size_t U8List_pushBack(U8List self, uint8_t value);


#endif
