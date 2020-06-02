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

// This file is generated from Dict.c.ohce by ohce.
#include "StrU32Dict.h"


#define PRIMES_TABLE_SIZE (sizeof(primes_table) / sizeof(uint32_t))
static const uint32_t primes_table[] = {
	3, 7, 17, 37, 79, 163, 331, 673, 1361, 2729,
	5471, 10949, 21911, 43853, 87719, 175447, 350899, 701819, 1403641, 2807303,
};

struct StrU32DictEntryNode {
	struct StrU32DictEntryNode *next;
	Str key;
	uint32_t value;
};

#define TABLE_SIZE(self) (self->fixed_size ? self->size : primes_table[self->size])
struct cutils_StrU32Dict_ {
	struct StrU32DictEntryNode **table;
	size_t length, size;
	bool fixed_size;
};

#define TABLE_INDEX(key, size) \
(Str_hash(key) % (size))

static void table_insertNode(struct StrU32DictEntryNode **table,
			     size_t table_size,
			     struct StrU32DictEntryNode *node);
static void StrU32Dict_resize(StrU32Dict self, size_t size);
static void StrU32Dict_freeTable(StrU32Dict self);
static void StrU32Dict_cloneTable(StrU32Dict self, StrU32Dict src);
static inline void StrU32Dict_checkSize(StrU32Dict self);
static struct StrU32DictEntryNode *new_node(Str key, uint32_t value);
static void free_node(struct StrU32DictEntryNode *node);
static struct StrU32DictEntryNode *clone_node(const struct StrU32DictEntryNode *src);
static void copy_node(struct StrU32DictEntryNode *node, const struct StrU32DictEntryNode *src);

StrU32Dict StrU32Dict_new()
{
	StrU32Dict self = malloc(sizeof(*self));
	self->length = self->size = 0;
	self->fixed_size = false;
	self->table = calloc(primes_table[0], sizeof(struct StrU32DictEntryNode *));
	return self;
}

StrU32Dict StrU32Dict_newWithSize(size_t size)
{
	StrU32Dict self = malloc(sizeof(*self));
	size = size < 3 ? 3 : size;
	self->length = 0;
	self->size = size;
	self->fixed_size = true;
	self->table = calloc(size, sizeof(struct StrU32DictEntryNode *));
	return self;
}

StrU32Dict StrU32Dict_clone(StrU32Dict src)
{
	StrU32Dict self = malloc(sizeof(*self));
	*self = *src;
	StrU32Dict_cloneTable(self, src);
	return self;
}

void StrU32Dict_copy(StrU32Dict self, StrU32Dict src)
{
	StrU32Dict_freeTable(self);
	*self = *src;
	StrU32Dict_cloneTable(self, src);
}

void StrU32Dict_free(StrU32Dict self)
{
	if (self == NULL)
		return;
	StrU32Dict_freeTable(self);
	free(self);
}

size_t StrU32Dict_getLength(StrU32Dict self)
{
	return self->length;
}

void StrU32Dict_setSize(StrU32Dict self, size_t size)
{
	size = size < 3 ? 3 : size;
	StrU32Dict_resize(self, size);
	self->fixed_size = true;
	self->size = size;
}

void StrU32Dict_insert(StrU32Dict self, Str key, uint32_t value)
{
	size_t size = TABLE_SIZE(self),
	       index = TABLE_INDEX(key, size);
	struct StrU32DictEntryNode *node = self->table[index];
	while (node != NULL) {
		if (Str_equal(key, node->key)) {
			node->value = value;
			return;
		}
		node = node->next;
	}
	struct StrU32DictEntryNode *new = new_node(Str_clone(key), value);
	new->next = self->table[index];
	self->table[index] = new;
	self->length += 1;
	StrU32Dict_checkSize(self);
}

bool StrU32Dict_find(StrU32Dict self, Str key, uint32_t *value)
{
	size_t size = TABLE_SIZE(self),
	       index = TABLE_INDEX(key, size);
	struct StrU32DictEntryNode *node = self->table[index];
	while (node != NULL) {
		if (
		    Str_equal(key, node->key)
		   ) {
			*value = node->value;
			return true;
		}
		node = node->next;
	}
	return false;
}

bool StrU32Dict_delete(StrU32Dict self, Str key)
{
	size_t size = TABLE_SIZE(self),
	       index = TABLE_INDEX(key, size);
	struct StrU32DictEntryNode *node = self->table[index],
			 **prev_next = self->table + index;
	while (node != NULL) {
		if (
		    Str_equal(key, node->key)
		   ) {
			*prev_next = node->next;
			free_node(node);
			self->length -= 1;
			return true;
		}
		prev_next = &node->next;
		node = node->next;
	}
	return false;
}



static void table_insertNode(struct StrU32DictEntryNode **table,
			     size_t table_size,
			     struct StrU32DictEntryNode *node)
{
	size_t index = TABLE_INDEX(node->key, table_size);
	if (table[index] != NULL) {
		node->next = table[index];
	}
	table[index] = node;
}

static void StrU32Dict_resize(StrU32Dict self, size_t size)
{
	size_t table_size = TABLE_SIZE(self);
	if (size == table_size)
		return;

	struct StrU32DictEntryNode **table = calloc(size, sizeof(struct StrU32DictEntryNode *));
	for (size_t i = 0; i < table_size; i++) {
		struct StrU32DictEntryNode *node = self->table[i];
		while (node != NULL) {
			struct StrU32DictEntryNode *tmp = node,
					 *new = new_node(tmp->key, tmp->value);
			node = node->next;
			table_insertNode(table, size, new);
			free(tmp);
		}
	}
	free(self->table);
	self->table = table;
}

static void StrU32Dict_freeTable(StrU32Dict self)
{
	size_t size = TABLE_SIZE(self);
	for (size_t i = 0; i < size; i++) {
		struct StrU32DictEntryNode *node = self->table[i];
		while (node != NULL) {
			struct StrU32DictEntryNode *tmp = node;
			node = node->next;
			Str_free(tmp->key);
			free(tmp);
		}
	}
	free(self->table);
}

static void StrU32Dict_cloneTable(StrU32Dict self, StrU32Dict src)
{
	size_t size = TABLE_SIZE(self);
	self->table = calloc(size, sizeof(struct StrU32DictEntryNode *));

	for (size_t i = 0; i < size; i++) {
		struct StrU32DictEntryNode *src_node = src->table[i],
				 **node = self->table + i;
		while (src_node != NULL) {
			*node = clone_node(src_node);
			src_node = src_node->next;
			node = &(*node)->next;
		}
	}
}

static struct StrU32DictEntryNode *new_node(Str key, uint32_t value)
{
	struct StrU32DictEntryNode *node = malloc(sizeof(*node));
	node->key = key;
	node->value = value;
	node->next = NULL;
	return node;
}

static void free_node(struct StrU32DictEntryNode *node)
{
	if (node == NULL)
		return;
	Str_free(node->key);
	free(node);
}

static struct StrU32DictEntryNode *clone_node(const struct StrU32DictEntryNode *src)
{
	struct StrU32DictEntryNode *node = calloc(1, sizeof(*node));
	node->key = Str_clone(src->key);
	node->value = src->value;
	return node;
}

static void copy_node(struct StrU32DictEntryNode *node, const struct StrU32DictEntryNode *src)
{
	Str_copy(node->key, src->key);
	node->value = src->value;
}

static inline void StrU32Dict_checkSize(StrU32Dict self)
{
	if (!self->fixed_size &&
	    self->size + 1 < PRIMES_TABLE_SIZE &&
	    self->length > primes_table[self->size] * 0.7) {
		size_t newsize = self->size + 1;
		StrU32Dict_resize(self, primes_table[newsize]);
		self->size = newsize;
	}
}

