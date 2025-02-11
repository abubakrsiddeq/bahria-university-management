#include <iostream>
#include <vector>
#include <string>
#include <conio.h> // For _getch()
#include <iomanip>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <fstream>
using namespace std;



// ======================== User Management ========================

class User {
protected:
    string name;
    int id;
    string contact;

    //for teacher and students
    string username;
    string password;

public:
   
    User(string name, int id, string contact)
        : name(name), id(id), contact(contact) {}

    //for teacher and students
    User(string username, string password) : username(username), password(password) {}
    bool login(string uname, string pwd) {
        return (username == uname && password == pwd);
    }
    string getUsername() const {
        return username;
    }

    void setUsername(string newUsername) {
        username = newUsername;
    }

    void setPassword(string newPassword) {
        password = newPassword;
    }
    //--------------------------------

    virtual void displayDetails() const {
        cout << left << setw(10) << id << setw(20) << name << setw(15) << contact;
    }

    int getID() const { return id; }
    string getName() const { return name; }

    virtual ~User() = default;
};

//----------------teacher class----------------
class Teacher : public User {
    static int enrollmentCounter;
    int enrollmentNumber;
    vector<string> lectures;
    vector<string> assignments;
    vector<string> quizzes;

public:
    Teacher(string username, string password)
        : User(username, password), enrollmentNumber(++enrollmentCounter) {}

    int getEnrollmentNumber() const {
        return enrollmentNumber;
    }

    void viewProfile() {
        cout << "\nTeacher Profile\n";
        cout << "Username: " << username << endl;
        cout << "Enrollment Number: " << enrollmentNumber << endl;
    }

    void dashboard() {
        int choice;
        do {
            cout << "\nTeacher Dashboard\n";
            cout << "1. View Profile\n2. Add Lecture\n3. Add Assignment\n4. Add Quiz\n5. Edit or Remove Item\n6. View Profile\n7. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
			case 1: viewProfile(); break;
            case 2: {
                string lecture;
                cout << "Enter Lecture: ";
                cin.ignore();
                getline(cin, lecture);
                lectures.push_back(lecture);
                break;
            }
            case 3: {
                string assignment;
                cout << "Enter Assignment: ";
                cin.ignore();
                getline(cin, assignment);
                assignments.push_back(assignment);
                break;
            }
            case 4: {
                string quiz;
                cout << "Enter Quiz: ";
                cin.ignore();
                getline(cin, quiz);
                quizzes.push_back(quiz);
                break;
            }
            case 5: {
                int subChoice;
                cout << "\nEdit or Remove\n1. Lectures\n2. Assignments\n3. Quizzes\nEnter choice: ";
                cin >> subChoice;
                vector<string>* selectedList = nullptr;
                switch (subChoice) {
                case 1:
                    selectedList = &lectures;
                    break;
                case 2:
                    selectedList = &assignments;
                    break;
                case 3:
                    selectedList = &quizzes;
                    break;
                default:
                    cout << "Invalid choice!\n";
                }
                if (selectedList) {
                    cout << "\nItems:\n";
                    for (size_t i = 0; i < selectedList->size(); ++i)
                        cout << i + 1 << ". " << (*selectedList)[i] << endl;

                    int index;
                    cout << "Enter item number to edit or remove (0 to cancel): ";
                    cin >> index;
                    if (index > 0 && index <= selectedList->size()) {
                        cout << "1. Edit\n2. Remove\nEnter choice: ";
                        int action;
                        cin >> action;
                        if (action == 1) {
                            cout << "Enter new value: ";
                            cin.ignore();
                            string newValue;
                            getline(cin, newValue);
                            (*selectedList)[index - 1] = newValue;
                        }
                        else if (action == 2) {
                            selectedList->erase(selectedList->begin() + index - 1);
                        }
                        else {
                            cout << "Invalid action!\n";
                        }
                    }
                    else {
                        cout << "Invalid item number!\n";
                    }
                }
                break;
            }
            case 6:
                viewProfile();
                break;
            case 7:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice!\n";
            }
        } while (choice != 7);
    }

    const vector<string>& getLectures() const { return lectures; }
    const vector<string>& getAssignments() const { return assignments; }
    const vector<string>& getQuizzes() const { return quizzes; }
};

int Teacher::enrollmentCounter = 1110;

//==================== E Library System ====================

// E-Book class
class EBook_ELib {
private:
    string title_ELib;
    string author_ELib;
    string contentFileName_ELib;
    int serialNumber_ELib;

public:
    EBook_ELib(string t, string a, int sn) : title_ELib(t), author_ELib(a), serialNumber_ELib(sn) {
        contentFileName_ELib = title_ELib;
        for (auto& c : contentFileName_ELib) {
            if (!isalnum(c)) {
                c = '_';
            }
        }
        contentFileName_ELib += ".txt";
    }

    string getTitle_ELib() const { return title_ELib; }
    string getAuthor_ELib() const { return author_ELib; }
    string getContentFileName_ELib() const { return contentFileName_ELib; }
    int getSerialNumber_ELib() const { return serialNumber_ELib; }

    void displayInfo_ELib() const {
        cout << "Serial Number: " << serialNumber_ELib << ", Title: " << title_ELib << ", Author: " << author_ELib << endl;
    }

    void saveToFile_ELib(ofstream& outFile) const {
        outFile << title_ELib << "|" << author_ELib << "|" << serialNumber_ELib << endl;
    }

    static EBook_ELib loadFromFile_ELib(ifstream& inFile) {
        string title_ELib, author_ELib;
        int serialNumber_ELib;
        getline(inFile, title_ELib, '|');
        getline(inFile, author_ELib, '|');
        inFile >> serialNumber_ELib;
        inFile.ignore();
        return EBook_ELib(title_ELib, author_ELib, serialNumber_ELib);
    }

    void saveContentToFile_ELib(const string& content_ELib) const {
        ofstream contentFile_ELib(contentFileName_ELib);
        contentFile_ELib << content_ELib;
        contentFile_ELib.close();
    }

    void readContent_ELib() const {
        ifstream contentFile_ELib(contentFileName_ELib);
        if (!contentFile_ELib) {
            cout << "Content file not found.\n";
            return;
        }

        string line_ELib;
        while (getline(contentFile_ELib, line_ELib)) {
            cout << line_ELib << endl;
        }
    }
};

// E-Library class
class ELibrary_ELib {
private:
    vector<EBook_ELib> books_ELib;
    unordered_map<string, vector<string>> downloadedBooks_ELib; // Maps student IDs to downloaded book titles
    int nextSerialNumber_ELib = 1;

public:
    ELibrary_ELib() {
        loadBooksFromFile_ELib();
        loadDownloadedBooksFromFile_ELib();
    }

    void addBook_ELib(const string& title_ELib, const string& author_ELib, const string& content_ELib) {
        for (const auto& book_ELib : books_ELib) {
            if (book_ELib.getTitle_ELib() == title_ELib && book_ELib.getAuthor_ELib() == author_ELib) {
                cout << "The book with the same title and author already exists.\n";
                return;
            }
        }

        EBook_ELib newBook_ELib(title_ELib, author_ELib, nextSerialNumber_ELib++);
        books_ELib.push_back(newBook_ELib);
        newBook_ELib.saveContentToFile_ELib(content_ELib);
        cout << "Book and content added successfully with serial number " << newBook_ELib.getSerialNumber_ELib() << "!\n";
        saveBooksToFile_ELib();
    }

    void deleteBook_ELib(int serialNumber_ELib) {
        for (auto it = books_ELib.begin(); it != books_ELib.end(); ++it) {
            if (it->getSerialNumber_ELib() == serialNumber_ELib) {
                books_ELib.erase(it);
                cout << "Book deleted successfully!\n";
                saveBooksToFile_ELib();
                return;
            }
        }
        cout << "Book not found!\n";
    }

    void updateBook_ELib(int serialNumber_ELib) {
        for (auto& book_ELib : books_ELib) {
            if (book_ELib.getSerialNumber_ELib() == serialNumber_ELib) {
                string newTitle_ELib, newAuthor_ELib, newContent_ELib;
                cout << "Enter new title: ";
                cin.ignore();
                getline(cin, newTitle_ELib);
                cout << "Enter new author: ";
                getline(cin, newAuthor_ELib);
                cout << "Enter new content: ";
                getline(cin, newContent_ELib);
                book_ELib = EBook_ELib(newTitle_ELib, newAuthor_ELib, book_ELib.getSerialNumber_ELib());
                book_ELib.saveContentToFile_ELib(newContent_ELib);
                cout << "Book updated successfully!\n";
                saveBooksToFile_ELib();
                return;
            }
        }
        cout << "Book not found!\n";
    }

    void viewBooks_ELib() const {
        if (books_ELib.empty()) {
            cout << "No books available in the library.\n";
            return;
        }

        cout << "\nAvailable Books:\n";
        for (const auto& book_ELib : books_ELib) {
            book_ELib.displayInfo_ELib();
        }
    }

    void downloadBook_ELib(int serialNumber_ELib, const string& studentID_ELib) {
        for (const auto& book_ELib : books_ELib) {
            if (book_ELib.getSerialNumber_ELib() == serialNumber_ELib) {
                auto& studentBooks_ELib = downloadedBooks_ELib[studentID_ELib];
                if (find(studentBooks_ELib.begin(), studentBooks_ELib.end(), book_ELib.getTitle_ELib()) != studentBooks_ELib.end()) {
                    cout << "You have already downloaded '" << book_ELib.getTitle_ELib() << "'.\n";
                    return;
                }
                studentBooks_ELib.push_back(book_ELib.getTitle_ELib());
                cout << "You have successfully downloaded '" << book_ELib.getTitle_ELib() << "'.\n";
                saveDownloadedBooksToFile_ELib();
                return;
            }
        }
        cout << "Book not found!\n";
    }

    void viewDownloadedBooks_ELib(const string& studentID_ELib) const {
        auto it_ELib = downloadedBooks_ELib.find(studentID_ELib);
        if (it_ELib == downloadedBooks_ELib.end() || it_ELib->second.empty()) {
            cout << "No books downloaded by you.\n";
            return;
        }

        cout << "\nBooks downloaded by you:\n";
        for (const auto& title_ELib : it_ELib->second) {
            for (const auto& book_ELib : books_ELib) {
                if (book_ELib.getTitle_ELib() == title_ELib) {
                    cout << "  Serial Number: " << book_ELib.getSerialNumber_ELib() <<
                        "- Title: " << book_ELib.getTitle_ELib()
                        << ", Author: " << book_ELib.getAuthor_ELib() << endl;
                }
            }
        }

        int SN_ELib;
        cout << "\nEnter the Serial Number of the book you want to read: ";
        cin.ignore();
        cin >> SN_ELib;

        for (const auto& book_ELib : books_ELib) {
            if (book_ELib.getSerialNumber_ELib() == SN_ELib) {
                book_ELib.readContent_ELib();
                return;
            }
        }

        cout << "Book not found in your downloaded books.\n";
    }

    void viewAllDownloadedBooks_ELib() const {
        if (downloadedBooks_ELib.empty()) {
            cout << "No books have been downloaded by any students.\n";
            return;
        }

        cout << "\nDownloaded Books by Students:\n";
        for (const auto& pair_ELib : downloadedBooks_ELib) {
            string studentName_ELib = pair_ELib.first;
            string studentID_ELib = " " + studentName_ELib; // Assuming student ID is derived from the name for simplicity.

            cout << "\nStudent: " << studentName_ELib << ", ID: " << studentID_ELib << "\n";
            for (const auto& title_ELib : pair_ELib.second) {
                for (const auto& book_ELib : books_ELib) {
                    if (book_ELib.getTitle_ELib() == title_ELib) {
                        cout << "- Book Title: " << book_ELib.getTitle_ELib()
                            << ", Serial Number: " << book_ELib.getSerialNumber_ELib()
                            << ", Author: " << book_ELib.getAuthor_ELib() << endl;
                    }
                }
            }
        }
    }

private:
    void saveBooksToFile_ELib() const {
        ofstream outFile_ELib("books_ELib.txt");
        for (const auto& book_ELib : books_ELib) {
            book_ELib.saveToFile_ELib(outFile_ELib);
        }
    }

    void loadBooksFromFile_ELib() {
        ifstream inFile_ELib("books_ELib.txt");
        while (inFile_ELib.peek() != EOF) {
            books_ELib.push_back(EBook_ELib::loadFromFile_ELib(inFile_ELib));
        }
    }

    void saveDownloadedBooksToFile_ELib() const {
        ofstream outFile_ELib("downloaded_books_ELib.txt");
        for (const auto& pair_ELib : downloadedBooks_ELib) {
            outFile_ELib << pair_ELib.first << endl;
            for (const auto& title_ELib : pair_ELib.second) {
                outFile_ELib << title_ELib << endl;
            }
        }
    }

    void loadDownloadedBooksFromFile_ELib() {
        ifstream inFile_ELib("downloaded_books_ELib.txt");
        string studentID_ELib, bookTitle_ELib;
        while (getline(inFile_ELib, studentID_ELib)) {
            vector<string> titles_ELib;
            while (getline(inFile_ELib, bookTitle_ELib) && !bookTitle_ELib.empty()) {
                titles_ELib.push_back(bookTitle_ELib);
            }
            downloadedBooks_ELib[studentID_ELib] = titles_ELib;
        }
    }
};

// E-Admin class
class EAdmin_ELib {
public:
    void adminPanel_ELib(ELibrary_ELib& library_ELib) {
        int choice_ELib;
        do {
            cout << "\n--- E Library Management ---\n";
            cout << "1. Add Book\n";
            cout << "2. View Books\n";
            cout << "3. Delete Book\n";
            cout << "4. Update Book\n";
            cout << "5. View Downloaded Books\n";
            cout << "6. Back to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> choice_ELib;

            switch (choice_ELib) {
            case 1: {
                string title_ELib, author_ELib, content_ELib;
                cin.ignore();
                cout << "Enter book title: ";
                getline(cin, title_ELib);
                cout << "Enter book author: ";
                getline(cin, author_ELib);
                cout << "Enter content for the book: ";
                getline(cin, content_ELib);
                library_ELib.addBook_ELib(title_ELib, author_ELib, content_ELib);
                break;
            }
            case 2:
                library_ELib.viewBooks_ELib();
                break;
            case 3: {
                int serialNumber_ELib;
                cout << "Enter the serial number of the book to delete: ";
                cin >> serialNumber_ELib;
                library_ELib.deleteBook_ELib(serialNumber_ELib);
                break;
            }
            case 4: {
                int serialNumber_ELib;
                cout << "Enter the serial number of the book to update: ";
                cin >> serialNumber_ELib;
                library_ELib.updateBook_ELib(serialNumber_ELib);
                break;
            }
            case 5:
                library_ELib.viewAllDownloadedBooks_ELib();
                break;
            case 6:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
            }
        } while (choice_ELib != 6);
    }
};

// E-Student class
class EStudent_ELib {
public:
    void studentPanel_ELib(ELibrary_ELib& library_ELib) {
        int choice_ELib;
        string studentID_ELib;
        string studentName_ELib;
        cin.ignore();
        cout << "Enter your university ID: ";
        getline(cin, studentID_ELib);
        cout << "Enter your Name: ";
        getline(cin, studentName_ELib);

        do {
            cout << "\n--- E Library Portal ---\n";
            cout << "1. Download Book\n";
            cout << "2. View Downloaded Books\n";
            cout << "3. View Available Books\n";
            cout << "4. Back to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> choice_ELib;

            switch (choice_ELib) {
            case 1: {
                int serialNumber_ELib;
                cout << "Enter the serial number of the book you want to download: ";
                cin >> serialNumber_ELib;
                library_ELib.downloadBook_ELib(serialNumber_ELib, studentID_ELib);
                break;
            }
            case 2:
                library_ELib.viewDownloadedBooks_ELib(studentID_ELib);
                break;
            case 3:
                library_ELib.viewBooks_ELib();
                break;
            case 4:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
            }
        } while (choice_ELib != 4);
    }
};

//=========================================================================================

//----------------student class----------------
class Student : public User {
    static int enrollmentCounter;
    int enrollmentNumber;
private:
    ELibrary_ELib library_ELib;
    EStudent_ELib student_ELib;
public:
    Student(string username, string password)
        : User(username, password), enrollmentNumber(++enrollmentCounter) {}

    int getEnrollmentNumber() const {
        return enrollmentNumber;
    }

    void viewProfile() {
        cout << "\nStudent Profile\n";
        cout << "Username: " << username << endl;
        cout << "Enrollment Number: " << enrollmentNumber << endl;
    }

    void dashboard() {
        const Teacher& teacher = Teacher("teacher", "password");
        cout << "\nStudent Dashboard\n";
        cout << "Welcome, " << username << "!\n\n";

        int choice;
        do {
            cout << "1. View Profile\n2. View Lectures\n3. View Assignments:\n4. View Quizzes:\n5. E Library\n6. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                viewProfile();
                break;
            case 2:
                cout << "\nLectures:\n";
                for (const auto& lecture : teacher.getLectures())
                    cout << "- " << lecture << endl;
                break;
            case 3:
                cout << "\nAssignments:\n";
                for (const auto& assignment : teacher.getAssignments())
                    cout << "- " << assignment << endl;
                break;
            case 4:
                cout << "\nQuizzes:\n";
                for (const auto& quiz : teacher.getQuizzes())
                    cout << "- " << quiz << endl;
                break;
            case 5:
                student_ELib.studentPanel_ELib(library_ELib);
                break;
            case 6:
                cout << "Logging out...\n";
                break;
            default:
                break;
            }
        } while (choice != 6);
    }
};

int Student::enrollmentCounter = 2000;
//---------------------------------------------------------------


// ======================== User Management ========================
class UserManagement {
private:
    vector<Teacher> teachers;
    vector<Student> students;

public:
    void addTeacher() {
        string username, password;
        cout << "Enter Teacher Username: ";
        cin >> username;
        cout << "Enter Teacher Password: ";
        cin >> password;
        Teacher teacher(username, password);
        teachers.push_back(teacher);
        cout << "Teacher added successfully! Enrollment Number: " << teacher.getEnrollmentNumber() << endl;
    }

    void addStudent() {
        string username, password;
        cout << "Enter Student Username: ";
        cin >> username;
        cout << "Enter Student Password: ";
        cin >> password;
        Student student(username, password);
        students.push_back(student);
        cout << "Student added successfully! Enrollment Number: " << student.getEnrollmentNumber() << endl;
    }

    Teacher* getTeacher(string username) {
        for (auto& teacher : teachers) {
            if (teacher.getUsername() == username) {
                return &teacher;
            }
        }
        return nullptr;
    }

    Student* getStudent(string username) {
        for (auto& student : students) {
            if (student.getUsername() == username) {
                return &student;
            }
        }
        return nullptr;
    }

    void editTeacherDetails() {
        string username;
        cout << "Enter Teacher Username to Edit: ";
        cin >> username;
        Teacher* teacher = getTeacher(username);
        if (teacher) {
            string newUsername, newPassword;
            cout << "Enter New Username: ";
            cin >> newUsername;
            cout << "Enter New Password: ";
            cin >> newPassword;
            teacher->setUsername(newUsername);
            teacher->setPassword(newPassword);
            cout << "Teacher details updated successfully!\n";
        }
        else {
            cout << "Teacher not found!\n";
        }
    }

    void editStudentDetails() {
        string username;
        cout << "Enter Student Username to Edit: ";
        cin >> username;
        Student* student = getStudent(username);
        if (student) {
            string newUsername, newPassword;
            cout << "Enter New Username: ";
            cin >> newUsername;
            cout << "Enter New Password: ";
            cin >> newPassword;
            student->setUsername(newUsername);
            student->setPassword(newPassword);
            cout << "Student details updated successfully!\n";
        }
        else {
            cout << "Student not found!\n";
        }
    }

    void userManagementMenu() {
        int choice;
        do {
            cout << "\n=== USER MANAGEMENT ===\n";
            cout << "1. Add New Student\n";
            cout << "2. Edit Student Details\n";
            cout << "3. Add New Teacher\n";
            cout << "4. Edit Teacher Details\n";
            cout << "5. View All Teachers\n";
            cout << "6. View All Students\n";
            cout << "7. Back To Admin Panel\n";
            cout << "========================\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: addStudent(); break;
            case 2: editStudentDetails(); break;
            case 3: addStudent(); break;
            case 4: editTeacherDetails(); break;
            case 5: {
                cout << "\nTeachers:\n";
                for (const auto& teacher : teachers) {
                    cout << "- Username: " << teacher.getUsername() << ", Enrollment: " << teacher.getEnrollmentNumber() << endl;
                }; break;
            }
            case 6: {
                cout << "\nStudents:\n";
                for (const auto& student : students) {
                    cout << "- Username: " << student.getUsername() << ", Enrollment: " << student.getEnrollmentNumber() << endl;
                }
            } break;
            case 7: cout << "Returning to Admin Panel...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
            }
        } while (choice != 7);
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

// NewStudent class definition
class NewStudent {
public:
    string name;
    string fatherName;
    string cnic;
    string homeAddress;
    float sscMarks;
    float hsscMarks;
    string username;
    string password;
    int registeredNumber;

    NewStudent() = default;

    NewStudent(const string& name, const string& fatherName, const string& cnic, const string& homeAddress, float sscMarks, float hsscMarks, const string& username, const string& password, int registeredNumber)
        : name(name), fatherName(fatherName), cnic(cnic), homeAddress(homeAddress), sscMarks(sscMarks), hsscMarks(hsscMarks), username(username), password(password), registeredNumber(registeredNumber) {}

    void displayDetails() const {
        cout << left << setw(10) << registeredNumber << setw(20) << name << setw(15) << cnic << "Pass-out\n";
    }

    void viewProfile() const {
        cout << "\n--- Profile Information ---\n";
        cout << "Name: " << name << "\n";
        cout << "Father's Name: " << fatherName << "\n";
        cout << "CNIC: " << cnic << "\n";
        cout << "Home Address: " << homeAddress << "\n";
        cout << "SSC Marks: " << sscMarks << "\n";
        cout << "HSSC Marks: " << hsscMarks << "\n";
        cout << "Username: " << username << "\n";
        cout << "Registered Number: " << registeredNumber << "\n";
    }
};

// AdmissionManagement class definition
class AdmissionManagement {
private:
    vector<string> meritList;
    vector<NewStudent> newStudents; // To store new students
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

    void addNewStudent(const NewStudent& student) {
        newStudents.push_back(student);
    }

    void addCBTTestScore(const string& studentName, int score) {
        cbtTestScores.emplace_back(studentName, score);
    }

    void deleteRegisteredStudent(int registeredNumber) {
        auto it = remove_if(newStudents.begin(), newStudents.end(), [registeredNumber](const NewStudent& student) {
            return student.registeredNumber == registeredNumber;
            });

        if (it != newStudents.end()) {
            newStudents.erase(it, newStudents.end());
            cout << "Student with registered number " << registeredNumber << " has been deleted.\n";
        }
        else {
            cout << "Student with registered number " << registeredNumber << " not found.\n";
        }
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
            cout << "7. Delete Registered Student\n";
            cout << "8. Back To Main Menu\n";
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
                displayMeritList();
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
            case 7: {
                int registeredNumber;
                cout << "Enter the registered number of the student to delete: ";
                cin >> registeredNumber;
                deleteRegisteredStudent(registeredNumber);
                break;
            }
            case 8:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 8);
    }

    vector<string> getMeritList() const {
        return meritList;
    }
};

// NewStudentPortal class definition
class NewStudentPortal {
private:
    AdmissionManagement& adminMgmt; // Pass by reference to ensure data consistency
    map<string, NewStudent> studentDatabase;
    int studentCounter = 2220; // Starting registered number for students

    void registerStudent() {
        string name, fatherName, cnic, homeAddress, username, password;
        float sscMarks, hsscMarks;

        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter your father's name: ";
        getline(cin, fatherName);

        cout << "Enter your CNIC: ";
        getline(cin, cnic);

        cout << "Enter your home address: ";
        getline(cin, homeAddress);

        cout << "Enter your SSC Marks: ";
        cin >> sscMarks;

        cout << "Enter your HSSC Marks: ";
        cin >> hsscMarks;

        cout << "Set your username: ";
        cin.ignore();
        getline(cin, username);

        cout << "Set your password: ";
        getline(cin, password);

        NewStudent newStudent(name, fatherName, cnic, homeAddress, sscMarks, hsscMarks, username, password, studentCounter++);
        studentDatabase[username] = newStudent;
        adminMgmt.addNewStudent(newStudent);

        cout << "Registration successful! Your registered number is: " << newStudent.registeredNumber << "\n";
    }

    // Function to input password securely
    string inputAPassword() {
        string password;
        char ch;

        // Loop to take character input securely
        while ((ch = _getch()) != '\r') { // '\r' is the Enter key
            if (ch == '\b' && !password.empty()) { // Handle Backspace
                password.pop_back();
                cout << "\b \b"; // Erase last asterisk from console
            }
            else if (ch != '\b') { // Add character to password
                password += ch;
                cout << '*'; // Display asterisk for security
            }
        }
        cout << endl;

        return password;
    }

    // Function to log in a student
    bool loginStudent(string& username) {
        string password;

        cout << "Enter username: ";
        cin.ignore();
        getline(cin, username);

        if (studentDatabase.find(username) == studentDatabase.end()) {
            cout << "Username not found!\n";
            return false;
        }

        cout << "Enter password: ";
        password = inputAPassword(); // Use secure password input

        if (studentDatabase[username].password != password) {
            cout << "Incorrect password!\n";
            return false;
        }

        return true;
    }

    void viewStudentProfile(const string& username) {
        if (studentDatabase.find(username) != studentDatabase.end()) {
            studentDatabase[username].viewProfile();
        }
        else {
            cout << "Profile not found!\n";
        }
    }

    void takeCBTTest(const string& username) {
        int score = 0;
        vector<pair<string, string>> questions = {
            {"What is the capital of France?", "Paris"},
            {"What is 2 + 2?", "4"},
            {"What is the color of the sky?", "Blue"},
            {"Who wrote 'Hamlet'?", "Shakespeare"},
            {"What is the boiling point of water?", "100"}
        };

        cout << "\n--- CBT Test ---\n";
        for (const auto& question : questions) {
            string answer;
            cout << question.first << "\n";
            cout << "Your answer: ";
            getline(cin, answer);
            if (answer == question.second) {
                ++score;
            }
        }

        adminMgmt.addCBTTestScore(username, score);
        cout << "CBT Test completed! Your score is: " << score << "/5\n";
    }

    void studentMenu(const string& username) {
        int choice;
        do {
            cout << "\n===== STUDENT MENU =====\n";
            cout << "1. View Profile\n";
            cout << "2. Take CBT Test\n";
            cout << "3. View Merit List\n";
            cout << "4. Logout\n";
            cout << "=========================\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                viewStudentProfile(username);
                break;
            case 2:
                takeCBTTest(username);
                break;
            case 3: {
                vector<string> meritList = adminMgmt.getMeritList();
                cout << "\n---- Merit List ----\n";
                for (size_t i = 0; i < meritList.size(); ++i) {
                    cout << i + 1 << ". " << meritList[i] << "\n";
                }
                cout << "----------------------\n";
                break;
            }
            case 4:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 4);
    }

public:
    NewStudentPortal(AdmissionManagement& adminMgmt) : adminMgmt(adminMgmt) {}

    void runPortal() {
        int studentChoice;
        cout << "\n===== STUDENT PANEL =====\n";
        cout << "1. Registration\n";
        cout << "2. Login\n";
        cout << "3. Back\n";
        cout << "=========================\n";
        cout << "Enter your choice: ";
        cin >> studentChoice;

        switch (studentChoice) {
        case 1:
            registerStudent();
            break;
        case 2: {
            string username;
            if (loginStudent(username)) {
                studentMenu(username);
            }
            break;
        }
        case 3:
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }

    }

};

//=========================================================================================


//===============Short Course Management System==================

class CourseUser {
protected:
    string email;
    string password;

public:
    virtual void courseregisterUser() = 0;   // Pure virtual function
    virtual bool courselogin() = 0;          // Pure virtual function
};

class CourseTeacher :public CourseUser {
private:
    string name;
    bool isLoggedIn = false;
    map<string, vector<string>> subjectDetails; // Store subjects with associated details
    const string fileName = "teacher_subjects.txt"; // File name for storing subject details
    const string teacherFileName = "teacher_details.txt"; // File name for storing teacher details
    const string studentFileName = "student_details.txt"; // File name for storing student details
    bool isSubjectDetailsLoaded = false;  // Track if subject details are loaded

public:
    void courseregisterUser() override {
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

    bool courselogin() override {
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
    void courseregisterUser() override {
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

    bool courselogin() override {
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

    void displayChosenSubjects(const CourseTeacher& courseteacher) {
        cout << "\n--- Your Subjects and Details ---\n";
        if (chosenSubjects.empty()) {
            cout << "No subjects chosen yet.\n";
            return;
        }

        if (!courseteacher.hasSubjectDetails()) {
            cout << "Teacher has not loaded subject details. Please try again later.\n";
            return;
        }

        const map<string, vector<string>>& courseteacherSubjects = courseteacher.getSubjectDetails();
        for (const string& subject : chosenSubjects) {
            if (courseteacherSubjects.find(subject) != courseteacherSubjects.end()) {
                cout << "\nSubject: " << subject << "\n";
                cout << "  - Topic: " << courseteacherSubjects.at(subject)[0] << "\n";
                cout << "  - Assignment: " << courseteacherSubjects.at(subject)[1] << "\n";
                cout << "  - Past Paper: " << courseteacherSubjects.at(subject)[2] << "\n";
                cout << "  - Quiz: " << courseteacherSubjects.at(subject)[3] << "\n";
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

    void dashboard(const CourseTeacher& courseteacher) {
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
                displayChosenSubjects(courseteacher);
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

// Admin Class for short courses
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

class CoursePortal {
public:
    // Constructor to initialize any necessary attributes (if any)
    CoursePortal() {}

    // Main menu function to display options
    void displayMainMenu() {
        cout << "--- COURSE PORTAL ---\n";
        cout << "1. Enter as Teacher\n";
        cout << "2. Enter as Student\n";
        cout << "3. Admin Panel\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
    }

    // Handle actions for all roles
    void handleActions() {
        int choice;
        do {
            displayMainMenu();
            cin >> choice;
            cin.ignore(); // Clear newline left in the buffer

            switch (choice) {
            case 1:
                handleTeacher();
                break;
            case 2:
                handleStudent();
                break;
            case 3:
                handleAdmin();
                break;
            case 4:
                cout << "Exiting Course Portal. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 4);
    }

private:
    // Teacher login and registration
    void handleTeacher() {
        int option;
        do {
            cout << "\n--- Teacher Menu ---\n";
            cout << "1. Login\n2. Registration\n3. Back to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> option;
            cin.ignore(); // Clear input buffer

            switch (option) {
            case 1:
                if (login("Teacher"))
                    teacherDashboard();
                break;
            case 2:
                registerUser("Teacher");
                break;
            case 3:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid choice. Try again!\n";
            }
        } while (option != 3);
    }

    // Student login and registration
    void handleStudent() {
        int option;
        do {
            cout << "\n--- Student Menu ---\n";
            cout << "1. Login\n2. Registration\n3. Back to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> option;
            cin.ignore(); // Clear input buffer

            switch (option) {
            case 1:
                if (login("Student"))
                    studentDashboard();
                break;
            case 2:
                registerUser("Student");
                break;
            case 3:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid choice. Try again!\n";
            }
        } while (option != 3);
    }

    // Admin login and panel access
    void handleAdmin() {
        int option;
        cout << "\n--- Admin Panel ---\n";
        cout << "1. Admin Login\n2. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;
        cin.ignore(); // Clear input buffer

        if (option == 1) {
            if (login("Admin"))
                adminPanel();
        }
        else {
            cout << "Exiting...\n";
        }
    }

    // Simulate login process for Teacher, Student, or Admin
    bool login(const string& userType) {
        string username, password;
        cout << "Enter " << userType << " Username: ";
        cin >> username;
        cout << "Enter " << userType << " Password: ";
        cin >> password;
        // In a real application, you would check against a database here
        cout << userType << " logged in successfully!\n";
        return true;
    }

    // Simulate registration process for Teacher or Student
    void registerUser(const string& userType) {
        string username, password;
        cout << "Enter " << userType << " Username: ";
        cin >> username;
        cout << "Enter " << userType << " Password: ";
        cin >> password;
        // In a real application, you would store the credentials
        cout << userType << " registered successfully!\n";
    }

    // Teacher dashboard (after successful login)
    void teacherDashboard() {
        cout << "Welcome to the Teacher Dashboard!\n";
        // Add teacher-specific functionalities here
    }

    // Student dashboard (after successful login)
    void studentDashboard() {
        cout << "Welcome to the Student Dashboard!\n";
        // Add student-specific functionalities here
    }

    // Admin panel (after successful login)
    void adminPanel() {
        cout << "Welcome to the Admin Panel!\n";
        // Add admin-specific functionalities like user management here
    }
};
// Function Prototypes
void displayMainMenu(CoursePortal);    // Displays the main menu for the CoursePortal
void handleTeacher(CourseTeacher);    // Handles teacher-related actions (login/registration)
void handleStudent(CourseStudent, CourseTeacher);    // Handles student-related actions (login/registration)
void handleAdmin(CourseAdmin);    // Handles admin-related actions (view teachers/students)
void displayTeacherMenu(CourseTeacher);    // Displays the teacher menu
void displayStudentMenu(CourseStudent, CourseTeacher);    // Displays the student menu
//----------------------------------------------------------------------------






//======================= ADMIN PANEL PASSWORD =======================
// Password verification function for admin panel
bool verifyPassword(const string& predefinedPassword) {
    string password;
    char ch;

    cout << "Enter Admin Password: ";

    // Loop to take character input securely
    while ((ch = _getch()) != '\r') { // '\r' is the Enter key
        if (ch == '\b' && !password.empty()) { // Handle Backspace
            password.pop_back();
            cout << "\b \b"; // Erase last asterisk from console
        }
        else if (ch != '\b') { // Add character to password
            password += ch;
            cout << '*'; // Display asterisk for security
        }
    }
    cout << endl;

    return password == predefinedPassword;
}
//=============================================================================

// Function to input password securely
string inputPassword() {
    string password;
    char ch;

    // Loop to take character input securely
    while ((ch = _getch()) != '\r') { // '\r' is the Enter key
        if (ch == '\b' && !password.empty()) { // Handle Backspace
            password.pop_back();
            cout << "\b \b"; // Erase last asterisk from console
        }
        else if (ch != '\b') { // Add character to password
            password += ch;
            cout << '*'; // Display asterisk for security
        }
    }
    cout << endl;

    return password;
}

// ======================== Main Program ========================

int main() {

	const string predefinedPassword = "admin123"; // Predefined password for admin panel

    UserManagement um;
    CourseManagement cm;
    CoursePortal portal;
    CourseTeacher cteacher;
    CourseStudent student;
    CourseAdmin admin;
    AdmissionManagement adminMgmt;
    NewStudentPortal studentPortal(adminMgmt);
    ELibrary_ELib library_ELib;
    EAdmin_ELib admin_ELib;
    EStudent_ELib student_ELib;


    int mainChoice;
    do {
        cout << "\n=========== MAIN MENU ===========\n";
        cout << "1. Admin Panel\n";
        cout << "2. Student Admission Portal\n";
        cout << "3. Teacher Portal\n";
        cout << "4. Student Portal\n";
        cout << "5. Short Courses Portal\n";
        cout << "6. Exit Program\n";
        cout << "================================\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
        case 1: {
            if (verifyPassword(predefinedPassword)) {
                int adminChoice;
                do {
                    cout << "\n===== ADMIN PANEL =====\n";
                    cout << "1. User Management\n";
                    cout << "2. Course Management\n";
                    cout << "3. Admission Management\n";
                    cout << "4. E Library Management\n";
                    cout << "5. Back to Main Menu\n";
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
                        adminMgmt.admissionMenu();
                        break;
                    case 4:
                        admin_ELib.adminPanel_ELib(library_ELib);
						break;
                    case 5:
                        cout << "Returning to Main Menu...\n";
                        break;
                    default:
                        cout << "Invalid choice! Please try again.\n";
                    }
                } while (adminChoice != 5);
            }
            else {
                cout << "Incorrect Password. Returning to Main Menu." << endl;
            }
            break;
            
        }
        case 2:
            studentPortal.runPortal();
			break;
        break;
		case 3:
		{
            string username, password;
            cout << "Enter Teacher Username: ";
            cin >> username;

            cout << "Enter Teacher Password: ";
            password = inputPassword(); // Use the existing inputPassword function

            // Assuming um is an instance of a class that manages teachers
            // and getTeacher is a method that retrieves a teacher by username
            Teacher* teacher = um.getTeacher(username);
            if (teacher && teacher->login(username, password)) {
                cout << "Teacher logged in successfully!" << endl;
                teacher->dashboard();
            }
            else {
                cout << "Invalid teacher credentials." << endl;
            }
		}
            break;
		case 4:
		{
			string username, password;
			cout << "Enter Student Username: ";
			cin >> username;
			cout << "Enter Student Password: ";
			password = inputPassword(); // Use the existing inputPassword function
			Student* student = um.getStudent(username);
			if (student && student->login(username, password)) {
				cout << "Student logged in successfully!" << endl;
                student->dashboard();  
			}
			else {
				cout << "Invalid student credentials." << endl;
			}
		}
		break;
             
        case 5:
            portal.handleActions();
            break;
        case 6:
            cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Try again!\n";
        }
    } while (mainChoice != 6);

    return 0;
}
