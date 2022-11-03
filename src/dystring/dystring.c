#include <dystring/dystring.h>
#include <stdlib.h>
#include <string.h>

dystring_t *dystring_from_cstring(char *str) {
	dystring_t *result;
	result = malloc(sizeof(dystring_t));
	if(!result)
		return NULL;
	result->len = strlen(str);
	result->_errno = 0;
	result->buf = malloc(2);
	if(!result->buf) {
		result->_errno = 1;
		return result;
	}
	memcpy(result->buf, str, result->len);
	return result;
}

int dystring_compare(dystring_t *s1, dystring_t *s2) {
	int len = ((s1->len < s2->len) ? s1->len : s2->len);
	for(int i = 0; i < len; i++) {
		if(s1->buf[i] < s2->buf[i])
			return -1;
		else if(s1->buf[i] > s2->buf[i])
			return 1;
	}
	return 0;
}

dystring_t *dystring_create(void) {
	return dystring_from_cstring("");
}

dystring_t *dystring_duplicate(dystring_t *obj) {
	if(!obj)
		return NULL;
	dystring_t *rs = dystring_create();
	if(!rs || rs->_errno) {
		return rs ? rs : NULL;
	}
	free(rs->buf);
	rs->buf = malloc(obj->len);
	if(!rs->buf) {
		rs->_errno = 1;
		return rs;
	}
	rs->len = obj->len;
	memcpy(rs->buf, obj->buf, rs->len);
	return rs;
}

int dystring_fputs(dystring_t *s, FILE *stream) {
	if(!stream)
		return -1;
	dword_t i;
	for(i = 0; i < s->len; i++) {
		if(fputc(s->buf[i], stream) == EOF) {
			return -1;
		}
	}
	return i;
}

void dystring_destroy(dystring_t *s) {
	free(s->buf);
	free(s);
}

dystring_t *dystring_append_char(dystring_t *s, char c) {
	char *nbuf;
	nbuf = realloc(s->buf, ++(s->len));
	if(nbuf) {
		s->buf = nbuf;
		s->buf[s->len - 1] = c;
		s->_errno = 0;
		return s;
	} else {
		--(s->len);
		s->_errno = 1;
		return s;
	}
}

dystring_t *dystring_from_char(char c) {
	return dystring_append_char(dystring_create(), c);
}

int dystring_append_string(dystring_t *s1, dystring_t *s2) {
	char *nbuf;
	dword_t len1 = s1->len;
	nbuf = realloc(s1->buf, (s1->len = (len1 + s2->len)));
	if(nbuf) {
		s1->buf = nbuf;
		memcpy(&(s1->buf[len1]), s2->buf, s2->len);
		return s1->len;
	} else {
		s1->len -= len1;
		return -1;
	}
}

dystring_t *dystring_copy(dystring_t *s1, dystring_t *s2) {
	if((!s1 || !s2) || (!(s1->buf) || !(s2->buf)))
		return NULL;
	free(s1->buf);
	s1->len = s2->len;
	s1->buf = malloc(s1->len);
	if(!s1->buf) {
		s1->_errno = 1;
		return s1;
	}
	memcpy(s1->buf, s2->buf, s1->len);
	return s1;
}

dystring_t *dystring_concat(dystring_t *s1, dystring_t *s2) {
	if((!s1 || !s2) || (!(s1->buf) || !(s2->buf)))
		return NULL;
	dystring_t *result = dystring_create();
	if(!result || result->_errno != 0)
		return result;
	dystring_copy(result, s1);
	if(result->_errno != 0)
		return result;
	dystring_append_string(result, s2);
	return result;
}

char *dystring_to_cstring(dystring_t *s) {
	return dystring_concat(s, dystring_from_char(0))->buf;
}

int dystring_puts(dystring_t *s) {
	return dystring_fputs(s, stdout);
}

int dystring_fprint(dystring_t *s, FILE *stream) {
	int i = dystring_fputs(s, stream);
	putc('\n', stream);
	return i;
}

int dystring_print(dystring_t *s) {
	return dystring_fprint(s, stdout);
}

int dystring_get_version(void) {
	return DY_STRING_VERSION;
}
