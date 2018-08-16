#include <stdlib.h>

int main (int argc, char *argv[])
{
	FILE *fsp, *dfp; // source and destination file descriptors 
	char dest_file[100];
	char open_file_command[100];
	pevent_t *event;

	/* opnen the file */
	if(NULL == (fsp = fopen(argv[1], "r")))
	{
		printf("Error! File %s could not be opened\n", argv[1]);
		return 2;
	}
	/* Check for output file */
	if (argc > 2) 	{
		sprintf(dest_file, "%s.html", argv[2]);
	}	else	{
		sprintf(dest_file, "%s.html", argv[1]);
	}
	........
	/* write HTML starting Tags */
	html_begin(dfp, HTML_OPEN);
        ........	 
	/* Call start_or_end_conv function for ending the convertation */
	html_end(dfp, HTML_CLOSE);

  /* close file */
	fclose(fsp);
	fclose(dfp);

	printf("Output file %s generated\n", dest_file);
	sprintf(open_file_command, "firefox %s", dest_file);
	system(open_file_command);
	return 0;
}
