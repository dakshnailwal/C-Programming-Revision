#include<stdio.h>
#include<math.h>

void print();
double div(double,double);
double mod(int,int);

 /*
--------------------------------------------------------------------------------
Why returning NAN from an int-returning function causes garbage values
--------------------------------------------------------------------------------

1. What is NAN?
   - NAN stands for "Not a Number".
   - It is a special constant defined in <math.h>, used to represent an undefined 
     or unrepresentable value in floating-point arithmetic (e.g., 0.0/0.0).
   - It is part of the IEEE 754 floating-point standard and only makes sense 
     when dealing with float/double types.

2. Why can't we return NAN from a function that returns int?
   - int and double are stored differently in memory.
   - When you try to return NAN (a double) from a function that returns int, 
     the compiler doesn't perform a valid type conversion.
   - Instead, it blindly copies bits (memory) assuming it's an int � this is 
     undefined behavior in C.

3. What is a Garbage Value?
   - A garbage value is an unpredictable and meaningless value that arises 
     when memory is interpreted incorrectly.
   - For example, interpreting a floating-point bit pattern (like NAN) as an 
     integer gives you a number that makes no logical sense in the context 
     of your program.

4. What actually gets returned?
   - Depending on your system (32-bit or 64-bit), compiler, and optimization
     level, the function may return:
       - 0
       - Some large positive or negative number
       - A crash
       - Or different values each time
   - This happens because the return value is being read from the CPU register 
     or stack as an int, but it contains the bit pattern of a double (NAN).

5. Why does it vary?
   - The exact garbage value depends on:
       - CPU architecture (x86, ARM, etc.)
       - Compiler (GCC, Clang, MSVC, etc.)
       - Optimization flags (-O0, -O2, etc.)
       - How memory and return registers are used internally

6. How to handle it correctly?
   - If you want to return NAN to signal an error, use `double` as your 
     return type:
         double mod(int a, int b) {
             if (b == 0) return NAN;
             return a % b;
         }
   - Alternatively, if using int, use a special value or error flag:
         int mod(int a, int b) {
             if (b == 0) return INT_MIN; // from <limits.h>
             return a % b;
         }

7. Summary:
   - Never return NAN from a function with return type int.
   - It results in undefined behavior, often causing garbage values.
   - Always match your return type to the kind of data you're returning.
*/

int main()
{
	int choice;
	double first,second,result;
	
	while(1)
	{
		print();
		scanf("%d",&choice);
		
		if(choice==7)
		{
			break;
		}
		if(choice<1 || choice>7)
		{
			fprintf(stderr,"Invalid Menu Choice");
			continue;
		}
		
		printf("\nEnter first Number: ");
		scanf("%lf",&first);
		
		printf("Enter second Number: ");
		scanf("%lf",&second);
		
		switch(choice)
		{
			case 1: // Addition
			    result = first+second;
				break;
			case 2: // Subtraction
				result = first-second;
				break;
			case 3: // Multiplication
			 	result = first*second;
				break;
			case 4: // Division
				result = div(first,second);
				break;
			case 5: // Modulous
				result = mod(first,second);
				break;
			case 6: // Power
					result = pow(first,second);
				break;
		}
		
		if(!isnan(result))
		{
			printf("\nThe result of the operation is %.2lf",result);
		}
	}
	return 0;
}

void print()
{
	printf("\n\n----------------------\n");
	printf("Welcome to the Simple Calculator\n\n");
	
	printf("...Choose one of the options below...\n\n");
	
	printf("1) Addition\n");
	printf("2) Subtraction\n");
	printf("3) Multiplication\n");
	printf("4) Division\n");
	printf("5) Modulous\n");
	printf("6) Power\n\n");
}

double div(double a,double b)
{
	if(b==0)
	{
		fprintf(stderr,"\nInvalid Divisor for Division");
		return NAN;
	}
	else
	{
		return a/b;
	}
}

/*
--------------------------------------------------------------------------------
Explanation of `stdout` vs `stderr`
--------------------------------------------------------------------------------

1. **Separate Streams:**
   - `stdout`: Used for normal program output (e.g., `printf`).
   - `stderr`: Used for error messages (e.g., `fprintf(stderr, ...)`).

2. **Buffering:**
   - `stdout` is **buffered** (may delay output).
   - `stderr` is **unbuffered** (prints immediately).

3. **Redirection Behavior:**
   - Redirecting `stdout`: `./program > output.txt`
     - Redirects normal output.
     - Error messages (`stderr`) **still print to terminal**.
   - Redirecting both `stdout` and `stderr`: `./program > output.txt 2> error.txt`
     - `stdout` goes to `output.txt`, `stderr` goes to `error.txt`.

4. **Why `stderr` is Always Visible:**
   - `stderr` is designed for error messages and is **always visible** unless explicitly redirected.
   - It prints immediately, even if `stdout` is buffered or redirected.

--------------------------------------------------------------------------------
*/

double mod(int a,int b)
{
	if(b==0)
	{
		fprintf(stderr,"\nInvalid Divisor for Modulous");
		return NAN;
	}
	
	else
	{
		return a%b;
	}
}
