#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Accepts a .c file (or a source code)
//Develop some sort of like a preprocessor
//Ouput the complete, and proper *sequence* of functions executed

//Return a file pointer to open a file
FILE *openPtr( char fDir[ ] );

//Print a given string toWrite to a given outputStream (e.g. output.txt)
void displayToOutput( char outputStream[ ], char toWrite[ ] );

//Return char pointer (para ma-access nimo ang after sa #include)
char *accessFileNameAfterInclude( char str[ ] );

//I-output sa usa ka-file ang pasunod na execution sa #include's (preprocessor directives)
void parse( FILE *fPtr, char outputStream[ ], char streamForRemembering[ ] );

//Return 1 if a given newDirective is not in the directivesArr (w/c contains the previous included directives)
//Return 0 otherwise
int isNotRepeating( char *directivesArr[], char newDirective[] );

//Return the number of times a certain header string appears in a file
int occurrence( FILE *fPtr, char header[] );

//Write katung mga preprocessor directives (sa pinaka source code lang) to a chosen output file (outputStream)
void remember( FILE *scodePtr, char outputStream[] );

//Unremember the contents written in streamForRemembering
void unremember( char streamForRemembering[] );

int main( ){
	//NOTE: "input.c" should be "inputFile.cpp"

	// char *streamForRemembering = "outer.txt";
	// char *inputFile = "input.c";
	// char *outputFile = "output.txt";

	unremember("outer.txt");
	unremember("output.txt");
	remember( openPtr("input.c"), "outer.txt");
	parse( openPtr("input.c"), "output.txt", "outer.txt");

	//NOTE: "outer.txt" (or what's assigned to streamForRemembering) upon the end of this main() execution will cause
	//some "logical errors" if tested for "input.c" (or other) again so function unremember must be ran
	return 0;
}

//What we need:
//1. Accept those na naa sa #include, but check sa if within "" and kung wala nagbalik2
	//to do: unsaon pag-acces sa per line para ma-extract ang sunod sa #include
//2. I-open ang katung naa sa #include na file, check for #include's nasad, if wala: iprint ang naa sa file na functions..
//*MAO NI PROBABLE BASE CASE*
	//...then balik na sa gi-originate'an sa naa sa #include (I think ma-apply ra ni sa recursion na part automatically)
//3. Else (kung naa): i-open ang naa sa #include (then balik sa one)
	//to do: i-accept again with the "file directory"
	//*NOTE* Be careful to include the *proper* file directory


FILE *openPtr( char fDir[ ] ){
	return fopen(fDir, "r");
} //end openPtr

void displayToOutput( char outputStream[ ], char toWrite[ ] ){
	FILE *out = fopen(outputStream, "a+");

	fprintf( out, "%s", toWrite );
	fclose(out);

} //end displayToOutput

char *accessFileNameAfterInclude( char str[ ] ){
	static char fName[50] = "\0";
	size_t i = 0;
	size_t j;

	if ( str[9] != '"'){
		//do nothing
	} else{
		while (str[i] != '"'){
			++i;
		} //end while

		//store katung naa's "" into array
		for (j = 0; str[++i] != '"'; ++j){
			fName[j] = str[i];
		} //end for

		fName[j] = '\0';
	} //end if-else

	return fName;
} //end accessFileNameAfterInclude

int isNotRepeating( char *directivesArr[], char newDirective[] ){
	
	//i starts at 1
	for ( size_t i = 1; directivesArr[i] != '\0'; i++ ){
		if ( strcmp(directivesArr[i], newDirective) == 0 ){
			return 0; //meaning, nagrepeat
		}
	}

	return 1; //newDirective is not repeated
} //end isNotRepeating

int occurrence( FILE *fPtr, char header[] ){
	char otherHeader[50] = "\0";
	int occurrence = 0;

	while( fgets(otherHeader, 50, fPtr) != NULL ){
		//meaning they are equal
		if ( memcmp(otherHeader, header, strlen(header)) == 0 ){
			occurrence++;
		}
	}

	return occurrence;
}

//outputStream is where to write the headers to "remember"
void remember( FILE *scodePtr, char outputStream[] ){
	char line[200] = "#";
	char *dir; //to store current directive

	while( fgets(line, 200, scodePtr) != NULL ){
		dir = accessFileNameAfterInclude(line);
		
		if (line[0] != '#'){
			fclose(scodePtr);
		} else{
		 	//include only dir (or directives) that didn't appear previously
		 	if (occurrence(openPtr(outputStream), dir) == 0){
		 		displayToOutput(outputStream, dir);
		 		displayToOutput(outputStream, "\n");
		 	}
		} //end if-else
	} //end while
} //end remember

void unremember( char streamForRemembering[] ){
	FILE *out = fopen(streamForRemembering, "w");

	fprintf( out, "%s", "" );
	fclose(out);
} //end unremember

void parse( FILE *fPtr, char outputStream[ ], char streamForRemembering[ ] ){
	static char line[200] = "#"; //to store a certain line from file
	static char *prepDirectivesArr[50];
	static size_t j = 0; //counter variable
	static char *remember; //to hold an important string

	if ( fPtr == NULL ){
		puts("File cannot be opened.");
	}

	while ( fgets(line, 200, fPtr) != NULL ){

		if( line[0] != '#' ){
			displayToOutput(outputStream, line);
		} else if ( line[0] == '#' && line[9] != '"' ){
			parse(fPtr, outputStream, streamForRemembering);
		} else {
			remember = accessFileNameAfterInclude(line);
			if ( occurrence(openPtr(streamForRemembering), remember) == 1
				&& !isNotRepeating(prepDirectivesArr, accessFileNameAfterInclude(line))){
				parse(openPtr(remember), outputStream, streamForRemembering);
				displayToOutput(streamForRemembering, remember);
				displayToOutput(streamForRemembering, "\n");
			} else {
				if ( isNotRepeating( prepDirectivesArr, accessFileNameAfterInclude(line)) ){
					parse(openPtr(accessFileNameAfterInclude(line)), outputStream, streamForRemembering);
					prepDirectivesArr[++j] = accessFileNameAfterInclude(line); //dapat ni i-something
					displayToOutput(outputStream, "\n");
				} else{
					printf( "WARNING: previous file %s was included\n", accessFileNameAfterInclude(line) );
				}
				
			}
		} //end if-else
	} //end while
} //end parse