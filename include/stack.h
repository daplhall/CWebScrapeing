#ifndef GENERIC_STACK_H
#define GENERIC_STACK_H
#ifdef __cplusplus
extern "C" {
#endif
#define T Stack
#include <stddef.h>
typedef struct T *T;

enum Stack_free_state {
	STACK_PUSH_OWNERSHIP,
	STACK_PUSH_STANDARD,
};

T Stack_create (void);
void Stack_free (T stack);
void Stack_pop (T stack, void **out);
void Stack_push (T stack, void *inpt, enum Stack_free_state free_state);
size_t Stack_length (T stack);

#undef T
#ifdef __cplusplus
}
#endif
#endif // GENERIC_STACK_H
