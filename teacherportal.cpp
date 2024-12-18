#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
using namespace std;

// ----------------------------- Login Module -------------------------------
class Login {
private:
    map<string, string> credentials; // Stores email-password pairs
    string currentUser;

public:
    Login() {
        // Predefined credentials
        credentials["teacher1@example.com"] = "password123";
        credentials["teacher2@example.com"] = "pass456";
    }

    bool loginUser() {
        string email, password;

        cout << "\n=== TEACHER PORTAL LOGIN ===\n";
        cout << "Enter Email: ";
        cin >> email;
        cout << "Enter Password: ";
        cin >> password;

        if (credentials.find(email) != credentials.end() && credentials[email] == password) {
            currentUser = email;
            cout << "\nLogin Successful! Welcome, " << email << ".\n";
            return true;
        }
        else {
            cout << "\nInvalid Email or Password. Try again!\n";
            return false;
        }
    }

    void logoutUser() {
        currentUser.clear();
        cout << "\nLogged out successfully.\n";
    }

    string getCurrentUser() const {
        return currentUser;
    }
};

// ----------------------------- CMS Dashboard -------------------------------
class CMSDashboard {
private:
    string teacherName;

public:
    CMSDashboard(string name) : teacherName(name) {}

    void profileInformation() {
        cout << "\n--- Profile Information ---\n";
        cout << "Name: " << teacherName << "\n";
        cout << "Role: Teacher\n";
        cout << "Email: " << teacherName << "@example.com\n";
    }

    void manageCourses() {
        cout << "\n--- Manage Courses ---\n";
        cout << "Feature under development.\n";
    }

    void viewSalary() {
        cout << "\n--- Salary Details ---\n";
        cout << "Monthly Salary: $4000\n";
        cout << "Bonus: $200\n";
    }

    void takeAttendance() {
        cout << "\n--- Take Attendance ---\n";
        cout << "Feature under development.\n";
    }

    void complainBox() {
        string complaint;
        cout << "\n--- Complain Box ---\n";
        cout << "Enter your complaint: ";
        cin.ignore();
        getline(cin, complaint);
        cout << "Your complaint has been submitted: \"" << complaint << "\"\n";
    }

    void displayOptions() {
        cout << "\n=== CMS DASHBOARD ===\n";
        cout << "1. Profile Information\n";
        cout << "2. Manage Courses\n";
        cout << "3. View Salary\n";
        cout << "4. Take Attendance\n";
        cout << "5. Go to LMS Dashboard\n";
        cout << "6. Complain Box\n";
        cout << "7. Logout\n";
    }
};

// ----------------------------- LMS Dashboard -------------------------------
class LMSDashboard {
public:
    void uploadLecture() {
        cout << "\n--- Upload Lecture ---\n";
        cout << "Lecture uploaded successfully.\n";
    }

    void uploadAssignments() {
        cout << "\n--- Upload Assignments ---\n";
        cout << "Assignments uploaded successfully.\n";
    }

    void uploadAnnouncements() {
        cout << "\n--- Upload Announcements ---\n";
        cout << "Announcement posted successfully.\n";
    }

    void uploadGrades() {
        cout << "\n--- Upload Student Grades ---\n";
        cout << "Grades uploaded successfully.\n";
    }

    void displayOptions() {
        cout << "\n=== LMS DASHBOARD ===\n";
        cout << "1. Upload Lecture\n";
        cout << "2. Upload Assignments\n";
        cout << "3. Upload Announcements\n";
        cout << "4. Upload Students Grades\n";
        cout << "5. Back To CMS\n";
    }
};

// ----------------------------- Main Program -------------------------------
class TeacherPortal {
private:
    Login loginSystem;
    CMSDashboard* cmsDashboard;
    LMSDashboard lmsDashboard;

public:
    TeacherPortal() : cmsDashboard(nullptr) {}

    void run() {
        while (true) {
            cout << "\n=== TEACHER PORTAL (CMS) ===\n";
            cout << "1. Login\n";
            cout << "2. Back to Main Menu\n";
            cout << "===========================\n";
            int choice;
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                if (loginSystem.loginUser()) {
                    cmsMenu();
                }
            }
            else if (choice == 2) {
                cout << "Exiting to Main Menu...\n";
                break;
            }
            else {
                cout << "Invalid choice. Try again.\n";
            }
        }
    }

    void cmsMenu() {
        string teacherName = loginSystem.getCurrentUser();
        cmsDashboard = new CMSDashboard(teacherName);

        while (true) {
            cmsDashboard->displayOptions();
            int choice;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cmsDashboard->profileInformation();
                break;
            case 2:
                cmsDashboard->manageCourses();
                break;
            case 3:
                cmsDashboard->viewSalary();
                break;
            case 4:
                cmsDashboard->takeAttendance();
                break;
            case 5:
                lmsMenu();
                break;
            case 6:
                cmsDashboard->complainBox();
                break;
            case 7:
                loginSystem.logoutUser();
                delete cmsDashboard;
                cmsDashboard = nullptr;
                return;
            default:
                cout << "Invalid choice. Try again.\n";
            }
        }
    }

    void lmsMenu() {
        while (true) {
            lmsDashboard.displayOptions();
            int choice;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                lmsDashboard.uploadLecture();
                break;
            case 2:
                lmsDashboard.uploadAssignments();
                break;
            case 3:
                lmsDashboard.uploadAnnouncements();
                break;
            case 4:
                lmsDashboard.uploadGrades();
                break;
            case 5:
                cout << "Returning to CMS Dashboard...\n";
                return;
            default:
                cout << "Invalid choice. Try again.\n";
            }
        }
    }
};

// ----------------------------- Main Function -------------------------------
int main() {
    TeacherPortal portal;
    portal.run();

    cout << "\nExiting Program...\n";
    return 0;
}
