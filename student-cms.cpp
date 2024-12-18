#include <iostream>
#include <string>
#include <vector>
#include <iomanip>  // For setting table format
using namespace std;

// Base class for Users
class User {
protected:
    string name;
    string password;
public:
    User(string n, string p) : name(n), password(p) {}
    virtual ~User() {}
    virtual void menu() = 0;  // Pure virtual function
    bool authenticate(string pass) { return password == pass; }
    string getName() { return name; }
};

// Derived class for Students
class Student : public User {
private:
    string enrollmentID;
public:
    Student(string n, string p, string id) : User(n, p), enrollmentID(id) {}

    // Getter function for Enrollment ID
    string getEnrollmentID() { return enrollmentID; }

    void menu() override {
        int choice;
        do {
            cout << "\n\t\t\t\t\t\t Welcome " << name << " \t\t\t\t\t\t\n";
            cout << "1. Profile Information\n";
            cout << "2. Course Registration\n";
            cout << "3. Time Table\n";
            cout << "4. Attendance\n";
            cout << "5. Results\n";
            cout << "6. Fee Challans\n";
            cout << "7. Available Scholarships\n";
            cout << "8. Announcements\n";
            cout << "9. Go to LMS\n";
            cout << "10. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: displayProfile(); break;
            case 2: courseRegistration(); break;
            case 3: viewTimeTable(); break;
            case 4: viewAttendance(); break;
            case 5: viewResults(); break;
            case 6: viewFeeChallans(); break;
            case 7: viewScholarships(); break;
            case 8: viewAnnouncements(); break;
            case 9: accessLMS(); break;
            case 10: cout << "Logging out...\n"; return;
            default: cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 10);
    }

    void displayProfile() {
        cout << "\n\t\t\t\t\t--- Profile Information ---\t\t\t\t\t\n";
        cout << "Name: " << name << "\nEnrollment ID: " << enrollmentID << "\nProgram: BS Computer Science\n";
    }

    void courseRegistration() {
        cout << "\n\t\t\t\t\t--- Course Registration ---\t\t\t\t\t\n";
        cout << "Courses available for registration:\n";
        cout << "1. OOP\n";
        cout << "2. OOP Lab\n";
        cout << "3. DLD\n";
        cout << "4. DLD Lab\n";
        cout << "5. Functional English\n";
        cout << "6. Pakistan Studies\n";
        cout << "7. Calculus\n";
        cout << "8. Maths @2\n";
        cout << "9. Statistics and Probability\n";
        cout << "10. Tajweed\n";
        cout << "\nSelect courses by their numbers (e.g., 1, 3, 5):\n";

        // Sample logic for course registration
        vector<string> availableCourses = {
            "OOP", "OOP Lab", "DLD", "DLD Lab", "Functional English",
            "Pakistan Studies", "Calculus", "Maths @2", "Statistics and Probability", "Tajweed"
        };

        string selected;
        cin.ignore();  // Clear input buffer
        getline(cin, selected);

        cout << "\nYou have registered for the following courses:\n";
        for (char ch : selected) {
            if (isdigit(ch)) {
                int index = ch - '0' - 1;  // Convert char to integer index
                if (index >= 0 && index < availableCourses.size()) {
                    cout << "- " << availableCourses[index] << "\n";
                }
            }
        }
    }

    void viewTimeTable() {
        cout << "\n\t\t\t\t\t--- Time Table ---\t\t\t\t\t\n";
        cout << setw(15) << left << "Day" << setw(30) << left << "Time" << setw(50) << left << "Subject" << endl;
        cout << setfill('-') << setw(95) << "" << setfill(' ') << endl;

        cout << setw(15) << left << "Monday" << setw(30) << left << "02:30 - 04:00" << setw(50) << left << "Applied Calculus" << endl;
        cout << setw(15) << left << "" << setw(30) << left << "04:00 - 06:00" << setw(50) << left << "DLD" << endl;

        cout << setw(15) << left << "Tuesday" << setw(30) << left << "11:30 - 02:30" << setw(50) << left << "DLD Lab" << endl;
        cout << setw(15) << left << "" << setw(30) << left << "05:30 - 07:00" << setw(50) << left << "OOP" << endl;

        cout << setw(15) << left << "Wednesday" << setw(30) << left << "03:00 - 05:00" << setw(50) << left << "Applied Calculus" << endl;
        cout << setw(15) << left << "" << setw(30) << left << "05:00 - 06:30" << setw(50) << left << "FE" << endl;

        cout << setw(15) << left << "Thursday" << setw(30) << left << "11:30 - 02:30" << setw(50) << left << "OOP Lab" << endl;
        cout << setw(15) << left << "" << setw(30) << left << "02:30 - 03:30" << setw(50) << left << "Tajweed" << endl;
        cout << setw(15) << left << "" << setw(30) << left << "03:30 - 05:00" << setw(50) << left << "Stats & Probability" << endl;
        cout << setw(15) << left << "" << setw(30) << left << "05:00 - 07:00" << setw(50) << left << "Pak Studies" << endl;

        cout << setw(15) << left << "Friday" << setw(30) << left << "02:30 - 04:00" << setw(50) << left << "Stats & Probability" << endl;
        cout << setw(15) << left << "" << setw(30) << left << "04:00 - 05:30" << setw(50) << left << "OOP" << endl;
        cout << setw(15) << left << "" << setw(30) << left << "05:30 - 07:00" << setw(50) << left << "FE" << endl;
        cout << setfill('-') << setw(95) << "" << setfill(' ') << endl;
    }

    void viewAttendance() {
        // Attendance data with credit hours
        struct Subject {
            string name;
            int creditHours;
            double attendancePercentage;
        };

        vector<Subject> subjects = {
            {"OOP", 3, 90.0},
            {"OOP Lab", 1, 85.0},
            {"DLD", 3, 88.0},
            {"DLD Lab", 1, 80.0},
            {"Functional English", 2, 92.0},
            {"Pakistan Studies", 2, 95.0},
            {"Calculus", 3, 87.0},
            {"Maths @2", 3, 85.0},
            {"Statistics and Probability", 3, 89.0},
            {"Tajweed", 1, 100.0}
        };

        cout << "\n\t\t\t\t\t--- Attendance ---\t\t\t\t\t\n";
        cout << setw(30) << left << "Subject" << setw(20) << left << "Credit Hours" << setw(20) << left << "Attendance (%)" << endl;
        cout << setfill('-') << setw(70) << "" << setfill(' ') << endl;

        for (const auto& subject : subjects) {
            cout << setw(30) << left << subject.name
                << setw(20) << left << subject.creditHours
                << setw(5) << left << subject.attendancePercentage << "%" << endl;
        }
        cout << setfill('-') << setw(70) << "" << setfill(' ') << endl;
    }

    void viewResults() {
        // Subject grades and credit hours
        struct Subject {
            string name;
            int creditHours;
            string grade;
        };

        vector<Subject> subjects = {
            {"OOP", 3, "A"},
            {"OOP Lab", 1, "B+"},
            {"DLD", 3, "A-"},
            {"DLD Lab", 1, "B"},
            {"Functional English", 2, "A"},
            {"Pakistan Studies", 2, "B+"},
            {"Calculus", 3, "A-"},
            {"Maths @2", 3, "B+"},
            {"Statistics and Probability", 3, "A"},
            {"Tajweed", 1, "A"}
        };

        double totalGradePoints = 0;
        double totalCreditHours = 0;
        cout << "\n\t\t\t\t\t--- Results ---\t\t\t\t\t\n";
        cout << setw(30) << left << "Subject" << setw(20) << left << "Credit Hours" << setw(20) << left << "Grade" << setw(20) << left << "Grade Points" << endl;
        cout << setfill('-') << setw(90) << "" << setfill(' ') << endl;

        for (const auto& subject : subjects) {
            double gradePoint = getGradePoint(subject.grade);
            totalGradePoints += gradePoint * subject.creditHours;
            totalCreditHours += subject.creditHours;

            cout << setw(30) << left << subject.name
                << setw(20) << left << subject.creditHours
                << setw(20) << left << subject.grade
                << setw(20) << left << gradePoint << endl;
        }
       

        double cgpa = totalGradePoints / totalCreditHours;
        cout << setfill('-') << setw(90) << "" << setfill(' ') << endl;
        cout << "\nYour CGPA: " << fixed << setprecision(2) << cgpa << endl;
        cout << setfill('-') << setw(90) << "" << setfill(' ') << endl;
    }

    double getGradePoint(const string& grade) {
        if (grade == "A") return 4.0;
        if (grade == "B+") return 3.5;
        if (grade == "B") return 3.0;
        if (grade == "C+") return 2.5;
        if (grade == "C") return 2.0;
        if (grade == "D") return 1.0;
        return 0.0;  // F grade
    }

    void viewFeeChallans() { cout << "\n\t\t\t\t\t--- Fee Challans ---\t\t\t\t\t\nPending Fee: Rs. 20,000 (Due: 30th April)\n"; }

    void viewScholarships() { cout << "\n\t\t\t\t\t--- Scholarships ---\t\t\t\t\t\n1. Merit-Based Scholarship\n2. Need-Based Aid\n"; }

    void viewAnnouncements() { cout << "\n\t\t\t\t\t--- Announcements ---\t\t\t\t\t\nFinal Exams start 5th May 2024.\n"; }

    void accessLMS() {
        int subjectChoice;
        do {
            cout << "\n\t\t\t\t\t--- LMS ---\t\t\t\t\t\n1. OOP\n2. OOP Lab\n3. DLD\n4. DLD Lab\n5. English\n6. Pak Studies\n";
            cout << "7. Calculus\n8. Statistics\n9. Back\nEnter your choice: ";
            cin >> subjectChoice;

            if (subjectChoice >= 1 && subjectChoice <= 8) {
                showSubjectMenu(subjectChoice);
            }
            else if (subjectChoice != 9) {
                cout << "Invalid choice!\n";
            }
        } while (subjectChoice != 9);
    }

    void showSubjectMenu(int subjectChoice) {
        string subjects[] = { "OOP", "OOP Lab", "DLD", "DLD Lab", "English", "Pak Studies", "Calculus", "Statistics" };
        int option;
        do {
            cout << "\n\t\t\t\t\t--- " << subjects[subjectChoice - 1] << " ---\t\t\t\t\t\n";
            cout << "1. Lecture Notes\n2. Assignments\n3. Quizzes\n4. Papers\n5. Back\nEnter choice: ";
            cin >> option;

            switch (option) {
            case 1: cout << "Lecture Notes: Week 1.pdf, Week 2.pdf\n"; break;
            case 2: cout << "Assignments: Assignment 1 (Due: 20th April)\n"; break;
            case 3: cout << "Quizzes: Quiz 1, Quiz 2\n"; break;
            case 4: cout << "Papers: Midterm, Final\n"; break;
            case 5: cout << "Returning to LMS...\n"; break;
            default: cout << "Invalid choice!\n";
            }
        } while (option != 5);
    }
};

// System Class to Manage Users
class System {
private:
    vector<Student> students;
public:
    System() { students.push_back(Student("Ali", "1234", "E001")); }

    void mainMenu() {
        int choice;
        do {
            cout << "\n\t\t\t\t\tUniversity Management System\t\t\t\t\t\n";
            cout << endl;
            cout << "1. Student (Sign In)\n2. Admission (Apply Online)\n3. Faculty Member (Sign In)\n";
            cout << "4. Alumni (Sign In)\n5. Administration (Staff)\n6. Exit\nEnter choice: ";
            cin >> choice;

            switch (choice) {
            case 1: studentSignIn(); break;
            case 2: applyOnline(); break;
            case 3: facultySignIn(); break;
            case 4: alumniSignIn(); break;
            case 5: administrationSignIn(); break;
            case 6: cout << "Exiting... Goodbye!\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 6);
    }

    void studentSignIn() {
        string id, pass;
        cout << "Enter Enrollment ID: "; cin >> id;
        cout << "Enter Password: "; cin >> pass;

        for (auto& student : students) {
            if (student.authenticate(pass) && student.getEnrollmentID() == id) {
                student.menu();
                return;
            }
        }
        cout << "Invalid ID or Password.\n";
    }

    void applyOnline() {
        cout << "Apply Online for Admission...\n";
    }

    void facultySignIn() {
        cout << "Faculty Member Sign In...\n";
    }

    void alumniSignIn() {
        cout << "Alumni Sign In...\n";
    }

    void administrationSignIn() {
        cout << "Administration Sign In...\n";
    }
};

int main() {
    System sys;
    sys.mainMenu();
    return 0;
}
