#include <stdio.h> 
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

//const char* read_path = "/home/josav09/Documents/C tests/fileReader/readme.txt";
const char* write_path = "./logs/directories.log";

/** converts an integer to a char * that can be printed
 * \param num the number to convert
 */
char *itoc (int num) {
	char store[50]; 
	sprintf(store, "%d", num);
	char* result = &store[0];
	return result;
}

/** Reads a character from a file. TODO: make it read a line or the whole file
 * \param read_path the file of the path that is being read
 */
char read_char (char* read_path) {
	FILE *fp;

   fp = fopen(read_path, "r"); // read mode

   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }

	char ch;
	ch = fgetc(fp);
	printf("%c", ch);

   fclose(fp);
   
   return ch;
}

/** Creates or overwrittes a new file log.txt in a known location (./logs)
 * and sets the 1st line as the local date
 */
void start_logg () {
	FILE *fp;
	system("[ -d logs ] || mkdir logs"); // creates folder for loggs if it doesn't exist
	fp = fopen(write_path, "w");

	if (fp == NULL) {
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	// give the log a time and date
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	fprintf(fp, "%s", "Logg started: ");
	fprintf(fp, "%s", asctime(timeinfo));

	fclose(fp);
}

/** logs a set of data into a known file by appending it. Finishes the log with a newline.
 * Create the file with "start_logg"
 * TODO: not distinguishing between variables: for now it can only manage 1. Use sprintf (buffer, "msg", params) and logg(1, buffer)
 * \param num the amount of data arguments passed to the function
 * \param char the data to be logged into the file
 */
void logg (int num, ...) {
	FILE *fp;
	va_list arglist;
	char* newline = "\n";
	fp = fopen(write_path, "a"); // append mode

	if (fp == NULL) {
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
    }

	va_start(arglist, num);
	for (int i=0; i<num; i++) {
		fprintf(fp, "%s", va_arg(arglist, char*));
	}
	fprintf(fp, "%s", newline);

	va_end(arglist);
	fclose(fp);
}
