//
// Created by Армен Захарян on 18.03.25.
//

#ifndef RESULT_H
#define RESULT_H

#include <stdlib.h>
#include <stdbool.h>

enum state: short {
    OK = 0,
    ERR
};

struct result {
    union inner {
        size_t ok;
        const char *error;
    } inner;
    enum state state;
};

struct result ok(size_t ok);
struct result err(const char *error);

bool result_is_ok(const struct result *r);
bool result_is_error(const struct result *r);

size_t result_unwrap_ok(const struct result *r);
const char* result_unwrap_error(const struct result *r);


#endif //RESULT_H
