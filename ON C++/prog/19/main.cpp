#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct Book {
    string udc;
    string author;
    string title;
    int year;
    int copies;

    Book(string udc, string author, string title, int year, int copies)
        : udc(udc), author(author), title(title), year(year), copies(copies) {}
};

void printBook(const Book& book) {
    cout << "UDC: " << book.udc << endl;
    cout << "Author: " << book.author << endl;
    cout << "Title: " << book.title << endl;
    cout << "Year: " << book.year << endl;
    cout << "Copies: " << book.copies << endl;
}

int main() {
    map<int, vector<Book>> library;
    int choice;

    do {
        cout << "Menu:\n"
                "1 - Add a book\n"
                "2 - Remove a book\n"
                "3 - Search for a book\n"
                "0 - Exit\n"
                "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string udc, author, title;
                int year, copies;
                cout << "Enter UDC: ";
                cin >> udc;
                cout << "Enter author: ";
                cin.ignore();
                getline(cin, author);
                cout << "Enter title: ";
                getline(cin, title);
                cout << "Enter year: ";
                cin >> year;
                cout << "Enter number of copies: ";
                cin >> copies;
                library[year].push_back(Book(udc, author, title, year, copies));
                break;
            }
            case 2: {
                int year;
                string title;
                cout << "Enter year of the book you want to remove: ";
                cin >> year;
                cout << "Enter title of the book you want to remove: ";
                cin.ignore();
                getline(cin, title);
                for (auto it = library[year].begin(); it != library[year].end(); ++it) {
                    if (it->title == title) {
                        library[year].erase(it);
                        break;
                    }
                }
                break;
            }
            case 3: {
                string searchTitle;
                cout << "Enter the title you want to search for: ";
                cin.ignore();
                getline(cin, searchTitle);
                bool found = false;
                for (const auto& [year, books] : library) {
                    for (const auto& book : books) {
                        if (book.title == searchTitle) {
                            cout << "Book found:" << endl;
                            printBook(book);
                            found = true;
                            break;
                        }
                    }
                    if (found)
                        break;
                }
                if (!found)
                    cout << "Book not found." << endl;
                break;
            }
            case 0:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
