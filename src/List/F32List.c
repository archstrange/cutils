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
#include "F32List.h"


struct _ADT_F32ListNode_ {
	float value;
	F32ListNode prev, next;
	F32List list;
};

struct _ADT_F32List_ {
	struct _ADT_F32ListNode_ guard;
	size_t length;
};

static inline F32ListNode Node_newInList(F32List list,
					      float value,
					      F32ListNode prev,
					      F32ListNode next)
{
	F32ListNode self = malloc(sizeof(*self));
	self->value = value;
	self->list = list;
	self->prev = prev;
	self->next = next;
	prev->next = next->prev = self;
	return self;
}

// Return @self's next node.
static inline F32ListNode F32ListNode_freeInList(F32ListNode self);

void F32ListNode_set(F32ListNode self, float value)
{
	self->value = value;
}

float F32ListNode_get(F32ListNode self)
{
	return self->value;
}

F32ListNode F32ListNode_getNext(F32ListNode self)
{
	return self->next == &self->list->guard ? NULL : self->next;
}

F32ListNode F32ListNode_getPrev(F32ListNode self)
{
	return self->prev == &self->list->guard ? NULL : self->prev;
}

#define INSERT_PREV(self, value) \
	self->list->length += 1; \
	return Node_newInList(self->list, value, self->prev, self)

F32ListNode F32ListNode_insertPrev(F32ListNode self, float value)
{
	INSERT_PREV(self, value);
}

#define INSERT_NEXT(self, value) \
	self->list->length += 1; \
	Node_newInList(self->list, value, self, self->next)

F32ListNode F32ListNode_insertNext(F32ListNode self, float value)
{
	INSERT_NEXT(self, value);
}

size_t F32ListNode_delete(F32ListNode self)
{
	self->list->length -= 1;
	self = F32ListNode_freeInList(self);
	return self->list->length;
}

F32List F32List_new()
{
	F32List self = malloc(sizeof(*self));
	self->guard.next = self->guard.prev = &self->guard;
	self->guard.list = self;
	self->length = 0;
	return self;
}

F32List F32List_clone(F32List src)
{
	F32List self = F32List_new();
	F32ListNode n = src->guard.next;
	while (n != &src->guard) {
		F32List_pushBack(self, n->value);
		n = n->next;
	}
	return self;
}

void F32List_copy(F32List self, F32List src)
{
	F32ListNode dstnode = self->guard.next,
		   srcnode = src->guard.next;
	bool dst_done = dstnode == &self->guard;
	bool src_done = srcnode == &src->guard;
	while (!dst_done || !src_done) {
		if (dst_done) { // dst is short than src
			F32List_pushBack(self, srcnode->value);
			srcnode = srcnode->next;
			src_done = srcnode == &src->guard;
		} else if (src_done) { // src is short than dst
			dstnode = F32ListNode_freeInList(dstnode);
			dst_done = dstnode == &self->guard;
		} else { // still in the middle...
			dstnode->value = srcnode->value;
			dst_done = (dstnode = dstnode->next) == &self->guard;
			src_done = (srcnode = srcnode->next) == &src->guard;
		}
	}
	self->length = src->length;
}

void F32List_free(F32List self)
{
	if (self != NULL) {
		F32ListNode n = self->guard.next;
		while (n != &self->guard) {
			n = F32ListNode_freeInList(n);
		}
		free(self);
	}
}

F32ListNode F32List_getHead(F32List self)
{
	return self->guard.next == &self->guard ? NULL : self->guard.next;
}

F32ListNode F32List_getTail(F32List self)
{
	return self->guard.prev == &self->guard ? NULL : self->guard.prev;
}

size_t F32List_getLength(F32List self)
{
	return self->length;
}

#define PUSH_FRONT(self, value) \
	Node_newInList(self, value, &self->guard, self->guard.next); \
	self->length += 1; \
	return self->length

size_t F32List_pushFront(F32List self, float value)
{
	PUSH_FRONT(self, value);
}

#define PUSH_BACK(self, value) \
	Node_newInList(self, value, self->guard.prev, &self->guard); \
	self->length += 1; \
	return self->length

size_t F32List_pushBack(F32List self, float value)
{
	PUSH_BACK(self, value);
}

static inline F32ListNode F32ListNode_freeInList(F32ListNode self)
{
	F32ListNode next = self->next;
	self->prev->next = self->next;
	self->next->prev = self->prev;
	free(self);
	return next;
}

