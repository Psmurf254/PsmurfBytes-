#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cstdlib> // For system("clear")

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

struct Student {
    std::string name;
    int age;
    std::string location;
    std::string course;
    int admissionNumber;
    int idNumber;
};

struct User {
    std::string username;
    int admissionNumber;
    int idNumber;
};

std::vector<Student> students;
std::vector<User> users;

bool isAdminRegistered = false; // Keep track if the admin is registered

// Function declarations
void clearScreen();
void saveAdminCredentials();
void loadAdminCredentials();
void registerAdmin();
bool authenticateAdmin();
void addStudent();
void viewAllStudents();
void searchStudent();
void modifyStudent();
void deleteStudent();
void saveDataToFile();
void loadDataFromFile();
void adminDashboard();
void studentDashboard(int studentIndex);
void displayTableHeader();
void displayTableRow(const Student& student);

// ANSI color codes for console text colors
const std::string ANSI_COLOR_RESET = "\033[0m";
const std::string ANSI_COLOR_YELLOW = "\033[93m";
const std::string ANSI_COLOR_GREEN = "\033[92m";
const std::string ANSI_COLOR_RED = "\033[91m";

void clearScreen() {
    system(CLEAR_COMMAND);
}

void saveAdminCredentials() {
    std::ofstream file("admin.txt");
    if (!file) {
        std::cout << "Error opening file for writing admin credentials.\n";
        return;
    }

    if (users.empty()) {
        file << "false";
    } else {
        file << "true\n";
        file << users[0].username << "\n";
        file << users[0].admissionNumber << "\n";
        file << users[0].idNumber;
    }
    file.close();
}

void loadAdminCredentials() {
    std::ifstream file("admin.txt");
    if (!file) {
        return;
    }

    std::string registered;
    file >> registered;

    if (registered == "true") {
        users.resize(1);
        file >> users[0].username >> users[0].admissionNumber >> users[0].idNumber;
        isAdminRegistered = true;
    }

    file.close();
}

void registerAdmin() {
    std::string username, password;
    std::cout << "Enter admin username: ";
    std::cin >> username;
    std::cout << "Enter admin password: ";
    std::cin >> password;

    
    users.push_back({username, -1, -1}); 
    isAdminRegistered = true;
    saveAdminCredentials();
    std::cout << "Admin registration successful!\n";
}

bool authenticateAdmin() {
    std::string username, password;
    std::cout << "Enter your username (admin): ";
    std::cin >> username;
    std::cout << "Enter your password: ";
    std::cin >> password;

    for (const auto& user : users) {
        if (user.username == username) {
            return true;
        }
    }
    return false;
}

void addStudent() {
    Student newStudent;
    std::cout << "\nEnter student name: ";
    std::cin.ignore();
    std::getline(std::cin, newStudent.name);
    std::cout << "Enter student age: ";
    std::cin >> newStudent.age;
    std::cout << "Enter student location: ";
    std::cin.ignore();
    std::getline(std::cin, newStudent.location);
    std::cout << "Enter student course: ";
    std::getline(std::cin, newStudent.course);
    std::cout << "Enter student admission number: ";
    std::cin >> newStudent.admissionNumber;
    std::cout << "Enter student ID number: ";
    std::cin >> newStudent.idNumber;

    students.push_back(newStudent);

    std::cout << "\nStudent added successfully!\n";

    
    saveDataToFile();
}

void displayTableHeader() {
    std::cout << std::setw(5) << ANSI_COLOR_YELLOW << "ID" << ANSI_COLOR_RESET;
    std::cout << std::setw(25) << ANSI_COLOR_YELLOW << "Name" << ANSI_COLOR_RESET;
    std::cout << std::setw(10) << ANSI_COLOR_YELLOW << "Age" << ANSI_COLOR_RESET;
    std::cout << std::setw(15) << ANSI_COLOR_YELLOW << "Location" << ANSI_COLOR_RESET;
    std::cout << std::setw(30) << ANSI_COLOR_YELLOW << "Course" << ANSI_COLOR_RESET;
    std::cout << std::setw(15) << ANSI_COLOR_YELLOW << "Admission No" << ANSI_COLOR_RESET;
    std::cout << std::setw(10) << ANSI_COLOR_YELLOW << "ID No" << ANSI_COLOR_RESET << "\n";
}

void displayTableRow(const Student& student) {
    std::cout << std::setw(5) << student.admissionNumber;
    std::cout << std::setw(25) << student.name;
    std::cout << std::setw(10) << student.age;
    std::cout << std::setw(15) << student.location;
    std::cout << std::setw(30) << student.course;
    std::cout << std::setw(15) << student.admissionNumber;
    std::cout << std::setw(10) << student.idNumber << "\n";
}

void viewAllStudents() {
    clearScreen();
    std::cout << ANSI_COLOR_YELLOW << "\nAll Students\n";
    displayTableHeader();

    if (students.empty()) {
        std::cout << "No students found.\n";
    } else {
        for (const auto& student : students) {
            displayTableRow(student);
        }
    }

    // Pause after showing student details to give time for user to read output
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void searchStudent() {
    int admissionNumber;
    std::cout << "Enter student admission number to search: ";
    std::cin >> admissionNumber;

    for (const auto& student : students) {
        if (student.admissionNumber == admissionNumber) {
            clearScreen();
            std::cout << ANSI_COLOR_YELLOW << "\nStudent Details:\n";
            std::cout << ANSI_COLOR_RESET << "Name: " << student.name << "\n";
            std::cout << "Age: " << student.age << "\n";
            std::cout << "Location: " << student.location << "\n";
            std::cout << "Course: " << student.course << "\n";
            std::cout << "Admission Number: " << student.admissionNumber << "\n";
            std::cout << "ID Number: " << student.idNumber << "\n";

            // Pause after showing student details to give time for user to read output
            std::cout << "Press Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            return;
        }
    }
    std::cout << "Student with admission number " << admissionNumber << " not found.\n";

    // Pause after displaying the message to give time for user to read output
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void modifyStudent() {
    int admissionNumber;
    std::cout << "Enter student admission number to modify: ";
    std::cin >> admissionNumber;

    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].admissionNumber == admissionNumber) {
            clearScreen();
            std::cout << ANSI_COLOR_YELLOW << "\nCurrent Student Details:\n";
            std::cout << ANSI_COLOR_RESET << "Name: " << students[i].name << "\n";
            std::cout << "Age: " << students[i].age << "\n";
            std::cout << "Location: " << students[i].location << "\n";
            std::cout << "Course: " << students[i].course << "\n";
            std::cout << "Admission Number: " << students[i].admissionNumber << "\n";
            std::cout << "ID Number: " << students[i].idNumber << "\n";

            std::cout << "\nEnter new details:\n";
            std::cout << "Name: ";
            std::cin.ignore();
            std::getline(std::cin, students[i].name);
            std::cout << "Age: ";
            std::cin >> students[i].age;
            std::cout << "Location: ";
            std::cin.ignore();
            std::getline(std::cin, students[i].location);
            std::cout << "Course: ";
            std::getline(std::cin, students[i].course);
            std::cout << "Admission Number: ";
            std::cin >> students[i].admissionNumber;
            std::cout << "ID Number: ";
            std::cin >> students[i].idNumber;

            std::cout << "\nStudent details modified successfully!\n";

            // Save the updated list of students to the file after modification
            saveDataToFile();
            return;
        }
    }
    std::cout << "Student with admission number " << admissionNumber << " not found.\n";

    
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void deleteStudent() {
    int admissionNumber;
    std::cout << "Enter student admission number to delete: ";
    std::cin >> admissionNumber;

    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].admissionNumber == admissionNumber) {
            students.erase(students.begin() + i);
            std::cout << "Student with admission number " << admissionNumber << " deleted successfully.\n";

            
            saveDataToFile();
            return;
        }
    }
    std::cout << "Student with admission number " << admissionNumber << " not found.\n";

    // Pause after displaying the message to give time for user to read output
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void saveDataToFile() {
    std::ofstream file("students.txt");
    if (!file) {
        std::cout << "Error opening file for writing student data.\n";
        return;
    }

    file << students.size() << "\n";
    for (const auto& student : students) {
        file << student.name << "\n";
        file << student.age << "\n";
        file << student.location << "\n";
        file << student.course << "\n";
        file << student.admissionNumber << "\n";
        file << student.idNumber << "\n";
    }
    file.close();
}

void loadDataFromFile() {
    std::ifstream file("students.txt");
    if (!file) {
        return;
    }

    int numStudents;
    file >> numStudents;

    students.resize(numStudents);
    for (auto& student : students) {
        file.ignore(); // Ignore newline character left by previous extraction
        std::getline(file, student.name);
        file >> student.age;
        file.ignore(); // Ignore newline character left by previous extraction
        std::getline(file, student.location);
        std::getline(file, student.course);
        file >> student.admissionNumber;
        file >> student.idNumber;
    }
    file.close();
}

void adminDashboard() {
    int adminChoice;
    while (true) {
        clearScreen();
        std::cout << ANSI_COLOR_GREEN << "\nAdmin Dashboard\n";
        std::cout << ANSI_COLOR_RESET << "1. Add Student\n";
        std::cout << "2. View All Students\n";
        std::cout << "3. Search Student\n";
        std::cout << "4. Modify Student Details\n";
        std::cout << "5. Delete Student\n";
        std::cout << "6. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> adminChoice;

        switch (adminChoice) {
        case 1:
            addStudent();
            break;
        case 2:
            clearScreen();
            viewAllStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            modifyStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 6:
            return;
        default:
            clearScreen();
            std::cout << "Invalid choice. Please try again.\n";
        }

    
        std::cout << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }
}

void studentDashboard(int studentIndex) {
    clearScreen();
    std::cout << ANSI_COLOR_GREEN << "\nWelcome " << students[studentIndex].name << "!\n";
    std::cout << ANSI_COLOR_RESET << "Student Dashboard\n";
    std::cout << "Name: " << students[studentIndex].name << "\n";
    std::cout << "Age: " << students[studentIndex].age << "\n";
    std::cout << "Location: " << students[studentIndex].location << "\n";
    std::cout << "Course: " << students[studentIndex].course << "\n";
    std::cout << "Admission Number: " << students[studentIndex].admissionNumber << "\n";
    std::cout << "ID Number: " << students[studentIndex].idNumber << "\n";

    
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

int main() {
    loadAdminCredentials();
    loadDataFromFile(); // Load data from the file if it exists

    int choice;
    bool foundStudent = false;

    while (true) {
        clearScreen();
        std::cout << "Choose an option:\n";
        std::cout << "1. Admin Panel\n";
        std::cout << "2. Student Panel\n";
        std::cout << "3. Quit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            if (!isAdminRegistered) {
                clearScreen();
                std::cout << "Admin not registered. Register first!\n";
                registerAdmin();
            } else {
                if (authenticateAdmin()) {
                    adminDashboard();
                } else {
                    clearScreen();
                    std::cout << "Invalid admin credentials!\n";
                }
            }
            break;

        case 2: {
            int admissionNumber, idNumber;
            clearScreen();
            std::cout << "Enter your admission number: ";
            std::cin >> admissionNumber;
            std::cout << "Enter your ID number: ";
            std::cin >> idNumber;

            for (size_t i = 0; i < students.size(); ++i) {
                if (students[i].admissionNumber == admissionNumber && students[i].idNumber == idNumber) {
                    foundStudent = true;
                    studentDashboard(i);
                    break;
                }
            }

            if (!foundStudent) {
                clearScreen();
                std::cout << "Student with the given admission number and ID number not found.\n";
            }
            break;
        }

        case 3:
            clearScreen();
            std::cout << "Saving data and exiting...\n";
            saveDataToFile();
            saveAdminCredentials();
            return 0;

        default:
            clearScreen();
            std::cout << "Invalid choice. Please try again.\n";
        }

        
        std::cout << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }

    return 0;
}
