/* Käyttöjärjestelmät ja systeemiohjelmointi Syksy 2018 */
/* my-cat by Pauli Pulkkinen 0081769                    */
/* my-cat olettaa syöteen olevan tekstiedosto           */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  int i;

/* Initilizing an empty file pointer fo internal system struct 'FILE'         */
  FILE *fp;

/* Value for the maximum length of one line */
/* The +1 is for ensuring that the EOF is also accounted for */
  char ch[1024+1];

/* For every file (entries in argv[] array), try to open file and then print  */
/* content. Exit with exit(1) in-case of a file open failure                  */


  for(i=1;i<argc;i++) {
    fp = fopen(argv[i], "r");
    
    /* If fopen() fails, it returns NULL. On success it returns a pointer to  */
    /* file stream object                                                     */

    if (fp == NULL) {
      printf("my-cat: cannot open file\n");
      exit(1);
      }

    /* we'll read and print the file stream until we encounter EOF           */
    while ((fgets(ch,sizeof(ch),fp)) != NULL) {
      printf("%s",ch);
      }

    /* Because *fp is a pointer to a 'file stream', it                        */
    /* must me closed or we risk a memory leak. It is a good practise to      */
    /* close all handles / streams rather than count on them being closed by  */
    /* the OS on program exit. ESPECIALLY IN C. It is simply a good coding    */
    /* practise.                                                              */

      fclose(fp);
    }
    /* When file open / print loop finished succesfully, exit with return(0)  */
  return(0);
};
