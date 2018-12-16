/* Käyttöjärjestelmät ja systeemiohjelmointi Syksy 2018 */
/* my-zip by Pauli Pulkkinen 0081769                    */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE *fp;
  int i;
  int charcount;
  char blobc_curr;
  char blobc_prev;

  if (argc == 1) {
    printf("my-zip: file1 [file2 ...]\n");
    exit(1);   
    }

  for(i=1;i<argc;i++) {
    fp = fopen(argv[i], "r");
    
    if (fp == NULL) {
      exit(1);
    }

  /* Lets set the initial conditions */
  /* At first the number of consecutive characters is 0 */

    charcount = 0;
  
  /* We'll read the first characters into buffer and initially set the first
     and prev characters to same */

    blobc_curr=fgetc(fp);
    blobc_prev=blobc_curr;

  /* Loop until we reach EOF. */
    while (blobc_curr != EOF) {
      if (blobc_curr != blobc_prev) {

      /* If the previous character is different than current, write the number
         (4 byte integer) of consecutive previous characters and then the actual 
         previous character (char) to stdout */

        fwrite(&charcount, sizeof(int), 1, stdout);
        fputc(blobc_prev, stdout);
      
      /* Set the character counter to 1 (as in the first count of a unique 
         character we have now */

        charcount = 1;
      } else {

      /* If the current and previous seen characters were same, we
         increase the character counter  */
        charcount++;
      }

      /* Now we move the stream read position, reading the next character in,
         returning to the beginning of the while loop */
      blobc_prev = blobc_curr;
      blobc_curr = fgetc(fp);
      }
  
    }
  return(0);
}