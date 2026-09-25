#include <iostream>
#include <algorithm>

int main() {
    int red = 0, blue = 0, green = 0, choice = 0;
    int out_red = 0, out_green = 0, out_blue = 0;

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

    std::cout << "\nChoose a color blindness type to simulate:\n";
    std::cout << "1. Protanopia (Red-blindness)\n";
    std::cout << "2. Deuteranopia (Green-blindness)\n";
    std::cout << "3. Tritanopia (Blue-blindness)\n";
    std::cout << "Enter 1, 2, or 3: ";
    std::cin >> choice;


    switch (choice) {
        case 1:
            // Protanopia math
            out_red = std::clamp((int)(red * 0.15 + green * 1.05 - blue * 0.20), 0, 255);
            out_green = std::clamp((int)(red * 0.11 + green * 0.79 + blue * 0.10), 0, 255);
            out_blue = std::clamp((int)(red * -0.01 - green * 0.05 + blue * 1.05), 0, 255);
            std::cout << "\n[Protanopia Output] R=" << out_red << " G=" << out_green << " B=" << out_blue << "\n";
            break;
            
        case 2:
            // Deuteranopia math
            out_red = std::clamp((int)(red * 0.37 + green * 0.86 - blue * 0.23), 0, 255);
            out_green = std::clamp((int)(red * 0.28 + green * 0.67 + blue * 0.05), 0, 255);
            out_blue = std::clamp((int)(red * -0.01 + green * 0.04 + blue * 0.97), 0, 255);
            std::cout << "\n[Deuteranopia Output] R=" << out_red << " G=" << out_green << " B=" << out_blue << "\n";
            break;
            
        case 3:
            // Tritanopia math
            out_red = std::clamp((int)(red * 0.95 + green * 0.05 + blue * 0.00), 0, 255);
            out_green = std::clamp((int)(red * 0.00 + green * 0.43 + blue * 0.57), 0, 255);
            out_blue = std::clamp((int)(red * 0.00 + green * 0.47 + blue * 0.53), 0, 255);
            std::cout << "\n[Tritanopia Output] R=" << out_red << " G=" << out_green << " B=" << out_blue << "\n";
            break;
            
        default:
            std::cout << "\nError: Invalid choice. Please run the program again and select 1, 2, or 3.\n";
            break;
    }

    return 0;
}