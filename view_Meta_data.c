#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "types.h"

void modify_mp3(char *argv[])
{
	FILE *file = fopen(argv[4], "r+b");
	if(!file)
	{
		perror("Error could not open the file\n");
		return;
	}

	unsigned char header[HEADERSIZE];
	fread(header, 1, HEADERSIZE, file);
	if(strncmp((char *)header, "ID3", 3) != 0)
	{
		printf("ID3v2 tag not found\n");
		fclose(file);
		return;
	}
	
	char *target = argv[2];
	char *new = argv[3];
	fseek(file, HEADERSIZE, SEEK_SET);
	unsigned char frame_header[FRAMEHEADERSIZE];

	while(fread(frame_header, 1, FRAMEHEADERSIZE, file) == FRAMEHEADERSIZE)
	{
		char field_id[5] = {0};
		memcpy(field_id, frame_header, 4);

		unsigned int field_size = (frame_header[4] << 21) |
		       	(frame_header[5] << 14) |
		       	(frame_header[6] << 7) |
		       	frame_header[7];
		
		if(field_size == 0)
			break;

		long pos = ftell(file);
		if((strcmp(target, "-t") == 0 && strcmp(field_id, "TIT2") ==0) ||
		(strcmp(target, "-a") == 0 && strcmp(field_id, "TPE1") ==0) ||
		(strcmp(target, "-A") == 0 && strcmp(field_id, "TALB") ==0) ||
		(strcmp(target, "-y") == 0 && strcmp(field_id, "TYER") ==0) ||
		(strcmp(target, "-g") == 0 && strcmp(field_id, "TCON") ==0))
		{
			fseek(file, pos, SEEK_SET);

			char *temp = (char *)calloc(field_size, 1);
			fwrite(temp, 1, field_size, file);
			free(temp);

			fseek(file, pos+1, SEEK_SET);
			fwrite(new, 1, strlen(new), file);
			printf("Updated %s to: %s\n", field_id, new);
			break;
		}

		fseek(file, field_size, SEEK_CUR);
	}

	fclose(file);		
}





