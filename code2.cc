#include <stdlib.h>

int main (int argc, char *argv[])
{
	FILE *fsp, *dfp; // source and destination file descriptors 
	char dest_file[100];
	char open_file_command[100];
	pevent_t *event;

	/* opnen the file */
	if(NULL == (fsp = fopen(argv[1], "r"))) // need to check argc size and also argv[1] is null or empty string
	{
		printf("Error! File %s could not be opened\n", argv[1]);
		return 2;
	}
	/* Check for output file */ 
	if (argc > 2) 	{
		sprintf(dest_file, "%s.html", argv[2]); // need to check size between dest_file and argv[2]
	}	else	{
		sprintf(dest_file, "%s.html", argv[1]); // need to check size between desf_file and argv[1] 
	}
	........
	/* write HTML starting Tags */
	html_begin(dfp, HTML_OPEN); // no null check for dfp
	                            // where is HTML_OPEN ?
        ........	 
	/* Call start_or_end_conv function for ending the convertation */
	html_end(dfp, HTML_CLOSE); //  do it when dfp is valid

  /* close file */
	fclose(fsp); // do it when fsp is valid
	fclose(dfp); // do it when dfp is valid

	printf("Output file %s generated\n", dest_file);
	sprintf(open_file_command, "firefox %s", dest_file); // need to check size of dest_file and open_file_command since fireforx takes a few characters
	system(open_file_command); // do not use system, fork ...
	return 0;
}
