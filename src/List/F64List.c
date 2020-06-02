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
#include "F64List.h"


struct _ADT_F64ListNode_ {
	double value;
	F64ListNode prev, next;
	F64List list;
};

struct _ADT_F64List_ {
	struct _ADT_F64ListNode_ guard;
	size_t length;
};

static inline F64ListNode Node_newInList(F64List list,
					      double value,
					      F64ListNode prev,
					      F64ListNode next)
{
	F64ListNode self = malloc(sizeof(*self));
	self->value = value;
	self->list = list;
	self->prev = prev;
	self->next = next;
	prev->next = next->prev = self;
	return self;
}

// Return @self's next node.
static inline F64ListNode F64ListNode_freeInList(F64ListNode self);

void F64ListNode_set(F64ListNode self, double value)
{
	self->value = value;
}

double F64ListNode_get(F64ListNode self)
{
	return self->value;
}

F64ListNode F64ListNode_getNext(F64ListNode self)
{
	return self->next == &self->list->guard ? NULL : self->next;
}

F64ListNode F64ListNode_getPrev(F64ListNode self)
{
	return self->prev == &self->list->guard ? NULL : self->prev;
}

#define INSERT_PREV(self, value) \
	self->list->length += 1; \
	return Node_newInList(self->list, value, self->prev, self)

F64ListNode F64ListNode_insertPrev(F64ListNode self, double value)
{
	INSERT_PREV(self, value);
}

#define INSERT_NEXT(self, value) \
	self->list->length += 1; \
	Node_newInList(self->list, value, self, self->next)

F64ListNode F64ListNode_insertNext(F64ListNode self, double value)
{
	INSERT_NEXT(self, value);
}

size_t F64ListNode_delete(F64ListNode self)
{
	self->list->length -= 1;
	self = F64ListNode_freeInList(self);
	return self->list->length;
}

F64List F64List_new()
{
	F64List self = malloc(sizeof(*self));
	self->guard.next = self->guard.prev = &self->guard;
	self->guard.list = self;
	self->length = 0;
	return self;
}

F64List F64List_clone(F64List src)
{
	F64List self = F64List_new();
	F64ListNode n = src->guard.next;
	while (n != &src->guard) {
		F64List_pushBack(self, n->value);
		n = n->next;
	}
	return self;
}

void F64List_copy(F64List self, F64List src)
{
	F64ListNode dstnode = self->guard.next,
		   srcnode = src->guard.next;
	bool dst_done = dstnode == &self->guard;
	bool src_done = srcnode == &src->guard;
	while (!dst_done || !src_done) {
		if (dst_done) { // dst is short than src
			F64List_pushBack(self, srcnode->value);
			srcnode = srcnode->next;
			src_done = srcnode == &src->guard;
		} else if (src_done) { // src is short than dst
			dstnode = F64ListNode_freeInList(dstnode);
			dst_done = dstnode == &self->guard;
		} else { // still in the middle...
			dstnode->value = srcnode->value;
			dst_done = (dstnode = dstnode->next) == &self->guard;
			src_done = (srcnode = srcnode->next) == &src->guard;
		}
	}
	self->length = src->length;
}

void F64List_free(F64List self)
{
	if (self != NULL) {
		F64ListNode n = self->guard.next;
		while (n != &self->guard) {
			n = F64ListNode_freeInList(n);
		}
		free(self);
	}
}

F64ListNode F64List_getHead(F64List self)
{
	return self->guard.next == &self->guard ? NULL : self->guard.next;
}

F64ListNode F64List_getTail(F64List self)
{
	return self->guard.prev == &self->guard ? NULL : self->guard.prev;
}

size_t F64List_getLength(F64List self)
{
	return self->length;
}

#define PUSH_FRONT(self, value) \
	Node_newInList(self, value, &self->guard, self->guard.next); \
	self->length += 1; \
	return self->length

size_t F64List_pushFront(F64List self, double value)
{
	PUSH_FRONT(self, value);
}

#define PUSH_BACK(self, value) \
	Node_newInList(self, value, self->guard.prev, &self->guard); \
	self->length += 1; \
	return self->length

size_t F64List_pushBack(F64List self, double value)
{
	PUSH_BACK(self, value);
}

static inline F64ListNode F64ListNode_freeInList(F64ListNode self)
{
	F64ListNode next = self->next;
	self->prev->next = self->next;
	self->next->prev = self->prev;
	free(self);
	return next;
}

