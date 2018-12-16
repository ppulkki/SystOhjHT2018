/* Käyttöjärjestelmät ja systeemiohjelmointi Syksy 2018 */
/* my-unzip by Pauli Pulkkinen 0081769                    */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE *fp;
  int i;
  size_t bread;
  int count;
  char blobc;
 
/* Print help if input given */

  if (argc == 1) {
    printf("my-unzip: file1 [file2 ...]\n");
    exit(1);   
    }

/* Run un-encode loop for every file inputted */

  for(i=1;i<argc;i++) {
    fp = fopen(argv[i], "r");
    
    if (fp == NULL) {
      exit(1);
    }

/* Lets run the unencode loop until the end of feed is reached. Man(3) fread()
   advices that when the end of file is reached, the output is short count or 
   zero. So the while loop will run until end of file. Here on succefull read
   the fread() output is always one. */

/* The fread() will read the first four bytes, while advancing FILE *fp
   structs stream location. The following fgetc() advances the stream by one
   byte and the while loop starst again at correct location at byte location
   6 keeping the system in sync. */

  while((bread=fread(&count, sizeof(int), 1, fp))==1) {
    blobc = fgetc(fp);
    for (int j = 0; j < count; j++) {
      printf("%c", blobc);
      }
    }
  }
  fclose(fp);
  return(0);

}





