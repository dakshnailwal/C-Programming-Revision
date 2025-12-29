#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define MAX_USERS 10          // max users allowed
#define CREDENTIAL_LENGTH 30  // max username/password length

typedef struct 
{
  char username[CREDENTIAL_LENGTH];
  char password[CREDENTIAL_LENGTH];
} User;

User users[MAX_USERS]; 
int user_count = 0;

void register_user();
int login_user(); 

void fix_fgets_input(char*);
void input_credentials(char* username, char* password);

int main() 
{
  int option, user_index;

  while (1) 
  {
    printf ("\nWelcome to User Management");
    printf ("\n1. Register");
    printf ("\n2. Login");
    printf ("\n3. Exit");
    printf ("\nSelect an option: ");

    scanf("%d", &option);
    getchar(); // clear newline after scanf

    switch (option) 
	{
      case 1: register_user(); break;
      
      case 2:
        user_index = login_user();
        
        if (user_index >= 0)
          printf("\nLogin successful! Welcome, %s!\n", users[user_index].username);
        else
          printf("\nLogin failed! Incorrect username or password.\n");
        break;
        
      case 3: printf("\nExiting Program.\n"); return 0;
      
      default: printf("\nInvalid option. Try again.\n"); break;
    }
  }
}

void register_user() 
{
  if (user_count == MAX_USERS) 
  { // block if full
    printf("\nMax %d users supported!\n", MAX_USERS);
    return;
  }
  
  printf("\nRegister a new user");
  input_credentials(users[user_count].username, users[user_count].password);
  user_count++;
  printf("\nRegistration successful!\n");
}

int login_user() 
{
  char username[CREDENTIAL_LENGTH], password[CREDENTIAL_LENGTH];
  input_credentials(username, password);

  for (int i = 0; i < user_count; i++) 
  {
    if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
      return i; // found match
  }
  return -1; // not found
}

void input_credentials(char* username, char* password) 
{
  printf("\nEnter username: ");
  fgets(username, CREDENTIAL_LENGTH, stdin);
  
  fix_fgets_input(username); // strip newline

  printf("Enter password (masked): ");
  fflush(stdout);

  struct termios old_props, new_props;
  tcgetattr(STDIN_FILENO, &old_props);
  new_props = old_props;
  
  new_props.c_lflag &= ~(ECHO | ICANON); // disable echo + line buffering
  tcsetattr(STDIN_FILENO, TCSANOW, &new_props);

  char ch; int i = 0;
  
  while ((ch = getchar()) != '\n' && ch != EOF) 
  {
    if ((ch == '\b' || ch == 127) && i > 0) // backspace
	{ 
      i--; printf("\b \b");
    } 
	
	else if (i < CREDENTIAL_LENGTH - 1) // store char safely
	{ 
      password[i++] = ch; printf("*");
    }
  }
  
  password[i] = '\0';
  tcsetattr(STDIN_FILENO, TCSANOW, &old_props); // restore terminal
}

void fix_fgets_input(char* string) 
{
  string[strcspn(string, "\n")] = '\0'; // cut at newline
}

