/* lab1.c
 * Ryan Auger
 * rwauger
 * ECE 2220, Fall 2017
 * MP1
 *
 *
 * Purpose:  To assess the threat level of the user input of numbers
 *
 * Assumptions: You will input the minimum threat level and then input how many times must that appear so as to show it is an actual threat.
 *
 * Bugs:
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 100
#define MAXSAMPLES 500
#define MINTHRESH 3

int main()
{
    char line[MAXLINE];
    int min_threat_level;
    int false_alarm_count;
    int breach_level;  // if a breach, this is the threat level
    int breach_count = 0;  // if a breach, how many times level found
    int b[MAXSAMPLES];
    int x, i, count = 0, counter = 1, j, a, breach;

    // sscanf looks at the array "line" to find the first integer (%d)
    // and puts it at the address of "min_threat_level"
    printf("What is the minimum threat level (or -1 to exit)? ");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &min_threat_level);
    
    if (min_threat_level == -1) {
    	return 0;
    }
    
    // if invalid input is entered
    do {
    	if (min_threat_level < MINTHRESH) {
        	printf("\nThe input is invalid, you entered: %d\n", min_threat_level);
    		printf("What is the minimum threat level (or -1 to exit)? ");
    		fgets(line, MAXLINE, stdin);
    		sscanf(line, "%d", &min_threat_level);
    		if (min_threat_level == -1) {
    			return 0;
    		}
    	}
    } while (min_threat_level < MINTHRESH );

    // Next read the the false alarm count.
    printf("How many times must a threat level occur so not a false alarm? ");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &false_alarm_count);
    // If invalid input is entered do this
	do {
    	if (false_alarm_count < 0) {
    		printf("\nThe input is invalid, you entered: %d\n", min_threat_level);
    		printf("How many times must a threat level occur so not a false alarm? ");
    		fgets(line, MAXLINE, stdin);
    		sscanf(line, "%d", &false_alarm_count);
    		if ( false_alarm_count == -1) {
    			return 0;
    		}
    	}
    } while (false_alarm_count < 0);
    
    // if a valid false alarm count is entered then print this
    printf("\nA false alarm if the count is < %d\n", false_alarm_count);
    
 // Collect the samples, one per line.
 for (i = 0; i < MAXSAMPLES; ++i) {
 	count = 0;
    	for (x = 0; x < MAXSAMPLES; x++) {
    		fgets(line, MAXLINE, stdin);
    		sscanf(line, "%d", &b[x]);
    		if (sscanf(line, "%d", &b[x]) != 1){
    			return 0;
    		}
    		printf("\n");
    		++count;
    		if (b[x] == -1) {
    			--count;
    			break;
    		}
			// if input is less than -1 it quits the program immediently
    		if (b[x] < -1){
    			printf("Goodbye\n");
    			exit(0);
    		}
    	}
   // bubble sort of the user inputed array
	for (i = 0; i < count; ++i)
    {
        for (j = i + 1; j < count; ++j)
        {
            if (b[i] < b[j])
            {
                a = b[i];
                b[i] = b[j];
                b[j] = a;
            }
        }
    }
  	counter = 1;
  	for(i = 0; i < count - 1; ++i){
  	// gets the breach count and breach level of the array that was sorted
  		if (b[i + 1] == b[i]){
  				++counter;
  				if (counter == false_alarm_count){
  					breach = b[i];
  				}
  		}		
 		else if(b[i+1] != b[i]) {
  			if (counter >= false_alarm_count){
  				break;
  			}
  			else if(counter < false_alarm_count){
  				counter = 1;
  			}
  		} 
	}
	breach_count = counter;
   breach_level = breach;
    // You must call exactly one of these prints for a valid sample set.
    // Do not change the text of the printf's
    if (breach_level >= min_threat_level && breach_count >= false_alarm_count) {
    	printf("Threat detected with level %d and appears %d times\n",
           breach_level, breach_count);
    }
    // or
    else{
    	printf("No threat detected\n");
    }
}

    exit(0);
}

