#include <dystring/dystring.h>
#include <dystring/reader.h>
#include <dystring/writer.h>
#include <string.h>
#include <time.h>


int main(int argc, char **argv) {
	if(argc < 2) {
		fprintf(stderr, "%s: usage: %s read/write", argv[0], argv[0]);
		return 1;
	}
	
	if(strcmp(argv[1], "read") == 0) {	
		/* Open file for reading */
		FILE *f = fopen("demo.bin", "rb");
		
		/* Failed to open */
		if(!f) {
			perror("Error when opening file for reading");
			return 5;
		}
		
		dystring_reader_t *r = dystring_reader_create(f);
		
		/* Failed to create reader object */
		if(!r || r->_errno != 0) {
			fprintf(stderr, "Error when creating reader: r is null or errno != 0\n");
			
			/* If we can, print */
			if(r)
				fprintf(stderr, "Note: r->_errno = %d\n", r->_errno);
			
			fclose(f);
			return 6;
		}
		
		/* Read string */
		dystring_reader_read_string(r);
		char *s = dystring_to_cstring(r->str);
		
		/* Read time */
		time_t ti = (time_t)dystring_reader_read_qword(r);
		dystring_reader_destroy(r);
		
		fclose(f);
		printf("Readed text: \"%s\"\nCreated at %s\n", s, ctime(&ti));
		
		/* Not needed to release memory, it is faster just exit and return */
		return 0;
	} else if(strcmp(argv[1], "write") == 0) {
		/* Open file for writing */
		FILE *f = fopen("demo.bin", "wb");
		
		/* Failed to open */
		if(!f) {
			perror("Error when opening file for writing");
			return 4;
		}
		
		/* Try create writer object */
		dystring_writer_t *w = dystring_writer_create(f);
		
		/* Failed to create object */
		if(!w || w->_errno != 0) {
			fprintf(stderr, "Error when creating writer: w is null or errno != 0\n");
			
			/* If we can, print errno */
			if(w)
				fprintf(stderr, "Note: w->_errno is %d\n", w->_errno);
			fclose(f);
			return 7;
		}
		
		char buf[512];
		puts("Enter your text: ");
		
		/* Read user input and convert him to `dystring_t` */
		fgets(buf, 512, stdin);
		dystring_t *str = dystring_from_cstring(buf);
		
		/* Check if convert failed */
		if(!str || str->_errno != 0) {
			fprintf(stderr, "Error when writing to file: writer errno is %d\n", w->_errno);
			
			/* If we can, print errno */
			if(str) {
				fprintf(stderr, "Note: str->_errno: %d\n", str->_errno);
				
				/* Release string */
				dystring_destroy(str);
			}
			
			/* Release resources and exit */
			dystring_writer_destroy(w);
			fclose(f);
			
			return 3;
		}
		
		/* Try write string */
		dystring_writer_t *wr = dystring_writer_write_string(w, str);
		
		/* Failed to write */
		if(!wr || w->_errno != 0) {
			fprintf(stderr, "error when writing to file: errno is %d", w->_errno);
			
			/* Release resources and exit */
			dystring_destroy(str);
			dystring_writer_destroy(w);
			fclose(f);
			
			return 2;
		}
		
		/* Write current time */
		dystring_writer_write_qword(w, time(0));
		
		/* Tell to user that all successfully got written */
		printf("Successfully wrote %zu bytes\n", ftell(f));
		
		/* Release resources */
		dystring_destroy(str);
		dystring_writer_destroy(w);
		fclose(f);
	} else {
		fprintf(stderr, "Error: unknown action (\"%s\")\n", argv[1]);
	}
	return 0;
}