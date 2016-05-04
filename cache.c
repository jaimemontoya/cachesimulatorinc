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
	
  

  printf("\nInput:\n");
  printf("Jaimes-iMac:csc252-project4 jaimemontoya$ ./cacheSim -s 1024 -w 2 -l 512 -t trace.trace\n");
  printf("Output:\n");
  printf("argv[0]: ./cacheSim\n");
  printf("argv[1]: -s\n");
  printf("argv[2]: 1024\n");
  printf("argv[3]: -w\n");
  printf("argv[4]: 2\n");
  printf("argv[5]: -l\n");
  printf("argv[6]: 512\n");
  printf("argv[7]: -t\n");
  printf("argv[8]: trace.trace\n");
  printf("\nargv[0]: %s", argv[0]);
  printf("\nargv[1]: %s", argv[1]);
  printf("\nargv[2]: %s", argv[2]);
  printf("\nargv[3]: %s", argv[3]);
  printf("\nargv[4]: %s", argv[4]);
  printf("\nargv[5]: %s", argv[5]);
  printf("\nargv[6]: %s", argv[6]);
  printf("\nargv[7]: %s", argv[7]);
  printf("\nargv[8]: %s\n", argv[8]);
  FILE * fp;
  char * lineinfile = NULL;
  size_t len = 0;
  ssize_t read; 
  char *folder = "traces/";
  char *tracefile = argv[8];
  char fileaddress[80];
  strcpy(fileaddress, "");
  strcat(fileaddress, folder);
  strcat(fileaddress, tracefile);
  char singlechar[10];  
  char sorl[1];
  fp = fopen(fileaddress, "r");
  if (fp == NULL){
  	printf("Exit failure");
  }else{
  	printf("Perfect, success");
  }
  while((read = getline(&lineinfile, &len, fp)) != -1) {  	
  	/*printf("%s", lineinfile);  	
  	printf("%c\n", lineinfile[0]);
  	printf("%c\n", lineinfile[1]);
  	printf("%c\n", lineinfile[2]);
  	printf("%c\n", lineinfile[3]);
  	printf("%c\n", lineinfile[4]);
  	printf("%c\n", lineinfile[5]);
  	printf("%c\n", lineinfile[6]);
  	printf("%c\n", lineinfile[7]);
  	printf("%c\n", lineinfile[8]);
  	printf("%c\n", lineinfile[9]);
  	printf("%c\n", lineinfile[10]);
  	printf("%c\n", lineinfile[11]);  */	
  	//if (lineinfile[11] == "0"){
  	//if (strcmp(lineinfile, "l 0x1ffff630\n") == 0){
  	//if (strcmp(&lineinfile[0], "l") == '\0'){
  		printf("We found a zero");
      strncpy(sorl, &lineinfile[0], 1);
  		strncpy(singlechar, &lineinfile[2], 10);
  		//printf("The value is: %s\n", singlechar);
  	//}
    printf("The value of sorl: %s\n", sorl);
    printf("The value of singlechar is: %s\n\n", singlechar);
  }
  fclose(fp);
  if (lineinfile)
  	free(lineinfile);
  exit(EXIT_SUCCESS);
  
  	




  /* TODO: Probably should intitalize the cache */

  printf("Ways: %u; Sets: %u; Line Size: %uB\n", 0, 0, 0/* FIXME */);
  printf("Tag: %d bits; Index: %d bits; Offset: %d bits\n", 0, 0, 0/* FIXME */);

	/* TODO: Now we read the trace file line by line */
  
  /* TODO: Now we simulate the cache */  

  /* Print results */
  printf("Miss Rate: %8lf%%\n", ((double) totalMisses) / ((double) totalMisses + (double) totalHits) * 100.0);
  printf("Read Transactions: %d\n", read_xactions);
  printf("Write Transactions: %d\n", write_xactions);

  /* TODO: Now we output the file */

  /* TODO: Cleanup */
}
