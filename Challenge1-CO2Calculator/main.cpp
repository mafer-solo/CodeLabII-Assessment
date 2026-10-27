#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <cstdlib>

// Ask for a valid distance in miles.
double getDistance() {
    std::string input;
    double distance;
    char extra;

    while (true) {
        std::cout << "Enter the distance travelled in miles: ";

        // Stop if the input is closed.
        if (!std::getline(std::cin, input)) {
            std::exit(0);
        }

        // Read a number from the user's answer.
        std::istringstream stream(input);

        // Accept one finite number that is zero or positive.
        if ((stream >> distance) && !(stream >> extra)
            && std::isfinite(distance) && distance >= 0) {
            return distance;
        }

        std::cout << "Invalid distance. Enter a non-negative number.\n";
    }
}

// Keep asking until the user enters diesel or petrol.
std::string getFuelType() {
    std::string fuelType;

    while (true) {
        std::cout << "Enter the fuel type (diesel or petrol): ";

        if (!std::getline(std::cin, fuelType)) {
            std::exit(0);
        }

        if (fuelType == "diesel" || fuelType == "petrol") {
            return fuelType;
        }

        std::cout << "Invalid fuel type. Please try again.\n";
    }
}

// Calculate the estimated CO2 emissions in kilograms.
double calculateEmissions(double distance, std::string fuelType) {
    const double litresPer100Miles = 9.66;

    // Calculate the fuel used for the journey.
    double litresUsed = distance * (litresPer100Miles / 100);
    double emissionFactor;

    // Select the CO2 produced per litre of fuel.
    if (fuelType == "diesel") {
        emissionFactor = 2.68;
    } else {
        emissionFactor = 2.31;
    }

    return litresUsed * emissionFactor;
}

int main() {
    std::cout << "CO2 Calculator\n";

    // Get the journey details and calculate the emissions.
    double distance = getDistance();
    std::string fuelType = getFuelType();
    double emissions = calculateEmissions(distance, fuelType);

    // Display numbers with two decimal places.
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Distance entered: " << distance << " miles\n";
    std::cout << "Fuel selected: " << fuelType << "\n";
    std::cout << "Estimated CO2 emissions: " << emissions << " kg\n";

    return 0;
}