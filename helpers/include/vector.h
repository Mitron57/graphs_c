#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

#include <result.h>

struct vector {
    size_t capacity;
    size_t size;
    size_t* data;
};

struct vector vector_ctor(size_t capacity);

struct result vector_push(struct vector* self, size_t elem);

struct result vector_get(struct vector* self, size_t index);

void vector_dtor(struct vector* self);


#endif //VECTOR_H
