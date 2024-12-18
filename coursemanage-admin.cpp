#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Class to manage Course data
class Course {
private:
    string courseName;
    string courseCode;
    string teacherAssigned;
    bool published;

public:
    // Constructor
    Course(string name, string code, string teacher, bool isPublished)
        : courseName(name), courseCode(code), teacherAssigned(teacher), published(isPublished) {}

    // Display course details
    void displayCourse(int index) const {
        cout << left << setw(5) << index + 1
            << setw(20) << courseName
            << setw(15) << courseCode
            << setw(20) << teacherAssigned
            << (published ? "Yes" : "No") << endl;
    }

    // Edit course details
    void editCourse(string name, string code, string teacher, bool isPublished) {
        courseName = name;
        courseCode = code;
        teacherAssigned = teacher;
        published = isPublished;
    }

    // Get course name (for delete verification)
    string getCourseName() const {
        return courseName;
    }

    // Mark as published
    void publishCourse() {
        published = true;
    }
};

// Course Management System Class
class CourseManagement {
private:
    vector<Course> courses; // List of courses

    // Utility: Display all courses
    void displayAllCourses() const {
        if (courses.empty()) {
            cout << "\nNo courses available.\n";
            return;
        }

        cout << "\n--- Course List ---\n";
        cout << left << setw(5) << "No."
            << setw(20) << "Course Name"
            << setw(15) << "Course Code"
            << setw(20) << "Assigned Teacher"
            << "Published\n";
        cout << string(65, '-') << endl;

        for (size_t i = 0; i < courses.size(); ++i) {
            courses[i].displayCourse(i);
        }
    }

public:
    // Functionality 1: Add New Course
    void addNewCourse() {
        string name, code, teacher;
        char isPublished;

        cout << "\nEnter Course Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Course Code: ";
        getline(cin, code);

        cout << "Enter Assigned Teacher: ";
        getline(cin, teacher);

        cout << "Is the course published? (y/n): ";
        cin >> isPublished;

        courses.emplace_back(name, code, teacher, (isPublished == 'y' || isPublished == 'Y'));
        cout << "Course added successfully!\n";
    }

    // Functionality 2: Edit Course
    void editCourse() {
        displayAllCourses();
        if (courses.empty()) return;

        int choice;
        cout << "Enter the course number to edit: ";
        cin >> choice;

        if (choice < 1 || choice > courses.size()) {
            cout << "Invalid choice!\n";
            return;
        }

        string name, code, teacher;
        char isPublished;

        cout << "\nEnter New Course Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter New Course Code: ";
        getline(cin, code);

        cout << "Enter New Assigned Teacher: ";
        getline(cin, teacher);

        cout << "Is the course published? (y/n): ";
        cin >> isPublished;

        courses[choice - 1].editCourse(name, code, teacher, (isPublished == 'y' || isPublished == 'Y'));
        cout << "Course updated successfully!\n";
    }

    // Functionality 3: Delete Course
    void deleteCourse() {
        displayAllCourses();
        if (courses.empty()) return;

        int choice;
        cout << "Enter the course number to delete: ";
        cin >> choice;

        if (choice < 1 || choice > courses.size()) {
            cout << "Invalid choice!\n";
            return;
        }

        cout << "Course \"" << courses[choice - 1].getCourseName() << "\" has been deleted.\n";
        courses.erase(courses.begin() + choice - 1);
    }

    // Functionality 4: Display Published Courses
    void displayPublishedCourses() const {
        bool found = false;

        cout << "\n--- Published Courses ---\n";
        cout << left << setw(5) << "No."
            << setw(20) << "Course Name"
            << setw(15) << "Course Code"
            << setw(20) << "Assigned Teacher" << endl;
        cout << string(60, '-') << endl;

        for (size_t i = 0; i < courses.size(); ++i) {
            if (courses[i].getCourseName() != "") {
                courses[i].displayCourse(i);
                found = true;
            }
        }

        if (!found) cout << "No published courses found.\n";
    }

    // Functionality 5: Attendance Controller (placeholder)
    void attendanceController() {
        cout << "\nAttendance Controller is under development.\n";
    }

    // Functionality 6: Assigned Teachers
    void displayAssignedTeachers() const {
        if (courses.empty()) {
            cout << "\nNo teachers assigned to any course yet.\n";
            return;
        }

        cout << "\n--- Assigned Teachers ---\n";
        for (const auto& course : courses) {
            cout << course.getCourseName() << endl;
        }
    }

    // Main Course Management Menu
    void courseManagementMenu() {
        int choice;
        do {
            cout << "\n=== COURSE MANAGEMENT ===\n";
            cout << "1. Add New Course\n";
            cout << "2. Edit Course\n";
            cout << "3. Delete Course\n";
            cout << "4. Published Courses\n";
            cout << "5. Attendance Controller\n";
            cout << "6. Assigned Teachers\n";
            cout << "7. Back To Admin Panel\n";
            cout << "=========================\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                addNewCourse();
                break;
            case 2:
                editCourse();
                break;
            case 3:
                deleteCourse();
                break;
            case 4:
                displayPublishedCourses();
                break;
            case 5:
                attendanceController();
                break;
            case 6:
                displayAssignedTeachers();
                break;
            case 7:
                cout << "Returning to Admin Panel...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 7);
    }
};

// Main function
int main() {
    CourseManagement cm;
    cm.courseManagementMenu();
    cout << "Exiting Program...\n";
    return 0;
}
