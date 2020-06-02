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
#include "I16List.h"


struct _ADT_I16ListNode_ {
	int16_t value;
	I16ListNode prev, next;
	I16List list;
};

struct _ADT_I16List_ {
	struct _ADT_I16ListNode_ guard;
	size_t length;
};

static inline I16ListNode Node_newInList(I16List list,
					      int16_t value,
					      I16ListNode prev,
					      I16ListNode next)
{
	I16ListNode self = malloc(sizeof(*self));
	self->value = value;
	self->list = list;
	self->prev = prev;
	self->next = next;
	prev->next = next->prev = self;
	return self;
}

// Return @self's next node.
static inline I16ListNode I16ListNode_freeInList(I16ListNode self);

void I16ListNode_set(I16ListNode self, int16_t value)
{
	self->value = value;
}

int16_t I16ListNode_get(I16ListNode self)
{
	return self->value;
}

I16ListNode I16ListNode_getNext(I16ListNode self)
{
	return self->next == &self->list->guard ? NULL : self->next;
}

I16ListNode I16ListNode_getPrev(I16ListNode self)
{
	return self->prev == &self->list->guard ? NULL : self->prev;
}

#define INSERT_PREV(self, value) \
	self->list->length += 1; \
	return Node_newInList(self->list, value, self->prev, self)

I16ListNode I16ListNode_insertPrev(I16ListNode self, int16_t value)
{
	INSERT_PREV(self, value);
}

#define INSERT_NEXT(self, value) \
	self->list->length += 1; \
	Node_newInList(self->list, value, self, self->next)

I16ListNode I16ListNode_insertNext(I16ListNode self, int16_t value)
{
	INSERT_NEXT(self, value);
}

size_t I16ListNode_delete(I16ListNode self)
{
	self->list->length -= 1;
	self = I16ListNode_freeInList(self);
	return self->list->length;
}

I16List I16List_new()
{
	I16List self = malloc(sizeof(*self));
	self->guard.next = self->guard.prev = &self->guard;
	self->guard.list = self;
	self->length = 0;
	return self;
}

I16List I16List_clone(I16List src)
{
	I16List self = I16List_new();
	I16ListNode n = src->guard.next;
	while (n != &src->guard) {
		I16List_pushBack(self, n->value);
		n = n->next;
	}
	return self;
}

void I16List_copy(I16List self, I16List src)
{
	I16ListNode dstnode = self->guard.next,
		   srcnode = src->guard.next;
	bool dst_done = dstnode == &self->guard;
	bool src_done = srcnode == &src->guard;
	while (!dst_done || !src_done) {
		if (dst_done) { // dst is short than src
			I16List_pushBack(self, srcnode->value);
			srcnode = srcnode->next;
			src_done = srcnode == &src->guard;
		} else if (src_done) { // src is short than dst
			dstnode = I16ListNode_freeInList(dstnode);
			dst_done = dstnode == &self->guard;
		} else { // still in the middle...
			dstnode->value = srcnode->value;
			dst_done = (dstnode = dstnode->next) == &self->guard;
			src_done = (srcnode = srcnode->next) == &src->guard;
		}
	}
	self->length = src->length;
}

void I16List_free(I16List self)
{
	if (self != NULL) {
		I16ListNode n = self->guard.next;
		while (n != &self->guard) {
			n = I16ListNode_freeInList(n);
		}
		free(self);
	}
}

I16ListNode I16List_getHead(I16List self)
{
	return self->guard.next == &self->guard ? NULL : self->guard.next;
}

I16ListNode I16List_getTail(I16List self)
{
	return self->guard.prev == &self->guard ? NULL : self->guard.prev;
}

size_t I16List_getLength(I16List self)
{
	return self->length;
}

#define PUSH_FRONT(self, value) \
	Node_newInList(self, value, &self->guard, self->guard.next); \
	self->length += 1; \
	return self->length

size_t I16List_pushFront(I16List self, int16_t value)
{
	PUSH_FRONT(self, value);
}

#define PUSH_BACK(self, value) \
	Node_newInList(self, value, self->guard.prev, &self->guard); \
	self->length += 1; \
	return self->length

size_t I16List_pushBack(I16List self, int16_t value)
{
	PUSH_BACK(self, value);
}

static inline I16ListNode I16ListNode_freeInList(I16ListNode self)
{
	I16ListNode next = self->next;
	self->prev->next = self->next;
	self->next->prev = self->prev;
	free(self);
	return next;
}

