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
#include "U16List.h"


struct _ADT_U16ListNode_ {
	uint16_t value;
	U16ListNode prev, next;
	U16List list;
};

struct _ADT_U16List_ {
	struct _ADT_U16ListNode_ guard;
	size_t length;
};

static inline U16ListNode Node_newInList(U16List list,
					      uint16_t value,
					      U16ListNode prev,
					      U16ListNode next)
{
	U16ListNode self = malloc(sizeof(*self));
	self->value = value;
	self->list = list;
	self->prev = prev;
	self->next = next;
	prev->next = next->prev = self;
	return self;
}

// Return @self's next node.
static inline U16ListNode U16ListNode_freeInList(U16ListNode self);

void U16ListNode_set(U16ListNode self, uint16_t value)
{
	self->value = value;
}

uint16_t U16ListNode_get(U16ListNode self)
{
	return self->value;
}

U16ListNode U16ListNode_getNext(U16ListNode self)
{
	return self->next == &self->list->guard ? NULL : self->next;
}

U16ListNode U16ListNode_getPrev(U16ListNode self)
{
	return self->prev == &self->list->guard ? NULL : self->prev;
}

#define INSERT_PREV(self, value) \
	self->list->length += 1; \
	return Node_newInList(self->list, value, self->prev, self)

U16ListNode U16ListNode_insertPrev(U16ListNode self, uint16_t value)
{
	INSERT_PREV(self, value);
}

#define INSERT_NEXT(self, value) \
	self->list->length += 1; \
	Node_newInList(self->list, value, self, self->next)

U16ListNode U16ListNode_insertNext(U16ListNode self, uint16_t value)
{
	INSERT_NEXT(self, value);
}

size_t U16ListNode_delete(U16ListNode self)
{
	self->list->length -= 1;
	self = U16ListNode_freeInList(self);
	return self->list->length;
}

U16List U16List_new()
{
	U16List self = malloc(sizeof(*self));
	self->guard.next = self->guard.prev = &self->guard;
	self->guard.list = self;
	self->length = 0;
	return self;
}

U16List U16List_clone(U16List src)
{
	U16List self = U16List_new();
	U16ListNode n = src->guard.next;
	while (n != &src->guard) {
		U16List_pushBack(self, n->value);
		n = n->next;
	}
	return self;
}

void U16List_copy(U16List self, U16List src)
{
	U16ListNode dstnode = self->guard.next,
		   srcnode = src->guard.next;
	bool dst_done = dstnode == &self->guard;
	bool src_done = srcnode == &src->guard;
	while (!dst_done || !src_done) {
		if (dst_done) { // dst is short than src
			U16List_pushBack(self, srcnode->value);
			srcnode = srcnode->next;
			src_done = srcnode == &src->guard;
		} else if (src_done) { // src is short than dst
			dstnode = U16ListNode_freeInList(dstnode);
			dst_done = dstnode == &self->guard;
		} else { // still in the middle...
			dstnode->value = srcnode->value;
			dst_done = (dstnode = dstnode->next) == &self->guard;
			src_done = (srcnode = srcnode->next) == &src->guard;
		}
	}
	self->length = src->length;
}

void U16List_free(U16List self)
{
	if (self != NULL) {
		U16ListNode n = self->guard.next;
		while (n != &self->guard) {
			n = U16ListNode_freeInList(n);
		}
		free(self);
	}
}

U16ListNode U16List_getHead(U16List self)
{
	return self->guard.next == &self->guard ? NULL : self->guard.next;
}

U16ListNode U16List_getTail(U16List self)
{
	return self->guard.prev == &self->guard ? NULL : self->guard.prev;
}

size_t U16List_getLength(U16List self)
{
	return self->length;
}

#define PUSH_FRONT(self, value) \
	Node_newInList(self, value, &self->guard, self->guard.next); \
	self->length += 1; \
	return self->length

size_t U16List_pushFront(U16List self, uint16_t value)
{
	PUSH_FRONT(self, value);
}

#define PUSH_BACK(self, value) \
	Node_newInList(self, value, self->guard.prev, &self->guard); \
	self->length += 1; \
	return self->length

size_t U16List_pushBack(U16List self, uint16_t value)
{
	PUSH_BACK(self, value);
}

static inline U16ListNode U16ListNode_freeInList(U16ListNode self)
{
	U16ListNode next = self->next;
	self->prev->next = self->next;
	self->next->prev = self->prev;
	free(self);
	return next;
}

