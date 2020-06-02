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
#ifndef CUTILS_I16List_H
#define CUTILS_I16List_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// I16List: a double linked list type.
typedef struct _ADT_I16List_ *I16List;

/// I16ListNode: I16List node type.
typedef struct _ADT_I16ListNode_ *I16ListNode;

/// Set the data hold by @self to @value.
void I16ListNode_set(I16ListNode self, int16_t value);

/// Get the data hold by @self.
int16_t I16ListNode_get(I16ListNode self);

/// Get next node. If @self is tail-node, NULL will be returned.
I16ListNode I16ListNode_getNext(I16ListNode self);

/// Get previous node. If @self is head-node, NULL will be returned.
I16ListNode I16ListNode_getPrev(I16ListNode self);

/// Create a new node that hold @value and insert it as
/// @self's previous node.
I16ListNode I16ListNode_insertPrev(I16ListNode self, int16_t value);

/// Create a new node that hold @value and insert it as
/// @self's next node.
I16ListNode I16ListNode_insertNext(I16ListNode self, int16_t value);

/// Delete this node from list.
size_t I16ListNode_delete(I16ListNode self);

/// Create a new empty I16List object.
I16List I16List_new();

I16List I16List_clone(I16List src);

void I16List_copy(I16List self, I16List src);

/// Free @self.
void I16List_free(I16List self);

/// Get head node.
I16ListNode I16List_getHead(I16List self);

/// Get tail node.
I16ListNode I16List_getTail(I16List self);

/// Get the number of nodes.
size_t I16List_getLength(I16List self);

size_t I16List_pushFront(I16List self, int16_t value);

size_t I16List_pushBack(I16List self, int16_t value);


#endif
