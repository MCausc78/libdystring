#include <dystring/types.h>
#include <stdio.h>

#ifndef DY_STRING_DY_STRING_H
#define DY_STRING_DY_STRING_H
#ifndef DY_STRING_VERSION

/********************
*                   *
* 1.2	0b00100001  *
* ^ ^	  ^^^^      *
* | |-----||||^^^^  *
* |-----------||||  *
*                   *
*********************/

#define DY_STRING_VERSION 0b00000001

#endif /* DY_STRING_VERSION */

typedef struct {
	char *buf;
	dword_t len;
	int _errno;
} dystring_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

dystring_t *dystring_from_cstring(char *);
int dystring_compare(dystring_t *, dystring_t *);
dystring_t *dystring_create(void);
dystring_t *dystring_duplicate(dystring_t *);
int dystring_fputs(dystring_t *, FILE *);
void dystring_destroy(dystring_t *);
dystring_t *dystring_append_char(dystring_t *, char);
dystring_t *dystring_from_char(char);
int dystring_append_string(dystring_t *, dystring_t *);
dystring_t *dystring_copy(dystring_t *, dystring_t *);
dystring_t *dystring_concat(dystring_t *, dystring_t *);
char *dystring_to_cstring(dystring_t *);
int dystring_puts(dystring_t *);
int dystring_fprint(dystring_t *, FILE *);
int dystring_print(dystring_t *);

int dystring_get_version(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DY_STRING_DY_STRING_H */
