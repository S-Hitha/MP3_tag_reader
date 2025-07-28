#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "types.h"


void read_mp3(char *argv[])
{
	FILE *file = fopen(argv[2], "rb");
	if(!file)
	{
		perror("Error: Unable open file");
		return;
	}

	unsigned char header[HEADERSIZE];
	fread(header, 1, HEADERSIZE, file);

	if(strncmp((char *)header, "ID3", 3) != 0)
	{
		printf("No ID3v2 tag found\n");
		fclose(file);
		return;
	}

	fseek(file, HEADERSIZE, SEEK_SET);

	while(1)
	{

	unsigned char framedata[FRAMEHEADERSIZE];
	
		if(fread(framedata, 1, FRAMEHEADERSIZE, file) != FRAMEHEADERSIZE)
			break;

		char framename[5] = {0};
		memcpy(framename, framedata, 4);

		unsigned int  framesize = (framedata[4] << 24) |
		       	(framedata[5] << 16) | 
			(framedata[6] << 8) | 
			framedata[7];

		if(framesize == 0)
			break;

		char *data_buffer = (char *)malloc(framesize + 1);
		if(!data_buffer)
		{
			printf("Memory allocation error\n");
			fclose(file);
			return;
		}

		fread(data_buffer, 1, framesize, file);
		data_buffer[framesize] = '\0';
		
		char *num = data_buffer + 1;

		if(strcmp(framename, "TIT2") == 0) 
			printf("Title	: %s\n", num);
		
		else if(strcmp(framename, "TPE1") == 0) 
			printf("Artist	: %s\n", num);
	
		else if (strcmp(framename, "TALB") == 0)
			printf("Album	: %s\n", num);

		else if (strcmp(framename, "TYER") == 0)
			printf("Year	: %s\n", num);
		 
		else if (strcmp(framename, "TCON") == 0)
			printf("Genre	: %s\n", num);
		
		free(data_buffer);

	}

		fclose(file);
}
