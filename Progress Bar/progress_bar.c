#include<stdio.h> 
#include<stdlib.h> // system();
#include<unistd.h>	// sleep();
#include<time.h>	// seeding rand();

const int BAR_LENGTH = 50;   // total length of the progress bar
const int MAX_TASKS = 10;    // number of tasks to simulate

typedef struct
{
	int id;         // task number (1 to MAX_TASKS)
	int progress;   // current progress of the task (0�100)
	int step;       // how much progress increases per loop
}Task;

void print_bar(Task task);
void clear_screen();

int main()
{
	srand(time(NULL)); // seed random so steps are different each run
	Task tasks[MAX_TASKS];
	int i;
	
	// INITIALIZATION 
	for(i=0;i<MAX_TASKS;i++)
	{
		tasks[i].id = i+1;      // task IDs from 1 to 10
		tasks[i].progress = 0;  // start with 0% progress
		tasks[i].step = rand()%5; // random increment (0�4) per cycle
	}
	
	int tasks_incomplete = 1; // flag to keep looping until all done
	
	while(tasks_incomplete)
	{
		clear_screen();  // clear terminal before re-printing bars
		tasks_incomplete = 0; // reset, will be set again if any < 100
		
		for( i=0;i<MAX_TASKS;i++)
		{
			tasks[i].progress += tasks[i].step; // update progress
			
			if(tasks[i].progress>100)
			{
				tasks[i].progress = 100; // cap progress at 100
			}
			else if(tasks[i].progress<100)
			{
				tasks_incomplete = 1; // at least one still running
			}
			
			print_bar(tasks[i]); // print progress bar for this task
		}
		
		sleep(1); // Sleep for 1 second to slow down animation
	}
	
	printf("---All Tasks Completed---");
    return 0;
}

void clear_screen()
{
	#ifdef _Win32
		system("cls");  // Windows clear screen command
	#else
		system("cls");  // On Unix it should be "clear", but left as "cls"
	#endif
}

void print_bar(Task task)
{

	int bars_to_show = task.progress*BAR_LENGTH/100;
	
	// bars_to_show = (progress * BAR_LENGTH) / 100
	// First multiplication keeps it in integer domain (avoids float inaccuracies).
	// If you divided first, progress/100 would become 0 for all values <100,
	// and you'd lose precision since it's integer division.
	
	
	int i;
	
	if(task.id<10)
	{
		printf("\nTask 0%d: [ ",task.id); // leading 0 for single digits
	}
	else
	{
		printf("\nTask %d: [ ",task.id);
	}

    // print "=" for completed portion, " " for remaining
    
    for( i=0;i<BAR_LENGTH;i++)
    {
    	if(i<bars_to_show)
    	{
    		printf("=");
		}
		else
		{
			printf(" ");
		}
	}
	
    printf("] %d%%\n", task.progress); // show exact % on the right
}

