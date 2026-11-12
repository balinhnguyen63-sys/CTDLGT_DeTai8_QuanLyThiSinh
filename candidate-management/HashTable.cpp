#include "HashTable.h"
#include <iostream>
#include <cctype>
#include <stdexcept>
#include <sstream>

using namespace std;

namespace {
string trim(const string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

string toLowerAscii(const string &s) {
    string result = s;
    for (char &c : result) {
        c = tolower((unsigned char)c);
    }
    return result;
}

string normalizeSpaces(const string &s) {
    istringstream iss(s);
    string word, result;
    while (iss >> word) {
        if (!result.empty()) result += ' ';
        result += word;
    }
    return result;
}

bool containsWord(const string &text, const string &word) {
    istringstream iss(text);
    string token;
    while (iss >> token) {
        if (toLowerAscii(token) == word) return true;
    }
    return false;
}
} // namespace

// Nguyen Ba Linh: Cai dat cac phuong thuc cua Bang bam HashTable

HashTable::HashTable() {}

HashTable::~HashTable() {
    clear();
}

// Ham bam: chuyen chu cai dau A-Z sang chi so 0-25
int HashTable::hashFunction(char firstLetter) const {
    char c = toupper((unsigned char)firstLetter);
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    }
    return 0; // Mac dinh ve 0 neu khong hop le
}

// Them thi sinh vao bucket tuong ung
void HashTable::insert(const Candidate &c) {
    if (c.getSBD().empty()) return;
    // Chan trung SBD
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (buckets[i].find(c.getSBD()) != nullptr) return;
    }
    char firstLetter = c.getFirstLetterOfName();
    int index = hashFunction(firstLetter);
    buckets[index].insertTail(c);
}

// Tim kiem theo SBD tren toan bo bang bam
Node* HashTable::searchBySBD(const string &sbd) const {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* found = buckets[i].find(sbd);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

// Tim kiem theo ten thi sinh tren bang bam
void HashTable::searchByName(const string &name) const {
    string query = normalizeSpaces(trim(name));
    if (query.empty()) {
        cout << "[!] Ten can tim khong hop le!\n";
        return;
    }

    string lowerQuery = toLowerAscii(query);
    bool isFullName = (query.find(' ') != string::npos);

    int startBucket = 0;
    int endBucket = TABLE_SIZE - 1;
    if (isFullName) {
        size_t lastSpace = query.find_last_of(' ');
        string ten = query.substr(lastSpace + 1);
        Candidate probe("", ten, "", "", "");
        startBucket = hashFunction(probe.getFirstLetterOfName());
        endBucket = startBucket;
    }

    cout << "\n=== KET QUA TRA CUU THEO TEN: \"" << query << "\"";
    if (isFullName) {
        cout << " (Tra cuu tai Nhom '" << (char)('A' + startBucket) << "')";
    } else {
        cout << " (Quet toan bo 26 nhom)";
    }
    cout << " ===\n";

    int count = 0;
    for (int i = startBucket; i <= endBucket; ++i) {
        Node* p = buckets[i].getHead();
        while (p != nullptr) {
            string firstName = toLowerAscii(trim(p->data.getFirstName()));
            string fullName = toLowerAscii(normalizeSpaces(p->data.getHoTen()));

            bool match = false;
            if (isFullName) {
                match = fullName.find(lowerQuery) != string::npos;
            } else {
                match = (firstName == lowerQuery) || containsWord(fullName, lowerQuery);
            }

            if (match) {
                if (count == 0) {
                    cout << "+---------+-----------------------+---------+-------------+----------------------+\n";
                    cout << "| SBD     | Ho va Ten             | Phai    | Ngay Sinh   | Que Quan             |\n";
                    cout << "+---------+-----------------------+---------+-------------+----------------------+\n";
                }
                p->data.displayRow();
                count++;
            }
            p = p->next;
        }
    }

    if (count == 0) {
        cout << "--> Khong tim thay thi sinh nao co ten \"" << query << "\".\n";
    } else {
        cout << "+---------+-----------------------+---------+-------------+----------------------+\n";
        cout << "Tim thay " << count << " thi sinh phu hop.\n";
    }
}

// Xoa thi sinh khoi bang bam
bool HashTable::remove(const string &sbd, char firstLetter) {
    int index = hashFunction(firstLetter);
    if (buckets[index].remove(sbd)) return true;

    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (i == index) continue;
        if (buckets[i].remove(sbd)) return true;
    }
    return false;
}

// Hien thi toan bo bang bam theo tung nhom chu cai A-Z
void HashTable::displayAll() const {
    cout << "\n=======================================================================\n";
    cout << "          BANG BAM THI SINH DANG BANG TRA (26 NHOM A - Z)              \n";
    cout << "=======================================================================\n";

    bool hasAny = false;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (!buckets[i].isEmpty()) {
            hasAny = true;
            char letter = 'A' + i;
            cout << "\n>>> [NHOM " << letter << "] (So luong: " << buckets[i].getCount() << " thi sinh):\n";
            buckets[i].display();
        }
    }

    if (!hasAny) {
        cout << "  (Bang bam hien tai dang rong!)\n";
    }
}

// Hien thi 1 bucket cu the
void HashTable::displayBucket(int index) const {
    if (index >= 0 && index < TABLE_SIZE) {
        char letter = 'A' + index;
        cout << "\n>>> Thong tin Nhom [" << letter << "]:\n";
        buckets[index].display();
    }
}

const LinkedList& HashTable::getBucket(int index) const {
    if (index < 0 || index >= TABLE_SIZE) {
        throw out_of_range("HashTable::getBucket: chi so bucket khong hop le");
    }
    return buckets[index];
}

LinkedList& HashTable::getBucket(int index) {
    if (index < 0 || index >= TABLE_SIZE) {
        throw out_of_range("HashTable::getBucket: chi so bucket khong hop le");
    }
    return buckets[index];
}

void HashTable::clear() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        buckets[i].clear();
    }
}
