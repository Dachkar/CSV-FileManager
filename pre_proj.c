#include<stdio.h>
#include<string.h>// lets us use the strcmp function. Used o compare strings in C
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
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

	char max[] = "-max";

	char min[] = "-min";

	char mean[]= "-mean";



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
		char OtherFields[900][300];//Hold other fields . Otherfields[How many fields][Length of each field]
		float  maxn;
		float minn;
		float meann;
		int rValue;



	};
	struct field fields[300];
	char words[300];//Acts like buf
	bool firstLine=true;
	int Li;// Comments below
	int p=0;//counter for fieldc. To know where to add the next char
	int fieldN=0;//keeps track of current field we are on
	char fieldC[300];//name of current field
	bool quoteTracker = false;//Tells if we are in a quote or not
	int fieldRows=0 ;//count which row we are on
	int Records=0;
	int FieldsA=0;
	while(fgets(words,300,inFile)!=NULL)
	{
		//int Li;//Counter to show which character we are on
		Records++;
		//int fieldN=0;// Counter for which field we a re on
		for(Li=0;Li<strlen(words);Li++)
		{
			//char fieldC[100];//name of current field
			switch(words[Li]){

				case'"':
				if(firstLine)
				{
					if((Li+1)==strlen(words))
					{
						memcpy(fields[fieldN].name,fieldC,sizeof(fieldC));
						fieldN=0;
						firstLine=false;
						p=0;
						FieldsA++;
					}
				}
				else//not firstline
				{
					if((Li+1)==strlen(words))
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
							memset(fieldC,0,300);// erase current word
							FieldsA++;
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
								memset(fieldC,0,300);
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
								//	fieldC[p]=words[Li];
								memcpy(fields[fieldN].name,fieldC,sizeof(fieldC));
								fieldN=0;
								firstLine=false;
								p=0;
								FieldsA++;
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
				memset(fieldC,0,300);
			}// end of while
			/*for(int k =0;k<10;k++){
			printf("%d",Records);
			printf("\n");
		}*/
		//	printf("%f\n",atof(fields[7].OtherFields[0]));
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
					for(I=0; I < strlen(buf); I++){


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
				//const int initializer = i + 1;

				char fieldName[200];
				char cleanFn[200];
				strcpy(fieldName, argv[i + 1]);
				printf("we are in the max\n");



				printf("fieldName %s\n", fieldName);
				printf("cleanFn: %s\n", cleanFn);
				int y = 0;
				int j = 0;
				float firstVal;

				for (y; y < FieldsA; y++){
					puts(fields[y].name);
					puts("COMPARE");
					puts(fieldName);
					if (strcmp(fieldName, fields[y].name) == 0){
						puts("FIRST LOOP> WE MADE IT BOYS");
						bool validNum = false;
						if(atof(fields[y].OtherFields[0]) != 0){
							validNum = true;
							firstVal = atof(fields[y].OtherFields[0]);


							printf("We are in a number");
						}else {
							puts("Non-numeric data - exit error 1");
							return -1;}
							if(validNum){
								for (j; j < Records; j++){
									fields[y].maxn = firstVal;
									if(atof(fields[y].OtherFields[j]) > fields[y].maxn){
										fields[y].maxn = atof(fields[y].OtherFields[j]);



									}

									printf("Max val#%f",fields[y].maxn);


								}
							}

						}


					}


					for (j; j < Records; j++){



					}
					//Displays the max value in the indicated field
				}

				else if(strcmp(argv[i],mean) == 0){
					char fieldName[200];
					char cleanFn[200];
					strcpy(fieldName, argv[i + 1]);
					printf("We are in the mean\n");


					printf("fieldName %s\n", fieldName);
					printf("cleanFn: %s\n", cleanFn);
					int y = 0;
					int j = 0;
					float firstVal;
					float meanVal[Records];
					float totalSum = 0.0;
					float validEntries = 0.0; /* TO be used if we are checking if values are
					0 before adding them to the average. Check the todo below for more info.*/

					float totalMean = 0.0;


					for (y; y < FieldsA; y++){
						puts(fields[y].name);
						puts("COMPARE");
						puts(fieldName);
						//If we are at the field that we were looking for, go in loop
						if (strcmp(fieldName, fields[y].name) == 0){
							puts("FIRST LOOP> WE MADE IT TO THE FIELD BOYYYYYSS");
							//validNum determines if the column has number values or not
							//It could be improoved, and maybe i will need to
							//TODO -min field Display the minimum value in the indicated field of the data records.
							// The first field is numbered 0. <-- This is what concerns me with our current checking method.
							//TODO ENSURE THAT --> This option ignores non-numeric data in the indicated field. If there is no
							// numeric data in the indicated field in *ANY* of the data records the program exits with error code 1.
							bool validNum = false;
							if(atof(fields[y].OtherFields[0]) != 0){
								validNum = true;
								firstVal = atof(fields[y].OtherFields[0]);
							}else {
								puts("Non-numeric data - exit error 1");
								return -1;}
								if(validNum){
									for (j; j < Records; j++){
										//if we are checking for the 0 here (todo requirement), we should have an if statement
										// that validates entries as we go. For now, all values are being added.
										totalSum = totalSum + atof(fields[y].OtherFields[j]);



									}
								}

							}


						}
							//Calculating mean over ALL records. Might need change if we filter entries.
							totalMean = totalSum / Records;
							printf("Total mean is:%f\n",totalMean);


				}


				else if(strcmp(argv[i],min) == 0)
				{





					char fieldName[200];
					char cleanFn[200];
					strcpy(fieldName, argv[i + 1]);
					printf("we are in the max\n");



					printf("fieldName %s\n", fieldName);
					printf("cleanFn: %s\n", cleanFn);
					int y = 0;
					int j = 0;
					float firstVal;

					for (y; y < FieldsA; y++){
						puts(fields[y].name);
						puts("COMPARE");
						puts(fieldName);
						if (strcmp(fieldName, fields[y].name) == 0){
							puts("FIRST LOOP> WE MADE IT BOYS");
							bool validNum = false;
							if(atof(fields[y].OtherFields[0]) != 0){
								validNum = true;
								firstVal = atof(fields[y].OtherFields[0]);


								printf("We are in a number");
							}else {
								puts("Non-numeric data - exit error 1");
								return -1;}
								if(validNum){
									for (j; j < Records; j++){
										fields[y].maxn = firstVal;
										if(atof(fields[y].OtherFields[j]) < fields[y].maxn){
											fields[y].maxn = atof(fields[y].OtherFields[j]);



										}

										printf("Max val#%f",fields[y].maxn);


									}
								}

							}


						}




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
