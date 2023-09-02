#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Student 
{
    std::string id;
    std::string name;
    std::string department;
};

struct Interview 
{
    std::string studentId;
    std::string date;
    std::string time;
    std::string panel;
};

void addStudent(const Student& student)
{
    std::ofstream file("students.txt", std::ios::app);
    if (!file) {
        std::cout << "Error opening file." << std::endl;
        return;
    }
    file << student.id << ',' << student.name << ',' << student.department << std::endl;
    std::cout << "Student added successfully." << std::endl;
    file.close();
}

void displayStudents()
{
    std::ifstream file("students.txt");
    if (!file)
    {
        std::cout << "Error opening file." << std::endl;
        return;
    }

    std::cout << "ID\tName\t\tDepartment" << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    std::string line;
    while (std::getline(file, line))
    {
        size_t commaPos1 = line.find(',');
        std::string id = line.substr(0, commaPos1);
        size_t commaPos2 = line.find(',', commaPos1 + 1);
        std::string name = line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1);
        std::string department = line.substr(commaPos2 + 1);

        std::cout << id << "\t" << name << "\t\t" << department << std::endl;
    }

    file.close();
}

void searchStudent(const std::string& id)
{
    std::ifstream file("students.txt");
    if (!file)
    {
        std::cout << "Error opening file." << std::endl;
        return;
    }

    std::string line;
    bool studentFound = false;
    while (std::getline(file, line))
    {
        size_t commaPos1 = line.find(',');
        std::string currentId = line.substr(0, commaPos1);

        if (currentId == id)
        {
            size_t commaPos2 = line.find(',', commaPos1 + 1);
            std::string name = line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1);
            std::string department = line.substr(commaPos2 + 1);

            std::cout << "ID: " << id << std::endl;
            std::cout << "Name: " << name << std::endl;
            std::cout << "Department: " << department << std::endl;

            studentFound = true;
            break;
        }
    }

    if (!studentFound)
    {
        std::cout << "Student not found." << std::endl;
    }

    file.close();
}

void modifyStudent(const std::string& id)
{
    std::ifstream inputFile("students.txt");
    std::ofstream outputFile("temp.txt");
    if (!inputFile || !outputFile)
    {
        std::cout << "Error opening file." << std::endl;
        return;
    }

    std::string line;
    bool studentFound = false;
    while (std::getline(inputFile, line))
    {
        size_t commaPos1 = line.find(',');
        std::string currentId = line.substr(0, commaPos1);

        if (currentId == id)
        {
            Student student;
            student.id = currentId;
            size_t commaPos2 = line.find(',', commaPos1 + 1);
            student.name = line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1);
            student.department = line.substr(commaPos2 + 1);

            std::cout << "Enter new name: ";
            std::cin.ignore(); // Clear newline character from buffer
            std::getline(std::cin, student.name);
            std::cout << "Enter new department: ";
            std::getline(std::cin, student.department);

            outputFile << student.id << ',' << student.name << ',' << student.department << std::endl;
            std::cout << "Student modified successfully." << std::endl;
            studentFound = true;
        } else
        {
            outputFile << line << std::endl;
        }
    }

    if (!studentFound)
    {
        std::cout << "Student not found." << std::endl;
    }

    inputFile.close();
    outputFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");
}

void deleteInterviews(const std::string& studentId)
{
    std::ifstream inputFile("interviews.txt");
    std::ofstream outputFile("temp.txt");
    if (!inputFile || !outputFile)
    {
        std::cout << "Error opening file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        size_t commaPos1 = line.find(',');
        std::string currentStudentId = line.substr(0, commaPos1);

        if (currentStudentId != studentId)
        {
            outputFile << line << std::endl;
        }
    }

    inputFile.close();
    outputFile.close();

    remove("interviews.txt");
    rename("temp.txt", "interviews.txt");
}

void deleteStudent(const std::string& id)
{
    std::ifstream inputFile("students.txt");
    std::ofstream outputFile("temp.txt");
    if (!inputFile || !outputFile)
    {
        std::cout << "Error opening file." << std::endl;
        return;
    }

    std::string line;
    bool studentFound = false;
    while (std::getline(inputFile, line))
    {
        size_t commaPos1 = line.find(',');
        std::string currentId = line.substr(0, commaPos1);

        if (currentId != id)
        {
            outputFile << line << std::endl;
        } else
        {
            studentFound = true;
        }
    }

    inputFile.close();
    outputFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (studentFound)
    {
        std::cout << "Student deleted successfully." << std::endl;
        deleteInterviews(id);
    } else {
        std::cout << "Student not found." << std::endl;
    }
}

void scheduleInterview(const std::string& id)
{
    std::ifstream inputFile("students.txt");
    if (!inputFile)
    {
        std::cout << "Error opening file." << std::endl;
        return;
    }

    std::string line;
    bool studentFound = false;
    while (std::getline(inputFile, line))
    {
        size_t commaPos1 = line.find(',');
        std::string currentId = line.substr(0, commaPos1);

        if (currentId == id)
        {
            Student student;
            student.id = currentId;
            size_t commaPos2 = line.find(',', commaPos1 + 1);
            student.name = line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1);
            student.department = line.substr(commaPos2 + 1);

            std::cin.ignore(); // Clear newline character from buffer

            Interview interview;
            interview.studentId = student.id;

            std::cout << "Enter interview date: ";
            std::getline(std::cin, interview.date);
            std::cout << "Enter interview time: ";
            std::getline(std::cin, interview.time);
            std::cout << "Enter interview panel: ";
            std::getline(std::cin, interview.panel);

            std::ofstream file("interviews.txt", std::ios::app);
            if (!file)
            {
                std::cout << "Error opening file." << std::endl;
                return;
            }

     file << interview.studentId << ',' << interview.date << ',' << interview.time << ',' << interview.panel << std::endl;
            std::cout << "Interview scheduled successfully." << std::endl;

            file.close();

            studentFound = true;
            break;
        }
    }

    if (!studentFound)
    {
        std::cout << "Student not found." << std::endl;
    }

    inputFile.close();
}

void displayInterviews()
{
    std::ifstream file("interviews.txt");
    if (!file)
    {
        std::cout << "Error opening file." << std::endl;
        return;
    }

    std::cout << "ID\tDate\t\tTime\t\tPanel" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    std::string line;
    bool interviewFound = false;
    while (std::getline(file, line))
    {
        size_t commaPos1 = line.find(',');
        std::string studentId = line.substr(0, commaPos1);
        size_t commaPos2 = line.find(',', commaPos1 + 1);
        std::string date = line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1);
        size_t commaPos3 = line.find(',', commaPos2 + 1);
        std::string time = line.substr(commaPos2 + 1, commaPos3 - commaPos2 - 1);
        std::string panel = line.substr(commaPos3 + 1);

        // Check if the student with this ID exists
        std::ifstream studentFile("students.txt");
        bool studentExists = false;
        std::string studentLine;
        while (std::getline(studentFile, studentLine))
        {
            size_t studentCommaPos = studentLine.find(',');
            std::string studentIdFromFile = studentLine.substr(0, studentCommaPos);

            if (studentIdFromFile == studentId)
            {
                studentExists = true;
                break;
            }
        }
        studentFile.close();

        if (studentExists)
        {
            std::cout << studentId << "\t" << date << "\t" << time << "\t" << panel << std::endl;
            interviewFound = true;
        }
    }

    file.close();

    if (!interviewFound)
    {
        std::cout << "No interviews scheduled." << std::endl;
    }
}

int main()
{
    int choice;
    std::string id;

    do
    {
        std::cout << "========== Placement Management System ==========" << std::endl;
        std::cout << "1. Add Student" << std::endl;
        std::cout << "2. Display Students" << std::endl;
        std::cout << "3. Search Student" << std::endl;
        std::cout << "4. Modify Student" << std::endl;
        std::cout << "5. Delete Student" << std::endl;
        std::cout << "6. Schedule Interview" << std::endl;
        std::cout << "7. Display Interviews" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
            case 1:
            {
                Student student;
                std::cout << "Enter ID: ";
                std::cin >> student.id;
                std::cin.ignore();
                std::cout << "Enter Name: ";
                std::getline(std::cin, student.name);
                std::cout << "Enter Department: ";
                std::getline(std::cin, student.department);
                addStudent(student);
                break;
            }
            case 2:
            {
                displayStudents();
                break;
            }
            case 3:
            {
                std::cout << "Enter ID to search: ";
                std::cin >> id;
                searchStudent(id);
                break;
            }
            case 4:
            {
                std::cout << "Enter ID to modify: ";
                std::cin >> id;
                modifyStudent(id);
                break;
            }
            case 5:
            {
                std::cout << "Enter ID to delete: ";
                std::cin >> id;
                deleteStudent(id);
                break;
            }
            case 6:
            {
                std::cout << "Enter ID to schedule interview: ";
                std::cin >> id;
                scheduleInterview(id);
                break;
            }
            case 7:
            {
                displayInterviews();
                break;
            }
            case 0:
            {
                std::cout << "Exiting the program." << std::endl;
                break;
            }
            default:
            {
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }
std::cout << std::endl;
    } 
    while (choice != 0);

    return 0;
}
