/*
Patrick 'PJ' Rape
CS224 Section 1
*/

#include <stdio.h>
#include <string.h>

int printHexBytes(FILE* inputFile, unsigned char* data);
int printBinaryBytes(FILE* inputFile, unsigned char* data);
int convertBinary(int num);


int main(int argC, char** argV){
	//check argument count...
	if(argC < 2){
		printf("Usage: %s <filename>\n", argV[0]);
		return 1;
	}

	//make sure we can open the file...
	FILE* inputFile = fopen(argV[1], "r");
	if(inputFile == NULL){
		printf("Could not open %s!!\n", argV[1]);
		return 2;
	}

	//find out how many bytes are in the file
	//Move file pointer to the end of file.
    fseek(inputFile,0,SEEK_END);
    	//Get the current position of the file pointer.
    int fileSize=ftell(inputFile);
	//now rewind the file
	fseek(inputFile,0,SEEK_SET);

	unsigned int linesPrinted = 0;
	//for hexadecimal print 16 bytes per line, 6 for binary
	int numBytesPrinted = 0;
	unsigned char bytesRead[17];
	bytesRead[16] = 0;//null terminate the array....
	while(fileSize > 0){
		//print the address string
		if (argC == 3 && argV[2][0] == 'b') {
			printf("%08x", linesPrinted * 6);
			printf("%s", ": ");
			
			numBytesPrinted = printBinaryBytes(inputFile, bytesRead);
			fileSize -= numBytesPrinted;
			printf("%s", "\n");
			linesPrinted++;
		}
		else {
			printf("%08x", linesPrinted * 16);
			printf("%s", ": ");
			//now print the data
			numBytesPrinted = printHexBytes(inputFile, bytesRead);
			fileSize -= numBytesPrinted;
			printf("%s", "\n");
			linesPrinted++;
		}
	}

	return 0;
}


int printHexBytes(FILE* inputFile, unsigned char* data){
	int numBytesRead = 0;
	numBytesRead = fscanf(inputFile, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
	&data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6],
	&data[7], &data[8], &data[9], &data[10], &data[11], &data[12], &data[13],
	&data[14], &data[15]);
	
	int bytesPrinted = 0;

	for(int i = 0; i < 16; i++){

		if(i < numBytesRead){//we have data

			printf("%02x", data[i]);
			bytesPrinted++;
	
			//if the byte is non-printable then make it a '.'
			if(data[i] < 32 || data[i] > 126){
				data[i] = 46;
			}
		}
		else {
			printf("%s", "  ");
			bytesPrinted++;
		}

		if (bytesPrinted % 2 == 0){
			printf("%s", " ");
		}
    
	}
	printf("%s", " ");

	for(int i = 0; i < numBytesRead; i++){
		printf("%c", data[i]);
	}
	memset(data, 0, 16 * sizeof(data[0]));
	return numBytesRead;
}

int printBinaryBytes(FILE* inputFile, unsigned char* data) {
	int numBytesRead = 0;
	numBytesRead = fscanf(inputFile, "%c%c%c%c%c%c",
	&data[0], &data[1], &data[2], &data[3], &data[4], &data[5]);
	
	int bytesPrinted = 0;

	for(int i = 0; i < 6; i++){

		if(i < numBytesRead){//we have data

			printf("%08d", convertBinary(data[i]));
			printf("%s", " ");
			bytesPrinted++;
		
			//if the byte is non-printable then make it a '.'
			if(data[i] < 32 || data[i] > 126){
				data[i] = 46;
			}
		}
		else {
			printf("%s", "         ");
			bytesPrinted++;
		}
	}

	printf("%s", " ");

	for(int i = 0; i < numBytesRead; i++){
		printf("%c", data[i]);
	}
	memset(data, 0, 6 * sizeof(data[0]));

	return numBytesRead;
}


int convertBinary(int num) {
	if (num == 0) {
		return 0;
	}
	else {
		return num % 2 + 10 * convertBinary(num / 2);
	}
}
