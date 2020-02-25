// xử lý đụng độ theo phương pháp separate chaining
// function programming

#include "stdio.h"
#include "stdlib.h"

#include "iostream"
using namespace std;

#include "fstream"
#include "string"
#include "vector"

struct Company {
    string name;
    string profit_tax;
    string address;
};

Company ReadCompany(string line) {
    char *anotherLine = new char[line.length() + 1];
    strcpy(anotherLine, line.c_str());

    Company c;
    c.name = strtok(anotherLine, "|");
    c.profit_tax = strtok(NULL, "|");
    c.address = strtok(NULL, "|");
    return c;
}

vector<Company> ReadListCompany(string file_name) {
    fstream file(file_name, ios::in);
    vector<Company> listCompany;
    if (file.is_open()) {
        string line;
        getline(file, line);
        Company c;
        while (getline(file, line)) {
            c = ReadCompany(line);
            listCompany.push_back(c);
        }
    }
    else {
        cout << "Loi file\n";
    }
    file.close();
    return listCompany;
}

void displayCompany(Company c) {
    cout << c.name << " | " << c.profit_tax << " | " << c.address;
}

unsigned long long HashString(string company_name) {
    unsigned long long h = 0;
}

int main(int argc, char const *argv[]) {
    vector<Company> listCompany = ReadListCompany("MST.txt");
    for (int i = 0; i < listCompany.size(); i++) {
        displayCompany(listCompany[i]);
        cout << endl;
    }

    // fstream file("MST.txt", ios::in);

    // string line;
    // getline(file, line);
    // Company c = ReadCompany(line);

    // displayCompany(c);

    return 0;
}
