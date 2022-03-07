#include <iostream>
#include <fstream>


void write_to_file() {
    // undesirable way
    std::ofstream out("test_file.txt");
    out.close();

    // more right way
    std::ofstream out_right;
    out_right.open("test_file.txt");

    if (out_right.is_open()) {
        out_right << "test text";
    }

    out_right.close();
}

void read_from_file() {
    std::string result;

    std::ifstream fin;
    fin.open("test_file.txt");
    if (fin.is_open()) {
        while (!fin.eof()) {
            fin >> result;
            std::cout << result << std::endl;
        }
    }
    fin.close();
}

void console_to_file() {
    std::ofstream fin;
    fin.open("console_log.txt");

    std::streambuf* buf = fin.rdbuf();
    std::streambuf* con_buf = std::cin.rdbuf();
    std::cout.rdbuf(buf);

    std::cout << "Test\n";
    std::cout << "Text\n";
    std::cout << "Test\n";

    fin.close();
    std::cout.rdbuf(con_buf);
}

int main() {
    write_to_file();
    read_from_file();
    console_to_file();
}