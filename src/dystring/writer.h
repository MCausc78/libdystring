#ifndef DYSTRING_WRITER_H
#define DYSTRING_WRITER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <dystring/dystring.h>
#include <dystring/types.h>

typedef struct {
	FILE *stream;
	int _errno;
} dystring_writer_t;

dystring_writer_t *dystring_writer_create(FILE *);

dystring_writer_t *dystring_writer_write_byte(dystring_writer_t *, byte_t);
dystring_writer_t *dystring_writer_write_word(dystring_writer_t *, word_t);
dystring_writer_t *dystring_writer_write_dword(dystring_writer_t *, dword_t);
dystring_writer_t *dystring_writer_write_qword(dystring_writer_t *, qword_t);
dystring_writer_t *dystring_writer_write_string(dystring_writer_t *, dystring_t *);

void dystring_writer_destroy(dystring_writer_t *);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DYSTRING_WRITER_H */
