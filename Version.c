////////////////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------------- //
//                                                                            //
//                         Version Time Stamping Tool                         //
//                             v1.3 - Jan 27 2014                             //
//                                                                            //
//                        (C) 2011-2014  David Krutsko                        //
//                        See LICENSE.md for copyright                        //
//                                                                            //
// -------------------------------------------------------------------------- //
////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------//
// Prefaces                                                                   //
//----------------------------------------------------------------------------//

#include <time.h>
#include <string.h>
#include <stdio.h>



//----------------------------------------------------------------------------//
// Utility                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the number of days since January 1, 2000. </summary>

static unsigned int Date (void)
{
	time_t lBase;
	time_t lCurr;
	struct tm lTime;

	lTime.tm_sec   = 0;
	lTime.tm_min   = 0;
	lTime.tm_hour  = 0;
	lTime.tm_mday  = 1;
	lTime.tm_mon   = 0;
	lTime.tm_year  = 100;
	lTime.tm_wday  = 6;
	lTime.tm_yday  = 0;
	lTime.tm_isdst = 0;

	lCurr = time   (NULL);
	lBase = mktime (&lTime);

	return (unsigned int) ((lCurr - lBase) / 86400);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the number of seconds since midnight / 2. </summary>

static unsigned int Time (void)
{
	time_t lBase;
	time_t lCurr;
	struct tm* lTime;

	lBase = 0;
	lCurr = time (NULL);

	lTime = localtime (&lCurr);

	lTime->tm_sec  = 0;
	lTime->tm_min  = 0;
	lTime->tm_hour = 0;

	lBase = mktime (lTime);

	return (unsigned int) ((lCurr - lBase) / 2);
}



//----------------------------------------------------------------------------//
// Main                                                                       //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Main execution point for this application. </summary>
/// <param name="argc"> Number of arguments in the command line. </param>
/// <param name="argv"> Arguments from the command line. </param>
/// <returns> Zero for success, error code for failure. </returns>

int main (int argc, const char **argv)
{
	FILE* lFile;
	const char* lFilename1;
	const char* lFilename2;

	int i, j;
	char c, lName[127], h[3] = { 0 };

	if (argc < 2)
	{
		// Print documentation
		printf ("\nVersion Time Stamping Tool\n"										);
		printf ("-------------------------------------\n"								);
		printf ("Copyright (C) 2011-2014 David Krutsko\n\n"								);

		printf ("This application generates c-style preprocessor definitions for\n"		);
		printf ("the current date and time and stores them in the specified file.\n"	);
		printf ("Generated definitions are customizable by the formatting options\n"	);
		printf ("described below. Date is set to the current number of days since\n"	);
		printf ("January 01, 2000. Time is set to the current number of seconds\n"		);
		printf ("since midnight divided by two.\n\n"									);

		printf ("WARNING: Existing contents of the file will be destroyed.\n\n"			);

		printf ("Input:\n"																);
		printf ("  $ Version [Format] [Filename]\n\n"									);

		printf ("Output:\n"																);
		printf ("  0 - No errors occurred\n"											);
		printf ("  1 - No filename was passed\n"										);
		printf ("  2 - File could not be opened\n\n"									);

		printf ("Format:\n"																);
		printf ("  0x - Output as hex (e.g. 0xD, 0xT)\n"								);
		printf ("  D  - Current date\n"													);
		printf ("  T  - Current time\n\n"												);

		printf ("Default:\n"															);
		printf ("  $ Version BUILD=D REVISION=T [Filename]\n\n"							);

		// Not enough arguments
		return 1;
	}

	// Attempt to open the specified file
	lFile = fopen (argv[argc-1], "w");

	// Could not open the file
	if (lFile == NULL) return 2;

	// Determine proper filename
	lFilename1 = strrchr (argv[argc-1], '\\');
	lFilename2 = strrchr (argv[argc-1], '/' );

	if (lFilename1 < lFilename2)
		lFilename1 = lFilename2;

	if (lFilename1 == NULL)
		lFilename1 = argv[argc-1];
	else ++lFilename1;

	// Print file
	if (argc == 2)
	{
		// Use default formatting
		fprintf (lFile, "#define BUILD    %u\n", Date());
		fprintf (lFile, "#define REVISION %u\n", Time());
	}

	else
	{
		h[0] = '%';

		// Handle custom formatting
		for (i = 1; i < argc - 1; ++i)
		{
			// Parse out name
			for (j = 0; ; ++j)
			{
				c = argv[i][j];

				if (c == '=' || c == 0)
					break;

				lName[j] = c;
			}

			// Parse type
			if (c == '=')
			{
				// Null-terminate name
				lName[j++] = 0;

				// Check for hexadecimal flag
				if (argv[i][j] == '0' && argv[i][j+1] == 'x')
				{
					h[1] = 'X';
					j += 2;

					// Hexadecimal output
					fprintf (lFile, "#define %s 0x", lName);
				}

				else
				{
					h[1] = 'u';

					// Decimal output
					fprintf (lFile, "#define %s ", lName);
				}

				// Parsing loop
				c = argv[i][j];
				while (c != 0)
				{
					if ((c | 32) == 'd')
						fprintf (lFile, h, Date());

					else if ((c | 32) == 't')
						fprintf (lFile, h, Time());

					c = argv[i][++j];
				}

				// Output newline
				fprintf (lFile, "\n");
			}
		}
	}

	// Job's done
	fclose (lFile);
	return 0;
}
