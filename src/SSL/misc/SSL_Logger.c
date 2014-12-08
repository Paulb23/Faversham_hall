/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Logger.c
   @author  P. Batty
   @brief   Implements a Logging function.

   This module implements a simple logging function that will
   write a message to a file.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/
#include "SSL_Logger.h"
#include "../SSL_Settings.h"

#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>



/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*!--------------------------------------------------------------------------
  @brief	 Gets the current system time
  @return 	 void string containing the current time.

  Gets the current system and returns a string with the information.


\-----------------------------------------------------------------------------*/
static char *getTime() {
	time_t current_time = time(NULL);
	return ctime(&current_time);
}


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	 Writes a message to a file
  @param    text		  Text to write.
  @param    ...          printf arguments
  @return 	 void

  Writes a message to a file, in the style of printf.


\-----------------------------------------------------------------------------*/
void SSL_Log_Write(const char *text, ...) {

	/* if we are logging */
	if (LOGGIN) {

		char format[250];
		int count = 0;
		int i, j;
		char c;
		double d;
		unsigned u;
		char *s;
		void *v;


		/* open the file */
		FILE *file = fopen(LOG_FILE_PATH, "a+");

		/* if we could not open the file return */
		if (file == NULL) {
			free(file);
			return;
		}

		/* get the current time */
		char* time = getTime();

		/* print out the time */
		fprintf(file, "%s: ", time);

		/* get the argument list */
		va_list arg;

		/* print out the message */
		va_start(arg, text);
			while (*text) {
				for (j = 0; text[j] && text[j] != '%'; j++)
				  format[j] = text[j];
				if (j) {
				  format[j] = '\0';
				  count += fprintf(file, format);
				  text += j;
				} else {
				  for (j = 0; !isalpha(text[j]); j++) {
					format[j] = text[j];
					if (j && text[j] == '%')
					  break;
				  }
				  format[j] = text[j];
				  format[j + 1] = '\0';
				  text += j + 1;

				  switch (format[j]) {
				  case 'd':
				  case 'i':
					i = va_arg(arg, int);
					count += fprintf(file, format, i);
					break;
				  case 'o':
				  case 'x':
				  case 'X':
				  case 'u':
					u = va_arg(arg, unsigned);
					count += fprintf(file, format, u);
					break;
				  case 'c':
					c = (char) va_arg(arg, int);
					count += fprintf(file, format, c);
					break;
				  case 's':
					s = va_arg(arg, char *);
					count += fprintf(file, format, s);
					break;
				  case 'f':
				  case 'e':
				  case 'E':
				  case 'g':
				  case 'G':
					d = va_arg(arg, double);
					count += fprintf(file, format, d);
					break;
				  case 'p':
					v = va_arg(arg, void *);
					count += fprintf(file, format, v);
					break;
				  case 'n':
					count += fprintf(file, "%d", count);
					break;
				  case '%':
					count += fprintf(file, "%%");
					break;
				  default:
					fprintf(stderr, "Invalid format specifier in log().\n");
					break;
				  }
				}
			  }
		va_end(arg);

		/* print a new line */
		fprintf(file, "\r\n");

		/* close the file and return */
		fclose(file);

		/* free memory */
		free(file);
		free(time);
	}
}
