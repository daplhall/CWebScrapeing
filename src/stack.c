/*
 * might need an arena locator for each generated stack
 */
#include "stack.h"
#include <stdlib.h>

#define T Stack
struct T {
	struct link {
		struct link *next;
		void *value;
		enum Stack_free_state free_state;
	} *link;
	size_t len;
};

T
Stack_create (void)
{
	struct T *new = malloc (sizeof (*new));
	new->link = NULL;
	new->len = 0;
	return new;
}

void
Stack_free (T stack)
{
	struct link *l;
	while ((l = stack->link)) {
		struct link *tmp = l;
		stack->link = l->next;
		if (tmp->free_state == STACK_PUSH_OWNERSHIP)
			free (tmp->value);
		free (tmp);
	}
	free (stack);
}

void
Stack_push (T stack, void *inpt, enum Stack_free_state free_state)
{
	struct link *new_link;
	new_link = (struct link *)malloc (sizeof (*new_link));
	new_link->value = inpt;
	new_link->free_state = free_state;

	new_link->next = stack->link;
	stack->link = new_link;
	stack->len++;
}
void
Stack_pop (T stack, void **out)
{
	struct link *to_pop = stack->link;
	stack->link = stack->link->next;
	*out = to_pop->value;
	stack->len--;
	free (to_pop);
}

size_t
Stack_length (T stack)
{
	return stack->len;
}
