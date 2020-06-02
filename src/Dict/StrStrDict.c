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
#include "StrStrDict.h"


#define PRIMES_TABLE_SIZE (sizeof(primes_table) / sizeof(uint32_t))
static const uint32_t primes_table[] = {
	3, 7, 17, 37, 79, 163, 331, 673, 1361, 2729,
	5471, 10949, 21911, 43853, 87719, 175447, 350899, 701819, 1403641, 2807303,
};

struct StrStrDictEntryNode {
	struct StrStrDictEntryNode *next;
	Str key;
	Str value;
};

#define TABLE_SIZE(self) (self->fixed_size ? self->size : primes_table[self->size])
struct cutils_StrStrDict_ {
	struct StrStrDictEntryNode **table;
	size_t length, size;
	bool fixed_size;
};

#define TABLE_INDEX(key, size) \
(Str_hash(key) % (size))

static void table_insertNode(struct StrStrDictEntryNode **table,
			     size_t table_size,
			     struct StrStrDictEntryNode *node);
static void StrStrDict_resize(StrStrDict self, size_t size);
static void StrStrDict_freeTable(StrStrDict self);
static void StrStrDict_cloneTable(StrStrDict self, StrStrDict src);
static inline void StrStrDict_checkSize(StrStrDict self);
static struct StrStrDictEntryNode *new_node(Str key, Str value);
static void free_node(struct StrStrDictEntryNode *node);
static struct StrStrDictEntryNode *clone_node(const struct StrStrDictEntryNode *src);
static void copy_node(struct StrStrDictEntryNode *node, const struct StrStrDictEntryNode *src);

StrStrDict StrStrDict_new()
{
	StrStrDict self = malloc(sizeof(*self));
	self->length = self->size = 0;
	self->fixed_size = false;
	self->table = calloc(primes_table[0], sizeof(struct StrStrDictEntryNode *));
	return self;
}

StrStrDict StrStrDict_newWithSize(size_t size)
{
	StrStrDict self = malloc(sizeof(*self));
	size = size < 3 ? 3 : size;
	self->length = 0;
	self->size = size;
	self->fixed_size = true;
	self->table = calloc(size, sizeof(struct StrStrDictEntryNode *));
	return self;
}

StrStrDict StrStrDict_clone(StrStrDict src)
{
	StrStrDict self = malloc(sizeof(*self));
	*self = *src;
	StrStrDict_cloneTable(self, src);
	return self;
}

void StrStrDict_copy(StrStrDict self, StrStrDict src)
{
	StrStrDict_freeTable(self);
	*self = *src;
	StrStrDict_cloneTable(self, src);
}

void StrStrDict_free(StrStrDict self)
{
	if (self == NULL)
		return;
	StrStrDict_freeTable(self);
	free(self);
}

size_t StrStrDict_getLength(StrStrDict self)
{
	return self->length;
}

void StrStrDict_setSize(StrStrDict self, size_t size)
{
	size = size < 3 ? 3 : size;
	StrStrDict_resize(self, size);
	self->fixed_size = true;
	self->size = size;
}

void __StrStrDict_insert_use_clone(StrStrDict self, Str key, Str *value)
{
	size_t size = TABLE_SIZE(self),
	       index = TABLE_INDEX(key, size);
	struct StrStrDictEntryNode *node = self->table[index];
	while (node != NULL) {
		if (Str_equal(key, node->key)) {
			Str_copy(node->value, *value);
			return;
		}
		node = node->next;
	}
	struct StrStrDictEntryNode *new = new_node(Str_clone(key), Str_clone(*value));
	new->next = self->table[index];
	self->table[index] = new;
	self->length += 1;
	StrStrDict_checkSize(self);
}

void __StrStrDict_insert_use_assign(StrStrDict self, Str key, Str value)
{
	size_t size = TABLE_SIZE(self),
	       index = TABLE_INDEX(key, size);
	struct StrStrDictEntryNode *node = self->table[index];
	while (node != NULL) {
		if (Str_equal(key, node->key)) {
			node->value = value;
			return;
		}
		node = node->next;
	}
	struct StrStrDictEntryNode *new = new_node(Str_clone(key), value);
	new->next = self->table[index];
	self->table[index] = new;
	self->length += 1;
	StrStrDict_checkSize(self);
}

bool StrStrDict_find(StrStrDict self, Str key, Str *value)
{
	size_t size = TABLE_SIZE(self),
	       index = TABLE_INDEX(key, size);
	struct StrStrDictEntryNode *node = self->table[index];
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

bool StrStrDict_delete(StrStrDict self, Str key)
{
	size_t size = TABLE_SIZE(self),
	       index = TABLE_INDEX(key, size);
	struct StrStrDictEntryNode *node = self->table[index],
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



static void table_insertNode(struct StrStrDictEntryNode **table,
			     size_t table_size,
			     struct StrStrDictEntryNode *node)
{
	size_t index = TABLE_INDEX(node->key, table_size);
	if (table[index] != NULL) {
		node->next = table[index];
	}
	table[index] = node;
}

static void StrStrDict_resize(StrStrDict self, size_t size)
{
	size_t table_size = TABLE_SIZE(self);
	if (size == table_size)
		return;

	struct StrStrDictEntryNode **table = calloc(size, sizeof(struct StrStrDictEntryNode *));
	for (size_t i = 0; i < table_size; i++) {
		struct StrStrDictEntryNode *node = self->table[i];
		while (node != NULL) {
			struct StrStrDictEntryNode *tmp = node,
					 *new = new_node(tmp->key, tmp->value);
			node = node->next;
			table_insertNode(table, size, new);
			free(tmp);
		}
	}
	free(self->table);
	self->table = table;
}

static void StrStrDict_freeTable(StrStrDict self)
{
	size_t size = TABLE_SIZE(self);
	for (size_t i = 0; i < size; i++) {
		struct StrStrDictEntryNode *node = self->table[i];
		while (node != NULL) {
			struct StrStrDictEntryNode *tmp = node;
			node = node->next;
			Str_free(tmp->key);
			Str_free(tmp->value);
			free(tmp);
		}
	}
	free(self->table);
}

static void StrStrDict_cloneTable(StrStrDict self, StrStrDict src)
{
	size_t size = TABLE_SIZE(self);
	self->table = calloc(size, sizeof(struct StrStrDictEntryNode *));

	for (size_t i = 0; i < size; i++) {
		struct StrStrDictEntryNode *src_node = src->table[i],
				 **node = self->table + i;
		while (src_node != NULL) {
			*node = clone_node(src_node);
			src_node = src_node->next;
			node = &(*node)->next;
		}
	}
}

static struct StrStrDictEntryNode *new_node(Str key, Str value)
{
	struct StrStrDictEntryNode *node = malloc(sizeof(*node));
	node->key = key;
	node->value = value;
	node->next = NULL;
	return node;
}

static void free_node(struct StrStrDictEntryNode *node)
{
	if (node == NULL)
		return;
	Str_free(node->key);
	Str_free(node->value);
	free(node);
}

static struct StrStrDictEntryNode *clone_node(const struct StrStrDictEntryNode *src)
{
	struct StrStrDictEntryNode *node = calloc(1, sizeof(*node));
	node->key = Str_clone(src->key);
	node->value = Str_clone(src->value);
	return node;
}

static void copy_node(struct StrStrDictEntryNode *node, const struct StrStrDictEntryNode *src)
{
	Str_copy(node->key, src->key);
	Str_copy(node->value, src->value);
}

static inline void StrStrDict_checkSize(StrStrDict self)
{
	if (!self->fixed_size &&
	    self->size + 1 < PRIMES_TABLE_SIZE &&
	    self->length > primes_table[self->size] * 0.7) {
		size_t newsize = self->size + 1;
		StrStrDict_resize(self, primes_table[newsize]);
		self->size = newsize;
	}
}

