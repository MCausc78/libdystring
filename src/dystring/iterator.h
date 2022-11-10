#ifndef DY_STRING_ITERATOR_H
#define DY_STRING_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <dystring/dystring.h>
#include <dystring/types.h>
#include <stdbool.h>

typedef struct {
	dystring_t *s;
	dword_t index;
	int _errno;
} dystring_iterator_t;

dystring_iterator_t *dystring_iterator_create(dystring_t *);

bool dystring_iterator_has_next(dystring_iterator_t *);
char *dystring_iterator_next_byte(dystring_iterator_t *);
dystring_iterator_t *dystring_iterator_rewind(dystring_iterator_t *);
dystring_iterator_t *dystring_iterator_set_index(dystring_iterator_t *, dword_t);

void dystring_iterator_destroy(dystring_iterator_t *);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DY_STRING_ITERATOR_H */