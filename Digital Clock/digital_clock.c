#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>

void fill_time(char*,int);
void fill_date(char*);
int input_format();
void clear_screen();

int main()
{
	char time[50],date[100];	
	
	int format = input_format();
	
	while(1)
	{
	
		
	fill_time(time,format);
	fill_date(date);
	clear_screen();
	
	printf("\nCurrent Time: %s\n",time);
	printf("Date: %s\n\n",date);
	
	sleep(1); // sleep for 1 sec
	}

	return 0;
}

void clear_screen()
{
	#ifdef _WIN32
		system("cls");
	#else
    	system("clear");
    #endif
}

void fill_date(char*buffer)
{
		time_t rawtime;
	struct tm *current_time;
	
	time(&rawtime);
	current_time = localtime(&rawtime);
	
	strftime(buffer, 100,"%A %B %d %Y",current_time);
}

void fill_time(char *buffer,int format)
{
	time_t rawtime;
	struct tm *current_time;
	
	time(&rawtime);
	current_time = localtime(&rawtime);
	
	if(format==1)
	{
	strftime(buffer, 50,"%H:%M:%S",current_time);
	}
	else
	{
	strftime(buffer, 50,"%I:%M:%S %p",current_time);
	}
	
}

int input_format()
{
		int format;
	
	printf("Choose the time format: ");
	printf("\n1. 24 Hour Format");
	printf("\n2. 12 Hour Format\n\n");
	printf("Make a choice(1/2)): \n");
	
	scanf("%d",&format);
	
	return format;
}

