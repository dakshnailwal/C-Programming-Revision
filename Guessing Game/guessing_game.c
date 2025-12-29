#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
    int random, guess;
    int n=0;

    srand(time(NULL)); // Random number is generated based on the current system time ( in seconds ) ( The number generated is not truly random )

                       // srand(seed) sets the starting point for the sequence.

    printf("...Welcome to the Guessing Game...\n\n");

    random = rand()%100 + 1; // rand() gives you the next number in the sequence.

    do
    {
        printf("Guess the Number: ");
        scanf("%d",&guess);

        n++;

        if(guess>random)
        {
            printf("Think of a smaller number...");
        }
        else if(guess<random)
        {
            printf("Think of a greater number...");
        }
        else
        {
                printf("Congratulations... You have Guessed the correct number in %d attempts",n);
        }
        
    }while(guess!=random);

    return 0;
}
