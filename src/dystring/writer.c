#include <dystring/writer.h>
#include <stdlib.h>

dystring_writer_t *dystring_writer_create(FILE *stream) {
	if(!stream)
		return NULL;
	dystring_writer_t *result;
	result = malloc(sizeof(dystring_writer_t));
	if(!result) {
		return NULL;
	}
	result->stream = stream;
	result->_errno = 0;
	return result;
}

dystring_writer_t *dystring_writer_write_byte(dystring_writer_t *obj, byte_t arg) {
	if(!obj || !obj->stream)
		return NULL;
	obj->_errno = 0;
	if(fwrite(&arg, 1, sizeof arg, obj->stream) != sizeof arg)
		obj->_errno = 1;
	return obj;
}

dystring_writer_t *dystring_writer_write_word(dystring_writer_t *obj, word_t arg) {
	if(!obj || !obj->stream)
		return NULL;
	obj->_errno = 0;
	if(fwrite(&arg, 1, sizeof arg, obj->stream) != sizeof arg)
		obj->_errno = 1;
	return obj;
}

dystring_writer_t *dystring_writer_write_dword(dystring_writer_t *obj, dword_t arg) {
	if(!obj || !obj->stream)
		return NULL;
	obj->_errno = 0;
	if(fwrite(&arg, 1, sizeof arg, obj->stream) != sizeof arg)
		obj->_errno = 1;
	return obj;
}

dystring_writer_t *dystring_writer_write_qword(dystring_writer_t *obj, qword_t arg) {
	if(!obj || !obj->stream)
		return NULL;
	obj->_errno = 0;
	if(fwrite(&arg, 1, sizeof arg, obj->stream) != sizeof arg)
		obj->_errno = 1;
	return obj;
}

dystring_writer_t *dystring_writer_write_string(dystring_writer_t *obj, dystring_t *s) {
	if((!obj || !s) || (!obj->stream || !s->buf)) {
		return NULL;
	}
	dystring_writer_write_dword(obj, s->len);
	obj->_errno = 0;
	if(fwrite(s->buf, sizeof(byte_t), s->len, obj->stream) != s->len)
		obj->_errno = 1;
	return obj;
}

void dystring_writer_destroy(dystring_writer_t *obj) {
	free(obj);
}
