#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <fstream>
using namespace std;

// ======================== User Management ========================

class User {
protected:
    string name;
    int id;
    string contact;

public:
    User(string name, int id, string contact)
        : name(name), id(id), contact(contact) {}

    virtual void displayDetails() const {
        cout << left << setw(10) << id << setw(20) << name << setw(15) << contact;
    }

    int getID() const { return id; }
    string getName() const { return name; }

    virtual ~User() = default;
};

class Student : public User {
private:
    bool isPassOut;

public:
    Student(string name, int id, string contact, bool passOut = false)
        : User(name, id, contact), isPassOut(passOut) {}

    void displayDetails() const override {
        User::displayDetails();
        cout << setw(10) << (isPassOut ? "Yes" : "No") << endl;
    }

    void markPassOut() { isPassOut = true; }

    void editDetails(const string& newName, const string& newContact) {
        name = newName;
        contact = newContact;
    }
};

class Teacher : public User {
private:
    string subject;

public:
    Teacher(string name, int id, string contact, string subject)
        : User(name, id, contact), subject(subject) {}

    void hasSubjectDetails(const string& newName, const string& newContact, const string& newSubject) {
        name = newName;
        contact = newContact;
        subject = newSubject;
    }
    void displayDetails() const override {
        User::displayDetails();
        cout << setw(20) << subject << endl;
    }

    void editDetails(const string& newName, const string& newContact, const string& newSubject) {
        name = newName;
        contact = newContact;
        subject = newSubject;
    }
};
class Login {
private:
    map<string, string> credentials; // Stores email-password pairs
    string currentUser;

public:
    Login() {
        // Predefined credentials
        credentials["teacher1@example.com"] = "f1";
        credentials["teacher2@example.com"] = "1";
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
class CourseUser {
protected:
    string email;
    string password;

public:
    virtual void registerUser() = 0;   // Pure virtual function
    virtual bool login() = 0;          // Pure virtual function
};

class CourseTeacher:public CourseUser {
private:
    string name;
    bool isLoggedIn = false;
    map<string, vector<string>> subjectDetails; // Store subjects with associated details
    const string fileName = "teacher_subjects.txt"; // File name for storing subject details
    const string teacherFileName = "teacher_details.txt"; // File name for storing teacher details
    const string studentFileName = "student_details.txt"; // File name for storing student details
    bool isSubjectDetailsLoaded = false;  // Track if subject details are loaded

public:
    void registerUser() override {
        cout << "\n--- Teacher Registration ---\n";
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Email: ";
        getline(cin, email);
        cout << "Enter Password: ";
        getline(cin, password);
        cout << "Teacher registered successfully!\n";

        // Adding subjects of expertise
        addSubjects();

        // Save teacher details
        saveTeacherDetails();
    }

    bool login() override {
        cout << "\n--- Teacher Login ---\n";
        string inputEmail, inputPassword;

        cout << "Enter Email: ";
        getline(cin, inputEmail);
        cout << "Enter Password: ";
        getline(cin, inputPassword);

        if (inputEmail == email && inputPassword == password) {
            cout << "Login successful!\n";
            isLoggedIn = true;
            loadSubjectDetails();  // Load subject details from the file
            isSubjectDetailsLoaded = true;  // Mark as loaded
            return true;
        }
        else {
            cout << "Invalid credentials. Try again!\n";
            return false;
        }
    }

    void addSubjects() {
        string subject;
        char choice;
        do {
            cout << "Enter a subject you are skilled in: ";
            getline(cin, subject);
            addSubjectDetails(subject);

            cout << "Do you want to add another subject? (y/n): ";
            cin >> choice;
            cin.ignore(); // Clear input buffer
        } while (tolower(choice) == 'y');

        // Save the subject details to a file after adding
        saveSubjectDetailsToFile();
    }

    void addSubjectDetails(const string& subject) {
        string topic, assignment, pastPaper, quiz;
        cout << "Enter details for subject '" << subject << "':\n";

        cout << "  - Topic: ";
        getline(cin, topic);
        cout << "  - Assignment: ";
        getline(cin, assignment);
        cout << "  - Past Paper: ";
        getline(cin, pastPaper);
        cout << "  - Quiz: ";
        getline(cin, quiz);

        subjectDetails[subject] = { topic, assignment, pastPaper, quiz };
        cout << "Details added successfully for '" << subject << "'.\n";
    }

    void updateSubjectDetails() {
        string subject;
        cout << "\nEnter the subject you want to update: ";
        getline(cin, subject);

        if (subjectDetails.find(subject) == subjectDetails.end()) {
            cout << "Subject not found! Add it first.\n";
            return;
        }

        cout << "Updating details for '" << subject << "'...\n";
        addSubjectDetails(subject);

        // Save the updated subject details to the file
        saveSubjectDetailsToFile();
    }

    void displaySubjects() {
        if (subjectDetails.empty()) {
            cout << "No subjects added yet.\n";
            return;
        }

        cout << "\nSubjects of expertise with details:\n";
        for (const auto& subject : subjectDetails) {
            cout << "\nSubject: " << subject.first << "\n";
            cout << "  - Topic: " << subject.second[0] << "\n";
            cout << "  - Assignment: " << subject.second[1] << "\n";
            cout << "  - Past Paper: " << subject.second[2] << "\n";
            cout << "  - Quiz: " << subject.second[3] << "\n";
        }
    }

    const map<string, vector<string>>& getSubjectDetails() const {
        return subjectDetails;
    }

    void saveSubjectDetailsToFile() {
        ofstream outFile(fileName, ios::app); // Append mode
        if (outFile.is_open()) {
            for (const auto& subject : subjectDetails) {
                outFile << subject.first << "\n";  // Write the subject name
                for (const auto& detail : subject.second) {
                    outFile << detail << "\n";  // Write the associated details (topic, assignment, etc.)
                }
                outFile << "---\n";  // Separator for each subject
            }
            outFile.close();
            cout << "Subject details saved to file: " << fileName << "\n";
        }
        else {
            cerr << "Error opening file to save data: " << fileName << "\n";
        }
    }

    void loadSubjectDetails() {
        ifstream inFile(fileName);
        string subject, topic, assignment, pastPaper, quiz;
        vector<string> details;

        if (inFile.is_open()) {
            while (getline(inFile, subject)) {
                details.clear();
                getline(inFile, topic);
                getline(inFile, assignment);
                getline(inFile, pastPaper);
                getline(inFile, quiz);

                details.push_back(topic);
                details.push_back(assignment);
                details.push_back(pastPaper);
                details.push_back(quiz);

                subjectDetails[subject] = details;

                // Skip the separator line
                string separator;
                getline(inFile, separator);
            }
            inFile.close();
            cout << "Subject details loaded from file: " << fileName << "\n";
        }
        else {
            cout << "Error opening file to load data: " << fileName << "\n";
        }
    }

    bool hasSubjectDetails() const {
        return isSubjectDetailsLoaded;
    }

    void loadStudentDetails() {
        ifstream inFile(studentFileName);
        string studentName, studentEmail, studentSubject;

        if (inFile.is_open()) {
            cout << "\n--- Students who have chosen your subjects ---\n";
            bool hasStudents = false;
            while (getline(inFile, studentName)) {
                getline(inFile, studentEmail);
                while (getline(inFile, studentSubject) && studentSubject != "---") {
                    if (subjectDetails.find(studentSubject) != subjectDetails.end()) {
                        hasStudents = true;
                        cout << "\nStudent Name: " << studentName << "\n";
                        cout << "Student Email: " << studentEmail << "\n";
                        cout << "Chosen Subject: " << studentSubject << "\n";
                    }
                }
            }
            if (!hasStudents) {
                cout << "No students have chosen your subjects yet.\n";
            }
            inFile.close();
        }
        else {
            cout << "Error opening file to load student details: " << studentFileName << "\n";
        }
    }

    void saveTeacherDetails() {
        ofstream outFile(teacherFileName, ios::app); // Append mode
        if (outFile.is_open()) {
            outFile << name << "\n";
            outFile << email << "\n";
            for (const auto& subject : subjectDetails) {
                outFile << subject.first << "\n";
            }
            outFile << "---\n"; // Separator for each teacher
            outFile.close();
            cout << "Teacher details saved to file: " << teacherFileName << "\n";
        }
        else {
            cerr << "Error opening file to save data: " << teacherFileName << "\n";
        }
    }

    void dashboard() {
        if (!isLoggedIn) {
            cout << "Please log in first!\n";
            return;
        }

        int choice;
        do {
            cout << "\n--- Teacher Dashboard ---\n";
            cout << "1. Display Subjects and Details\n";
            cout << "2. Update Subject Details\n";
            cout << "3. View Students for Your Subjects\n";
            cout << "4. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(); // Clear newline left in the buffer

            switch (choice) {
            case 1:
                displaySubjects();
                break;
            case 2:
                updateSubjectDetails();
                break;
            case 3:
                loadStudentDetails();
                break;
            case 4:
                cout << "Logged out.\n";
                isLoggedIn = false;
                break;
            default:
                cout << "Invalid choice! Try again.\n";
            }
        } while (isLoggedIn);
    }
};
// Student Class
class CourseStudent : public CourseUser {
private:
    string name;
    bool isLoggedIn = false;
    vector<string> chosenSubjects;
    const string studentFileName = "student_details.txt"; // File name for storing student details

public:
    void registerUser() override {
        cout << "\n--- Student Registration ---\n";
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Email: ";
        getline(cin, email);
        cout << "Enter Password: ";
        getline(cin, password);
        cout << "Student registered successfully!\n";

        // Select subjects
        selectSubjects();

        // Save student details
        saveStudentDetailsToFile();
    }

    bool login() override {
        cout << "\n--- Student Login ---\n";
        string inputEmail, inputPassword;

        cout << "Enter Email: ";
        getline(cin, inputEmail);
        cout << "Enter Password: ";
        getline(cin, inputPassword);

        if (inputEmail == email && inputPassword == password) {
            cout << "Login successful!\n";
            isLoggedIn = true;
            return true;
        }
        else {
            cout << "Invalid credentials. Try again!\n";
            return false;
        }
    }

    void selectSubjects() {
        string subject;
        char choice;
        do {
            cout << "Enter a subject you want to study: ";
            getline(cin, subject);
            chosenSubjects.push_back(subject);
            cout << "Subject '" << subject << "' added to your list.\n";

            cout << "Do you want to select another subject? (y/n): ";
            cin >> choice;
            cin.ignore(); // Clear input buffer
        } while (tolower(choice) == 'y');
    }

    void displayChosenSubjects(const Teacher& teacher) {
        cout << "\n--- Your Subjects and Details ---\n";
        if (chosenSubjects.empty()) {
            cout << "No subjects chosen yet.\n";
            return;
        }

        if (!teacher.hasSubjectDetails()) {
            cout << "Teacher has not loaded subject details. Please try again later.\n";
            return;
        }

        const map<string, vector<string>>& teacherSubjects = teacher.getSubjectDetails();
        for (const string& subject : chosenSubjects) {
            if (teacherSubjects.find(subject) != teacherSubjects.end()) {
                cout << "\nSubject: " << subject << "\n";
                cout << "  - Topic: " << teacherSubjects.at(subject)[0] << "\n";
                cout << "  - Assignment: " << teacherSubjects.at(subject)[1] << "\n";
                cout << "  - Past Paper: " << teacherSubjects.at(subject)[2] << "\n";
                cout << "  - Quiz: " << teacherSubjects.at(subject)[3] << "\n";
            }
            else {
                cout << "\nSubject: " << subject << " - No details available.\n";
            }
        }
    }

    void saveStudentDetailsToFile() {
        ofstream outFile(studentFileName, ios::app); // Append mode
        if (outFile.is_open()) {
            outFile << name << "\n";
            outFile << email << "\n";
            for (const auto& subject : chosenSubjects) {
                outFile << subject << "\n";
            }
            outFile << "---\n"; // Separator for each student
            outFile.close();
            cout << "Student details saved to file: " << studentFileName << "\n";
        }
        else {
            cerr << "Error opening file to save data: " << studentFileName << "\n";
        }
    }

    void dashboard(const Teacher& teacher) {
        if (!isLoggedIn) {
            cout << "Please log in first!\n";
            return;
        }

        int choice;
        do {
            cout << "\n--- Student Dashboard ---\n";
            cout << "1. View Chosen Subjects and Details\n";
            cout << "2. Select More Subjects\n";
            cout << "3. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(); // Clear newline left in the buffer

            switch (choice) {
            case 1:
                displayChosenSubjects(teacher);
                break;
            case 2:
                selectSubjects();
                saveStudentDetailsToFile(); // Save updated subjects
                break;
            case 3:
                cout << "Logged out.\n";
                isLoggedIn = false;
                break;
            default:
                cout << "Invalid choice! Try again.\n";
            }
        } while (isLoggedIn);
    }
};

// Admin Class
class CourseAdmin {
private:
    const string teacherFileName = "teacher_details.txt"; // File name for storing teacher details
    const string studentFileName = "student_details.txt"; // File name for storing student details

public:
    void viewTeachers() {
        ifstream inFile(teacherFileName);
        string name, email, subject;
        int teacherCount = 1;
        bool hasTeachers = false;

        if (inFile.is_open()) {
            cout << "\n--- Registered Teachers ---\n";
            while (getline(inFile, name)) {
                hasTeachers = true;
                getline(inFile, email);
                cout << teacherCount++ << ". Name: " << name << "\n";
                cout << "   Email: " << email << "\n";
                cout << "   Subjects: ";
                while (getline(inFile, subject) && subject != "---") {
                    cout << subject << ", ";
                }
                cout << "\n";
            }
            if (!hasTeachers) {
                cout << "No teachers have been registered yet.\n";
            }
            inFile.close();
        }
        else {
            cout << "Error opening file to load teacher details: " << teacherFileName << "\n";
        }
    }

    void viewStudents() {
        ifstream inFile(studentFileName);
        string name, email, subject;
        int studentCount = 1;
        bool hasStudents = false;

        if (inFile.is_open()) {
            cout << "\n--- Registered Students ---\n";
            while (getline(inFile, name)) {
                hasStudents = true;
                getline(inFile, email);
                cout << studentCount++ << ". Name: " << name << "\n";
                cout << "   Email: " << email << "\n";
                cout << "   Subjects: ";
                while (getline(inFile, subject) && subject != "---") {
                    cout << subject << ", ";
                }
                cout << "\n";
            }
            if (!hasStudents) {
                cout << "No students have been registered yet.\n";
            }
            inFile.close();
        }
        else {
            cout << "Error opening file to load student details: " << studentFileName << "\n";
        }
    }

    void dashboard() {
        int choice;
        do {
            cout << "\n--- Admin Dashboard ---\n";
            cout << "1. View Registered Teachers\n";
            cout << "2. View Registered Students\n";
            cout << "3. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(); // Clear newline left in the buffer

            switch (choice) {
            case 1:
                viewTeachers();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                cout << "Logged out.\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
            }
        } while (choice != 3);
    }
};
// Function Prototypes
void displayMainMenu();
void handleTeacher(Teacher& teacher);
void handleStudent(Student& student, Teacher& teacher);
void handleAdmin(Admin& admin);

class UserManagement {
private:
    vector<Student> students;
    vector<Teacher> teachers;
    int studentIDCounter = 1000;
    int teacherIDCounter = 2000;

    void displayStudents() const {
        if (students.empty()) {
            cout << "\nNo students available.\n";
            return;
        }

        cout << "\n--- Student List ---\n";
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Contact" << "Pass-out\n";
        cout << string(55, '-') << endl;

        for (const auto& student : students)
            student.displayDetails();
    }

    void displayTeachers() const {
        if (teachers.empty()) {
            cout << "\nNo teachers available.\n";
            return;
        }

        cout << "\n--- Teacher List ---\n";
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Contact" << "Subject\n";
        cout << string(65, '-') << endl;

        for (const auto& teacher : teachers)
            teacher.displayDetails();
    }

public:
    void addNewStudent() {
        string name, contact;
        cout << "\nEnter Student Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Contact: ";
        getline(cin, contact);

        students.emplace_back(name, studentIDCounter++, contact);
        cout << "Student added successfully!\n";
    }

    void editStudent() {
        displayStudents();
        if (students.empty()) return;

        int id;
        cout << "\nEnter Student ID to edit: ";
        cin >> id;

        cin.ignore();
        for (auto& student : students) {
            if (student.getID() == id) {
                string newName, newContact;
                cout << "Enter New Name: ";
                getline(cin, newName);

                cout << "Enter New Contact: ";
                getline(cin, newContact);

                student.editDetails(newName, newContact);
                cout << "Student details updated successfully!\n";
                return;
            }
        }
        cout << "Student ID not found!\n";
    }

    void removeStudent() {
        displayStudents();
        if (students.empty()) return;

        int id;
        cout << "\nEnter Student ID to remove: ";
        cin >> id;

        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->getID() == id) {
                cout << "Student \"" << it->getName() << "\" removed successfully.\n";
                students.erase(it);
                return;
            }
        }
        cout << "Student ID not found!\n";
    }

    void addNewTeacher() {
        string name, contact, subject;
        cout << "\nEnter Teacher Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Contact: ";
        getline(cin, contact);

        cout << "Enter Subject: ";
        getline(cin, subject);

        teachers.emplace_back(name, teacherIDCounter++, contact, subject);
        cout << "Teacher added successfully!\n";
    }

    void userManagementMenu() {
        int choice;
        do {
            cout << "\n=== USER MANAGEMENT ===\n";
            cout << "1. Add New Student\n";
            cout << "2. Edit Student Details\n";
            cout << "3. Remove Student\n";
            cout << "4. Add New Teacher\n";
            cout << "5. Back To Admin Panel\n";
            cout << "========================\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: addNewStudent(); break;
            case 2: editStudent(); break;
            case 3: removeStudent(); break;
            case 4: addNewTeacher(); break;
            case 5: cout << "Returning to Admin Panel...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
            }
        } while (choice != 5);
    }
};

// ======================== Course Management ========================

class Course {
private:
    string courseName;
    string courseCode;
    string teacherAssigned;
    bool published;

public:
    Course(string name, string code, string teacher, bool isPublished)
        : courseName(name), courseCode(code), teacherAssigned(teacher), published(isPublished) {}

    void displayCourse(int index) const {
        cout << left << setw(5) << index + 1
            << setw(20) << courseName
            << setw(15) << courseCode
            << setw(20) << teacherAssigned
            << (published ? "Yes" : "No") << endl;
    }

    void editCourse(string name, string code, string teacher, bool isPublished) {
        courseName = name;
        courseCode = code;
        teacherAssigned = teacher;
        published = isPublished;
    }

    string getCourseName() const {
        return courseName;
    }

    void publishCourse() {
        published = true;
    }
};

class CourseManagement {
private:
    vector<Course> courses;

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

    void courseManagementMenu() {
        int choice;
        do {
            cout << "\n=== COURSE MANAGEMENT ===\n";
            cout << "1. Add New Course\n";
            cout << "2. Edit Course\n";
            cout << "3. Delete Course\n";
            cout << "4. Back To Admin Panel\n";
            cout << "========================\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: addNewCourse(); break;
            case 2: editCourse(); break;
            case 3: deleteCourse(); break;
            case 4: cout << "Returning to Admin Panel...\n"; break;
            default: cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 4);
    }
};

// ======================== Admission Management ========================

class AdmissionManagement {
private:
    vector<string> meritList;
    vector<Student> newStudents; // To store new students
    vector<pair<string, int>> cbtTestScores; // To store CBT test scores (student name and score)

    void displayMeritList() const {
        if (meritList.empty()) {
            cout << "\nMerit list is empty!\n";
        }
        else {
            cout << "\n---- Merit List ----\n";
            for (size_t i = 0; i < meritList.size(); ++i) {
                cout << i + 1 << ". " << meritList[i] << "\n";
            }
        }
        cout << "----------------------\n";
    }

    void displayNewStudents() const {
        if (newStudents.empty()) {
            cout << "\nNo new students available.\n";
            return;
        }

        cout << "\n--- New Student List ---\n";
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Contact" << "Pass-out\n";
        cout << string(55, '-') << endl;

        for (const auto& student : newStudents)
            student.displayDetails();
    }

    void displayCBTTestScores() const {
        if (cbtTestScores.empty()) {
            cout << "\nNo CBT test scores available.\n";
            return;
        }

        cout << "\n--- CBT Test Scores ---\n";
        cout << left << setw(20) << "Student Name" << "Score\n";
        cout << string(30, '-') << endl;

        for (const auto& score : cbtTestScores) {
            cout << left << setw(20) << score.first << score.second << "\n";
        }
    }

public:
    void addMeritList() {
        string studentName;
        cout << "Enter student name to add to the merit list: ";
        cin.ignore();
        getline(cin, studentName);
        meritList.push_back(studentName);
        cout << "Student \"" << studentName << "\" has been added to the merit list.\n";
    }

    void editMeritList() {
        if (meritList.empty()) {
            cout << "\nMerit list is empty! Nothing to edit.\n";
            return;
        }

        displayMeritList();
        int index;
        cout << "Enter the number of the student you want to edit: ";
        cin >> index;

        if (index < 1 || index > meritList.size()) {
            cout << "Invalid choice! Try again.\n";
            return;
        }

        string newName;
        cout << "Enter the new name for student " << index << ": ";
        cin.ignore();
        getline(cin, newName);
        meritList[index - 1] = newName;
        cout << "Student's name has been updated successfully!\n";
    }

    void displayMenuMeritList() const {
        displayMeritList();
    }

    void deleteMeritList() {
        if (meritList.empty()) {
            cout << "\nMerit list is empty! Nothing to delete.\n";
            return;
        }

        displayMeritList();
        int index;
        cout << "Enter the number of the student to delete: ";
        cin >> index;

        if (index < 1 || index > meritList.size()) {
            cout << "Invalid choice! Try again.\n";
            return;
        }

        cout << "Student \"" << meritList[index - 1] << "\" has been removed from the merit list.\n";
        meritList.erase(meritList.begin() + index - 1);
    }

    void addNewStudent(const Student& student) {
        newStudents.push_back(student);
    }

    void addCBTTestScore(const string& studentName, int score) {
        cbtTestScores.emplace_back(studentName, score);
    }

    void admissionMenu() {
        int choice;
        do {
            cout << "\n===== ADMISSION MANAGEMENT MENU =====\n";
            cout << "1. Add Merit List\n";
            cout << "2. Edit Merit List\n";
            cout << "3. Display Merit List\n";
            cout << "4. Delete Merit List\n";
            cout << "5. Display New Students\n";
            cout << "6. Display All CBT Tests Scores\n";
            cout << "7. Back To Main Menu\n";
            cout << "======================================\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                addMeritList();
                break;
            case 2:
                editMeritList();
                break;
            case 3:
                displayMenuMeritList();
                break;
            case 4:
                deleteMeritList();
                break;
            case 5:
                displayNewStudents();
                break;
            case 6:
                displayCBTTestScores();
                break;
            case 7:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 7);
    }
};

// ======================== Main Program ========================

int main() {
    UserManagement um;
    CourseManagement cm;
    AdmissionManagement am;
    TeacherPortal teacher;
    CourseTeacher cteacher;
    CourseStudent student;
    CourseAdmin admin;
    int choice;

    int mainChoice;
    do {
        cout << "\n=========== MAIN MENU ===========\n";
        cout << "1. Admin Panel\n";
        cout << "2. Student Admission Portal\n";
        cout << "3. Teacher Portal\n";
        cout << "4. Short Courses Portal\n";
        cout << "5. Exit Program\n";
        cout << "================================\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
        case 1: {
            int adminChoice;
            do {
                cout << "\n===== ADMIN PANEL =====\n";
                cout << "1. User Management\n";
                cout << "2. Course Management\n";
                cout << "3. Admission Management\n";
                cout << "4. Back to Main Menu\n";
                cout << "========================\n";
                cout << "Enter your choice: ";
                cin >> adminChoice;

                switch (adminChoice) {
                case 1:
                    um.userManagementMenu();
                    break;
                case 2:
                    cm.courseManagementMenu();
                    break;
                case 3:
                    am.admissionMenu();
                    break;
                case 4:
                    cout << "Returning to Main Menu...\n";
                    break;
                default:
                    cout << "Invalid choice! Please try again.\n";
                }
            } while (adminChoice != 4);
            break;
        }
        case 2:
            // Add functionality to register new students and record their CBT test scores
        {
            string name, contact;
            cout << "\nEnter Student Name: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter Contact: ";
            getline(cin, contact);

            Student student(name, 1000 + rand() % 9000, contact); // Generate a random ID for new student
            am.addNewStudent(student);

            int score;
            cout << "Enter CBT Test Score: ";
            cin >> score;

            am.addCBTTestScore(name, score);
            cout << "Student registered and test score recorded successfully!\n";
        }
        break;
        case 3:
            teacher.run();
        case 4:
            cteacher.dashboard();
            do {
                displayMainMenu();
                cin >> choice;
                cin.ignore(); // Clear newline left in the buffer

                switch (choice) {
                case 1:
                    handleTeacher(teacher);
                    break;
                case 2:
                    handleStudent(student, teacher);
                    break;
                case 3:
                    handleAdmin(admin);
                    break;
                case 4:
                    cout << "Exiting Course Portal. Goodbye!\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                }
            } while (choice != 4);

            return 0;
        }

        // Function to Display Main Menu
        void displayMainMenu() {
            cout << "--- COURSE PORTAL ---\n";
            cout << "1. Enter as Teacher\n";
            cout << "2. Enter as Student\n";
            cout << "3. Admin Panel\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
        }

        // Function to Handle Teacher Actions
        void handleTeacher(Teacher& teacher) {
            int option;
            do {
                cout << "\n--- Teacher Menu ---\n";
                cout << "1. Login\n2. Registration\n3. Back to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> option;
                cin.ignore(); // Clear input buffer

                switch (option) {
                case 1:
                    if (teacher.login())
                        teacher.dashboard();
                    break;
                case 2:
                    teacher.registerUser();
                    break;
                case 3:
                    cout << "Returning to Main Menu...\n";
                    break;
                default:
                    cout << "Invalid choice. Try again!\n";
                }
            } while (option != 3);
        }

        // Function to Handle Student Actions
        void handleStudent(Student& student, Teacher& teacher) {
            int option;
            do {
                cout << "\n--- Student Menu ---\n";
                cout << "1. Login\n2. Registration\n3. Back to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> option;
                cin.ignore(); // Clear input buffer

                switch (option) {
                case 1:
                    if (student.login())
                        student.dashboard(teacher);
                    break;
                case 2:
                    student.registerUser();
                    break;
                case 3:
                    cout << "Returning to Main Menu...\n";
                    break;
                default:
                    cout << "Invalid choice. Try again!\n";
                }
            } while (option != 3);
            break;
        case 5:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (mainChoice != 4);

    return 0;
}
