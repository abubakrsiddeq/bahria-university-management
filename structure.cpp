#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base class for all users
class User {
protected:
    string name;
    string email;
    string password;

public:
    User(string name, string email, string password)
        : name(name), email(email), password(password) {}

    virtual void displayMenu() = 0; // Pure virtual function
};

// Derived class for Admin
class Admin : public User {
public:
    Admin(string name, string email, string password)
        : User(name, email, password) {}

    void displayMenu() override {
        int choice;
        do {
            cout << "\nADMIN PANEL" << endl;
            cout << "1. USER MANAGEMENT" << endl;
            cout << "2. COURSE MANAGEMENT" << endl;
            cout << "3. ADMISSION MANAGEMENT" << endl;
            cout << "4. REPORTS" << endl;
            cout << "5. COMMUNICATION DESK" << endl;
            cout << "6. STUDENT FACILITIES" << endl;
            cout << "7. BACK TO MAIN MENU" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                userManagementMenu();
                break;
            case 2:
                courseManagementMenu();
                break;
            case 3:
                admissionManagementMenu();
                break;
            case 4:
                reportsMenu();
                break;
            case 5:
                communicationMenu();
                break;
            case 6:
                cout << "Student Facilities management is under construction." << endl;
                break;
            case 7:
                cout << "Returning to Main Menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 7);
    }

private:
    void userManagementMenu() {
        int choice;
        do {
            cout << "\nUSER MANAGEMENT" << endl;
            cout << "1. Add New Student" << endl;
            cout << "2. Edit Student Details" << endl;
            cout << "3. Remove Student" << endl;
            cout << "4. Add New Teacher" << endl;
            cout << "5. Edit Teacher Details" << endl;
            cout << "6. Remove Teacher" << endl;
            cout << "7. Add Pass-out Students" << endl;
            cout << "8. Back to Admin Panel" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Adding new student..." << endl;
                break;
            case 2:
                cout << "Editing student details..." << endl;
                break;
            case 3:
                cout << "Removing student..." << endl;
                break;
            case 4:
                cout << "Adding new teacher..." << endl;
                break;
            case 5:
                cout << "Editing teacher details..." << endl;
                break;
            case 6:
                cout << "Removing teacher..." << endl;
                break;
            case 7:
                cout << "Adding pass-out students..." << endl;
                break;
            case 8:
                cout << "Returning to Admin Panel..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 8);
    }

    void courseManagementMenu() {
        int choice;
        do {
            cout << "\nCOURSE MANAGEMENT" << endl;
            cout << "1. Add New Course" << endl;
            cout << "2. Edit Course" << endl;
            cout << "3. Delete Course" << endl;
            cout << "4. Published Courses" << endl;
            cout << "5. Attendance Controller" << endl;
            cout << "6. Assigned Teachers" << endl;
            cout << "7. Back to Admin Panel" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Adding new course..." << endl;
                break;
            case 2:
                cout << "Editing course..." << endl;
                break;
            case 3:
                cout << "Deleting course..." << endl;
                break;
            case 4:
                cout << "Displaying published courses..." << endl;
                break;
            case 5:
                cout << "Attendance management is under construction." << endl;
                break;
            case 6:
                cout << "Managing assigned teachers..." << endl;
                break;
            case 7:
                cout << "Returning to Admin Panel..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 7);
    }

    void admissionManagementMenu() {
        int choice;
        do {
            cout << "\nADMISSION MANAGEMENT" << endl;
            cout << "1. Add Merit List" << endl;
            cout << "2. Edit Merit List" << endl;
            cout << "3. Display Merit List" << endl;
            cout << "4. Delete Merit List" << endl;
            cout << "5. Back to Admin Panel" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Adding merit list..." << endl;
                break;
            case 2:
                cout << "Editing merit list..." << endl;
                break;
            case 3:
                cout << "Displaying merit list..." << endl;
                break;
            case 4:
                cout << "Deleting merit list..." << endl;
                break;
            case 5:
                cout << "Returning to Admin Panel..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 5);
    }

    void reportsMenu() {
        int choice;
        do {
            cout << "\nREPORTS" << endl;
            cout << "1. Display Teachers" << endl;
            cout << "2. Enrolled Students" << endl;
            cout << "3. Passed Out Students" << endl;
            cout << "4. Generate Transcript" << endl;
            cout << "5. Generate NOC" << endl;
            cout << "6. Back to Admin Panel" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Displaying teachers..." << endl;
                break;
            case 2:
                cout << "Displaying enrolled students..." << endl;
                break;
            case 3:
                cout << "Displaying passed out students..." << endl;
                break;
            case 4:
                cout << "Generating transcript..." << endl;
                break;
            case 5:
                cout << "Generating NOC..." << endl;
                break;
            case 6:
                cout << "Returning to Admin Panel..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 6);
    }

    void communicationMenu() {
        int choice;
        do {
            cout << "\nCOMMUNICATION DESK" << endl;
            cout << "1. Add New Survey" << endl;
            cout << "2. Edit Survey" << endl;
            cout << "3. Display Students Survey" << endl;
            cout << "4. Students Complains" << endl;
            cout << "5. Back to Admin Panel" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Adding new survey..." << endl;
                break;
            case 2:
                cout << "Editing survey..." << endl;
                break;
            case 3:
                cout << "Displaying students survey..." << endl;
                break;
            case 4:
                cout << "Displaying student complaints..." << endl;
                break;
            case 5:
                cout << "Returning to Admin Panel..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 5);
    }
};

// Main function
int main() {
    Admin admin("Admin", "admin@university.com", "password");

    int mainChoice;
    do {
        cout << "\nMAIN MENU" << endl;
        cout << "1. ADMIN PANEL" << endl;
        cout << "2. STUDENT ADMISSION PORTAL" << endl;
        cout << "3. STUDENT PORTAL (CMS)" << endl;
        cout << "4. TEACHER/FACULTY PORTAL" << endl;
        cout << "5. SHORT COURSES PORTAL" << endl;
        cout << "6. EXIT PROGRAM" << endl;
        cout << "Enter your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
        case 1:
            admin.displayMenu();
            break;
        case 2:
            cout << "Student Admission Portal is under construction." << endl;
            break;
        case 3:
            cout << "Student Portal (CMS) is under construction." << endl;
            break;
        case 4:
            cout << "Teacher/Faculty Portal is under construction." << endl;
            break;
        case 5:
            cout << "Short Courses Portal is under construction." << endl;
            break;
        case 6:
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (mainChoice != 6);

    return 0;
}
