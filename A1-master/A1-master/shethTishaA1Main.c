#include "givenA1.h"

/**
This main helps run the functions in the shethTishaA1.c file. Since we are 
using multiple files, we make char *argv[] empty instead of 1. 
Furthermore, I have initialized all the variables I have used for the whole
main in the start as per the guidelines. Moreover, I have included the header
file which consists of all the prototypes and all the #includes. 
*/

int main(int argc, char * argv[]){
  int func2;
  int func3;
  int func4;
  int number;
  int checkID;
  int func5;
  int func6;
  int checkCourse;
  int func7;
  float func8;
  struct courseStruct courseInfo[NUMBER_COURSES];
  struct profStruct profInfo[NUMBER_COURSES];
  char  profsNCourses[NUMBER_PROFS][MAX_STR];
  char cNameFound[50];
  char cName[MAX_STR];
  int cNumFound=0;
  char taughtBy[NUMBER_PROFS][MAX_STR];
  int userChoice;

/**
The first couple of lines call function 2.One of the arguments being passed
is the file at the index 1. In this case, it would be the courses.txt
file. It is not the file at the index 0 because that index holds a.out.
The second parameter is the courseInfo struct. 
If the value returned is -1, then "Error!" is printed onto the screen. 
To catch the value that is being returned I have named the variable func2 
for easier reading purposes. 
*/

  func2 = readCourse(argv[1], courseInfo);

  if(func2 == -1){
    printf("Error! \n");
  }



/**
These following statements call function 3. One of the parameters is the file
that is at index 2 when running the program. In this case it would be the
data.txt file. Furthermore, the other two parameters are both structs, one
is a profInfo struct and the other is courseInfo struct. 
The if statement is executed if the value returned is -1. 
This means that the file does not exist, thus it will print Error! 
on to the screen. 
*/


  func3 = readProfAndCoursesTaught(argv[2], profInfo, courseInfo);

  if(func3 == -1) {
    printf("Error! \n");
  }

/**
These follwing print statements allow the user to know what will execute
when they input a specific number. Each number corresponds to a specific 
function. It is just the display menu. 
*/

do {

  printf("\nHere are the different options: \n");
  printf("4. Function 4- Returns the number of professors who teach n or more courses. \n");
  printf("5. Function 5- Asks the user to input a course number to see if it exists. \n");
  printf("6. Function 6- Asks the user to input a course name to see if it exists. \n");
  printf("7. Function 7- Asks the user to input a course ID to see the number of professors who teach that course. \n");
  printf("8. Function 8- Returns the average number of courses taught by a professor. \n");
  printf("\n");
  printf("\n");
  printf("Please enter your option: ");
  scanf("%d", &userChoice);

/**
These series of if-else statements are executed when the userChoice matches
one of the options. The first one executes if the user enters 4 and so forth.
If the user input does not match any of the options then, the program ends 
and prints Sorry invalid choice!
*/
  if(userChoice == 4){
    /**
    First the user is asked to input a number.
    Then, function 4 is called with the arguments being the user input,
    the profInfo struct and a empty char array profsNCourses.
    Finally, a print statement with the value returned is shown onto the screen.
    In this case, it will print the number of professors who teach n or more 
    courses, n being the user input.
   **/
    printf("Please enter a number: ");
    scanf("%d", &number);
    func4 = nCourses(number, profInfo, profsNCourses);
    printf("The total number of professors who teach %d courses is: %d\n", number, func4); 
  }

  /**
  This else if statement is executed if the user choice is 5.
  First the user is asked to enter a course ID.
  Then, function 5 is called with the arguments being the user input, cNameFound
  and the courseInfo struct.
  If the value that is being returned to the function is 1, 
  that means that the course ID exists. Thus, the corresponding message 
  is shown to the screen. Else, the message that the course does not exists is printed onto the screen. 
  */

  else if(userChoice == 5){

    printf("Please enter a course ID: ");
    scanf("%d", &checkID);
    func5 = getCourseName(checkID, cNameFound, courseInfo);  //write statement when return value is 1 and when its 0

    if(func5 == 1){
      printf("The course ID exists! \n");
    }
 
    else{
      printf("The course ID does not match any of the ones in the file! \n");
    }
  }

  /**

  This else if statment runs if the userChoice is equal to 6.
  This means that function 6 will execute. First, the user is asked
  to enter a course name. 
  getchar is used to grab the newline chracter so it does not mess with the actual input.
  Then I called fgets since some courses consist of spaces. Furthermore, 
  the last index consists of the newline chracter, therefore, I am 
  making the last index value null. 
  Then, I am calling the 6th function with cName, a pointer variable 
  cNUmFound and the courseInfo struct as the arguments.
  If the value being returned is 1, then a specific message is printed 
  on to the screen showcasing that the course name exists. If 0 is returned,
  then the message stating that the course does not exist is printed onto the screen.
  */


  else if(userChoice == 6){
    printf("Please enter a course name: ");
    getchar();
    fgets(cName, MAX_STR, stdin);
    cName[strlen(cName) -1] = '\0';
    func6 = getCourseNum(cName, &cNumFound, courseInfo);

    if(func6 == 1){
      printf("The course name you have inputted exists! \n");
    }

    else{
      printf("The course name you have inputted does not exist! \n");
    }

  }

  /**
  This else if statement is executed if the user choice is 7.
  First I ask the user to enter a course ID. 
  Then, function 7 is called with checkCourse, profInfo struct and taughtby
  being the arguments being passed into the function. 
  If the value being returned is greater than 0 then a message
  with the number of professors teaching that course is printed onto the screen.
  If the value is not greater than 0, then a mesage lettin the user know that this course either
  does not exist or has no one teaching it.
  */

  else if(userChoice == 7){

    printf("Please enter a course ID: ");
    scanf("%d", &checkCourse);
    func7 = profsTeachingCourse(checkCourse, profInfo, taughtBy);

    if(func7 > 0){
      printf("The number of professors who teach this course is: %d \n", func7);
    }

    else{
      printf("This course does not exist or no professor is teaching the course! \n");
    }
  }

  /**
  This else if statement is executed if the user choice is 8.
  All this block of code does is call function 8 with the argument being the profInfo struct
  and prints the average number of professors who are teaching a course 
  that is rounded to one decimal place. 
  */

  else if(userChoice == 8){

    func8 = avgNumCourses(profInfo);
    printf("The average number is: %.1f \n", func8);

  }

  /**
  If the userChoice does not match any of the values, then this else block 
  of code executes where it ends the program while also letting the user
  know they inputted a invalid number.
  */

  else{
    printf("Sorry, invalid choice!\n");
  }


} while(userChoice == 4 || userChoice == 5 || userChoice == 6 || userChoice == 7 || userChoice == 8);

  return 0;
}
