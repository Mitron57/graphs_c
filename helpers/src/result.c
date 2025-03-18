#include <result.h>

struct result ok(size_t elem) {
    struct result r = {};
    r.inner = (union inner){.ok = elem};
    r.state = OK;
    return r;
}

struct result err(const char* msg) {
    struct result r = {};
    r.state = ERR;
    r.inner = (union inner){.error = msg};
    return r;
}

bool result_is_ok(const struct result* r) {
    return r != NULL && r->state == OK;
}

bool result_is_error(const struct result* r) {
    return r != NULL && r->state == ERR;
}

size_t result_unwrap_ok(const struct result *r) {
    return r->inner.ok;
}

const char* result_unwrap_error(const struct result *r) {
    return r->inner.error;
}