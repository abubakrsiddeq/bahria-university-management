#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <ctime> // For random number generation
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

// Class for managing student admissions
class Student {
private:
    string username;
    string password;
    string fullName;
    string email;
    string contactNumber;
    string fatherName;
    long long cnic;
    int sscMarks;
    int fscMarks;
    int cbtScore = 0;

public:
    Student(string user, string pass, string name, string mail, string contact, long long cnicNum, string father, int ssc, int fsc)
        : username(user), password(pass), fullName(name), email(mail), contactNumber(contact), cnic(cnicNum), fatherName(father), sscMarks(ssc), fscMarks(fsc) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getFullName() const { return fullName; }
    string getEmail() const { return email; }
    string getContactNumber() const { return contactNumber; }
    long long getCnic() const { return cnic; }
    int getSscMarks() const { return sscMarks; }
    int getFscMarks() const { return fscMarks; }
    int getTotalMarks() const { return sscMarks + fscMarks; }
    void setCbtScore(int score) { cbtScore = score; }
    int getCbtScore() const { return cbtScore; }

    void takeCbtTest() {
        struct Question {
            string questionText;
            vector<string> options;
            char correctAnswer;
        };

        vector<Question> questions = {
            {"What is 2 + 2?", {"A. 3", "B. 4", "C. 5", "D. 6"}, 'B'},
            {"What is the capital of France?", {"A. Paris", "B. London", "C. Berlin", "D. Madrid"}, 'A'},
            {"What is the chemical symbol for water?", {"A. CO2", "B. O2", "C. H2O", "D. H2"}, 'C'},
            {"Who wrote 'Romeo and Juliet'?", {"A. Charles Dickens", "B. J.K. Rowling", "C. William Shakespeare", "D. Mark Twain"}, 'C'},
            {"What is the largest planet in our solar system?", {"A. Earth", "B. Mars", "C. Jupiter", "D. Saturn"}, 'C'}
        };

        int score = 0;
        char answer;

        for (const auto& q : questions) {
            cout << q.questionText << endl;
            for (const auto& opt : q.options) {
                cout << opt << endl;
            }

            cout << "Enter your answer (A, B, C, or D): ";
            cin >> answer;
            answer = toupper(answer);

            if (answer == q.correctAnswer) {
                score += 2;
            }
        }

        setCbtScore(score);
        cout << "You have completed the CBT test. Your score is: " << score << "/10" << endl;
    }
};

class AdmissionPortal {
private:
    vector<Student> students;

public:
    void registerStudent() {
        string username, password, fullName, email, contactNumber, fatherName;
        long long cnic;
        int sscMarks, fscMarks;

        cout << "\n----------------- Register New Student -----------------\n";
        cout << "Enter username: ";
        cin >> username;
        cin.ignore();

        cout << "Enter password: ";
        getline(cin, password);

        cout << "Enter full name: ";
        getline(cin, fullName);

        cout << "Enter email: ";
        getline(cin, email);

        cout << "Enter contact number: ";
        getline(cin, contactNumber);

        cout << "Enter CNIC number: ";
        cin >> cnic;
        cin.ignore();

        cout << "Enter father's name: ";
        getline(cin, fatherName);

        cout << "Enter SSC marks: ";
        while (!(cin >> sscMarks) || sscMarks < 0 || sscMarks > 1100) {
            cout << "Invalid SSC marks. Please enter a value between 0 and 1100: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        cout << "Enter FSC marks: ";
        while (!(cin >> fscMarks) || fscMarks < 0 || fscMarks > 1100) {
            cout << "Invalid FSC marks. Please enter a value between 0 and 1100: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        students.push_back(Student(username, password, fullName, email, contactNumber, cnic, fatherName, sscMarks, fscMarks));
        cout << "\nRegistration successful!\n";
    }

    void studentLogin() {
        string username, password;
        cout << "\n----------------- Student Login -----------------\n";
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        for (auto& student : students) {
            if (student.getUsername() == username && student.getPassword() == password) {
                studentMenu(student);
                return;
            }
        }
        cout << "Invalid username or password.\n";
    }

    void studentMenu(Student& student) {
        int choice;
        do {
            cout << "\nSTUDENT MENU" << endl;
            cout << "1. Take CBT Test" << endl;
            cout << "2. View Merit List" << endl;
            cout << "3. Back" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                student.takeCbtTest();
                break;
            case 2:
                viewMeritList();
                break;
            case 3:
                cout << "Returning to previous menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 3);
    }

    void addMeritList() {
        cout << "\nAdding Merit List...\n";

        // Sort students by their total marks (SSC + FSC)
        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.getTotalMarks() > b.getTotalMarks();
            });

        cout << "\nMerit List Added Successfully!\n";
    }

    void viewMeritList() const {
        cout << "\nDisplaying Merit List:\n";

        for (const auto& student : students) {
            cout << "Name: " << student.getFullName()
                << ", SSC Marks: " << student.getSscMarks()
                << ", FSC Marks: " << student.getFscMarks()
                << ", CBT Score: " << student.getCbtScore()
                << ", Total Marks: " << student.getTotalMarks() << "\n";
        }
    }

    const vector<Student>& getStudents() const {
        return students;
    }
};

// Derived class for Admin
class Admin : public User {
private:
    AdmissionPortal* portal;
public:
    Admin(string name, string email, string password, AdmissionPortal* portal)
        : User(name, email, password), portal(portal) {}

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
            cout << "2. View Merit List" << endl;
            cout << "3. View Registered Students" << endl;
            cout << "4. Back to Admin Panel" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                portal->addMeritList();
                break;
            case 2:
                portal->viewMeritList();
                break;
            case 3: {
                const auto& students = portal->getStudents();
                for (const auto& student : students) {
                    cout << "Name: " << student.getFullName()
                        << ", Email: " << student.getEmail()
                        << ", Contact: " << student.getContactNumber() << "\n";
                }
                break;
            }
            case 4:
                cout << "Returning to Admin Panel..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 4);
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
    AdmissionPortal portal;
    Admin admin("Admin", "admin@university.com", "password", &portal);
    const string predefinedPassword = "admin123";

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
            if (verifyPassword(predefinedPassword)) {
                admin.displayMenu();
            }
            else {
                cout << "Incorrect Password. Returning to Main Menu." << endl;
            }
            break;
        case 2: {
            int subChoice;
            cout << "\nSTUDENT ADMISSION PORTAL" << endl;
            cout << "1. Registration" << endl;
            cout << "2. Login" << endl;
            cout << "Enter your choice: ";
            cin >> subChoice;

            if (subChoice == 1) {
                portal.registerStudent();
            }
            else if (subChoice == 2) {
                portal.studentLogin();
            }
            else {
                cout << "Invalid choice. Returning to Main Menu." << endl;
            }
            break;
        }
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
