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
#include "I64List.h"


struct _ADT_I64ListNode_ {
	int64_t value;
	I64ListNode prev, next;
	I64List list;
};

struct _ADT_I64List_ {
	struct _ADT_I64ListNode_ guard;
	size_t length;
};

static inline I64ListNode Node_newInList(I64List list,
					      int64_t value,
					      I64ListNode prev,
					      I64ListNode next)
{
	I64ListNode self = malloc(sizeof(*self));
	self->value = value;
	self->list = list;
	self->prev = prev;
	self->next = next;
	prev->next = next->prev = self;
	return self;
}

// Return @self's next node.
static inline I64ListNode I64ListNode_freeInList(I64ListNode self);

void I64ListNode_set(I64ListNode self, int64_t value)
{
	self->value = value;
}

int64_t I64ListNode_get(I64ListNode self)
{
	return self->value;
}

I64ListNode I64ListNode_getNext(I64ListNode self)
{
	return self->next == &self->list->guard ? NULL : self->next;
}

I64ListNode I64ListNode_getPrev(I64ListNode self)
{
	return self->prev == &self->list->guard ? NULL : self->prev;
}

#define INSERT_PREV(self, value) \
	self->list->length += 1; \
	return Node_newInList(self->list, value, self->prev, self)

I64ListNode I64ListNode_insertPrev(I64ListNode self, int64_t value)
{
	INSERT_PREV(self, value);
}

#define INSERT_NEXT(self, value) \
	self->list->length += 1; \
	Node_newInList(self->list, value, self, self->next)

I64ListNode I64ListNode_insertNext(I64ListNode self, int64_t value)
{
	INSERT_NEXT(self, value);
}

size_t I64ListNode_delete(I64ListNode self)
{
	self->list->length -= 1;
	self = I64ListNode_freeInList(self);
	return self->list->length;
}

I64List I64List_new()
{
	I64List self = malloc(sizeof(*self));
	self->guard.next = self->guard.prev = &self->guard;
	self->guard.list = self;
	self->length = 0;
	return self;
}

I64List I64List_clone(I64List src)
{
	I64List self = I64List_new();
	I64ListNode n = src->guard.next;
	while (n != &src->guard) {
		I64List_pushBack(self, n->value);
		n = n->next;
	}
	return self;
}

void I64List_copy(I64List self, I64List src)
{
	I64ListNode dstnode = self->guard.next,
		   srcnode = src->guard.next;
	bool dst_done = dstnode == &self->guard;
	bool src_done = srcnode == &src->guard;
	while (!dst_done || !src_done) {
		if (dst_done) { // dst is short than src
			I64List_pushBack(self, srcnode->value);
			srcnode = srcnode->next;
			src_done = srcnode == &src->guard;
		} else if (src_done) { // src is short than dst
			dstnode = I64ListNode_freeInList(dstnode);
			dst_done = dstnode == &self->guard;
		} else { // still in the middle...
			dstnode->value = srcnode->value;
			dst_done = (dstnode = dstnode->next) == &self->guard;
			src_done = (srcnode = srcnode->next) == &src->guard;
		}
	}
	self->length = src->length;
}

void I64List_free(I64List self)
{
	if (self != NULL) {
		I64ListNode n = self->guard.next;
		while (n != &self->guard) {
			n = I64ListNode_freeInList(n);
		}
		free(self);
	}
}

I64ListNode I64List_getHead(I64List self)
{
	return self->guard.next == &self->guard ? NULL : self->guard.next;
}

I64ListNode I64List_getTail(I64List self)
{
	return self->guard.prev == &self->guard ? NULL : self->guard.prev;
}

size_t I64List_getLength(I64List self)
{
	return self->length;
}

#define PUSH_FRONT(self, value) \
	Node_newInList(self, value, &self->guard, self->guard.next); \
	self->length += 1; \
	return self->length

size_t I64List_pushFront(I64List self, int64_t value)
{
	PUSH_FRONT(self, value);
}

#define PUSH_BACK(self, value) \
	Node_newInList(self, value, self->guard.prev, &self->guard); \
	self->length += 1; \
	return self->length

size_t I64List_pushBack(I64List self, int64_t value)
{
	PUSH_BACK(self, value);
}

static inline I64ListNode I64ListNode_freeInList(I64ListNode self)
{
	I64ListNode next = self->next;
	self->prev->next = self->next;
	self->next->prev = self->prev;
	free(self);
	return next;
}

