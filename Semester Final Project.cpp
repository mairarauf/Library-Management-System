#include <iostream>
#include <string>

using namespace std;

class Book {
public:
    Book(const string& title, const string& author) : title(title), author(author), isIssued(false) {}

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author;
        if (isIssued) {
            cout << " (Issued)";
        }
        cout << endl;
    }

    void issueBook() {
        isIssued = true;
    }

    void returnBook() {
        isIssued = false;
    }

    bool isBookIssued() const {
        return isIssued;
    }

    string getTitle() const {
        return title;
    }

private:
    string title;
    string author;
    bool isIssued;
};

class User {
public:
    User(const string& name, const string& id) : name(name), id(id) {}

    virtual void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

    virtual void displayOptions() const = 0;

    virtual void handleOption(int option, Book* books, int numBooks) = 0;

    virtual bool wantsToIssueBook() const {
        return true;
    }

    void returnBooks(Book* books, int numBooks) const {
        // Implementation for returning books (shared among Teacher, Student, and Staff)
    }


    virtual void processReturn(Book* books, int numBooks) const {
        string returnTitle;
        cout << "Enter the title of the book you want to return: ";
        cin.ignore();
        getline(cin, returnTitle);

        bool found = false;
        for (int i = 0; i < numBooks; ++i) {
            if (returnTitle == books[i].getTitle() && books[i].isBookIssued()) {
                books[i].returnBook();
                cout << "Book returned successfully!\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Book not found or not issued by you.\n";
        }
    }
protected:
    const string& getName() const {
        return name;
    }

private:
    string name;
    string id;
};

class Teacher : public User {
public:
    Teacher(const string& name, const string& employeeID)
        : User(name, ""), employeeID(employeeID) {}

    void displayOptions() const override {
        cout << "Options:\n";
        cout << "1. Search a book\n";
        cout << "2. See Issued Books\n";
        cout << "3. Return Books\n";
        cout << "4. Re-issue Books\n";
        cout << "5. GO BACK\n";
    }

    void handleOption(int option, Book* books, int numBooks) override {
        switch (option) {
            case 1:
                searchBook(books, numBooks);
                break;
            case 2:
                cout << "Issued Books:\n";
                displayIssuedBooks(books, numBooks);
                break;
            case 3:
                returnBooks(books, numBooks);
                break;
            case 4:
                // Implement re-issue books logic for teachers
                break;
            case 5:
                cout << "Going back...\n";
                break;
            default:
                cout << "Invalid option!\n";
        }
    }

private:
    string employeeID;

    void displayIssuedBooks(Book* books, int numBooks) const {
        cout << "Teacher " << getName() << "'s Issued Books:\n";
        for (int i = 0; i < numBooks; ++i) {
            if (books[i].isBookIssued()) {
                books[i].displayInfo();
            }
        }
    }

    void searchBook(Book* books, int numBooks) const {
        cout << "Available Books:\n";
        for (int i = 0; i < numBooks; ++i) {
            books[i].displayInfo();
        }

        string searchTitle;
        cout << "Enter the title of the book you want to issue: ";
        cin.ignore(); // Consume the newline character left in the buffer
        getline(cin, searchTitle);

        bool found = false;
        int foundIndex = -1;

        for (int i = 0; i < numBooks; ++i) {
            if (searchTitle == books[i].getTitle()) {
                cout << "Book found:\n";
                books[i].displayInfo();
                found = true;
                foundIndex = i;
                break;
            }
        }

        if (found) {
            if (wantsToIssueBook() && !books[foundIndex].isBookIssued()) {
                books[foundIndex].issueBook();
                cout << "Book issued successfully!\n";
            } else {
                cout << "Book not issued.\n";
            }
        } else {
            cout << "Book not found.\n";
        }
    }
};

class Student : public User {
public:
    Student(const string& name, const string& studentID)
        : User(name, ""), studentID(studentID) {}

    void displayOptions() const override {
        cout << "Options:\n";
        cout << "1. Issue a book\n";
        cout << "2. See Issued Books\n";
        cout << "3. Return Books\n";
        cout << "4. Re-issue Books\n";
        cout << "5. GO BACK\n";
    }

    void handleOption(int option, Book* books, int numBooks) override {
        switch (option) {
            case 1:
                searchBook(books, numBooks);
                break;
            case 2:
                cout << "Issued Books:\n";
                displayIssuedBooks(books, numBooks);
                break;
            case 3:
                returnBooks(books, numBooks);
                break;
            case 4:
                // Implement re-issue books logic for students
                break;
            case 5:
                cout << "Going back...\n";
                break;
            default:
                cout << "Invalid option!\n";
        }
    }

private:
    string studentID;

    void displayIssuedBooks(Book* books, int numBooks) const {
        cout << "Student " << getName() << "'s Issued Books:\n";
        for (int i = 0; numBooks; ++i) {
            if (books[i].isBookIssued()) {
                books[i].displayInfo();
            }
        }
    }

    void searchBook(Book* books, int numBooks) const {
        cout << "Available Books:\n";
        for (int i = 0; i < numBooks; ++i) {
            books[i].displayInfo();
        }

        string searchTitle;
        cout << "Enter the title of the book you want to search: ";
        cin.ignore(); // Consume the newline character left in the buffer
        getline(cin, searchTitle);

        bool found = false;
        int foundIndex = -1;

        for (int i = 0; i < numBooks; ++i) {
            if (searchTitle == books[i].getTitle()) {
                cout << "Book found:\n";
                books[i].displayInfo();
                found = true;
                foundIndex = i;
                break;
            }
        }

        if (found) {
            if (wantsToIssueBook() && !books[foundIndex].isBookIssued()) {
                books[foundIndex].issueBook();
                cout << "Book issued successfully!\n";
            } else {
                cout << "Book not issued.\n";
            }
        } else {
            cout << "Book not found.\n";
        }
    }
};

class Staff : public User {
public:
    Staff(const string& name, const string& employeeID)
        : User(name, ""), employeeID(employeeID) {}

    void displayOptions() const override {
        cout << "Options:\n";
        cout << "1. Search a book\n";
        cout << "2. See Issued Books\n";
        cout << "3. Return Books\n";
        cout << "4. Re-issue Books\n";
        cout << "5. Remove fine\n";
        cout << "6. Enter New Book\n";
        cout << "7. GO BACK\n";
    }

    void handleOption(int option, Book* books, int numBooks) override {
        switch (option) {
            case 1:
                searchBook(books, numBooks);
                break;
            case 2:
                cout << "Issued Books:\n";
                displayIssuedBooks(books, numBooks);
                break;
            case 3:
                returnBooks(books, numBooks);
                break;
            case 4:
                // Implement re-issue books logic for staff
                break;
            case 5:
                // Implement remove fine logic for staff
                break;
            case 6:
                // Implement enter new book logic for staff
                break;
            case 7:
                cout << "Going back...\n";
                break;
            default:
                cout << "Invalid option!\n";
        }
    }

private:
    string employeeID;

    void displayIssuedBooks(Book* books, int numBooks) const {
        cout << "Staff " << getName() << "'s Issued Books:\n";
        for (int i = 0; i < numBooks; ++i) {
            if (books[i].isBookIssued()) {
                books[i].displayInfo();
            }
        }
    }

    void searchBook(Book* books, int numBooks) const {
        cout << "Available Books:\n";
        for (int i = 0; i < numBooks; ++i) {
            books[i].displayInfo();
        }

        string searchTitle;
        cout << "Enter the title of the book you want to search: ";
        cin.ignore(); // Consume the newline character left in the buffer
        getline(cin, searchTitle);

        bool found = false;
        int foundIndex = -1;

        for (int i = 0; i < numBooks; ++i) {
            if (searchTitle == books[i].getTitle()) {
                cout << "Book found:\n";
                books[i].displayInfo();
                found = true;
                foundIndex = i;
                break;
            }
        }

        if (found) {
            if (wantsToIssueBook() && !books[foundIndex].isBookIssued()) {
                books[foundIndex].issueBook();
                cout << "Book issued successfully!\n";
            } else {
                cout << "Book not issued.\n";
            }
        } else {
            cout << "Book not found.\n";
        }
    }

    void returnBooks(Book* books, int numBooks) const {
        cout << "Issued Books:\n";
        for (int i = 0; i < numBooks; ++i) {
            if (books[i].isBookIssued()) {
                books[i].displayInfo();
            }
        }

        string returnTitle;
        cout << "Enter the title of the book you want to return: ";
        cin.ignore(); // Consume the newline character left in the buffer
        getline(cin, returnTitle);

        bool found = false;
        for (int i = 0; i < numBooks; ++i) {
            if (returnTitle == books[i].getTitle() && books[i].isBookIssued()) {
                books[i].returnBook();
                cout << "Book returned successfully!\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Book not found or not issued by anyone.\n";
        }
    }
};

int main() {
    const int numBooks = 5;  // Adjust the size as needed
    Book libraryBooks[numBooks] = {
        {"Book1", "Author1"},
        {"Book2", "Author2"},
        {"Book3", "Author3"},
        {"Book4", "Author4"},
        {"Book5", "Author5"}
    };

    int choice;

    while (true) {
        cout << "Choose User Type:\n";
        cout << "1. Teacher\n";
        cout << "2. Student\n";
        cout << "3. Staff\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        string name;

        switch (choice) {
            case 1:
                cout << "Enter Teacher's Name: ";
                cin >> name;
                {
                    string employeeID;
                    cout << "Enter Teacher's Employee ID: ";
                    cin >> employeeID;
                    Teacher teacher(name, employeeID);
                    while (true) {
                        teacher.displayOptions();
                        cout << "Enter your option: ";
                        cin >> choice;
                        if (choice == 5) {
                            break;
                        }
                        teacher.handleOption(choice, libraryBooks, numBooks);
                    }
                }
                break;
            case 2:
                cout << "Enter Student's Name: ";
                cin >> name;
                {
                    string studentID;
                    cout << "Enter Student's Student ID: ";
                    cin >> studentID;
                    Student student(name, studentID);
                    while (true) {
                        student.displayOptions();
                        cout << "Enter your option: ";
                        cin >> choice;
                        if (choice == 5) {
                            break;
                        }
                        student.handleOption(choice, libraryBooks, numBooks);
                    }
                }
                break;
            case 3:
                cout << "Enter Staff's Name: ";
                cin >> name;
                {
                    string employeeID;
                    cout << "Enter Staff's Employee ID: ";
                    cin >> employeeID;
                    Staff staff(name, employeeID);
                    while (true) {
                        staff.displayOptions();
                        cout << "Enter your option: ";
                        cin >> choice;
                        if (choice == 7) {
                            break;
                        }
                        staff.handleOption(choice, libraryBooks, numBooks);
                   

                    }
                }
                break;
            case 4:
                cout << "Thanks for using the program.\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

        if (choice == 4) {
            break;
        }
    }

    return 0;
}

