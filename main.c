#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "book.h"
#include "commands.h"

// Function Prototypes
void menu();
int empty(char* buf);
void doprocessing(int sock);

int main(int argc, char** argv) {

    // Confirm the correct number of arguments are entered

    if (argc != 2) {
        printf("You have entered an incorrect number of arguments.\n");
        printf("Command format: grades <port number>");
        return 0;
    }

   int sockfd, newsockfd, portno;
   socklen_t  clilen;
   char buffer[256];
   struct sockaddr_in serv_addr;
   struct sockaddr  cli_addr;
   int n, pid;

   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);

   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }

   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 23672;

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }

   /* Now start listening for the clients, here
    * process will go in sleep mode and will wait
    * for the incoming connection
    */
   if(listen(sockfd, 5))
   {
      perror("ERROR on listening");
      exit(1);
   }



   clilen = sizeof(cli_addr);
   while (1) {
      newsockfd = accept(sockfd,  &cli_addr, &clilen);
      if (newsockfd < 0) {
         perror("ERROR on accept");
         exit(1);
      }

      /* Create child process */
      pid = fork();
      if (pid < 0) 
      {
         perror("ERROR on fork");
         exit(1);
      }

      if (pid == 0) 
      {
         /* This is the child  process */
         close(sockfd);
         doprocessing(newsockfd);
         exit(0);
      }
      else 
      {
         /* this is the parent process */
         close(newsockfd);
         listen(sockfd,5);
      }

   } /* end of while */
}

int empty(char buf[])
{
  int flag = 1;
  for(int i = 0; i < strlen(buf); ++i)
    flag = flag && isspace(buf[i]);

  return flag;
}

/* Menu Method
 * This method displays the menu, receives the menu choice, and then branches to the appropriate sub-method for processing.
 * Used numbers instead of original commands to make switch block happy and to avoid multiple if-else statements.
 */
void doprocessing (int sock)
{
    // Variable Declarations
    char response[256];
    char* route;
	
	while(1)
	{
		do
		{
			write(sock, "Gradebook Main Menu:\n\n", 24);
			write(sock, "1. To Add a Student, Enter '1 <StudentName>'", 44);
			write(sock, "2. To Add an Assignment, Enter '2'", 34);
			write(sock, "3. To Add an Exam, Enter '3'", 28);
			write(sock, "4. To Add All Grades for a Student, Enter '4 <StudentName>'", 59);
			write(sock, "5. To Add Grades for an Assignment, Enter '5 <AssignmentNumber>'", 64);
			write(sock, "6. To Add Grades for an Exam, Enter '6 <ExamNumber>'", 52);
			write(sock, "7. To Display all Grades, Enter '7'", 35);
			write(sock, "\n9. To Quit, Enter '9'", 23);
			write(sock, "\n\n", 2);
			write(sock, "Please enter your selection: ", 29);

			n = read(sock, response, 255);

			route = strtok(response, " ");

			switch(route[0])
			{
				case '1':
				{
					if (route[1] == NULL)
					{
						write(sock, "\nERROR!! You did not enter a student's name!", 38);
						write(sock, "Returning to main menu.\n\n", 27);
						write(sock, "\n\n\n", 3);
						break;
					}

					else if (route.length > 2)		// To re-combine student names, if necessary
					{
						for (int i = 2; i < route.length; i++)
							route[1] += " " + route [i];
					}

					write(sock, "\n", 1);
					addStudent(sock, route[1]);
					write(sock, "\n\n\n", 3);

					break;
				}

				case '2':
				{
					write(sock, "\n", 1);
					addAssignment(sock);
					write(sock, "\n\n\n", 3);
					break;
				}

				case '3':
				{
					write(sock, "\n", 1);
					addExam(sock);
					write(sock, "\n\n\n", 3);
					break;
				}

				case '4':
				{
					if (route.length == 1)
					{
						write(sock, "\nERROR!! You did not enter a student's name!", 45);
						write(sock, "Returning to main menu.\n\n", 27);
						break;
					}

					else if (route.length > 2)		// To re-combine student names, if necessary
					{
						for (int i = 2; i < route.length; i++)
							route[1] += " " + route [i];
					}

					write(sock, "\n", 1);
					studentGrade(sock, route[1]);
					write(sock, "\n\n\n", 3);
					break;
				}

				case '5':
				{
					if (route.length == 1)
					{
						write(sock, "\nERROR!! You did not enter an Assignment Number!", 49);
						write(sock, "Returning to main menu.\n\n", 27);
						break;
					}

					write(sock, "\n", 1);
					assignmentGrade(sock, route[1]);
					write(sock, "\n\n\n", 3);
					break;
				}

				case '6':
				{
					if (route.length == 1)
					{
						write(sock, "\nERROR!! You did not enter an Exam Number!", 43);
						write(sock, "Returning to main menu.\n\n", 27);
						break;
					}

					write(sock, "\n", 1);
					examGrade(sock, route[1]);
					write(sock, "\n\n\n", 3);
					break;
				}

				case '7':
				{
					write(sock, "\n", 1);
					displayAllGrades();
					write(sock, "\n\n\n", 3);
					break;
				}

				case '9':
				{

					write(sock, "\nExiting the Gradebook, You Are.", 33);
					write(sock, "May the Force be With You!\n\n", 30);
					return;
				}

				default:
					write(sock, "\nYou have entered an invalid item.\n\nPlease make another selection.", 69);
					write(sock, "\n\n\n", 3);
					doprocessing(sock);
			}

		} while (strcmp(response, "q") != 0);
		
		if (!empty(buffer) && n>0)
		{
			char out[256];
			int printed = snprintf(out,256,"\nHere is the message %d: %s",n,buffer);
			write(1,out,printed);
			n = write(sock,"Tell me more: ",14);
			sync();
		}

		if (n < 0) {
			perror("ERROR writing to socket");
			exit(1);
		}
	}
}



