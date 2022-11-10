#include <dystring/dystring.h>

int main(void) {
	dystring_t *s = dystring_from_cstring("Hello, world!");
	dystring_puts(s);
	dystring_destroy(s);
	return 0;
}