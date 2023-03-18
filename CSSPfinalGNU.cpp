#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//classes to model individual frameworks
class Course{
private:
    string name;
    int cutOff;

public:
    void setName(string name){
        this->name = name;
    }
    void setCutOff(int cutOff){
        this->cutOff = cutOff;
    }
    int getCutOff(){
        return  this->cutOff;
    }
    string getName(){
        return this->name;
    }
};

class School{
private:
    string name;
    Course course[7];
    Course selectCourse;
    //int counter = 0;

public:
    School(){
        this->name = name;
        for(int i = 0; i<7; i++){
            this->course[i].setCutOff(0);
        }
    }
    void setName(string name){
        this->name = name;
    }
    void setCourse(Course courseChoice[7]){
       for(int i = 0; i<7; i++ ) {
           this->course[i] = courseChoice[i];
       }
    }
    void setSelectCourse(Course course){
        this->selectCourse = course;
    }
    Course getSelectCourse(){
        return this->selectCourse;
    }
    Course* getCourse(){
        Course* courses = new Course[7];
        for(int i = 0; i<7; i++){
            courses[i] = this->course[i];
        }

        return courses;
    }
    string getName(){
        return this->name;
    }

};

class Student{
private:
      int indexNo;
      string name;
      int results[9];
      School choices[5];
public:
    Student(){
        this->indexNo = 0;
    }
    Student(int indexNo, string name, int results[9], School choices[5]){
        this->indexNo = indexNo;
        this->name = name;
        for(int i = 0; i <9; i++){
            this->results[i] = results[i];
        }
        for(int i= 0; i<5; i++){
            this->choices[i] = choices[i];
        }
    }
    void setName(string name){
        this->name = name;
    }
    void setIndexNo(int indexNo){
        this->indexNo = indexNo;
    }
    void setResults(int result[9]){
        for(int i = 0; i <9; i++){
            this->results[i] = result[i];
        }
    }
    void setChoices(School choices[5]){
        for(int i= 0; i<5; i++){
            this->choices[i] = choices[i];
        }
    }
    string getName(){
        return this->name;
    }
    int getIndexNo(){
        return this->indexNo;
    }
    int* getResults(){
        int * results = new int[9];
        for(int i = 0; i <9; i++){
            results[i] = this->results[i];
        }
        return results;
    }
    //Find the aggregate of a score requires 4 core courses and two electives
    int getAggregate(){
        int aggregateScore = 0;
        int firstMin;
        int firstMinPosition;
        int secondMin;
        for(int i = 0; i<4; i++){
            aggregateScore += this->results[i];
        }
        //must find the first minimum and the second minimum
        for(int i = 4; i<9; i++){
            firstMin = results[4];
            if(firstMin > results[i]){
                firstMin = results[i];
                firstMinPosition = i;
            }
            if(firstMin == 1){
                break;
            }
        }
        //trying to find the second minimum
        for(int i = 4; i<9; i++){
            secondMin = results[4];
            if(secondMin > results[i] && i != firstMinPosition){
                secondMin = results[i];
            }
        }
        // Adding the minimums to the core summation
        aggregateScore += firstMin;
        aggregateScore += secondMin;

        return aggregateScore;
    }
    School* getChoices(){
        School * choices = new School[5];
        for(int i = 0; i <5; i++){
            choices[i] = this->choices[i];
        }
        return choices;
    }
};

//Arrays to keep data
Course courses[6];
School schools[10];
Student students[10];

//number of students, courses and schools
int schoolsLogged = 0;
int studentsLogged = 0;
int courseRegistered = 0;

struct student
{
    string name=" ";
    int indexNo;
};
struct school
{
    string  name=" ";
    student placed[10];
};

school filledSchools[10];
int studentFilling = 0;


//functions to operate the system
//functions to add courses
void addCourse(string name){
    //add courses that to be offered in the schools
    Course course;
    course.setName(name);
    course.setCutOff(0);
    courses[courseRegistered] = course;
    courseRegistered ++;
}
//functions to add schools
void addSchool(string name, Course courses[7]){
    //add schools that students can choose from
    School school;
    school.setName(name);
    school.setCourse(courses);
    schools[schoolsLogged] = school;
    schoolsLogged += 1;
    cout<<"School(s) added to the system successfully"<<endl;
}
//functions to students
void addStudent(int indexNo, string name, int results[9], School choices[5]){
    //add students; their results and choices
    Student student(indexNo, name, results, choices);
    students[studentsLogged] = student;
    studentsLogged += 1;
    cout<<"Student added to the system successfully"<<endl;
}
void addStudent(Student student){
    //add students; their results and choices
    students[studentsLogged] = student;
    studentsLogged += 1;
}
//take in the bulk students and match them to their appropriate and qualified choices
void schoolPlacement(School schools[10], Student students[10]) {
    //
    string studentsNotPlaced[10] = {};
    int numberOfUnplacedStudents = 0;
    int choice = 0;
    bool checkState = true;
    int studentPosted = 0;
    //make space for the schools logged
    for (int school = 0; school < schoolsLogged; school++){
        if(schools[school].getName().size() != 0 && schools[school].getName() != "0" ){
            struct school school_1;
            school_1.name = schools[school].getName();
            filledSchools[school] = school_1;
        }
    }

    if(studentsLogged < 1){
        cout<<"There are no students to be placed in schools"<<endl;
    }
    else if(schoolsLogged < 1){
        cout<<"There are no schools for students to be placed"<<endl;
    }
    else {
        //comb through all logged students
        for (int student = 0; student < studentsLogged; student++) {
            School *choices = students[student].getChoices();
            //for every student comb through their choices
            while (checkState) {
                //for every choice comb through all the schools to find the school
                for (int school = 0; school < schoolsLogged; school++) {
                    School schoolSelect = schools[school];
                    //compare the name of the select school and the logged schools
                    if (choices[choice].getName() == schoolSelect.getName()) {
                        for (int selectCourse = 0; selectCourse < 7; selectCourse++) {
                            //compare the name of the student's selected course to the list of courses done by the select school
                            if (choices[choice].getSelectCourse().getName() ==
                                schoolSelect.getCourse()[selectCourse].getName()) {
                                //compare know if the aggregate of a student is less than or equal to the cut off point
                                if (students[student].getAggregate() <=
                                    schoolSelect.getCourse()[selectCourse].getCutOff()) {
                                    //place student in school
                                    struct student std_1;
                                    std_1.name = students[student].getName();
                                    std_1.indexNo = students[student].getIndexNo();
                                    for(struct school schoolFields : filledSchools){
                                        if (choices[choice].getName() == schoolFields.name){
                                            filledSchools[studentFilling].placed[studentPosted] = std_1;
                                            studentFilling += 1;
                                            studentPosted += 1;
                                        }
                                    }
                                    studentPosted = 0;
                                    //skip if any going through other choices
                                    checkState = false;
                                    cout<<"This student with name: "<<std_1.name<<" has been successfully placed"<<endl;
                                }
                                    //if  the value of choice exceeds 5 then the while loop must exit
                                else if (choice > 5) {
                                    //student was not placed
                                    studentsNotPlaced[numberOfUnplacedStudents] = students[student].getName();
                                    checkState = false;
                                    numberOfUnplacedStudents += 1;
                                }
                            }
                        }

                    }
                }
                choice += 1;
            }

        }
    }
    if(numberOfUnplacedStudents > 0){
        for(int printSchool = 0; printSchool < numberOfUnplacedStudents; printSchool++) {
            cout <<printSchool + 1<< ". "<<studentsNotPlaced[printSchool]<<endl;
        }
    }else{
        cout<<"There are no unplaced students"<<endl;
    }
}

//variables to temporarily keep details
string schoolName;
string studentName;
string courseName;
int studentIndexNo;
int studentResults[9];
Course schoolCourses[7];
int courseCutOff;
School studentChoices[5];
int courseCount;
int schoolNo;
int studentPopulation;
string subject[9] = {"Integrated Science", "Mathematics", "Social Studies", "English", "RME", "ICT", "Ghanaian language", "French", "BDT"};

//functions to interact with the interface
//function to enter students
void enterSchools(){
    cout << "Please enter the details of the schools for students to be placed in" << endl;
    cout << "How many schools(max 10): " << endl;
    cin >> schoolNo;
    if (schoolNo > 10) {
        cout << "The number of schools cannot exceed 10" << endl;
    } else {
        //adding schools
        for (int schoolCount = 0; schoolCount < schoolNo; schoolCount++) {
            cout << "Enter School name: ";
            cin.ignore();
            getline(cin, schoolName);
            cout << "How many courses are offered in school(max 10): " << endl;
            cin >> courseCount;
            for (int count = 0; count < courseCount; count++) {
                cout << "Enter Course name:";
                cin.ignore();
                getline(cin, courseName);
                cout << "Enter course cut off mark: ";
                cin >> courseCutOff;
                Course course;
                course.setName(courseName);
                course.setCutOff(courseCutOff);
                schoolCourses[count] = course;
            }
            addSchool(schoolName, schoolCourses);
        }
    }
    //system("clear");
}

//Function to enter students
void enterStudents(){
    //variables to be used
    int courseNumber;
    int schoolSelectNumber;
    int schoolNumber = 1;
    int numberOfCourses = 1;

    //add students
    if(schoolsLogged == 0){
        //Students cannot be added to the system if there are no schools in the system
        cout<<"Sorry students cannot be added to system since there are no schools"<<endl;
    }else {
        cout << "Please enter the details of the students to be placed" << endl;
        cout << "How many students(max 10): " << endl;
        cin >> studentPopulation;
        if (studentPopulation > 10) {
            cout << "The number of students must not exceed 10" << endl;
        } else {
            for (int studentFull = 0; studentFull < studentPopulation; studentFull++) {
                cout << " Enter index number:";
                cin >> studentIndexNo;
                cout << "Enter student name : ";
                cin.ignore();
                getline(cin, studentName);

                //Entering results for students
                cout << "Enter the grades for the following courses from 1 - 9" << endl;
                int tempResult;
                for (int gradeCount = 0; gradeCount < 9; gradeCount++) {
                    cout << "Enter grade (" << subject[gradeCount] << "): ";
                    cin >> tempResult;
                    studentResults[gradeCount] = tempResult;
                }
                //making choices for the student
                cout << "What are the schools of choice and their respective choices" << endl;

                for (int schoolChoice = 0; schoolChoice < 5; schoolChoice++) {
                    Course *schoolChoiceChoice;
                    cout << "--Choose the name of the school and choose the course of choice---" << endl;
                    cout << "Choose by entering the according number of the school" << endl;
                    for (School school: schools) {
                        if (school.getName().size() > 0) {
                            cout << schoolNumber << ". " << school.getName() << endl;
                            schoolNumber += 1;
                        }
                    }
                    schoolNumber = 1;
                    cout << "Choose by entering the according number of the school:" << endl;
                    cin >> schoolSelectNumber;
                    schoolName = schools[schoolSelectNumber - 1].getName();
                    cout << "Choose by entering the number of the course " << endl;
                    for (School school: schools) {
                        if (school.getName() == schoolName) {
                            schoolChoiceChoice = school.getCourse();
                        }
                    }
                    for (int coursenumber = 0; coursenumber < 7; coursenumber++) {
                        if (schoolChoiceChoice[coursenumber].getName().size() > 0) {
                            cout << numberOfCourses << ". " << schoolChoiceChoice[coursenumber].getName() << endl;
                            numberOfCourses += 1;
                        }
                    }
                    numberOfCourses = 1;
                    cin >> courseNumber;
                    School selectSchool;
                    selectSchool.setName(schoolName);
                    selectSchool.setSelectCourse(schoolChoiceChoice[courseNumber - 1]);
                    studentChoices[schoolChoice] = selectSchool;
                }
                addStudent(studentIndexNo, studentName, studentResults, studentChoices);
            }
        }
        //system("clear");
    }
}

//function to view schools
void viewSchools(){
    //variables been used
    int schoolNumber = 1;
    //if the schools in the system are
    if(schoolsLogged > 0) {
        for (School school: schools) {
            if (school.getName().size() > 0) {
                cout << schoolNumber << ". " << school.getName() << endl;
                schoolNumber += 1;
            }
        }
    }else{
        cout<<"There are no schools in the systems"<<endl;
    }
}

//function to view students
void viewStudents(){
    //variables been used
    int studentPos = 1;
    //checking if any students have been logged
    if(studentsLogged > 0) {
        for (Student student: students) {
            if (student.getName().size() > 0) {
                cout << studentPos << ". " << student.getName() <<"\t"<< student.getIndexNo()<< endl;
                studentPos++;
            }
        }
    }//prints this if no students are found
    else{
        cout<<"There are no students in the system"<<endl;
    }
}

//function to show student placement
void showSchoolPlacement(){
    //counting displays
    int dispCountSt = 1;
    int dispCountSch = dispCountSt;
    //checking if schools have been filled
    if(studentFilling > 0) {
        cout << "Index Number \tStudent Name  \tSchool \n";
        for (struct school placedSchool: filledSchools) {
            string schName = placedSchool.name;
            if(schName.size() != 0 && schName != "0") {
                for (struct student placedStudent: placedSchool.placed) {
                    if(placedStudent.name.size() != 0 && placedStudent.name != "0") {
                        if(placedStudent.indexNo != 0) {
                            cout << placedStudent.indexNo << " \t" << placedStudent.name << " \t" << schName << endl;
                            dispCountSt += 1;
                        }
                    }
                    if(dispCountSt > studentFilling){
                        break;
                    }
                }
            }
            if(dispCountSch > studentFilling) {
                break;
            }
        }
    }else{
        cout<<"No students have been placed"<<endl;
    }
}

//function to place for a particular student
void showStudentPlacement(int stIndex){
    int currentSchool = 0;
    bool searchState = true;
    while(searchState){
        struct school placedSchool = filledSchools[currentSchool];
        string schName = placedSchool.name;
        for(struct student placedStudents : placedSchool.placed){
            if(placedStudents.indexNo == stIndex){
                cout<<"Student with name "<<placedStudents.name<<"and index no.: "<<stIndex<<" was placed in "
                << schName<<" school"<<endl;
                searchState = false;
                break;
            }
            else{
                cout<<"There is no student with such index number in the system"<<endl;
                searchState = false;
                break;
            }
        }
        currentSchool += 1;
    }
}

//declaration of home page
void firstPage();
//login as a student
void studentLogin(){
    int optionNumber;
    int studentIndexNumber;
    //entering students into the system
    start:
    cout << "Please select an option by entering the corresponding number" << endl;
    cout<<"What do you want to do?" << endl;
    cout<<"1. New here? Enter your details" << endl;
    cout<<"2. Already here? check where you were placed" << endl;
    cout<<"0. Back to home page"<<endl;

    cin>>optionNumber;
    switch(optionNumber){
        case 1:
            enterStudents();
            goto start;
            break;
        case 2:
            cout<<"Please enter your index number:";
            cin>>studentIndexNumber;
            showStudentPlacement(studentIndexNumber);
            goto start;
            break;
        case 0:
            //go back to home page
            firstPage();
            break;
        default:
            cout<<"PLease enter a valid option";
            goto start;
    }
}

//Login as an admin
void admininistratorLogin(){
    int optionNumber;
    //interface for administrative tasks
    start:
    cout << "Please select an option by entering the corresponding number" << endl;
    cout<<"What do you want to do?" << endl;
    cout<<"1. Add Schools to the system" << endl;
    cout<<"2. Show the schools in the system " << endl;
    cout<<"3. Show the students in the system" << endl;
    cout<<"4. PLace students in their qualify schools" << endl;
    cout<<"5. Shows students and where they have been placed"<<endl;
    cout<<"0. Back to home page"<<endl;
    cin>>optionNumber;

    switch(optionNumber){
        case 1:
            //call function to add school to the system
            enterSchools();
            goto start;
            break;
        case 2:
            //call function to view schools in the system
            viewSchools();
            goto start;
            break;
        case 3:
            //call function to view students in the system
            viewStudents();
            goto start;
            break;
        case 4:
            //call function to place students in their respective schools
            schoolPlacement(schools, students);
            goto start;
            break;
        case 5:
            //call function to show school placement
            showSchoolPlacement();
            goto start;
            break;
        case 0:
            //go back to home page
            firstPage();
            break;
        default:
            cout<< "Please enter a valid option"<<endl;
            goto start;
    }
}

void firstPage(){
    int optionNumber;

    cout << "----Welcome to the school placement system----" << endl;
    cout << "Please select an option by entering the corresponding number" << endl;
    cout << "What are you?" << endl;
    cout << "1. Administrator" << endl;
    cout << "2. Student" << endl;
    cin >> optionNumber;

    switch (optionNumber) {
        case 1:
            admininistratorLogin();
            break;
        case 2:
            studentLogin();
            break;
        default:
            cout << "Please enter a valid option" << endl;
            firstPage();
    }
}


int main() {
    //adding courses to be studied
    string courseOfStudy[6] = {"Science", "Business", "Government", "Technical", "Visual Arts", "General Arts"};
    for(string name: courseOfStudy){
        addCourse(name);
    }
   int stIndex;
    //Interface of the program
   firstPage();

    return 0;
}
