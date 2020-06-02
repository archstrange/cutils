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
#include "U32List.h"


struct _ADT_U32ListNode_ {
	uint32_t value;
	U32ListNode prev, next;
	U32List list;
};

struct _ADT_U32List_ {
	struct _ADT_U32ListNode_ guard;
	size_t length;
};

static inline U32ListNode Node_newInList(U32List list,
					      uint32_t value,
					      U32ListNode prev,
					      U32ListNode next)
{
	U32ListNode self = malloc(sizeof(*self));
	self->value = value;
	self->list = list;
	self->prev = prev;
	self->next = next;
	prev->next = next->prev = self;
	return self;
}

// Return @self's next node.
static inline U32ListNode U32ListNode_freeInList(U32ListNode self);

void U32ListNode_set(U32ListNode self, uint32_t value)
{
	self->value = value;
}

uint32_t U32ListNode_get(U32ListNode self)
{
	return self->value;
}

U32ListNode U32ListNode_getNext(U32ListNode self)
{
	return self->next == &self->list->guard ? NULL : self->next;
}

U32ListNode U32ListNode_getPrev(U32ListNode self)
{
	return self->prev == &self->list->guard ? NULL : self->prev;
}

#define INSERT_PREV(self, value) \
	self->list->length += 1; \
	return Node_newInList(self->list, value, self->prev, self)

U32ListNode U32ListNode_insertPrev(U32ListNode self, uint32_t value)
{
	INSERT_PREV(self, value);
}

#define INSERT_NEXT(self, value) \
	self->list->length += 1; \
	Node_newInList(self->list, value, self, self->next)

U32ListNode U32ListNode_insertNext(U32ListNode self, uint32_t value)
{
	INSERT_NEXT(self, value);
}

size_t U32ListNode_delete(U32ListNode self)
{
	self->list->length -= 1;
	self = U32ListNode_freeInList(self);
	return self->list->length;
}

U32List U32List_new()
{
	U32List self = malloc(sizeof(*self));
	self->guard.next = self->guard.prev = &self->guard;
	self->guard.list = self;
	self->length = 0;
	return self;
}

U32List U32List_clone(U32List src)
{
	U32List self = U32List_new();
	U32ListNode n = src->guard.next;
	while (n != &src->guard) {
		U32List_pushBack(self, n->value);
		n = n->next;
	}
	return self;
}

void U32List_copy(U32List self, U32List src)
{
	U32ListNode dstnode = self->guard.next,
		   srcnode = src->guard.next;
	bool dst_done = dstnode == &self->guard;
	bool src_done = srcnode == &src->guard;
	while (!dst_done || !src_done) {
		if (dst_done) { // dst is short than src
			U32List_pushBack(self, srcnode->value);
			srcnode = srcnode->next;
			src_done = srcnode == &src->guard;
		} else if (src_done) { // src is short than dst
			dstnode = U32ListNode_freeInList(dstnode);
			dst_done = dstnode == &self->guard;
		} else { // still in the middle...
			dstnode->value = srcnode->value;
			dst_done = (dstnode = dstnode->next) == &self->guard;
			src_done = (srcnode = srcnode->next) == &src->guard;
		}
	}
	self->length = src->length;
}

void U32List_free(U32List self)
{
	if (self != NULL) {
		U32ListNode n = self->guard.next;
		while (n != &self->guard) {
			n = U32ListNode_freeInList(n);
		}
		free(self);
	}
}

U32ListNode U32List_getHead(U32List self)
{
	return self->guard.next == &self->guard ? NULL : self->guard.next;
}

U32ListNode U32List_getTail(U32List self)
{
	return self->guard.prev == &self->guard ? NULL : self->guard.prev;
}

size_t U32List_getLength(U32List self)
{
	return self->length;
}

#define PUSH_FRONT(self, value) \
	Node_newInList(self, value, &self->guard, self->guard.next); \
	self->length += 1; \
	return self->length

size_t U32List_pushFront(U32List self, uint32_t value)
{
	PUSH_FRONT(self, value);
}

#define PUSH_BACK(self, value) \
	Node_newInList(self, value, self->guard.prev, &self->guard); \
	self->length += 1; \
	return self->length

size_t U32List_pushBack(U32List self, uint32_t value)
{
	PUSH_BACK(self, value);
}

static inline U32ListNode U32ListNode_freeInList(U32ListNode self)
{
	U32ListNode next = self->next;
	self->prev->next = self->next;
	self->next->prev = self->prev;
	free(self);
	return next;
}

