#include "givenA1.h"

/* Task 1:
This is the first function. The main purpose of this function is to check if
the file exists. The parameter consists of a file name that the user chooses.
Then, this function tries to open the file in the read mode. If the file
does exist, it returns the file. Else, it returns NULL.
*/

FILE *openFileForReading(char fileName [MAX_STR]){

  FILE * fptr = fopen(fileName, "r");

  if (fptr != NULL){
    return fptr;
  }

  printf("File not found! \n");
  return NULL;

}


/* Task 2: 
This is function 2. The main purpose of this function is to read the information
that is in the file, for example courses.txt. The parameters of this function are
the file name it self, and the courseStruct struct. First the file is checked
by calling the openFileForReading function if the file does not exist,-1 is returned to the calling function. 
Then all the information is stored into a tempArray. Next, the file is opened 
again. This time it runs through a series of for loops to populate the struct information.
*/

int readCourse (char filename [MAX_STR], struct courseStruct courseInfo [NUMBER_COURSES]){

 //The file is opened here just to see the number of lines the text file is.
  FILE * fptc = openFileForReading(filename);
  
  //checks to see the number of lines in the text file
  int count = 0;

  if(fptc == NULL){
    return -1;
  }

  char tempArray[100];

  fgets(tempArray, 100, fptc);

  while(!feof(fptc)){
    fgets(tempArray, 100, fptc);

    count++;
  }

  fclose(fptc);

  //This time the file is opened to actually populate
  FILE * fptr = openFileForReading(filename);

    //Using fgets, the courseNames are populated.
    //I also added a null character at the end of each course name that fgets adds.
  for(int i = 0; i < NUMBER_COURSES; i++){
    fgets(courseInfo[i].courseName, MAX_STR, fptr);
    courseInfo[i].courseName[strlen(courseInfo[i].courseName) - 1] = '\0';

  }
    //Using fscanf I am populating the courseID into the struct
  for(int j = 0; j < NUMBER_COURSES; j++){
    fscanf(fptr,"%d", &courseInfo[j].courseID);
  }

    //Checks to see if the number of lines are more than twice the 
    //number of courses or less. If it is, it returns -1.
  if(count < 2 * NUMBER_COURSES || count > 2 * NUMBER_COURSES){
    return -1;
  }

//Once all conditions are met, it returns 1 back to the calling program.
  return 1;

}



/*Task 3:
This is the third function.
The main purpose of this function is to read information from the second
file.The parameters consist of the filename, profInfo struct and the courseInfo
struct. First it checks to see if the file exists and if there is information
on it. If there is not, then it returns -1 to the calling program.
If there is, then it runs through a series of nested for loops
to populate the struct information.
*/

int readProfAndCoursesTaught (char filename [MAX_STR],struct profStruct profInfo [NUMBER_PROFS],struct courseStruct courseInfo [NUMBER_COURSES]){

  //Checking to see if the file exists.
  FILE * fptr = openFileForReading(filename);
  //Temp array created
  char tempArray[MAX_STR];

  if(fptr == NULL){
    return -1;
  } // end of if statement

  //First it runs through this for loop 6 times to get the professor names.
  for(int i = 0; i < NUMBER_PROFS; i++){
    fgets(profInfo[i].profName, MAX_STR, fptr);
    profInfo[i].profName[strlen(profInfo[i].profName) - 1] = '\0';
  } // end of i for loop

  //I have created a nested for loop so that it runs through the outer loop
  //as many times as the constant of NUMBER_PROFS is initialized to.
  //The inner for loop runs as many times as the NUMBER_COURSES is initialized to.
  //This is so that for every professor it checks to see whether if that professor
  //teaches that specific course.
  for(int k = 0; k < NUMBER_PROFS; k++){
    fscanf(fptr, "%s", tempArray);

    for(int j = 0; j < NUMBER_COURSES; j++){
      //This statement checks to see if the value of the index at the temp array
     // is y or Y. If it is,then the courseID of that specific index
     //is assigned to profInfo[k].coursesTaught.
     //This means that the course is taught by the specific course.
      if(tempArray[j] == 'y' || tempArray[j] == 'Y'){
        profInfo[k].coursesTaught[j] = courseInfo[j].courseID;
      }

      //If the char is 'N' or 'n', then the value of -1 is assigned to that 
      //specific index value.
      else{
        profInfo[k].coursesTaught[j] = -1;
      }

    } 

  strcpy(tempArray, "");

  }
//Since, it runs through everything sucessfully, it returns 1 back to the calling
//program.
return 1;
}


/*Task 4:
This is function 4. The main purpose of this function is to populate an array called
profsNCourses with professor names  who teach n or more courses. The n value is based on user input.
The parameters of this function are a int n, the profInfo struct and the empty 
profsNcourses array.
This function runs through a nested for loop that checks to see the value 
of profInfo.coursesTaught at a specific value.
If it is not -1, it increments the count variable.It does this for each professor
at every single course.
Next, it runs through another for loop to check if the temp array index value 
is greater than or equal to n. If it is, the name of the professor is stored into
the profsNcourses array while incrementing the count value.
Once that is done, the count value is returned to the calling program.
*/

int nCourses (int n, struct profStruct profInfo [NUMBER_PROFS], char profsNCourses [NUMBER_PROFS][MAX_STR]){

  int count = 0;
  int numberOfCoursesArray[NUMBER_PROFS];

  for(int k = 0; k < NUMBER_PROFS; k++){
    for(int m =0; m < NUMBER_COURSES; m++){
      if(profInfo[k].coursesTaught[m] != -1){
        count++;
      }
    }
   //The count value is stored into this temp array I created.
    numberOfCoursesArray[k] = count;
   //Once inner for loop is done running, count is reinitialized to 0. 
    count = 0;
  }

  
  for(int i = 0; i < NUMBER_PROFS; i++){
    if(numberOfCoursesArray[i] >= n){
    strcpy(profsNCourses[i], profInfo[i].profName);
    count++;
    }
    else{
      strcpy(profsNCourses[i], " ");

    }
  }
//number of profs who teach n or more courses is returned back to the calling program.
return count;
}

/* Task 5:
This is the 5th function.The parameters of this function is courseNum, inputted
by the user. A empty char array where the course name will be stored and the
courseInfo struct.
The main purpose of this function is to check if the
course ID  inputted by the user exists.If it does, it returns 1 if the course is
found, else it returns 0. If the course is found, the course name is stored into
a char array  called cNameFound.
*/
 
int getCourseName (int courseNum, char cNameFound [50], struct courseStruct courseInfo [NUMBER_COURSES]){

//For loop to run through all the courses.
  for(int i = 0; i < NUMBER_COURSES; i++){
 //If course number equals to courseId at that index of the struct
 //it copies the name into the char array called cNameFound.
    if(courseNum == courseInfo[i].courseID){
      strcpy(cNameFound, courseInfo[i].courseName);
      return 1;
    }
  }
return 0;
}

/* Task 6
This is the 6th function. The parameters of this function consist of the course name
inputted by the user. The pointer variable cNumFound and the courseInfo struct.
The main purpose of this function is to check if the 
course name inputted by the user exists.If it does, it returns 1 to the calling
program. Else, it returns 0. If the course name is found, the courseID is 
stored into the pointer variable cNumFound.
*/

int getCourseNum (char cName [50], int * cNumFound, struct courseStruct courseInfo [NUMBER_COURSES]){

  for(int i = 0; i < NUMBER_COURSES; i++){
    if(strcmp(cName, courseInfo[i].courseName) == 0){
      * cNumFound = courseInfo[i].courseID;
      return 1;
    }

  }

return 0;

}

/* Task 7 
This is the 7th function. The parameters consist of courseNum which is inputted
by the user, the profInfo struct and the two dimesional array taught by.
The main purpose of this function is to ask the user for the course ID and 
searches for the professors that teach it and populate the array taughtby.
Furthermore, it returns the number of professors who teach that course. 
If the course is not found or if there are no professors teaching it then,
0 is returned to the calling program.
*/

int profsTeachingCourse (int courseNum, struct profStruct profInfo [NUMBER_PROFS], char taughtBy [NUMBER_PROFS][MAX_STR]){

//This count variable counts the number of professors teaching that course.
int count = 0;

  //This nested for loop checks to see if the courseNum matches the coursesTaught
 // values. If it does, the professor name is stored into the taughtby array and count is incremented.
  for(int i = 0; i < NUMBER_PROFS; i++){
    for(int j = 0; j < NUMBER_COURSES; j++){
      if(courseNum == profInfo[i].coursesTaught[j]){
        strcpy(taughtBy[i], profInfo[i].profName);
        count++;
      }
    }
  }

  //This if statement checks to see if the count value is greater than 1.
  //If it is, the count value is returned or 0 is returned.
  if(count > 0){
    return count;
  }
  return 0;
}


/*Task 8
This is the 8th function. The parameters of this function consist of the profInfo struct.
The main puprose of this function is to find the average number of courses taught by a professor. 
It returns the average number back to the calling program that is rounded to the next whole float value.
*/

float avgNumCourses (struct profStruct profInfo [NUMBER_PROFS]){

  //These variables will help with returning the whole value.
  int sum = 0;
  float avg = 0;
  int check = 0;

  //This nested for loop checks to see if a specific coruse is taught by
  //a specific professor. If the value at that index is not -1,
  //then the sum value is incrememted by one.
  for(int i = 0; i < NUMBER_PROFS; i++){
    for(int j = 0; j < NUMBER_COURSES; j++){
      if(profInfo[i].coursesTaught[j] != -1){
        sum++;
      }

    }
  }

  //The average value is calculated by first typecasting the sum value to a float
  //and divided by the number of professors.
  //To round, I have added 1 to the average value to always round up.
  //Before returning, the check value is typecasted to float again.
  avg = (float)sum / NUMBER_PROFS;
  check = avg + 1;
  return (float)check;
}

