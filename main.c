#include<stdio.h>
#include "types.h"
#include<string.h>

int main(int argc, char *argv[])
{
	if(argc<3)
	{
		if(argc > 1 && strcmp(argv[1], "--help") == 0)
			show_help_menu();
		
		else
			error_msg();

		return 0;
	}


	if(strcmp(argv[1], "-v") == 0)
		read_mp3(argv);

	else if(strcmp(argv[1], "-e") == 0 && argc == 5)
		modify_mp3(argv);

	return 0;
}

void error_msg( )
{
	for(int i=0;i<50;i++)
	{
		printf("-");
	}
	printf("\n");

	printf("ERROR: Invalid arguments provided\n");
	printf("Here's how to use :\n");
	printf("To view : ./a.out -v <Mp3_filename>\n");
	printf("To edit : ./a.out -e -t/-a/-A/-m/-y/-c <new_name>< Mp3_filename>\n");
	printf("Need help? Use: ./a,out --help\n");

	for(int i=0;i<50;i++)
	{
	printf("-");
	}
	printf("\n");	
}

void show_help_menu()
{
	for(int i=0;i<20;i++)
		printf("-");
	printf("Help_Menu");
	for(int i=0;i<20;i++)
		printf("-");
	printf("\n");

	printf("1. -v -> to view the contents\n");
	printf("2. -e -> to edit the contents\n");
	printf("\t\t2.1 -t -> to edit song title\n");
	printf("\t\t2.2 -a -> to edit artist name\n");
	printf("\t\t2.3 -A -> to edit album name\n");
	printf("\t\t2.4 -y -> to edit year\n");
	printf("\t\t2.5 -m -> to edit content\n");
	printf("\t\t2.6 -c -> to edit comment\n");

	for(int i=0;i<50;i++)
		printf("-");
	printf("\n");
}
