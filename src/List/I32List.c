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
#include "I32List.h"


struct _ADT_I32ListNode_ {
	int32_t value;
	I32ListNode prev, next;
	I32List list;
};

struct _ADT_I32List_ {
	struct _ADT_I32ListNode_ guard;
	size_t length;
};

static inline I32ListNode Node_newInList(I32List list,
					      int32_t value,
					      I32ListNode prev,
					      I32ListNode next)
{
	I32ListNode self = malloc(sizeof(*self));
	self->value = value;
	self->list = list;
	self->prev = prev;
	self->next = next;
	prev->next = next->prev = self;
	return self;
}

// Return @self's next node.
static inline I32ListNode I32ListNode_freeInList(I32ListNode self);

void I32ListNode_set(I32ListNode self, int32_t value)
{
	self->value = value;
}

int32_t I32ListNode_get(I32ListNode self)
{
	return self->value;
}

I32ListNode I32ListNode_getNext(I32ListNode self)
{
	return self->next == &self->list->guard ? NULL : self->next;
}

I32ListNode I32ListNode_getPrev(I32ListNode self)
{
	return self->prev == &self->list->guard ? NULL : self->prev;
}

#define INSERT_PREV(self, value) \
	self->list->length += 1; \
	return Node_newInList(self->list, value, self->prev, self)

I32ListNode I32ListNode_insertPrev(I32ListNode self, int32_t value)
{
	INSERT_PREV(self, value);
}

#define INSERT_NEXT(self, value) \
	self->list->length += 1; \
	Node_newInList(self->list, value, self, self->next)

I32ListNode I32ListNode_insertNext(I32ListNode self, int32_t value)
{
	INSERT_NEXT(self, value);
}

size_t I32ListNode_delete(I32ListNode self)
{
	self->list->length -= 1;
	self = I32ListNode_freeInList(self);
	return self->list->length;
}

I32List I32List_new()
{
	I32List self = malloc(sizeof(*self));
	self->guard.next = self->guard.prev = &self->guard;
	self->guard.list = self;
	self->length = 0;
	return self;
}

I32List I32List_clone(I32List src)
{
	I32List self = I32List_new();
	I32ListNode n = src->guard.next;
	while (n != &src->guard) {
		I32List_pushBack(self, n->value);
		n = n->next;
	}
	return self;
}

void I32List_copy(I32List self, I32List src)
{
	I32ListNode dstnode = self->guard.next,
		   srcnode = src->guard.next;
	bool dst_done = dstnode == &self->guard;
	bool src_done = srcnode == &src->guard;
	while (!dst_done || !src_done) {
		if (dst_done) { // dst is short than src
			I32List_pushBack(self, srcnode->value);
			srcnode = srcnode->next;
			src_done = srcnode == &src->guard;
		} else if (src_done) { // src is short than dst
			dstnode = I32ListNode_freeInList(dstnode);
			dst_done = dstnode == &self->guard;
		} else { // still in the middle...
			dstnode->value = srcnode->value;
			dst_done = (dstnode = dstnode->next) == &self->guard;
			src_done = (srcnode = srcnode->next) == &src->guard;
		}
	}
	self->length = src->length;
}

void I32List_free(I32List self)
{
	if (self != NULL) {
		I32ListNode n = self->guard.next;
		while (n != &self->guard) {
			n = I32ListNode_freeInList(n);
		}
		free(self);
	}
}

I32ListNode I32List_getHead(I32List self)
{
	return self->guard.next == &self->guard ? NULL : self->guard.next;
}

I32ListNode I32List_getTail(I32List self)
{
	return self->guard.prev == &self->guard ? NULL : self->guard.prev;
}

size_t I32List_getLength(I32List self)
{
	return self->length;
}

#define PUSH_FRONT(self, value) \
	Node_newInList(self, value, &self->guard, self->guard.next); \
	self->length += 1; \
	return self->length

size_t I32List_pushFront(I32List self, int32_t value)
{
	PUSH_FRONT(self, value);
}

#define PUSH_BACK(self, value) \
	Node_newInList(self, value, self->guard.prev, &self->guard); \
	self->length += 1; \
	return self->length

size_t I32List_pushBack(I32List self, int32_t value)
{
	PUSH_BACK(self, value);
}

static inline I32ListNode I32ListNode_freeInList(I32ListNode self)
{
	I32ListNode next = self->next;
	self->prev->next = self->next;
	self->next->prev = self->prev;
	free(self);
	return next;
}

