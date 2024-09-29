#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    if(argc < 2)
    {
        std::cout << "Please provide a Mini program" << std::endl;
        return -1;
    }
    std::ifstream fileStream(argv[1]); // Open a file for reading
    if (!fileStream.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(fileStream, line)) {
        std::cout << line << std::endl; // Print each line from the file
    }

    fileStream.close(); // Always close the file when done
    return 0;
}
