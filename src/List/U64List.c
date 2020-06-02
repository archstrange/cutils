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
#include "U64List.h"


struct _ADT_U64ListNode_ {
	uint64_t value;
	U64ListNode prev, next;
	U64List list;
};

struct _ADT_U64List_ {
	struct _ADT_U64ListNode_ guard;
	size_t length;
};

static inline U64ListNode Node_newInList(U64List list,
					      uint64_t value,
					      U64ListNode prev,
					      U64ListNode next)
{
	U64ListNode self = malloc(sizeof(*self));
	self->value = value;
	self->list = list;
	self->prev = prev;
	self->next = next;
	prev->next = next->prev = self;
	return self;
}

// Return @self's next node.
static inline U64ListNode U64ListNode_freeInList(U64ListNode self);

void U64ListNode_set(U64ListNode self, uint64_t value)
{
	self->value = value;
}

uint64_t U64ListNode_get(U64ListNode self)
{
	return self->value;
}

U64ListNode U64ListNode_getNext(U64ListNode self)
{
	return self->next == &self->list->guard ? NULL : self->next;
}

U64ListNode U64ListNode_getPrev(U64ListNode self)
{
	return self->prev == &self->list->guard ? NULL : self->prev;
}

#define INSERT_PREV(self, value) \
	self->list->length += 1; \
	return Node_newInList(self->list, value, self->prev, self)

U64ListNode U64ListNode_insertPrev(U64ListNode self, uint64_t value)
{
	INSERT_PREV(self, value);
}

#define INSERT_NEXT(self, value) \
	self->list->length += 1; \
	Node_newInList(self->list, value, self, self->next)

U64ListNode U64ListNode_insertNext(U64ListNode self, uint64_t value)
{
	INSERT_NEXT(self, value);
}

size_t U64ListNode_delete(U64ListNode self)
{
	self->list->length -= 1;
	self = U64ListNode_freeInList(self);
	return self->list->length;
}

U64List U64List_new()
{
	U64List self = malloc(sizeof(*self));
	self->guard.next = self->guard.prev = &self->guard;
	self->guard.list = self;
	self->length = 0;
	return self;
}

U64List U64List_clone(U64List src)
{
	U64List self = U64List_new();
	U64ListNode n = src->guard.next;
	while (n != &src->guard) {
		U64List_pushBack(self, n->value);
		n = n->next;
	}
	return self;
}

void U64List_copy(U64List self, U64List src)
{
	U64ListNode dstnode = self->guard.next,
		   srcnode = src->guard.next;
	bool dst_done = dstnode == &self->guard;
	bool src_done = srcnode == &src->guard;
	while (!dst_done || !src_done) {
		if (dst_done) { // dst is short than src
			U64List_pushBack(self, srcnode->value);
			srcnode = srcnode->next;
			src_done = srcnode == &src->guard;
		} else if (src_done) { // src is short than dst
			dstnode = U64ListNode_freeInList(dstnode);
			dst_done = dstnode == &self->guard;
		} else { // still in the middle...
			dstnode->value = srcnode->value;
			dst_done = (dstnode = dstnode->next) == &self->guard;
			src_done = (srcnode = srcnode->next) == &src->guard;
		}
	}
	self->length = src->length;
}

void U64List_free(U64List self)
{
	if (self != NULL) {
		U64ListNode n = self->guard.next;
		while (n != &self->guard) {
			n = U64ListNode_freeInList(n);
		}
		free(self);
	}
}

U64ListNode U64List_getHead(U64List self)
{
	return self->guard.next == &self->guard ? NULL : self->guard.next;
}

U64ListNode U64List_getTail(U64List self)
{
	return self->guard.prev == &self->guard ? NULL : self->guard.prev;
}

size_t U64List_getLength(U64List self)
{
	return self->length;
}

#define PUSH_FRONT(self, value) \
	Node_newInList(self, value, &self->guard, self->guard.next); \
	self->length += 1; \
	return self->length

size_t U64List_pushFront(U64List self, uint64_t value)
{
	PUSH_FRONT(self, value);
}

#define PUSH_BACK(self, value) \
	Node_newInList(self, value, self->guard.prev, &self->guard); \
	self->length += 1; \
	return self->length

size_t U64List_pushBack(U64List self, uint64_t value)
{
	PUSH_BACK(self, value);
}

static inline U64ListNode U64ListNode_freeInList(U64ListNode self)
{
	U64ListNode next = self->next;
	self->prev->next = self->next;
	self->next->prev = self->prev;
	free(self);
	return next;
}

