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
#ifndef CUTILS_I64List_H
#define CUTILS_I64List_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// I64List: a double linked list type.
typedef struct _ADT_I64List_ *I64List;

/// I64ListNode: I64List node type.
typedef struct _ADT_I64ListNode_ *I64ListNode;

/// Set the data hold by @self to @value.
void I64ListNode_set(I64ListNode self, int64_t value);

/// Get the data hold by @self.
int64_t I64ListNode_get(I64ListNode self);

/// Get next node. If @self is tail-node, NULL will be returned.
I64ListNode I64ListNode_getNext(I64ListNode self);

/// Get previous node. If @self is head-node, NULL will be returned.
I64ListNode I64ListNode_getPrev(I64ListNode self);

/// Create a new node that hold @value and insert it as
/// @self's previous node.
I64ListNode I64ListNode_insertPrev(I64ListNode self, int64_t value);

/// Create a new node that hold @value and insert it as
/// @self's next node.
I64ListNode I64ListNode_insertNext(I64ListNode self, int64_t value);

/// Delete this node from list.
size_t I64ListNode_delete(I64ListNode self);

/// Create a new empty I64List object.
I64List I64List_new();

I64List I64List_clone(I64List src);

void I64List_copy(I64List self, I64List src);

/// Free @self.
void I64List_free(I64List self);

/// Get head node.
I64ListNode I64List_getHead(I64List self);

/// Get tail node.
I64ListNode I64List_getTail(I64List self);

/// Get the number of nodes.
size_t I64List_getLength(I64List self);

size_t I64List_pushFront(I64List self, int64_t value);

size_t I64List_pushBack(I64List self, int64_t value);


#endif
