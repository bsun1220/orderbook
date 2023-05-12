#include "OrderBook.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

int main(int argc, char* argv[]){
    if (argc == 1){
        std::cout << "Need Input File Name\n";
        return 1; 
    }

    std::fstream myFile;
    myFile.open(argv[1], std::ios::in);


    std::string line;
    std::getline(myFile, line);

    OrderBook b(true);
    if (line == "0"){
        b.verbose = false; 
    }

    long line_num = 2;

    while(std::getline(myFile, line)){
        std::vector<std::string> values = split(line, ",");

        if (values[0] == "Add"){
            long id = stol(values[1]);
            bool side = stol(values[2]);
            double price = stod(values[3]);
            long amount = stol(values[4]);
            b.addOrder(id, side, price, amount);
        } else if (values[0] == "Update"){
            long id = stol(values[1]);
            long amount = stol(values[2]);
            b.updateOrder(id, amount);
        } else if (values[0] == "Delete"){
            long id = stol(values[1]);
            b.deleteOrder(id);
        } else if (values[0] == "Print"){
            b.printBook();
        } else {
            std::cout << "Error on Line " << line_num << "\n";
        }

        line_num++;

    }

}