#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book {
    int bookID;
    string title;
    string author;
    bool isIssued;

public:
    Book(int id, string t, string a) : bookID(id), title(t), author(a), isIssued(false) {}

    void displayBook() {
        cout << "Book ID: " << bookID << "\nTitle: " << title << "\nAuthor: " << author 
             << "\nStatus: " << (isIssued ? "Issued" : "Available") << endl;
    }

    int getBookID() { return bookID; }
    bool getIssueStatus() { return isIssued; }

    void issueBook() { isIssued = true; }
    void returnBook() { isIssued = false; }
};

class Student {
    int studentID;
    string name;
    vector<int> borrowedBooks;

public:
    Student(int id, string n) : studentID(id), name(n) {}

    void displayStudent() {
        cout << "Student ID: " << studentID << "\nName: " << name << "\nBooks Borrowed: ";
        if (borrowedBooks.empty()) {
            cout << "None";
        } else {
            for (int bookID : borrowedBooks) {
                cout << bookID << " ";
            }
        }
        cout << endl;
    }

    int getStudentID() { return studentID; }

    void borrowBook(int bookID) { borrowedBooks.push_back(bookID); }
    void returnBook(int bookID) {
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (*it == bookID) {
                borrowedBooks.erase(it);
                break;
            }
        }
    }
};

class LibraryManagementSystem {
    vector<Book> books;
    vector<Student> students;

public:
    void addBook() {
        int id;
        string title, author;
        cout << "Enter Book ID: ";
        cin >> id;
        cout << "Enter Title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);

        books.push_back(Book(id, title, author));
        cout << "Book added successfully!" << endl;
    }

    void displayBooks() {
        cout << "\n--- Library Books ---" << endl;
        for (Book &book : books) {
            book.displayBook();
            cout << endl;
        }
    }

    void addStudent() {
        int id;
        string name;
        cout << "Enter Student ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);

        students.push_back(Student(id, name));
        cout << "Student added successfully!" << endl;
    }

    void displayStudents() {
        cout << "\n--- Registered Students ---" << endl;
        for (Student &student : students) {
            student.displayStudent();
            cout << endl;
        }
    }

    void borrowBook() {
        int studentID, bookID;
        cout << "Enter Student ID: ";
        cin >> studentID;
        cout << "Enter Book ID: ";
        cin >> bookID;

        Student *student = findStudentByID(studentID);
        Book *book = findBookByID(bookID);

        if (student && book) {
            if (!book->getIssueStatus()) {
                student->borrowBook(bookID);
                book->issueBook();
                cout << "Book borrowed successfully!" << endl;
            } else {
                cout << "Sorry, the book is already issued." << endl;
            }
        } else {
            cout << "Invalid Student ID or Book ID." << endl;
        }
    }

    void returnBook() {
        int studentID, bookID;
        cout << "Enter Student ID: ";
        cin >> studentID;
        cout << "Enter Book ID: ";
        cin >> bookID;

        Student *student = findStudentByID(studentID);
        Book *book = findBookByID(bookID);

        if (student && book) {
            student->returnBook(bookID);
            book->returnBook();
            cout << "Book returned successfully!" << endl;
        } else {
            cout << "Invalid Student ID or Book ID." << endl;
        }
    }

private:
    Book* findBookByID(int id) {
        for (Book &book : books) {
            if (book.getBookID() == id) {
                return &book;
            }
        }
        return nullptr;
    }

    Student* findStudentByID(int id) {
        for (Student &student : students) {
            if (student.getStudentID() == id) {
                return &student;
            }
        }
        return nullptr;
    }
};

int main() {
    LibraryManagementSystem library;
    int choice;

    do {
        cout << "\n--- Library Management System ---\n";
        cout << "1. Add Book\n2. Add Student\n3. Display Books\n4. Display Students\n5. Borrow Book\n6. Return Book\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                library.addBook();
                break;
            case 2:
                library.addStudent();
                break;
            case 3:
                library.displayBooks();
                break;
            case 4:
                library.displayStudents();
                break;
            case 5:
                library.borrowBook();
                break;
            case 6:
                library.returnBook();
                break;
            case 7:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 7);

    return 0;
}
