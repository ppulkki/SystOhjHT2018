/* Käyttöjärjestelmät ja systeemiohjelmointi Syksy 2018 */
/* my-grep by Pauli Pulkkinen 0081769                    */
/* my-grep olettaa syöteen olevan tekstiedosto           */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

/* Initilizing an empty file pointer fo internal system struct 'FILE'         */
  FILE *fp;

/* from 'man 3 getline' : If *lineptr is set to NULL and *n is set 0 before   */
/* the call, then getline() will allocate a buffer for storing the line.      */ 
/* This buffer should be freed by the user program even if getline() failed.  */
/* By setting these as such, we avoid playing with malloc()                   */

/* size_t is used to store how many bytes does a given object take.           */
/* Of course the complete definition is more complicated than that, but for   */
/* this the definition suffices. ssize_t is the signed version of this,       */
/* making it possible to have return value for example of value of -1. This   */
/* is useful in many operations */
         
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  int i;

/* Print command help if no paramters given */

  if (argc == 1) {
    printf("my-grep: searchterm [file ...]\n");
    exit(1);
  }

/* When reading from stdin, you must terminate the feed by providing EOF
   yourself from console (default ctrl + d in linux). This implementation is 
   not very robust, as long stdin feeds cause problems. 
   
   When using stdin, its better to pipe the output to a file and then print
   its contents. Otherwise the local echo makes readibng the output hard.
   for e.g.

   $./my-grep search_term 1> temp_file
   $cat temp_file
*/

  if (argc == 2) {
    while ((nread = getline(&line, &len, stdin)) != -1) {
      if(strstr(line,argv[1]))
        printf("%s",line);
      }
      free(line);
      exit(0);
  }

  for(i=2;i<argc;i++) {
    fp = fopen(argv[i], "r");

/* When reading from a file, check if the file can be opened */

    if (fp == NULL) {
      printf("my-grep: cannot open file\n");
      exit(1);
      }

/* Read the input file one line at a time (arbitary line length). For every
   line read, make text comparison with strstr() and print the line when
   comparison has a hit
*/

    while ((nread = getline(&line, &len, fp)) != -1) {
      if(strstr(line,argv[1]))
        printf("%s",line);
      }
    }
/* Lets free the memory aloocated by getline()          */
  free(line);
/* Lets close the file handles */
  fclose(fp);
  return(0);
}