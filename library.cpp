#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Book class
class Book {
public:
    string title;
    string author;
    int id;
    bool isIssued;

    Book(int i, string t, string a) {
        id = i;
        title = t;
        author = a;
        isIssued = false;
    }

    void display() {
        cout << "ID: " << id << " | Title: " << title 
             << " | Author: " << author 
             << " | " << (isIssued ? "Issued" : "Available") << endl;
    }
};

// Function to save books to file
void saveToFile(vector<Book>& books) {
    ofstream file("books.txt");
    for (auto& book : books) {
        file << book.id << "," << book.title << "," 
             << book.author << "," << book.isIssued << endl;
    }
    file.close();
}

// Function to load books from file
void loadFromFile(vector<Book>& books) {
    ifstream file("books.txt");
    if (!file.is_open()) return;

    books.clear();
    string line;
    while (getline(file, line)) {
        int pos1 = line.find(',');
        int pos2 = line.find(',', pos1 + 1);
        int pos3 = line.find(',', pos2 + 1);

        int id = stoi(line.substr(0, pos1));
        string title = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string author = line.substr(pos2 + 1, pos3 - pos2 - 1);
        bool isIssued = stoi(line.substr(pos3 + 1));

        Book b(id, title, author);
        b.isIssued = isIssued;
        books.push_back(b);
    }
    file.close();
}

// Main program
int main() {
    vector<Book> books;
    loadFromFile(books);

    int choice;
    do {
        cout << "\n====== Library Management System ======\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // to consume newline

        if (choice == 1) {
            int id;
            string title, author;
            cout << "Enter Book ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Book Title: ";
            getline(cin, title);
            cout << "Enter Book Author: ";
            getline(cin, author);
            books.push_back(Book(id, title, author));
            saveToFile(books);
            cout << "Book added successfully!\n";
        }
        else if (choice == 2) {
            cout << "\nAll Books:\n";
            for (auto& book : books)
                book.display();
        }
        else if (choice == 3) {
            int id;
            cout << "Enter Book ID to issue: ";
            cin >> id;
            bool found = false;
            for (auto& book : books) {
                if (book.id == id) {
                    found = true;
                    if (!book.isIssued) {
                        book.isIssued = true;
                        cout << "Book issued successfully!\n";
                    } else {
                        cout << "Book already issued!\n";
                    }
                    break;
                }
            }
            if (!found) cout << "Book not found!\n";
            saveToFile(books);
        }
        else if (choice == 4) {
            int id;
            cout << "Enter Book ID to return: ";
            cin >> id;
            bool found = false;
            for (auto& book : books) {
                if (book.id == id) {
                    found = true;
                    if (book.isIssued) {
                        book.isIssued = false;
                        cout << "Book returned successfully!\n";
                    } else {
                        cout << "Book was not issued!\n";
                    }
                    break;
                }
            }
            if (!found) cout << "Book not found!\n";
            saveToFile(books);
        }
    } while (choice != 5);

    cout << "Exiting Library Management System.\n";
    return 0;
}

