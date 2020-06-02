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
#ifndef CUTILS_I8List_H
#define CUTILS_I8List_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// I8List: a double linked list type.
typedef struct _ADT_I8List_ *I8List;

/// I8ListNode: I8List node type.
typedef struct _ADT_I8ListNode_ *I8ListNode;

/// Set the data hold by @self to @value.
void I8ListNode_set(I8ListNode self, int8_t value);

/// Get the data hold by @self.
int8_t I8ListNode_get(I8ListNode self);

/// Get next node. If @self is tail-node, NULL will be returned.
I8ListNode I8ListNode_getNext(I8ListNode self);

/// Get previous node. If @self is head-node, NULL will be returned.
I8ListNode I8ListNode_getPrev(I8ListNode self);

/// Create a new node that hold @value and insert it as
/// @self's previous node.
I8ListNode I8ListNode_insertPrev(I8ListNode self, int8_t value);

/// Create a new node that hold @value and insert it as
/// @self's next node.
I8ListNode I8ListNode_insertNext(I8ListNode self, int8_t value);

/// Delete this node from list.
size_t I8ListNode_delete(I8ListNode self);

/// Create a new empty I8List object.
I8List I8List_new();

I8List I8List_clone(I8List src);

void I8List_copy(I8List self, I8List src);

/// Free @self.
void I8List_free(I8List self);

/// Get head node.
I8ListNode I8List_getHead(I8List self);

/// Get tail node.
I8ListNode I8List_getTail(I8List self);

/// Get the number of nodes.
size_t I8List_getLength(I8List self);

size_t I8List_pushFront(I8List self, int8_t value);

size_t I8List_pushBack(I8List self, int8_t value);


#endif
