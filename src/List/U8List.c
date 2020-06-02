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
#include "U8List.h"


struct _ADT_U8ListNode_ {
	uint8_t value;
	U8ListNode prev, next;
	U8List list;
};

struct _ADT_U8List_ {
	struct _ADT_U8ListNode_ guard;
	size_t length;
};

static inline U8ListNode Node_newInList(U8List list,
					      uint8_t value,
					      U8ListNode prev,
					      U8ListNode next)
{
	U8ListNode self = malloc(sizeof(*self));
	self->value = value;
	self->list = list;
	self->prev = prev;
	self->next = next;
	prev->next = next->prev = self;
	return self;
}

// Return @self's next node.
static inline U8ListNode U8ListNode_freeInList(U8ListNode self);

void U8ListNode_set(U8ListNode self, uint8_t value)
{
	self->value = value;
}

uint8_t U8ListNode_get(U8ListNode self)
{
	return self->value;
}

U8ListNode U8ListNode_getNext(U8ListNode self)
{
	return self->next == &self->list->guard ? NULL : self->next;
}

U8ListNode U8ListNode_getPrev(U8ListNode self)
{
	return self->prev == &self->list->guard ? NULL : self->prev;
}

#define INSERT_PREV(self, value) \
	self->list->length += 1; \
	return Node_newInList(self->list, value, self->prev, self)

U8ListNode U8ListNode_insertPrev(U8ListNode self, uint8_t value)
{
	INSERT_PREV(self, value);
}

#define INSERT_NEXT(self, value) \
	self->list->length += 1; \
	Node_newInList(self->list, value, self, self->next)

U8ListNode U8ListNode_insertNext(U8ListNode self, uint8_t value)
{
	INSERT_NEXT(self, value);
}

size_t U8ListNode_delete(U8ListNode self)
{
	self->list->length -= 1;
	self = U8ListNode_freeInList(self);
	return self->list->length;
}

U8List U8List_new()
{
	U8List self = malloc(sizeof(*self));
	self->guard.next = self->guard.prev = &self->guard;
	self->guard.list = self;
	self->length = 0;
	return self;
}

U8List U8List_clone(U8List src)
{
	U8List self = U8List_new();
	U8ListNode n = src->guard.next;
	while (n != &src->guard) {
		U8List_pushBack(self, n->value);
		n = n->next;
	}
	return self;
}

void U8List_copy(U8List self, U8List src)
{
	U8ListNode dstnode = self->guard.next,
		   srcnode = src->guard.next;
	bool dst_done = dstnode == &self->guard;
	bool src_done = srcnode == &src->guard;
	while (!dst_done || !src_done) {
		if (dst_done) { // dst is short than src
			U8List_pushBack(self, srcnode->value);
			srcnode = srcnode->next;
			src_done = srcnode == &src->guard;
		} else if (src_done) { // src is short than dst
			dstnode = U8ListNode_freeInList(dstnode);
			dst_done = dstnode == &self->guard;
		} else { // still in the middle...
			dstnode->value = srcnode->value;
			dst_done = (dstnode = dstnode->next) == &self->guard;
			src_done = (srcnode = srcnode->next) == &src->guard;
		}
	}
	self->length = src->length;
}

void U8List_free(U8List self)
{
	if (self != NULL) {
		U8ListNode n = self->guard.next;
		while (n != &self->guard) {
			n = U8ListNode_freeInList(n);
		}
		free(self);
	}
}

U8ListNode U8List_getHead(U8List self)
{
	return self->guard.next == &self->guard ? NULL : self->guard.next;
}

U8ListNode U8List_getTail(U8List self)
{
	return self->guard.prev == &self->guard ? NULL : self->guard.prev;
}

size_t U8List_getLength(U8List self)
{
	return self->length;
}

#define PUSH_FRONT(self, value) \
	Node_newInList(self, value, &self->guard, self->guard.next); \
	self->length += 1; \
	return self->length

size_t U8List_pushFront(U8List self, uint8_t value)
{
	PUSH_FRONT(self, value);
}

#define PUSH_BACK(self, value) \
	Node_newInList(self, value, self->guard.prev, &self->guard); \
	self->length += 1; \
	return self->length

size_t U8List_pushBack(U8List self, uint8_t value)
{
	PUSH_BACK(self, value);
}

static inline U8ListNode U8ListNode_freeInList(U8ListNode self)
{
	U8ListNode next = self->next;
	self->prev->next = self->next;
	self->next->prev = self->prev;
	free(self);
	return next;
}

