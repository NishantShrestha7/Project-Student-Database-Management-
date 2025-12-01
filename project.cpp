#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <conio.h>
#include <chrono>
#include <thread>
#include <algorithm>
#include <limits>
#include "project.h"

using namespace std::literals::chrono_literals;

bool Student::studentEnrolled(const std::string& studentId , std::vector <Student>& studentData){
    for ( auto student : studentData){
        if(student.StudentId == studentId){
            return true;
            break;
        }
    }
    return false;
}

void Student::getStudentDetails(const std::string& filename ,std::vector <Student>& studentData){
    std::fstream studentDetails;
    Student student;
    studentDetails.open(filename,std::ios::in);

    if (!studentDetails.is_open()){
        std::cout << "File not found" << std::endl;
        return;
    }
    std::string line;
    while (getline(studentDetails, line)) {
        std::stringstream ss(line);
        getline(ss, student.StudentId, ',');
        getline(ss, student.name, ',');
        getline(ss, student.city, ',');
        getline(ss, student.state, ',');
        getline(ss, student.zip, ',');
        getline(ss, student.course, ',');
        getline(ss, student.score, ',');

        studentData.push_back(student);
    }
}

void Student::printStudentData(std::vector <Student>& studentData){
    for ( auto s : studentData){
        std::cout << s.StudentId << "-" << s.name << "-" << s.city << "-" << s.state << "-" << s.zip
        << "-" << s.course << "-" << s.score << std::endl;
    }
}

void Student::findStudentByZip(const std::string& zipToFind, std::vector <Student>& studentData){
    int tempIterator = 0;
    for ( auto studentZip : studentData){
        if(studentZip.zip == zipToFind){
            std::cout << studentZip.StudentId << "-" << studentZip.name << "-" << studentZip.city << "-" << studentZip.state << "-" 
            << studentZip.zip << "-" << studentZip.course << "-" << studentZip.score << std::endl;
        }
        else {
            tempIterator++;
        }
    }

    if(tempIterator == studentData.size()){
        std::cout << "Student not found" << std::endl;
    }
}
 
double Student::calculateAverageMarks(std::vector <Student>& studentData){
    int score;
    int tempMarkIterator = 0;
    int tempMark = 0;
    for (int i = 1; i < studentData.size(); i++){  //starts iterating from the second line of the file
        score = stoi(studentData[i].score); //changes the score to integer from string
        tempMark = tempMark + score;
        tempMarkIterator++;
    }
    return (tempMark / tempMarkIterator); //return the average score of all the students;
}

void Student::studentEnrolledInCourse(std::string& course , std::vector <Student>& studentData){
    std::transform(course.begin(),course.end(),course.begin(), ::toupper);
    std::transform(course.begin() + 1,course.end(),course.begin() + 1, ::tolower);
    for ( auto s : studentData){
        if(s.course == course){
            std::cout << s.StudentId << "-" << s.name << "-" << s.city << "-" << s.state << "-" << s.zip
            << "-" << s.course << "-" << s.score << std::endl;
        }
    }
}

void Student::editStudentDetails(const std::string& filename , std::vector <Student>& studentData){
    std::string studentId;
    int indexTracker = 1;
    std::fstream editFile;
    editFile.open(filename,std::ios::out);
    char c = ',';

    if(!editFile.is_open()){
        std::cout << "File not found" << std::endl;
        return;
    }

    // header of the file
    editFile << "StudentId,Name,City,State,Zip,Course,Score," << std::endl;

    std::cout << "Enter student Id: "; std::cin >> studentId;

    for(int i = 1; i < studentData.size(); i++){
        if(studentData[i].StudentId == studentId){
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Name: "; getline(std::cin,studentData[i].name);
            std::cout << "City: "; std::cin >> studentData[i].city;
            std::cout << "State: "; std::cin >> studentData[i].state;
            std::cout << "Zip: "; std::cin >> studentData[i].zip;
            std::cout << "Course: "; std::cin >> studentData[i].course;
            std::cout << "Score: "; std::cin >> studentData[i].score;

            editFile << studentData[i].StudentId << c << studentData[i].name << c << studentData[i].city << c << studentData[i].state
            << c << studentData[i].zip << c << studentData[i].course << c << studentData[i].score << c << std::endl;
        }
        else {
            editFile << studentData[i].StudentId << c << studentData[i].name << c << studentData[i].city << c << studentData[i].state
            << c << studentData[i].zip << c << studentData[i].course << c << studentData[i].score << c << std::endl;
            indexTracker++;
        }
    }

    if(indexTracker == studentData.size()){
        std::cout << "Student not found" << std::endl;
    }

}

void Student::findStudentById(const std::string& studentId , std::vector <Student>& studentData){
    if(studentEnrolled(studentId,studentData)){
        for (auto s : studentData){
            if (studentId == s.StudentId){
                std::cout << "Name: " << s.name << std::endl;
                std::cout << "City: " << s.city << std::endl;
                std::cout << "State: " << s.state << std::endl;
                std::cout << "Zip: " << s.zip << std::endl;
                std::cout << "Course: " << s.course << std::endl;
                std::cout << "Score: " << s.score << std::endl;
            }
        }
    }
    else {
        std::cout << "Student not enrolled in this class" << std::endl;
    }
}

void Student::addStudent(const std::string& fileName, std::vector <Student>& studentData){
    std::fstream file;
    std::stringstream ss;
    Student student;
    std::string newStudentId;
    char c = ',';

    std::string studentId = studentData[studentData.size() - 1].StudentId;
    std::string Id = studentId.substr(1,studentId.length() - 1);
    int intID = stoi(Id) + 1;
    ss << intID;
    ss >> newStudentId;

    file.open(fileName , std::ios::app); //opening file in append mode

    if(!file.is_open()){
        std::cout << "File not found" << std::endl;
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignores the leftover input buffer for getline to work properly;
    std::cout << "Enter student name: "; getline(std::cin , student.name);
    std::cout << "Enter student city: "; std::cin >> student.city;
    std::cout << "Enter student state: "; std::cin >> student.state;
    std::cout << "Enter student zip: "; std::cin >> student.zip;
    std::cout << "Enter student course: "; std::cin >> student.course;
    std::cout << "Enter student score: "; std::cin >> student.score;

    studentData.push_back(student);

    file << "S" + newStudentId << c << student.name << c << student.city << 
    c << student.state << c << student.zip << c << student.course << c << student.score << c << std::endl;
}

void Student::studentWithHighestMark(std::vector <Student>& studentData){
    std::stack <int> tempStack;
    int tempScore;
    int tempIndex;
    tempStack.push(0); //Pushed 0 in the stack for the loop to work correctly.
    for (int i = 1; i < studentData.size(); i++){  //starts iterating from the second line of the file
        tempScore = stoi(studentData[i].score);
        if(tempScore > tempStack.top()){
            tempStack.pop();
            tempStack.push(tempScore);
            tempIndex = i; //shows that the student with highest score is in this index
        }
    }

    if(tempStack.size() == 1){
        std::cout << "------Topper------" << std::endl;
        std::cout << "Student ID:  " << studentData[tempIndex].StudentId << std::endl;
        std::cout << "Name:  " << studentData[tempIndex].name << std::endl;
        std::cout << "City: " << studentData[tempIndex].city << std::endl;
        std::cout << "State: " << studentData[tempIndex].state << std::endl;
        std::cout << "Zip: " << studentData[tempIndex].zip << std::endl;
        std::cout << "Course: " << studentData[tempIndex].course << std::endl;
        std::cout << "Score: " << studentData[tempIndex].score << std::endl;
    }
    else {
        std::cout << "Multiple student have the same score" << std::endl;
    }
}

void Student::studentWithTheLowestMark(std::vector <Student>& studentData){
    std::stack <int> tempStack;
    int tempScore;
    int tempIndex;

    tempStack.push(stoi(studentData[1].score)); //pushed the first score of the list to the stack so that the loop runs properly
   
    for ( int i = 1; i < studentData.size() - 1; i++){
        tempScore = stoi(studentData[i].score);
        if(tempStack.top() > tempScore){
            tempStack.pop();
            tempStack.push(tempScore);
            tempIndex = i;
        }
    }

    if(tempStack.size() == 1){
        std::cout << "------Student With The Lowest Score------" << std::endl;
        std::cout << "Student ID:  " << studentData[tempIndex].StudentId << std::endl;
        std::cout << "Name:  " << studentData[tempIndex].name << std::endl;
        std::cout << "City: " << studentData[tempIndex].city << std::endl;
        std::cout << "State: " << studentData[tempIndex].state << std::endl;
        std::cout << "Zip: " << studentData[tempIndex].zip << std::endl;
        std::cout << "Course: " << studentData[tempIndex].course << std::endl;
        std::cout << "Score: " << studentData[tempIndex].score << std::endl;
    }
    else {
        std::cout << "Multiple student have the same score" << std::endl;
    }

}

double Student::averageScorePerCourse(std::string& course , std::vector <Student>& studentData){
    int tempScore = 0;
    int tempIterator = 0;
    std::transform(course.begin(),course.end(),course.begin(), ::toupper);
    std::transform(course.begin() + 1,course.end(),course.begin() + 1, ::tolower);
    for(auto s : studentData){
        if(s.course == course){
            tempScore = tempScore + stoi(s.score);
            tempIterator++;
        }
    }
    return (tempScore / tempIterator);
}

void Student::numberOfStudentsPerCourse(std::string& course , std::vector <Student>& studentData){
    std::transform(course.begin(),course.end(),course.begin(), ::toupper);
    std::transform(course.begin() + 1,course.end(),course.begin() + 1, ::tolower);
    int courseIterator = 0;
    for (auto s : studentData){
        if(s.course == course){
            courseIterator++;
        }
    }
    std::cout << "Number of students enrolled in " << course << ": " << courseIterator << std::endl;
}

// function to convert integer value to a string value
std::string intToRank(const int& rank){
    switch(rank){
        case 1:
            return "First";
            break;
        case 2:
            return "Second";
            break;
        case 3:
            return "Third";
            break;
        case 4:
            return "Fourth";
            break;
        case 5:
            return "Fifth";
            break;
        default:
            return "Invalid rank";
            break;
    }
}

void Student::top5Students(std::vector <Student>& studentData){
    std::vector <Student> tempVector;
    std::string tempStorageForScore;
    std::string tempStorageForName;

    //used tempVector so that the data inside of a studentData vector won't get updated for other functions
    //made another copy of studentData vector
    for(auto student : studentData){
        tempVector.push_back(student);
    }

    for(int i = 1; i < tempVector.size() - 1; i++){
        for(int j = i + 1; j < tempVector.size(); j++){
            if(stoi(tempVector[j].score) > stoi(tempVector[i].score)){
                tempStorageForScore = tempVector[i].score;
                tempVector[i].score = tempVector[j].score;
                tempVector[j].score = tempStorageForScore;

                //swapping the name of students with the score
                tempStorageForName = tempVector[i].name;
                tempVector[i].name = tempVector[j].name;
                tempVector[j].name = tempStorageForName;
            }
        }
    }

    //displays the name of top 5 students
    for ( int i = 1; i <= 5; i++){
        std::cout << intToRank(i) << ": " << tempVector[i].name << std::endl;
    }
}

char displayGrade(const std::string& score){
    int grade = stoi(score);
    if(grade >= 90){
        return 'A';
    }
    else if (grade >= 80 && grade < 90){
        return 'B';
    }
    else if (grade >= 70 && grade < 80){
        return 'C';
    }
    else if (grade >= 60 && grade < 70){
        return 'D';
    }
    else {
        return 'F';
    }
}

std::string generateComments(const std::string& score){
    int grade = stoi(score);
    if(grade >= 90){
        return "Outstanding performance! Keep up the excellent work";
    }
    else if (grade >= 80 && grade < 90){
        return "Strong performance. A little more effort can bring you to the top";
    }
    else if (grade >= 70 && grade < 80){
        return "Decent effort. Try to practice more to strengthen your skills";
    }
    else if (grade >= 60 && grade < 70){
        return "Below average — needs improvement with consistent study";
    }
    else {
        return "Poor result — must put in more consistent effort";
    }
}  

void Student::displayReportCard(const std::string& studentId,  std::vector <Student>& studentData){
    if(!studentEnrolled(studentId,studentData)){
        std::cout << "Student not found" << std::endl;
        return;
    }
    else {
        std::fstream report;
        std::string reportFileName;
        for ( auto student : studentData){
            if(student.StudentId == studentId){
                std::stringstream ss(student.name); //saves the student name in a string stream
                getline(ss,reportFileName,' '); //gets the first name of the student for the file name
                reportFileName = reportFileName + ".txt";
                report.open(reportFileName,std::ios::out);
                //cout's the students report in a text file
                report << "-----------------" << std::endl;
                report << "   Report Card     " << std::endl;
                report << "Id: " << student.StudentId << std::endl;
                report << "Name: " << student.name << std::endl;
                report << "Course: " << student.course << std::endl;
                report << "Score: " << student.score << std::endl;
                report << "Grade: " << displayGrade(student.score) << std::endl;
                report << "Comment: " << generateComments(student.score) << std::endl;

                std::cout << "Creating a report......." << std::endl;
                std::this_thread::sleep_for(2s);
                
                if(report.is_open()){
                    std::cout << "Report Card Created" << std::endl; 
                }
                else {
                    std::cout << "Error creating report card" << std::endl;
                }
            }
        }
    }
}
   
void Student::sortStudent(std::vector <Student>& studentData){
    int option;
    std::stack <Student> tempStack;
    std::vector <Student> tempVector;
    std::fstream sort;
    char c = ',';

    for ( auto student : studentData){
        tempVector.push_back(student);
    }

    std::cout << "1: " << "Score (High to Low)" << std::endl;
    std::cout << "2: " << "Score (Low to High)" << std::endl;
    std::cout << "Choose one option: "; std::cin >> option;
    switch(option){
        case 1:
            sort.open("Score (High to Low).txt",std::ios::out);
            for(int i = 1; i < tempVector.size() - 1; i++){
                for ( int j = i + 1; j < tempVector.size(); j++){
                    if(stoi(tempVector[j].score) > stoi(tempVector[i].score)){
                        tempStack.push(tempVector[i]);
                        tempVector[i] = tempVector[j];
                        tempVector[j] = tempStack.top();
                        tempStack.pop();
                    }
                }
            }

            std::cout << "Sorting...." << std::endl;
            std::this_thread::sleep_for(2s);
            for ( auto student : tempVector){
                sort << student.StudentId << c << student.name << c << student.city << c << student.state 
                << c << student.zip << c << student.course << c << student.score << c << std::endl;
            }
            std::cout << "Sorting successfull" << std::endl;
            break;
        case 2:
            sort.open("Score (Low to High).txt",std::ios::out);
            for(int i = 1; i < tempVector.size() - 1; i++){
                for ( int j = i + 1; j < tempVector.size(); j++){
                    if(stoi(tempVector[j].score) < stoi(tempVector[i].score)){
                        tempStack.push(tempVector[i]);
                        tempVector[i] = tempVector[j];
                        tempVector[j] = tempStack.top();
                        tempStack.pop();
                    }
                }
            }

            std::cout << "Sorting...." << std::endl;
            std::this_thread::sleep_for(2s);
            for ( auto student : tempVector){
                sort << student.StudentId << c << student.name << c << student.city << c << student.state 
                << c << student.zip << c << student.course << c << student.score << c << std::endl;
            }
            std::cout << "Sorting successfull" << std::endl;
            break;
        default:
            std::cout << "Please choose the right option" << std::endl;
            break;
    }
}

void displayMenuOption(const std::string& filename,std::vector <Student>& studentData){
    Student student;
    int menuOption;
    std::string studentId;
    std::string course;
    std::string zip;
    
    while(true){
        student.getStudentDetails(filename,studentData);
        std::cout << "1: Display All Studens" << std::endl;
        std::cout << "2: Search Student By Id" << std::endl;
        std::cout << "3: Get Average Score" << std::endl;
        std::cout << "4: Get Average Score Per Course" << std::endl;
        std::cout << "5: Display Student With The Highest Mark" << std::endl;
        std::cout << "6: Display Student With The Lowest Mark" << std::endl;
        std::cout << "7: Find Student Details By Zip Code" << std::endl;
        std::cout << "8: Edit Student Details" << std::endl;
        std::cout << "9: Add Student Details" << std::endl;
        std::cout << "10: Display Top 5 Students" << std::endl;
        std::cout << "11: Get Report Card" << std::endl;
        std::cout << "12: Sort Student List" << std::endl;

        std::cout << "Choose one of the option: "; std::cin >> menuOption;

        switch(menuOption){
            case 1:
                system("cls");
                student.printStudentData(studentData);
                break;
            case 2:
                system("cls");
                std::cout << "Enter student ID: "; std::cin >> studentId;
                student.findStudentById(studentId,studentData);
                break;
            case 3:
                system("cls");
                std::cout << "Average: " << student.calculateAverageMarks(studentData) << std::endl;
                break;
            case 4:
                system("cls");
                std::cout << "Enter course: "; std::cin >> course;
                std::cout << "Average Score in " << course << ": " << student.averageScorePerCourse(course,studentData) << std::endl;
                break;
            case 5:
                system("cls");
                student.studentWithHighestMark(studentData);
                break;
            case 6:
                system("cls");
                student.studentWithTheLowestMark(studentData);
                break;
            case 7:
                system("cls");
                std::cout << "Enter zip code: "; std::cin >> zip;
                student.findStudentByZip(zip,studentData);
                break;
            case 8:
                system("cls");
                student.editStudentDetails(filename,studentData);
                break;
            case 9:
                system("cls");
                student.addStudent(filename,studentData);
                break;
            case 10:
                system("cls");
                student.top5Students(studentData);
                break;
            case 11:
                system("cls");
                std::cout << "Enter student Id: "; std::cin >> studentId;
                student.displayReportCard(studentId,studentData);
                break;
            case 12:
                system("cls");
                student.sortStudent(studentData);
                break;
            default:
                std::cout << "Invalid Option" << std::endl;
                break;
        }

        std::cout << "\nPress any key to continue or ESC to exit..."; int ch = _getch();
        if (ch == 27) {
            std::cout << "\nExiting.....";
            std::this_thread::sleep_for(3s);
            system("cls");
            break;
        }
        else {
            studentData.clear();
            system("cls");
        }
    }
}  

int main () {
    Student student;
    std::vector <Student> studentData;
    std::string filename = "Student.txt";

    displayMenuOption(filename,studentData);
    return 0;
}