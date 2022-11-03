#ifndef DYSTRING_READER_H
#define DYSTRING_READER_H

#include <dystring/dystring.h>
#include <dystring/types.h>
#include <stdio.h>

typedef struct {
	dystring_t *str;
	FILE *stream;
	int _errno;
} dystring_reader_t;

dystring_reader_t *dystring_reader_create(void);

byte_t dystring_reader_read_byte(dystring_reader_t *);
word_t dystring_reader_read_word(dystring_reader_t *);
dword_t dystring_reader_read_dword(dystring_reader_t *);
qword_t dystring_reader_read_qword(dystring_reader_t *);
dystring_reader_t *dystring_reader_read_string(dystring_reader_t *);
void dystring_reader_destroy(dystring_reader_t *);

#endif /* DYSTRING_READER_H */
