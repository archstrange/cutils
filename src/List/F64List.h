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
#ifndef CUTILS_F64List_H
#define CUTILS_F64List_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// F64List: a double linked list type.
typedef struct _ADT_F64List_ *F64List;

/// F64ListNode: F64List node type.
typedef struct _ADT_F64ListNode_ *F64ListNode;

/// Set the data hold by @self to @value.
void F64ListNode_set(F64ListNode self, double value);

/// Get the data hold by @self.
double F64ListNode_get(F64ListNode self);

/// Get next node. If @self is tail-node, NULL will be returned.
F64ListNode F64ListNode_getNext(F64ListNode self);

/// Get previous node. If @self is head-node, NULL will be returned.
F64ListNode F64ListNode_getPrev(F64ListNode self);

/// Create a new node that hold @value and insert it as
/// @self's previous node.
F64ListNode F64ListNode_insertPrev(F64ListNode self, double value);

/// Create a new node that hold @value and insert it as
/// @self's next node.
F64ListNode F64ListNode_insertNext(F64ListNode self, double value);

/// Delete this node from list.
size_t F64ListNode_delete(F64ListNode self);

/// Create a new empty F64List object.
F64List F64List_new();

F64List F64List_clone(F64List src);

void F64List_copy(F64List self, F64List src);

/// Free @self.
void F64List_free(F64List self);

/// Get head node.
F64ListNode F64List_getHead(F64List self);

/// Get tail node.
F64ListNode F64List_getTail(F64List self);

/// Get the number of nodes.
size_t F64List_getLength(F64List self);

size_t F64List_pushFront(F64List self, double value);

size_t F64List_pushBack(F64List self, double value);


#endif
