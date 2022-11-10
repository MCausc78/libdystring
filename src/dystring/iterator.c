#include <dystring/dystring.h>
#include <dystring/iterator.h>
#include <dystring/types.h>
#include <stdlib.h>

dystring_iterator_t *dystring_iterator_create(dystring_t *s) {
	/* For creating, we need string, otherwise we will return null */
	if(!s)
		return NULL;
	
	dystring_iterator_t *self = malloc(sizeof(dystring_iterator_t));
	
	/* Failed to allocate memory for object, we will return null */
	if(!self)
		return NULL;
	
	/* Successfully allocated, setup iterator */
	self->s = s;
	self->index = 0;
	self->_errno = 0;
	return self;
}

bool dystring_iterator_has_next(dystring_iterator_t *self) {
	/* Check for object invalidity */
	if(!self
	|| !self->s) {
		if(self)
			self->_errno = 1;
		return false;
	}
	self->_errno = 0;
	return (!(self->index > (self->s->len - 1) ) );
}

char *dystring_iterator_next_byte(dystring_iterator_t *self) {
	/* Check for object invalidity */
	if(!self
	|| !self->s) {
		if(self)
			self->_errno = 1;
		return NULL;
	}
	self->_errno = 0;
	return (dystring_iterator_has_next(self)
		? &((self->s)->buf[self->index++])
		: NULL);
}

dystring_iterator_t *dystring_iterator_rewind(dystring_iterator_t *self) {
	/* Check for object invalidity */
	if(!self
	|| !self->s) {
		if(self)
			self->_errno = 1;
		return NULL;
	}
	
	self->_errno = 0;
	
	/* XOR trick */
	self->index ^= self->index;
	return self;
}

dystring_iterator_t *dystring_iterator_set_index(dystring_iterator_t *self, dword_t index) {
	/* Check for object invalidity */
	if(!self
	|| !self->s) {
		if(self)
			self->_errno = 1;
		return NULL;
	}
	
	self->_errno = 0;
	
	/* Check for invalid index */
	if ( index > ((self->s)->len) ) {
		self->_errno = 2;
		return self;
	}
	self->index = index;
	return self;
}

void dystring_iterator_destroy(dystring_iterator_t *self) {
	/* Check for object invalidity */
	if(!self)
		return;
	
	/* Release memory */
	free(self);
}
