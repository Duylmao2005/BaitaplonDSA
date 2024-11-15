#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Book {
    int bookId;
    string bookName;
    string location;
    int quantity;

    Book() : bookId(0), bookName(""), location(""), quantity(0) {}
    Book(int id, string name, string loc, int qty) : bookId(id), bookName(name), location(loc), quantity(qty) {}
};

class HashTable {
private:
    static const int size = 1999; 
    Book** table;

    int hashFunction(int id) {
        return id % size;
    }

public:
    HashTable() {
        table = new Book*[size];
        for (int i = 0; i < size; ++i) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < size; ++i) {
            delete table[i];
        }
        delete[] table;
    }

    // Them sach vao bang bam
    void addBook(const Book& book) {
        int index = hashFunction(book.bookId);
        int originalIndex = index; 

       //Xu li xung dot
        while (table[index] != nullptr && table[index]->bookId != book.bookId) {
            index = (index + 1) % size;
            if (index == originalIndex) {
                cout << "Khong the them sach, bang bam da day!" << endl;
                return;
            }
        }

        // N?u v? trí tr?ng ho?c mã sách gi?ng nhau, ta s? thêm ho?c ghi dè
        table[index] = new Book(book);
    }

    // Tim kiem sach bang ma sach
    Book* searchBook(int bookId) {
        int index = hashFunction(bookId);
        int originalIndex = index;

        //Xu li xung dot
        while (table[index] != nullptr) {
            if (table[index]->bookId == bookId) {
                return table[index];
            }
            index = (index + 1) % size;
            if (index == originalIndex) { 
                break;
            }
        }
        return nullptr; 
    }

    // Xoa sach khoi bang bam
    bool deleteBook(int bookId) {
        int index = hashFunction(bookId);
        int originalIndex = index;

        //Xu li xung dot
        while (table[index] != nullptr) {
            if (table[index]->bookId == bookId) {
                delete table[index];
                table[index] = nullptr;
                return true;
            }
            index = (index + 1) % size;
            if (index == originalIndex) {
                break;
            }
        }
        return false;
    }

    // Luu thong tin bang bam vao file
    void saveToFile(const string& filename) {
        ofstream outFile(filename);
        for (int i = 0; i < size; ++i) {
            if (table[i] != nullptr) {
                outFile << table[i]->bookId << "," << table[i]->bookName << "," << table[i]->location << "," << table[i]->quantity << endl;
            }
        }
        outFile.close();
    }

    // Nap thong tin tu file vao bang bam
    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        int id, quantity;
        string name, location;
        while (inFile >> id) {
            getline(inFile, name, ',');
            getline(inFile, location, ',');
            inFile >> quantity;
            Book book(id, name, location, quantity);
            addBook(book);
        }
        inFile.close();
    }
};

// Lop quan ly thu vien
class Library {
private:
    HashTable hashTable;

public:
    // Nap thong tin sach tu file vao thu vien
    void loadLibrary(const string& filename) {
        hashTable.loadFromFile(filename);
    }

    // Tim kiem sach trong thu vien
    Book* searchBook(int bookId) {
        return hashTable.searchBook(bookId);
    }

    // Them sach moi vao thu vien
    void addBook(int id, const string& name, const string& location, int quantity) {
        Book book(id, name, location, quantity);
        hashTable.addBook(book);
    }

    // Xoa sach khoi thu vien
    bool deleteBook(int bookId) {
        return hashTable.deleteBook(bookId);
    }

    // Luu thong tin thu vien vao file
    void saveLibrary(const string& filename) {
        hashTable.saveToFile(filename);
    }
};

int main() {
    Library library;

    // Nap thong tin thu vien tu file
    library.loadLibrary("library.txt");

    // Them sach moi vao thu vien
    library.addBook(1001, "Lap trinh C++", "Ke 1", 10);
    library.addBook(1002, "Cau truc du lieu", "Ke 2", 5);
    library.addBook(1001, "Lap trinh C++", "Ke 1", 10);
    library.addBook(1222, "sach hay", "Ke 5", 14);

    // Tim kiem sach
    Book* book = library.searchBook(1001);
    if (book) {
        cout << "Sach tim thay: " << book->bookName << " - " << book->location << endl;
    } else {
        cout << "Khong tim thay sach!" << endl;
    }

    // Xoa sach khoi thu vien
    if (library.deleteBook(1002)) {
        cout << "Sach 1002 da bi xoa." << endl;
    } else {
        cout << "Khong the xoa sach 1002." << endl;
    }

    // Luu thong tin thu vien vao file
    library.saveLibrary("library.txt");

    return 0;
}

