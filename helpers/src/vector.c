#include <vector.h>

struct vector vector_ctor(size_t capacity) {
    size_t* data = malloc(capacity * sizeof(size_t));
    if (data == NULL) {
        return (struct vector){0, 0, NULL};
    }
    return (struct vector){capacity, 0, data};
}

struct result vector_push(struct vector* self, size_t elem) {
    if (self->size == self->capacity) {
        self->capacity = self->capacity == 0 ? 2 : self->capacity * 2;
        size_t* data = realloc(self->data, self->capacity * sizeof(size_t));
        if (data == NULL) {
            return err("realloc");
        }
        self->data = data;
    }
    self->data[self->size++] = elem;
    return ok(elem);
}

struct result vector_get(struct vector* self, size_t index) {
    if (index >= self->size) {
        return err("index out of range");
    }
    return ok(self->data[index]);
}

void vector_dtor(struct vector* self) {
    self->size = 0;
    self->capacity = 0;
    if (self->data != NULL) {
        free(self->data);
    }
    self->data = NULL;
}