#include <dystring/reader.h>
#include <stdlib.h>

dystring_reader_t *dystring_reader_create(void) {
	dystring_reader_t *result;
	result = malloc(sizeof(dystring_reader_t));
	if(!result) {
		return NULL;
	}
	result->_errno = 0;
	return result;
}

byte_t dystring_reader_read_byte(dystring_reader_t *obj) {
	if(!obj)
		return 0;
	obj->_errno = 0;
	byte_t rs = 0;
	if(fread(&rs, 1, sizeof(byte_t), obj->stream) != 1)
		obj->_errno = 1;
	return rs;
}
word_t dystring_reader_read_word(dystring_reader_t *obj) {
	if(!obj)
		return 0;
	obj->_errno = 0;
	word_t rs = 0;
	if(fread(&rs, 1, sizeof(word_t), obj->stream) != 1)
		obj->_errno = 1;
	return rs;
}
dword_t dystring_reader_read_dword(dystring_reader_t *obj) {
	if(!obj)
		return 0;
	obj->_errno = 0;
	dword_t rs = 0;
	if(fread(&rs, 1, sizeof(dword_t), obj->stream) != 1)
		obj->_errno = 1;
	return rs;
}
qword_t dystring_reader_read_qword(dystring_reader_t *obj) {
	if(!obj)
		return 0;
	obj->_errno = 0;
	qword_t rs = 0;
	if(fread(&rs, 1, sizeof(qword_t), obj->stream) != 1)
		obj->_errno = 1;
	return rs;
}

dystring_reader_t *dystring_reader_read_string(dystring_reader_t *obj) {
	if(!obj)
		return NULL;
	obj->str = dystring_create();
	free((obj->str)->buf);
	((obj->str)->len) = dystring_reader_read_dword(obj);
	((obj->str)->buf) = malloc((obj->str)->len);
	if(fread(
		(obj->str)->buf,
		sizeof(byte_t),
		(obj->str)->len, obj->stream
	) != ((obj)->str)->len) {
		obj->_errno = 2;
	}
	return obj;
}

void dystring_reader_destroy(dystring_reader_t *obj) {
	dystring_destroy(obj->str);
	free(obj);
}
