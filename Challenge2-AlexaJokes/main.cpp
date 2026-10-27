#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

int main() {
    // Open the file containing the jokes.
    std::ifstream file("randomJokes.txt");

    if (!file) {
        std::cout << "Error: could not open randomJokes.txt.\n";
        return 1;
    }

    std::vector<std::string> jokes;
    std::string line;

    // Store lines that contain a setup and a punchline.
    while (std::getline(file, line)) {
        // Remove a Windows line ending if present.
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        std::size_t separator = line.find('?');

        if (separator != std::string::npos
            && separator > 0 && separator + 1 < line.size()) {
            jokes.push_back(line);
        }
    }

    if (jokes.empty()) {
        std::cout << "Error: no valid jokes were found.\n";
        return 1;
    }

    // Prepare the random number generator.
    std::random_device seed;
    std::mt19937 generator(seed());
    std::uniform_int_distribution<std::size_t> choose(
        0, jokes.size() - 1);

    std::string request;
    std::string answer;

    std::cout << "Alexa Joke Teller\n";

    while (true) {
        std::cout << "\nType \"Alexa, tell me a joke\"";
        std::cout << " or \"quit\" to exit:\n";

        if (!std::getline(std::cin, request)) {
            break;
        }

        if (request == "quit") {
            break;
        }

        if (request != "Alexa, tell me a joke") {
            std::cout << "Please use the exact phrase shown above.\n";
            continue;
        }

        // Select a joke and locate the question mark.
        std::string joke = jokes[choose(generator)];
        std::size_t separator = joke.find('?');

        // Show the setup, including its question mark.
        std::cout << "\n" << joke.substr(0, separator + 1) << "\n";
        std::cout << "Press Enter to reveal the punchline.";

        if (!std::getline(std::cin, answer)) {
            break;
        }

        // Show the text after the question mark.
        std::cout << joke.substr(separator + 1) << "\n";
    }

    std::cout << "Goodbye!\n";
    return 0;
}