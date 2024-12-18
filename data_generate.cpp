#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip> // for std::quoted

struct Person {
    int key;
    int id;
    std::string name;
};

int main() {
    std::string line;
    std::vector<Person> people;

    // Open list_pool.txt for reading
    std::ifstream inputFile("list_pool.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    // Read input line by line
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int key, id;
        std::string name;

        // Parse key, id, and name from the line
        if (iss >> key >> id && std::getline(iss, name)) {
            // Remove leading whitespace from the name
            name.erase(0, name.find_first_not_of(" "));
            people.push_back({key, id, name});
        }
    }

    inputFile.close();

    // Open result.json for writing
    std::ofstream outputFile("result.json");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return 1;
    }

    // Write JSON array to file
    outputFile << "[\n";
    for (size_t i = 0; i < people.size(); ++i) {
        const auto& person = people[i];
        outputFile << "  { \"name\": " << std::quoted(person.name)
                   << ", \"key\": " << person.key
                   << ", \"id\": " << person.id << " }";
        if (i < people.size() - 1) {
            outputFile << ",";
        }
        outputFile << "\n";
    }
    outputFile << "]" << std::endl;

    outputFile.close();

    std::cout << "JSON written to result.json successfully." << std::endl;

    return 0;
}

