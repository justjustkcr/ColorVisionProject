#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>

//pass by value parameter that returns an int
int clampRGB(int value);

//pass by value AND pass by reference AND parameters, returns void
void simulateColorBlindness(int red, int green, int blue, int choice,
                            int &out_red, int &out_green, int &out_blue);

//returns true or false if the colors are safe
bool isCombinationSafe(int r1, int g1, int b1, int r2, int g2, int b2);

// main
int main() {
    int num_colors = 0;
    int choice = 0;

    // vectors to store the user's original RGB color combinations
    std::vector<int> red_list;
    std::vector<int> green_list;
    std::vector<int> blue_list;

    // vectors to store the simulated RGB colors
    std::vector<int> sim_red_list;
    std::vector<int> sim_green_list;
    std::vector<int> sim_blue_list;

    std::cout << "=== Colorblind Safe Combination Analyzer ===\n";
    std::cout << "How many colors do you want to compare in your palette (2 to 5)? \n";
    std::cin >> num_colors;
    while (num_colors < 2 || num_colors > 5) {
        std::cout << "Please enter a number between 2 and 5: \n";
        std::cin >> num_colors;
    }

    // collects rgb values for each color in the combination
    for (int i = 0; i < num_colors; i++) {
        int red = 0, green = 0, blue = 0;
        std::cout << "\n--- Color #" << (i + 1) << " ---\n";

        std::cout << "Enter a red rgb color <= 255: \n";
        std::cin >> red;
        while (red > 255 || red < 0) {
            std::cout << "Enter a correct number between 0 and 255: \n";
            std::cin >> red;
        }

        std::cout << "Enter a blue rgb color <= 255: \n";
        std::cin >> blue;
        while (blue > 255 || blue < 0) {
            std::cout << "Enter a correct number between 0 and 255: \n";
            std::cin >> blue;
        }

        std::cout << "Enter a green rgb color <= 255: \n";
        std::cin >> green;
        while (green > 255 || green < 0) {
            std::cout << "Enter a correct number between 0 and 255: \n";
            std::cin >> green;
        }

        red_list.push_back(red);
        green_list.push_back(green);
        blue_list.push_back(blue);
    }

    // choose color blindness type to simulate
    std::cout << "\nChoose a color blindness type to simulate:\n";
    std::cout << "1. Protanopia (Red-blindness)\n";
    std::cout << "2. Deuteranopia (Green-blindness)\n";
    std::cout << "3. Tritanopia (Blue-blindness)\n";
    std::cout << "Enter 1, 2, or 3: ";
    std::cin >> choice;
    while (choice < 1 || choice > 3) {
        std::cout << "Invalid choice. Please enter 1, 2, or 3: ";
        std::cin >> choice;
    }

    std::string mode_name = "";
    if (choice == 1) {
        mode_name = "Protanopia";
    } else if (choice == 2) {
        mode_name = "Deuteranopia";
    } else {
        mode_name = "Tritanopia";
    }

    // opens output file to save the color combination safety report
    std::ofstream report_file("palette_report.txt");

    std::cout << "\n--- [" << mode_name << " Simulation Results] ---\n";
    if (report_file.is_open()) {
        report_file << "=== " << mode_name << " Color Combination Report ===\n\n";
    }

    // loops through vectors and simulates each color using pass by reference
    for (int i = 0; i < num_colors; i++) {
        int out_red = 0, out_green = 0, out_blue = 0;

        // Function call demonstrating pass-by-value and pass-by-reference
        simulateColorBlindness(red_list[i], green_list[i], blue_list[i], choice,
                               out_red, out_green, out_blue);

        sim_red_list.push_back(out_red);
        sim_green_list.push_back(out_green);
        sim_blue_list.push_back(out_blue);

        std::cout << "Color #" << (i + 1)
                  << " Original: (" << red_list[i] << ", " << green_list[i] << ", " << blue_list[i] << ")"
                  << " -> Simulated: R=" << out_red << " G=" << out_green << " B=" << out_blue << "\n";

        if (report_file.is_open()) {
            report_file << "Color #" << (i + 1)
                        << " Original: (" << red_list[i] << ", " << green_list[i] << ", " << blue_list[i] << ")"
                        << " -> Simulated: R=" << out_red << " G=" << out_green << " B=" << out_blue << "\n";
        }
    }

    // compares every pair of rgb values to messure if its safe
    std::cout << "\n--- [Color Combination Safety Check] ---\n";
    if (report_file.is_open()) {
        report_file << "\n--- Color Combination Safety Check ---\n";
    }

    for (int i = 0; i < num_colors; i++) {
        for (int j = i + 1; j < num_colors; j++) {
            bool safe = isCombinationSafe(sim_red_list[i], sim_green_list[i], sim_blue_list[i],
                                          sim_red_list[j], sim_green_list[j], sim_blue_list[j]);

            std::cout << "Color #" << (i + 1) << " & Color #" << (j + 1) << ": ";
            if (safe) {
                std::cout << "SAFE (Easy to distinguish)\n";
            } else {
                std::cout << "UNSAFE (Too similar under " << mode_name << ")\n";
            }

            if (report_file.is_open()) {
                report_file << "Color #" << (i + 1) << " & Color #" << (j + 1) << ": "
                            << (safe ? "SAFE (Easy to distinguish)\n" : "UNSAFE (Too similar)\n");
            }
        }
    }

    if (report_file.is_open()) {
        report_file.close();
        std::cout << "\nReport successfully saved to 'palette_report.txt'.\n";
    } else {
        std::cout << "\nWarning: Could not open 'palette_report.txt' for writing.\n";
    }

    return 0;
}

// functions

// limits the rgb to strictly 0-255
int clampRGB(int value) {
    if (value < 0) {
        return 0;
    } else if (value > 255) {
        return 255;
    }
    return value;
}

// uses pass by refrence to modify which color blindness
void simulateColorBlindness(int red, int green, int blue, int choice,
                            int &out_red, int &out_green, int &out_blue) {
    switch (choice) {
        case 1:
            // Protanopia math
            out_red = clampRGB((int)(red * 0.15 + green * 1.05 - blue * 0.20));
            out_green = clampRGB((int)(red * 0.11 + green * 0.79 + blue * 0.10));
            out_blue = clampRGB((int)(red * -0.01 - green * 0.05 + blue * 1.05));
            break;

        case 2:
            // Deuteranopia math
            out_red = clampRGB((int)(red * 0.37 + green * 0.86 - blue * 0.23));
            out_green = clampRGB((int)(red * 0.28 + green * 0.67 + blue * 0.05));
            out_blue = clampRGB((int)(red * -0.01 + green * 0.04 + blue * 0.97));
            break;

        case 3:
            // Tritanopia math
            out_red = clampRGB((int)(red * 0.95 + green * 0.05 + blue * 0.00));
            out_green = clampRGB((int)(red * 0.00 + green * 0.43 + blue * 0.57));
            out_blue = clampRGB((int)(red * 0.00 + green * 0.47 + blue * 0.53));
            break;
    }
}

// calculates distance between the 2 rgb colors
bool isCombinationSafe(int r1, int g1, int b1, int r2, int g2, int b2) {
    double diff_r = r1 - r2;
    double diff_g = g1 - g2;
    double diff_b = b1 - b2;

    double distance = std::sqrt(diff_r * diff_r + diff_g * diff_g + diff_b * diff_b);

    // uses 100 as a baseline for distance
    return distance >= 100.0;
}