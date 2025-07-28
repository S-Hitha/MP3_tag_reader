#ifndef TYPES_H
#define TYPES_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define HEADERSIZE 10
#define FRAMEHEADERSIZE 10

typedef struct
{
	char tag[3];
	char title[30];
	char artist[30];
	char album[30];
	char year[4];
	char *img_file;
	FILE *fptr_img;

}Mp3Info;

void error_msg();
void show_help_menu();
void read_mp3(char *argv[]);
void modify_mp3(char *argv[]);

#endif

