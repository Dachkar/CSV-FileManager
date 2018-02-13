#include<stdio.h>
#include<string.h>// lets us use the strcmp function. Used o compare strings in C
/*Joe Mingoia
 *Tyler Turnbull
 *Douglas Achkar
 .Dylan Wong */


int main(int argc, char* argv[]){

FILE* inFile = fopen(argv[argc - 1], "r");  // To open the csv file

if(inFile == NULL){
	printf("No such file.");
	return 0;
}

char _f[]= "-f";
char _r[]= "-r";
char _h[]= "-h";

char max[] = "max";

char min[] = "min";

char mean[]= "mean";



// Here is an idea for the object
struct data {
	int ref_date;
	char geo[40];
	char viewer[100];
	char content[100];
	char program[100];
	char vector[20];
	char coordinate[10];
	float value;
};
int i;// for loop iterator vairable. Its 1 cause argv[0] is this program
// Loop iterates to argc - 1 because the final arg is the filename
for(i = 1; i < argc -1; i++)
{


	printf("Start of loop, i = %d, arg is %s\n", i, argv[i]);

         if(strcmp(argv[i],_f) == 0 ) // compares both strings to see if they match
		{
			// Display the number of fields in first record.
			printf("Running -f command");

			FILE* inFile = fopen(argv[argc - 1], "r");
                        if(inFile == NULL){
                                printf("No such file.");
                                 return 0;
                        } 
		
			char* buf[100];
			
			while(fscanf(inFile, "%s,", buf) == 1){
				printf("%s\n", buf);
			}

			fclose(inFile);	
		}
 
	else if(strcmp(argv[i],_r) == 0)
		{
			//Display the number of records in file. We could count the amount of times we scan
			printf("Running -r command\n");
			FILE* inFile = fopen(argv[argc - 1], "r");
                        if(inFile == NULL){
                                printf("No such file.");
                                 return 0;
                        } 
			int count;
	
			char* buf[100];	
			while(fscanf(inFile,"%s", buf) == 1){
				printf("%s\n", buf);
			}
			
		
			printf("%d \n", count);
			fclose(inFile);
			
		}
	else if(strcmp(argv[i],_h) == 0)
		{
		//Treat the first record of the file as a header record rather than a data record
		//This is kind of painful, but we could make an int that represents true and false,1 and 0. and have an if statement everywhere that would
		//progress the first scan without doing anything.
		}          
	

	
	else if(strcmp(argv[i],max) == 0) // Compares strings
		{
		//Displays the max value in the indicated field
		// we could scan the whole field and just have a vairable that keeps track of the highest number. 
		}
	
		
	else if(strcmp(argv[i],min) == 0)
		{
		//Displays the lowest value in the indicated field
		// Same as Max but for min
		}

	
	else if(strcmp(argv[i],mean) == 0)
		{
		// Displays the mean in a given field. 
		// Can have a variable that sums everything up and a counter to count how many times we scanned. 
		}
	else if ( 5== 5) // ref field value goes here. I dont know what the argument call is 
		{

		}
}

  return 0;
}
