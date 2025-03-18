#include <queue.h>
#include <stdio.h>
#include <string.h>
#include <vector.h>
#include <limits.h>

struct vector* array_init(size_t size) {
    struct vector* array = malloc(sizeof(struct vector) * size);
    if (array == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < size; i++) {
        struct vector v = vector_ctor(1);
        memcpy(array + i, &v, sizeof(struct vector));
    }
    return array;
}

void array_free(struct vector* array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        vector_dtor(array + i);
    }
    free(array);
}

struct vector count(const struct vector* adj, size_t size, size_t target) {
    struct vector v = vector_ctor(size);

    if (v.data == NULL) {
        return v;
    }

    v.size = size;
    for (size_t i = 0; i < size; ++i) {
        v.data[i] = SIZE_T_MAX;
    }
    v.data[target] = 0;

    struct queue q = queue_ctor();
    struct result pushed = queue_push(&q, target);
    if (result_is_error(&pushed)) {
        queue_dtor(&q);
        return v;
    }

    while (!queue_is_empty(&q)) {
        struct result popped = queue_pop(&q);
        const size_t node = result_unwrap_ok(&popped);

        struct vector adjacents = adj[node];

        for (size_t i = 0; i < adjacents.size; ++i) {
            size_t adjacent = adjacents.data[i];
            if (v.data[adjacent] == SIZE_T_MAX) {
                v.data[adjacent] = v.data[node] + 1;
                queue_push(&q, adjacent);
            }
        }
    }

    queue_dtor(&q);
    return v;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error opening file %s\n", argv[1]);
        fclose(f);
        return EXIT_FAILURE;
    }

    size_t nodes, edges;
    //IDGAF about strtoll
    fscanf(f, "%zd\n%zd", &nodes, &edges);

    struct vector* nodes_arr = array_init(nodes);;
    if (nodes_arr == NULL) {
        printf("Error allocating memory for nodes_arr\n");
        fclose(f);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < edges; i++) {
        size_t from, to;
        fscanf(f, "%zd %zd", &from, &to);
        vector_push(nodes_arr + from, to);
        vector_push(nodes_arr + to, from);
    }

    size_t target;
    fscanf(f, "%zd", &target);
    fclose(f);

    struct vector adj = count(nodes_arr, nodes, target);

    for (size_t i = 0; i < adj.size; ++i) {
        printf("%zd\n", adj.data[i]);
    }

    array_free(nodes_arr, nodes);
    vector_dtor(&adj);
    return 0;
}
