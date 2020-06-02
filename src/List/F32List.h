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
#ifndef CUTILS_F32List_H
#define CUTILS_F32List_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// F32List: a double linked list type.
typedef struct _ADT_F32List_ *F32List;

/// F32ListNode: F32List node type.
typedef struct _ADT_F32ListNode_ *F32ListNode;

/// Set the data hold by @self to @value.
void F32ListNode_set(F32ListNode self, float value);

/// Get the data hold by @self.
float F32ListNode_get(F32ListNode self);

/// Get next node. If @self is tail-node, NULL will be returned.
F32ListNode F32ListNode_getNext(F32ListNode self);

/// Get previous node. If @self is head-node, NULL will be returned.
F32ListNode F32ListNode_getPrev(F32ListNode self);

/// Create a new node that hold @value and insert it as
/// @self's previous node.
F32ListNode F32ListNode_insertPrev(F32ListNode self, float value);

/// Create a new node that hold @value and insert it as
/// @self's next node.
F32ListNode F32ListNode_insertNext(F32ListNode self, float value);

/// Delete this node from list.
size_t F32ListNode_delete(F32ListNode self);

/// Create a new empty F32List object.
F32List F32List_new();

F32List F32List_clone(F32List src);

void F32List_copy(F32List self, F32List src);

/// Free @self.
void F32List_free(F32List self);

/// Get head node.
F32ListNode F32List_getHead(F32List self);

/// Get tail node.
F32ListNode F32List_getTail(F32List self);

/// Get the number of nodes.
size_t F32List_getLength(F32List self);

size_t F32List_pushFront(F32List self, float value);

size_t F32List_pushBack(F32List self, float value);


#endif
