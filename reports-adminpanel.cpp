#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // For formatted output
using namespace std;

// Base class for Reports
class Report {
public:
    virtual void display() {} //  virtual function
};

// Class for Teachers
class Teacher : public Report {
    vector<string> teachers = { "Mr. Smith", "Ms. Johnson", "Dr. Brown" };

public:
    void display() override {
        cout << "\n--- Teachers List ---\n";
        for (size_t i = 0; i < teachers.size(); ++i) {
            cout << i + 1 << ". " << teachers[i] << endl;
        }
    }
};

// Class for Students
class Student : public Report {
protected:
    vector<string> enrolledStudents = { "Alice", "Bob", "Charlie" };
    vector<string> passedOutStudents = { "David", "Eva", "Frank" };

public:
    void displayEnrolled() {
        cout << "\n--- Enrolled Students ---\n";
        for (size_t i = 0; i < enrolledStudents.size(); ++i) {
            cout << i + 1 << ". " << enrolledStudents[i] << endl;
        }
    }

    void displayPassedOut() {
        cout << "\n--- Passed Out Students ---\n";
        for (size_t i = 0; i < passedOutStudents.size(); ++i) {
            cout << i + 1 << ". " << passedOutStudents[i] << endl;
        }
    }
};

// Class for Transcripts
class Transcript : public Report {
public:
    void display() override {
        cout << "\n--- Generate Transcript ---\n";
        cout << "Transcript for Student: Alice\n";
        cout << "Subject 1: A\nSubject 2: B\nSubject 3: A+\n\n";
        cout << "Transcript successfully generated!\n";
    }
};

// Class for NOC
class NOC : public Report {
public:
    void display() override {
        cout << "\n--- Generate NOC ---\n";
        cout << "NOC generated for student Alice.\n";
        cout << "Status: Approved\n\n";
    }
};

// Admin Panel
class AdminPanel {
    Teacher teacher;
    Student student;
    Transcript transcript;
    NOC noc;

public:
    void displayMenu() {
        int choice;
        do {
            cout << "\n================ REPORTS MENU ================\n";
            cout << "1. Display Teachers\n";
            cout << "2. Enrolled Students\n";
            cout << "3. Passed Out Students\n";
            cout << "4. Generate Transcript\n";
            cout << "5. Generate NOC\n";
            cout << "6. Back to Admin Panel\n";
            cout << "=============================================\n";
            cout << "Enter your choice: ";

            // Error Handling for Invalid Input
            if (!(cin >> choice)) {
                cin.clear(); // Clear the error state
                cin.ignore(10000, '\n'); // Ignore invalid input
                cout << "Invalid input. Please enter a number between 1 and 6.\n";
                continue;
            }

            switch (choice) {
            case 1:
                teacher.display();
                break;
            case 2:
                student.displayEnrolled();
                break;
            case 3:
                student.displayPassedOut();
                break;
            case 4:
                transcript.display();
                break;
            case 5:
                noc.display();
                break;
            case 6:
                cout << "Returning to Admin Panel...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 6);
    }
};

// Main function
int main() {
    AdminPanel adminPanel;
    cout << "======= Welcome to the Report Management System =======\n";
    adminPanel.displayMenu();
    cout << "Thank you for using the system!\n";
    return 0;
}
