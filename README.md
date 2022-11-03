# libdystring

A library for dynamic strings and reading/writing binary files

## Building

To build, run:

```bash
# If you want install to something another directory, set PREFIX variable
# PREFIX="$HOME/opt/mybuilds"

# Build
./builder build
```

To install:
```bash
# Install
# Note: You can remove 'sudo' if installing to home directory
sudo ./builder install
```

## Programs

Hello, world!

```c
#include <dystring/dystring.h>

int main(void) {
	dystring_t *s = dystring_from_cstring("Hello, world!");
	dystring_puts(s);
	dystring_destroy(s);
	return 0;
}
```
