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
#ifndef CUTILS_I32List_H
#define CUTILS_I32List_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// I32List: a double linked list type.
typedef struct _ADT_I32List_ *I32List;

/// I32ListNode: I32List node type.
typedef struct _ADT_I32ListNode_ *I32ListNode;

/// Set the data hold by @self to @value.
void I32ListNode_set(I32ListNode self, int32_t value);

/// Get the data hold by @self.
int32_t I32ListNode_get(I32ListNode self);

/// Get next node. If @self is tail-node, NULL will be returned.
I32ListNode I32ListNode_getNext(I32ListNode self);

/// Get previous node. If @self is head-node, NULL will be returned.
I32ListNode I32ListNode_getPrev(I32ListNode self);

/// Create a new node that hold @value and insert it as
/// @self's previous node.
I32ListNode I32ListNode_insertPrev(I32ListNode self, int32_t value);

/// Create a new node that hold @value and insert it as
/// @self's next node.
I32ListNode I32ListNode_insertNext(I32ListNode self, int32_t value);

/// Delete this node from list.
size_t I32ListNode_delete(I32ListNode self);

/// Create a new empty I32List object.
I32List I32List_new();

I32List I32List_clone(I32List src);

void I32List_copy(I32List self, I32List src);

/// Free @self.
void I32List_free(I32List self);

/// Get head node.
I32ListNode I32List_getHead(I32List self);

/// Get tail node.
I32ListNode I32List_getTail(I32List self);

/// Get the number of nodes.
size_t I32List_getLength(I32List self);

size_t I32List_pushFront(I32List self, int32_t value);

size_t I32List_pushBack(I32List self, int32_t value);


#endif
