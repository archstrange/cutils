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
#ifndef CUTILS_StrList_H
#define CUTILS_StrList_H
#include "../Vector/Str.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// StrList: a double linked list type.
typedef struct _ADT_StrList_ *StrList;

/// StrListNode: StrList node type.
typedef struct _ADT_StrListNode_ *StrListNode;

/// Set the data hold by @self to @value.
#define StrListNode_set(self, value) \
_Generic(value, \
	 Str: __StrListNode_set_use_assign, \
	 default: __StrListNode_set_use_copy \
) (self, value)

void __StrListNode_set_use_copy(StrListNode self, Str *value);
void __StrListNode_set_use_assign(StrListNode self, Str value);

/// Get the data hold by @self.
Str StrListNode_get(StrListNode self);

/// Get next node. If @self is tail-node, NULL will be returned.
StrListNode StrListNode_getNext(StrListNode self);

/// Get previous node. If @self is head-node, NULL will be returned.
StrListNode StrListNode_getPrev(StrListNode self);

/// Create a new node that hold @value and insert it as
/// @self's previous node.
#define StrListNode_insertPrev(self, value) \
_Generic(value, \
	 Str: __StrListNode_insertPrev_use_assign, \
	 default: __StrListNode_insertPrev_use_clone \
) (self, value)

StrListNode __StrListNode_insertPrev_use_clone(StrListNode self, Str *value);
StrListNode __StrListNode_insertPrev_use_assign(StrListNode self, Str value);

/// Create a new node that hold @value and insert it as
/// @self's next node.
#define StrListNode_insertNext(self, value) \
_Generic(value, \
	 Str: __StrListNode_insertNext_use_assign, \
	 default: __StrListNode_insertNext_use_clone \
) (self, value)

StrListNode __StrListNode_insertNext_use_clone(StrListNode self, Str *value);
StrListNode __StrListNode_insertNext_use_assign(StrListNode self, Str value);

/// Delete this node from list.
size_t StrListNode_delete(StrListNode self);

/// Create a new empty StrList object.
StrList StrList_new();

StrList StrList_clone(StrList src);

void StrList_copy(StrList self, StrList src);

/// Free @self.
void StrList_free(StrList self);

/// Get head node.
StrListNode StrList_getHead(StrList self);

/// Get tail node.
StrListNode StrList_getTail(StrList self);

/// Get the number of nodes.
size_t StrList_getLength(StrList self);

#define StrList_pushFront(self, value) \
_Generic(value, \
	 Str: __StrList_pushFront_use_assign, \
	 default: __StrList_pushFront_use_clone \
) (self, value)

size_t __StrList_pushFront_use_clone(StrList self, Str *value);
size_t __StrList_pushFront_use_assign(StrList self, Str value);

#define StrList_pushBack(self, value) \
_Generic(value, \
	 Str: __StrList_pushBack_use_assign, \
	 default: __StrList_pushBack_use_clone \
) (self, value)

size_t __StrList_pushBack_use_clone(StrList self, Str *value);
size_t __StrList_pushBack_use_assign(StrList self, Str value);


#endif
