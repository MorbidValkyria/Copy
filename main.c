#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char const *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <source_file> <destination_file>\n",argv[0]);
		return 1;
	}
	 const char *src = argv[1];
	 const char *dst = argv[2];
	 FILE *f_src = fopen(src, "rb"); // rb = Read Binary mode

	 if (!f_src) {
	 	perror("Error opening source file");
	 	return 1;
	 }

	FILE *f_dst = fopen(dst, "wb"); // wb = write binary mode

	 if (!f_dst) {
	 	perror("Error opening destination file");
	 	fclose(f_src);
	 	return 1;
	 }

	 char buffer[4096];
	 size_t bytes_read, bytes_written;
	 int copy_failed = 0;

	 while ((bytes_read = fread(buffer, 1, sizeof(buffer), f_src)) > 0) {
	 	bytes_written = fwrite(buffer, 1, bytes_read, f_dst);
	 	if (bytes_written != bytes_read) {
	 		perror("Error writing to destination file");
	 		copy_failed = 1;
	 		break;
	 	}
	 }

	 if (ferror(f_src)) {
	 	perror("Error reading from source file");
	 	copy_failed = 1;
	 }

	 fclose(f_src);
	 fclose(f_dst);

	 if (copy_failed) {
	 	remove(dst); // remove file if failed
	 	return 1;
	 }

	 printf("File copied successfully!\n");
	 return 0;
}