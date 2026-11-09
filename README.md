# Color blindness caculator

## Description

**version 2.0**

gives you different color blindness colors based off input, checks if a combination of colors is safe to use together, and saves the results to a file


## Developer

Kenneth Price

## Example

To run the program, give the following commands:

g++ --std=c++11 *.cpp -o cvp
./cvp

Here is an example of the program running:

== Colorblind Safe Combination Analyzer ===
How many colors do you want to compare in your palette (2 to 5)?
2

--- Color #1 ---
Enter a red rgb color <= 255:
255
Enter a blue rgb color <= 255:
0
Enter a green rgb color <= 255:
0

--- Color #2 ---
Enter a red rgb color <= 255:
0
Enter a blue rgb color <= 255:
0
Enter a green rgb color <= 255:
40

Choose a color blindness type to simulate:

Protanopia (Red-blindness)

Deuteranopia (Green-blindness)

Tritanopia (Blue-blindness)
Enter 1, 2, or 3: 1

--- [Protanopia Simulation Results] ---
Color #1 Original: (255, 0, 0) -> Simulated: R=38 G=28 B=0
Color #2 Original: (0, 40, 0) -> Simulated: R=42 G=31 B=0

--- [Color Combination Safety Check] ---
Color #1 & Color #2: UNSAFE (Too similar under Protanopia)

Report successfully saved to 'palette_report.txt'.