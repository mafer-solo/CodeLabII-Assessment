#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>

// Store each book's details and manage its availability.
class Book {
private:
    std::string title;
    std::string author;
    int pages;
    std::string id;
    bool borrowed;

public:
    // Set the details when a book is created.
    Book(std::string bookTitle, std::string bookAuthor,
         int bookPages, std::string bookId, bool isBorrowed) {
        title = bookTitle;
        author = bookAuthor;
        pages = bookPages;
        id = bookId;
        borrowed = isBorrowed;
    }

    std::string getId() const {
        return id;
    }

    // Display the details without changing the book.
    void display() const {
        std::cout << "\nTitle: " << title << "\n";
        std::cout << "Author: " << author << "\n";
        std::cout << "Pages: " << pages << "\n";
        std::cout << "ID: " << id << "\n";
        if (borrowed) {
            std::cout << "Status: Borrowed\n";
        } else {
            std::cout << "Status: Available\n";
        }
    }

    // Borrow the book only if it is available.
    void borrowBook() {
        if (borrowed) {
            std::cout << "This book is already borrowed.\n";
        } else {
            borrowed = true;
            std::cout << "Book borrowed successfully.\n";
        }
    }

    // Return the book only if it is borrowed.
    void returnBook() {
        if (!borrowed) {
            std::cout << "This book is already available.\n";
        } else {
            borrowed = false;
            std::cout << "Book returned successfully.\n";
        }
    }
};

// Read the file and create the books.
bool loadBooks(std::vector<Book>& books) {
    std::ifstream file("bookData.txt");
    if (!file) {
        std::cout << "Error: could not open bookData.txt.\n";
        return false;
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)) {
        ++lineNumber;
        // Remove a Windows line ending if present.
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        std::istringstream row(line);
        std::string title, author, pagesText, id, status;
        // Separate and check the five fields.
        if (!std::getline(row, title, ',')
            || !std::getline(row, author, ',')
            || !std::getline(row, pagesText, ',')
            || !std::getline(row, id, ',')
            || !std::getline(row, status)
            || title.empty() || author.empty() || id.empty()
            || (status != "true" && status != "false")) {
            std::cout << "Error: invalid data on line "
                      << lineNumber << ".\n";
            return false;
        }

        // Convert the pages from text to a positive integer.
        try {
            std::size_t used;
            int pages = std::stoi(pagesText, &used);
            if (used != pagesText.size() || pages <= 0) {
                throw std::invalid_argument("Invalid pages");
            }
            // Check that each book has a unique ID.
            for (const Book& book : books) {
                if (book.getId() == id) {
                    std::cout << "Error: duplicate book ID.\n";
                    return false;
                }
            }
            books.push_back(Book(title, author, pages, id,
                                 status == "true"));
        } catch (const std::exception&) {
            std::cout << "Error: invalid pages on line "
                      << lineNumber << ".\n";
            return false;
        }
    }

    if (file.bad() || books.empty()) {
        std::cout << "Error: could not load the books.\n";
        return false;
    }
    return true;
}

// Find a book and perform the selected action.
void manageBook(std::vector<Book>& books,
                const std::string& id, const std::string& choice) {
    for (Book& book : books) {
        if (book.getId() == id) {
            if (choice == "2") {
                book.display();
            } else if (choice == "3") {
                book.borrowBook();
            } else if (choice == "4") {
                book.returnBook();
            }
            return;
        }
    }
    std::cout << "Book not found. Please check the ID.\n";
}

int main() {
    std::cout << "Book Manager\n";
    std::vector<Book> books;
    if (!loadBooks(books)) {
        return 1;
    }
    std::cout << "Books loaded: " << books.size() << "\n";
    std::cout << "Loan changes apply during this session only.\n";

    std::string choice;
    // Keep showing the menu until the user exits.
    while (true) {
        std::cout << "\n1. View all books\n";
        std::cout << "2. View a book by ID\n";
        std::cout << "3. Borrow a book\n";
        std::cout << "4. Return a book\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        if (!std::getline(std::cin, choice)) {
            break;
        }

        if (choice == "1") {
            for (const Book& book : books) {
                book.display();
            }
        } else if (choice == "2" || choice == "3" || choice == "4") {
            std::string id;
            std::cout << "Enter the book ID (e.g. 001): ";
            if (!std::getline(std::cin, id)) {
                break;
            }
            manageBook(books, id, choice);
        } else if (choice == "5") {
            break;
        } else {
            std::cout << "Invalid choice. Please enter 1 to 5.\n";
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}