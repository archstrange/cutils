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

// This file is generated from List.c.ohce by ohce.
#include "StrList.h"


struct _ADT_StrListNode_ {
	Str value;
	StrListNode prev, next;
	StrList list;
};

struct _ADT_StrList_ {
	struct _ADT_StrListNode_ guard;
	size_t length;
};

#define Node_newInList(list, value, prev, next) \
_Generic(value, \
	 Str: Node_newInList_use_assign, \
	 default: Node_newInList_use_copy \
) (list, value, prev, next)

static inline StrListNode Node_newInList_use_copy(StrList list,
					     Str *value,
					     StrListNode prev,
					     StrListNode next)
{
	StrListNode self = malloc(sizeof(*self));
	self->value = Str_clone(*value);
	self->list = list;
	self->prev = prev;
	self->next = next;
	prev->next = next->prev = self;
	return self;
}

static inline StrListNode Node_newInList_use_assign(StrList list,
					     Str value,
					     StrListNode prev,
					     StrListNode next)
{
	StrListNode self = malloc(sizeof(*self));
	self->value = value;
	self->list = list;
	self->prev = prev;
	self->next = next;
	prev->next = next->prev = self;
	return self;
}

// Return @self's next node.
static inline StrListNode StrListNode_freeInList(StrListNode self);

void __StrListNode_set_use_copy(StrListNode self, Str *value)
{
	Str_copy(self->value, *value);
}

void __StrListNode_set_use_assign(StrListNode self, Str value)
{
	Str_free(self->value);
	self->value = value;
}

Str StrListNode_get(StrListNode self)
{
	return self->value;
}

StrListNode StrListNode_getNext(StrListNode self)
{
	return self->next == &self->list->guard ? NULL : self->next;
}

StrListNode StrListNode_getPrev(StrListNode self)
{
	return self->prev == &self->list->guard ? NULL : self->prev;
}

#define INSERT_PREV(self, value) \
	self->list->length += 1; \
	return Node_newInList(self->list, value, self->prev, self)

StrListNode __StrListNode_insertPrev_use_clone(StrListNode self, Str *value)
{
	INSERT_PREV(self, value);
}

StrListNode __StrListNode_insertPrev_use_assign(StrListNode self, Str value)
{
	INSERT_PREV(self, value);
}

#define INSERT_NEXT(self, value) \
	self->list->length += 1; \
	Node_newInList(self->list, value, self, self->next)

StrListNode __StrListNode_insertNext_use_clone(StrListNode self, Str *value)
{
	INSERT_NEXT(self, value);
}

StrListNode __StrListNode_insertNext_use_assign(StrListNode self, Str value)
{
	INSERT_NEXT(self, value);
}

size_t StrListNode_delete(StrListNode self)
{
	self->list->length -= 1;
	self = StrListNode_freeInList(self);
	return self->list->length;
}

StrList StrList_new()
{
	StrList self = malloc(sizeof(*self));
	self->guard.next = self->guard.prev = &self->guard;
	self->guard.list = self;
	self->length = 0;
	return self;
}

StrList StrList_clone(StrList src)
{
	StrList self = StrList_new();
	StrListNode n = src->guard.next;
	while (n != &src->guard) {
		StrList_pushBack(self, &n->value);
		n = n->next;
	}
	return self;
}

void StrList_copy(StrList self, StrList src)
{
	StrListNode dstnode = self->guard.next,
		   srcnode = src->guard.next;
	bool dst_done = dstnode == &self->guard;
	bool src_done = srcnode == &src->guard;
	while (!dst_done || !src_done) {
		if (dst_done) { // dst is short than src
			StrList_pushBack(self, &srcnode->value);
			srcnode = srcnode->next;
			src_done = srcnode == &src->guard;
		} else if (src_done) { // src is short than dst
			dstnode = StrListNode_freeInList(dstnode);
			dst_done = dstnode == &self->guard;
		} else { // still in the middle...
			Str_copy(dstnode->value, srcnode->value);
			dst_done = (dstnode = dstnode->next) == &self->guard;
			src_done = (srcnode = srcnode->next) == &src->guard;
		}
	}
	self->length = src->length;
}

void StrList_free(StrList self)
{
	if (self != NULL) {
		StrListNode n = self->guard.next;
		while (n != &self->guard) {
			n = StrListNode_freeInList(n);
		}
		free(self);
	}
}

StrListNode StrList_getHead(StrList self)
{
	return self->guard.next == &self->guard ? NULL : self->guard.next;
}

StrListNode StrList_getTail(StrList self)
{
	return self->guard.prev == &self->guard ? NULL : self->guard.prev;
}

size_t StrList_getLength(StrList self)
{
	return self->length;
}

#define PUSH_FRONT(self, value) \
	Node_newInList(self, value, &self->guard, self->guard.next); \
	self->length += 1; \
	return self->length

size_t __StrList_pushFront_use_clone(StrList self, Str *value)
{
	PUSH_FRONT(self, value);
}

size_t __StrList_pushFront_use_assign(StrList self, Str value)
{
	PUSH_FRONT(self, value);
}

#define PUSH_BACK(self, value) \
	Node_newInList(self, value, self->guard.prev, &self->guard); \
	self->length += 1; \
	return self->length

size_t __StrList_pushBack_use_clone(StrList self, Str *value)
{
	PUSH_BACK(self, value);
}

size_t __StrList_pushBack_use_assign(StrList self, Str value)
{
	PUSH_BACK(self, value);
}

static inline StrListNode StrListNode_freeInList(StrListNode self)
{
	StrListNode next = self->next;
	self->prev->next = self->next;
	self->next->prev = self->prev;
	Str_free(self->value);
	return next;
}

