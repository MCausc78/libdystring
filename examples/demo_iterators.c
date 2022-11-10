#include <dystring/dystring.h>
#include <dystring/iterator.h>
#include <stdlib.h>

int main(void) {
	/* Create string */
	dystring_t *s = dystring_from_cstring("Hello, world!");
	
	/* If failed create string */
	if(!s
	||	s->_errno != 0) {
		fprintf(stderr, "Error when creating 's': ");
		
		/* Tell error to user */
		if(!s) {
			fputs("Failed to allocate!", stderr);
		} else {
			fprintf(stderr, "Unknown error, errno = %d\n", s->_errno);
		}
		return 1;
	}
	
	/* Create iterator */
	dystring_iterator_t *it = dystring_iterator_create(s);
	
	/* If failed create iterator */
	if(!it) {
		fputs("Error when creating iterator: Failed to allocate!", stderr);
	}
	
	/* All success, iterate! */
	char *cs = dystring_to_cstring(s);
	printf("Iterating string \"%s\".\n", cs);

	free(cs);
	
	for(char *ch = NULL; (ch = dystring_iterator_next_byte(it)) != NULL; ) {
		printf("Char at index %d: '%c'\n", it->index, *ch);
	}
	
	/* Release resources */
	dystring_iterator_destroy(it);
	dystring_destroy(s);
	
	return 0;
}