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
#include "I8List.h"


struct _ADT_I8ListNode_ {
	int8_t value;
	I8ListNode prev, next;
	I8List list;
};

struct _ADT_I8List_ {
	struct _ADT_I8ListNode_ guard;
	size_t length;
};

static inline I8ListNode Node_newInList(I8List list,
					      int8_t value,
					      I8ListNode prev,
					      I8ListNode next)
{
	I8ListNode self = malloc(sizeof(*self));
	self->value = value;
	self->list = list;
	self->prev = prev;
	self->next = next;
	prev->next = next->prev = self;
	return self;
}

// Return @self's next node.
static inline I8ListNode I8ListNode_freeInList(I8ListNode self);

void I8ListNode_set(I8ListNode self, int8_t value)
{
	self->value = value;
}

int8_t I8ListNode_get(I8ListNode self)
{
	return self->value;
}

I8ListNode I8ListNode_getNext(I8ListNode self)
{
	return self->next == &self->list->guard ? NULL : self->next;
}

I8ListNode I8ListNode_getPrev(I8ListNode self)
{
	return self->prev == &self->list->guard ? NULL : self->prev;
}

#define INSERT_PREV(self, value) \
	self->list->length += 1; \
	return Node_newInList(self->list, value, self->prev, self)

I8ListNode I8ListNode_insertPrev(I8ListNode self, int8_t value)
{
	INSERT_PREV(self, value);
}

#define INSERT_NEXT(self, value) \
	self->list->length += 1; \
	Node_newInList(self->list, value, self, self->next)

I8ListNode I8ListNode_insertNext(I8ListNode self, int8_t value)
{
	INSERT_NEXT(self, value);
}

size_t I8ListNode_delete(I8ListNode self)
{
	self->list->length -= 1;
	self = I8ListNode_freeInList(self);
	return self->list->length;
}

I8List I8List_new()
{
	I8List self = malloc(sizeof(*self));
	self->guard.next = self->guard.prev = &self->guard;
	self->guard.list = self;
	self->length = 0;
	return self;
}

I8List I8List_clone(I8List src)
{
	I8List self = I8List_new();
	I8ListNode n = src->guard.next;
	while (n != &src->guard) {
		I8List_pushBack(self, n->value);
		n = n->next;
	}
	return self;
}

void I8List_copy(I8List self, I8List src)
{
	I8ListNode dstnode = self->guard.next,
		   srcnode = src->guard.next;
	bool dst_done = dstnode == &self->guard;
	bool src_done = srcnode == &src->guard;
	while (!dst_done || !src_done) {
		if (dst_done) { // dst is short than src
			I8List_pushBack(self, srcnode->value);
			srcnode = srcnode->next;
			src_done = srcnode == &src->guard;
		} else if (src_done) { // src is short than dst
			dstnode = I8ListNode_freeInList(dstnode);
			dst_done = dstnode == &self->guard;
		} else { // still in the middle...
			dstnode->value = srcnode->value;
			dst_done = (dstnode = dstnode->next) == &self->guard;
			src_done = (srcnode = srcnode->next) == &src->guard;
		}
	}
	self->length = src->length;
}

void I8List_free(I8List self)
{
	if (self != NULL) {
		I8ListNode n = self->guard.next;
		while (n != &self->guard) {
			n = I8ListNode_freeInList(n);
		}
		free(self);
	}
}

I8ListNode I8List_getHead(I8List self)
{
	return self->guard.next == &self->guard ? NULL : self->guard.next;
}

I8ListNode I8List_getTail(I8List self)
{
	return self->guard.prev == &self->guard ? NULL : self->guard.prev;
}

size_t I8List_getLength(I8List self)
{
	return self->length;
}

#define PUSH_FRONT(self, value) \
	Node_newInList(self, value, &self->guard, self->guard.next); \
	self->length += 1; \
	return self->length

size_t I8List_pushFront(I8List self, int8_t value)
{
	PUSH_FRONT(self, value);
}

#define PUSH_BACK(self, value) \
	Node_newInList(self, value, self->guard.prev, &self->guard); \
	self->length += 1; \
	return self->length

size_t I8List_pushBack(I8List self, int8_t value)
{
	PUSH_BACK(self, value);
}

static inline I8ListNode I8ListNode_freeInList(I8ListNode self)
{
	I8ListNode next = self->next;
	self->prev->next = self->next;
	self->next->prev = self->prev;
	free(self);
	return next;
}

