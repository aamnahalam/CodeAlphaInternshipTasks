#include <iostream>
#include <iomanip> // for setw and formatting
#include <vector>
#include <string>

using namespace std;

// Struct to hold course info
struct Course {
    string name;
    float grade;
    float creditHours;
    float gradePoints;
};

int main() {
    int numCourses;
    cout << "=== Detailed CGPA Calculator ===\n";
    cout << "Enter number of courses taken: ";
    cin >> numCourses;
    cin.ignore(); // To ignore leftover newline

    vector<Course> courses(numCourses);
    float totalCredits = 0;
    float totalGradePoints = 0;

    // Input course details
    for (int i = 0; i < numCourses; i++) {
        cout << "\nCourse " << i + 1 << " name: ";
        getline(cin, courses[i].name);

        cout << "Enter grade (e.g., 4.0, 3.7): ";
        cin >> courses[i].grade;

        cout << "Enter credit hours: ";
        cin >> courses[i].creditHours;
        cin.ignore(); // ignore leftover newline

        courses[i].gradePoints = courses[i].grade * courses[i].creditHours;
        totalCredits += courses[i].creditHours;
        totalGradePoints += courses[i].gradePoints;
    }

    float cgpa = totalGradePoints / totalCredits;

    // Display results
    cout << "\n=== CGPA Summary ===\n";
    cout << left << setw(20) << "Course Name" 
         << setw(10) << "Grade" 
         << setw(10) << "Credits" 
         << setw(15) << "Grade Points" << endl;

    cout << string(55, '-') << endl;

    for (int i = 0; i < numCourses; i++) {
        cout << left << setw(20) << courses[i].name
             << setw(10) << courses[i].grade
             << setw(10) << courses[i].creditHours
             << setw(15) << courses[i].gradePoints << endl;
    }

    cout << string(55, '-') << endl;
    cout << left << setw(20) << "TOTAL"
         << setw(10) << " "
         << setw(10) << totalCredits
         << setw(15) << totalGradePoints << endl;

    cout << "\nFinal CGPA: " << cgpa << endl;

    return 0;
}