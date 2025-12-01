#pragma once
#include <iostream>
#include <vector>
#include <queue>

struct Student {
    std::string StudentId;
    std::string name;
    std::string city;
    std::string state;
    std::string zip;
    std::string course;
    std::string score;

    bool studentEnrolled(const std::string& studentId , std::vector <Student>& studentData);
    void getStudentDetails(const std::string& filename ,std::vector <Student>& studentData);
    void printStudentData(std::vector <Student>& studentData);
    void findStudentByZip(const std::string& zipToFind,std::vector <Student>& studentData);
    double calculateAverageMarks(std::vector <Student>& studentData);
    void studentEnrolledInCourse(std::string& course , std::vector <Student>& studentData);
    void findStudentById(const std::string& studentId , std::vector <Student>& studentData);
    void addStudent(const std::string& fileName, std::vector <Student>& studentData);
    void studentWithHighestMark(std::vector <Student>& studentData);
    double averageScorePerCourse(std::string& course , std::vector <Student>& studentData);
    void studentWithTheLowestMark(std::vector <Student>& studentData);
    void numberOfStudentsPerCourse(std::string& course , std::vector <Student>& studentData);
    void editStudentDetails(const std::string& filename , std::vector <Student>& studentData);
    void top5Students(std::vector <Student>& studentData);
    void displayReportCard(const std::string& studentId,  std::vector <Student>& studentData);
    void sortStudent(std::vector <Student>& studentData);
};
