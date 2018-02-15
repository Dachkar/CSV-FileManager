#include<stdio.h>
#include<string.h>// lets us use the strcmp function. Used o compare strings in C
#include<stdbool.h>
#include<string.h>
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
struct field {
char name[300];
char OtherFields[10][300];//Hold other fields . Otherfields[How many fields][Length of each field]
int max;
int min;
int rValue;



};
struct field fields[300];
char words[300];//Acts like buf
bool firstLine=true;
int Li;// Comments below
int p=0;//counter for fieldc. To know where to add the next char
int fieldN=0;//keeps track of current field we are on
char fieldC[100];//name of current field
bool quoteTracker = false;//Tells if we are in a quote or not
int fieldRows=0 ;//count which row we are on
while(fgets(words,300,inFile)!=NULL)
{
//int Li;//Counter to show which character we are on

//int fieldN=0;// Counter for which field we a re on
for(Li=0;Li<strlen(words);Li++)
{
//char fieldC[100];//name of current field
switch(words[Li]){

case'"':
	if(firstLine)
	{
	if((Li+1)==strlen(words)&&words[Li]=='"')
	{
	memcpy(fields[fieldN].name,fieldC,sizeof(fieldC));
	fieldN=0;	
	firstLine=false;	
	p=0;	
	}
	}
	else//not firstline
		{
		if((Li+1)==strlen(words)&&words[Li]=='"')
		{
		memcpy(fields[fieldN].OtherFields[fieldRows],fieldC,sizeof(fieldC));
		fieldRows++;
		fieldN=0;
		p=0;	
		}
		}
	if(!quoteTracker){
	quoteTracker=true;
	break;}//end of if
	
	else{quoteTracker=false; break;}

case',':
	if(firstLine){
	if(!quoteTracker){
	memcpy(fields[fieldN].name,fieldC,sizeof(fieldC));//memory copy
	p=0;//resets
	fieldN++;
	memset(fieldC,0,100);// erase current word
	break;
	}
	else
	{fieldC[p]=words[Li];
	p++;break;}//does what default does and adds the comma
		}// end of if with first line qrg
	else//not first line
	{
	if(!quoteTracker){
	memcpy(fields[fieldN].OtherFields[fieldRows],fieldC,sizeof(fieldC));//copy string int field struct
	fieldN++;
	p=0;
	memset(fieldC,0,100);
	break;
	}
	else
	{
	fieldC[p]=words[Li];
	p++;break;
	}
	}
	
default:
	if(firstLine){
	

	 if((Li+1)==strlen(words)){
	fieldC[p]=words[Li];
	memcpy(fields[fieldN].name,fieldC,sizeof(fieldC));
	fieldN=0;
	firstLine=false;
	p=0;
	break;
	}
	else{//normal adding chars to fieldC to make a field
	fieldC[p]=words[Li];
	p++;
	break;
	}
	}
	else//not first line
	{
	
	 if((Li+1)==strlen(words))
		{
		fieldC[p]=words[Li];
		memcpy(fields[fieldN].OtherFields[fieldRows],fieldC,sizeof(fieldC));
		fieldRows++;
		fieldN=0;
		p=0;	
		break;
		}
	else//for if its not first line
		{
			fieldC[p]=words[Li];
			p++;
			break;
		}
	}
	
}// end of switch

}// end of fore
memset(fieldC,0,100);
}// end of while
//printf(fields[1].OtherFields[1]);
//printf("\n");
fclose(inFile);
int i;// for loop iterator vairable. Its 1 cause argv[0] is this program
// Loop iterates to argc - 1 because the final arg is the filename
for(i = 1; i < argc -1; i++)
{
	int count=0;// Inializing here for h

	printf("Start of loop, i = %d, arg is %s\n", i, argv[i]);

         if(strcmp(argv[i],_f) == 0 ) // compares both strings to see if they match
		{
			// Display the number of fields in first record.
		

			FILE* inFile = fopen(argv[argc - 1], "r");
                        if(inFile == NULL){
                                printf("No such file.");
                                 return 0;
                        } 
		
			char buf[300];
			char currString[100];
			char *p;
			int cols = 0;	
			while(fgets(buf, 300, inFile) != NULL){
		
				p = buf;
				int I;//changed to cap i to no get confused with little i in big for loop
				bool comma = false; // if true tricky comma detected
				char curString[100];
				memset(curString, 0, 100);
				int curStringIndex = 0;
				cols = 0;
				for(I=0; i < strlen(buf); i++){
			
					 
					if(buf[I] == '"' && comma == false ){
						comma = true;
						curString[curStringIndex] = buf[I];
						curStringIndex++;
						
					}else if(buf[I] == '"' && comma == true){
						comma = false;
						curString[curStringIndex] = buf[I];
						curStringIndex++;
						
					}else if((buf[I] == ',' && comma == false) || I == strlen(buf) - 1){
						// at end of curString
						
						curStringIndex = 0;
						memset(curString, 0, 100);
						cols++;
					}else {
						curString[curStringIndex] = buf[I];
						curStringIndex++;
						
					}
				}		
			}
			printf("%d\n", cols);	
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
		//	int count;
	
			 char buf[300];

                        while(fgets(buf, 300, inFile) != NULL){
                               // puts(buf); // This Prints

                       		count++; 
                        }
			
		
			printf("%d \n", count);
			fclose(inFile);
			
		}
	else if(strcmp(argv[i],_h) == 0)
		{
		//Treat the first record of the file as a header record rather than a data record
	FILE* inFile = fopen(argv[argc-1],"r");
			
		}          
	

	
	else if(strcmp(argv[i],max) == 0) // Compares strings
		{
		//Displays the max value in the indicated field
/*		FILE* inFile = fopen(argv[argc-1],"r");
		if (inFile== NULL){printf("No such file");return 0;}
		
		int fCount=0;//Int to iterate through my fields.
		char buf[300];
		int i ;
		while(fgets(buf,300,inFile) != NULL)
		 {
	

		for(i=0;strlen;(buf);i++)
		{


		fCount++;
		printf("printing max names, %s.",fields[fCount].name);	
		}

		}


		fclose(inFile);
	*/	}
	
		
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
