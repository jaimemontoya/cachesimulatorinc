#include "cache.h"
#include "trace.h"

int write_xactions = 0;
int read_xactions = 0;

/*
  Print help message to user
*/
void printHelp(const char * prog) {
  printf("%s [-h] | [-s <size>] [-w <ways>] [-l <line>] [-t <trace>]\n", prog);
  printf("options:\n");
  printf("-h: print out help text\n");
  printf("-s <cache size>: set the total size of the cache in KB\n");
  printf("-w <ways>: set the number of ways in each set\n");
  printf("-l <line size>: set the size of each cache line in bytes\n");
  printf("-t <trace>: use <trace> as the input file for memory traces\n");
  /* EXTRA CREDIT
  printf("-lru: use LRU replacement policy instead of FIFO\n");
  */
}
/*
  Main function. Feed to options to set the cache
  
  Options:
  -h : print out help message
  -s : set L1 cache Size (KB)
  -w : set L1 cache ways
  -l : set L1 cache line size
*/
int main(int argc, char* argv[])
{
  int i;
  uint32_t size = 32; //total size of L1$ (KB)
  uint32_t ways = 1; //# of ways in L1. Default to direct-mapped
  uint32_t line = 32; //line size (B)

  // hit and miss counts
  int totalHits = 0;
  int totalMisses = 0;

  char * filename;

  //strings to compare
  const char helpString[] = "-h";
  const char sizeString[] = "-s";
  const char waysString[] = "-w";
  const char lineString[] = "-l";
  const char traceString[] = "-t";
  const char lruString[] = "-lru";
  
  if (argc == 1) {
    // No arguments passed, show help
    printHelp(argv[0]);
    return 1;
  }
  
  //parse command line
  for(i = 1; i < argc; i++)
  {
    //check for help
    if(!strcmp(helpString, argv[i]))
    {
      //print out help text and terminate
      printHelp(argv[0]);
      return 1; //return 1 for help termination
    }
    //check for size
    else if(!strcmp(sizeString, argv[i]))
    {
      //take next string and convert to int
      i++; //increment i so that it skips data string in the next loop iteration
      //check next string's first char. If not digit, fail
      if(isdigit(argv[i][0]))
      {
        size = atoi(argv[i]);
      }
      else
      {
        printf("Incorrect formatting of size value\n");
        return -1; //input failure
      }
    }
    //check for ways
    else if(!strcmp(waysString, argv[i]))
    {
      //take next string and convert to int
      i++; //increment i so that it skips data string in the next loop iteration
      //check next string's first char. If not digit, fail
      if(isdigit(argv[i][0]))
      {
        ways = atoi(argv[i]);
      }
      else
      {
        printf("Incorrect formatting of ways value\n");
        return -1; //input failure
      }
    }
    //check for line size
    else if(!strcmp(lineString, argv[i]))
    {
      //take next string and convert to int
      i++; //increment i so that it skips data string in the next loop iteration
      //check next string's first char. If not digit, fail
      if(isdigit(argv[i][0]))
      {
        line = atoi(argv[i]);
      }
      else
      {
        printf("Incorrect formatting of line size value\n");
        return -1; //input failure
      }
    }
    else if (!strcmp(traceString, argv[i])) {
      filename = argv[++i];
    }
    else if (!strcmp(lruString, argv[i])) {
      // Extra Credit: Implement Me!
      printf("Unrecognized argument. Exiting.\n");
      return -1;
    }
    //unrecognized input
    else{
      printf("Unrecognized argument. Exiting.\n");
      return -1;
    }
  }
  
  uint32_t sets = size * 1024 / (line * ways);
  int offset = log2(line);
  int index = log2(sets);
  int tag = 32 - (index + offset);
  

  printf("\nInput:\n");
  FILE * fp;
  char * lineinfile = NULL;
  size_t len = 0;
  ssize_t read; 
  char *folder = "";
  char *tracefile = filename;
  char fileaddress[80];
  strcpy(fileaddress, "");
  strcat(fileaddress, folder);
  strcat(fileaddress, tracefile);

  int cachedata[sets][line];
  int cachetag[sets][line];
  int cachevb[sets][line];
  int cachedb[sets][line];
  int validbit[sets];
  int dirtybit[sets];

  char hexstring[10];
  uint32_t hexvalue;
  char sorl[1];
  uint32_t offsetvalue;
  uint32_t indexvalue;
  uint32_t tagvalue;
  int existsincache;

  /* TODO: Probably should intitalize the cache */

  printf("Ways: %u; Sets: %u; Line Size: %uB\n", ways, sets, line);
  printf("Tag: %d bits; Index: %d bits; Offset: %d bits\n", tag, index, offset);

  for (int i = 0; i < sets; i++) {
  	validbit[i] = 0;
  	dirtybit[i] = 0;
  	for (int j = 0; j < line; j++) {
  		cache[i][j] = 0;
  	}
  }

  /* TODO: Now we read the trace file line by line */

    fp = fopen(fileaddress, "r");
  if (fp == NULL){
    printf("Exit failure");
  }else{
    printf("Perfect, success");
  }
  while((read = getline(&lineinfile, &len, fp)) != -1) {    

  	// load in data
	  strncpy(sorl, &lineinfile[0], 1);
	  strncpy(hexstring, &lineinfile[2], 10);
	  hexvalue = (int)strtol(hexstring, NULL, 0);
	  printf("The value of sorl: %s\n", sorl);
	  printf("The value of hexstring is: %s\n", hexstring);
	  printf("The value of hexvalue is: %x\n", hexvalue);

	  offsetvalue = ((hexvalue << (32 - offset)) >> (32 - offset));
	  printf("Offset value: %i\n", offsetvalue);

	  indexvalue = ((hexvalue << (32 - offset - index)) >> (32 - index));
	  printf("Index value: %i\n", indexvalue);

	  tagvalue = (hexvalue >> (32 - tag));
	  printf("Tag value: %i\n", tagvalue);


	  // we now have ways, sets, line (size), sorl, offsetvalue, indexvalue, tagvalue






	  printf("\n");
    
  }
  
  /* TODO: Now we simulate the cache */  

  /* Print results */
  printf("Miss Rate: %8lf%%\n", ((double) totalMisses) / ((double) totalMisses + (double) totalHits) * 100.0);
  printf("Read Transactions: %d\n", read_xactions);
  printf("Write Transactions: %d\n", write_xactions);

  /* TODO: Now we output the file */

  /* TODO: Cleanup */
  fclose(fp);
  if (lineinfile)
    free(lineinfile);
  exit(EXIT_SUCCESS);
}
