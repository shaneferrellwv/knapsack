# knapsack

## Project Description
This C++ program implements a solution to the Knapsack problem using dynamic programming. The Knapsack problem is a classic problem in combinatorial optimization. The program is designed to solve the problem of selecting a number of items with given weights and values to maximize the total value in a knapsack of a given capacity.

#### Files in this Project
1. `knapsack.cpp`: The main program file that contains the `knapsack` class and the `main` function.
2. `item.h`: A header file that defines the `item` class, representing the items to be put in the knapsack.

#### How to Run
To compile and run this program, you need a C++ compiler. Use the following commands:

``g++ -o knapsack knapsack.cpp``

``./knapsack <input_file> <capacity> <number_of_items>``

- `<input_file>`: A file containing the list of items (format: name weight value).
- `<capacity>`: The maximum weight capacity of the knapsack.
- `<number_of_items>`: The number of items to be included in the knapsack.

---

## Additional Information & Troubhleshooting

#### Implementation Details
- **Class `knapsack`**: Manages the knapsack problem's solution. It includes methods for allocating/deallocating the 3D dynamic programming array, solving the knapsack problem, and tracing back the items included in the solution.
- **Class `item`**: Represents an item with a name, weight, and value. Includes a utility function to create a list of items from an input file.

#### Input File Format
The input file should be in the `input/` directory and formatted as whitespace-separated values: `name weight value`.

The sum of the values of items in the input file should not be greater than 99999998. The program may produce unexpected behavior if provided an input file that does not meet this specification.

#### Dependencies
- Standard C++ libraries: `<iostream>`, `<vector>`, `<algorithm>`, `<limits>`, `<fstream>`, `<sstream>`

#### Error Handling
The program includes basic error handling for file input and format issues.

---

#### Developer
- Created by Shane Ferrell, a Computer Science and Electrical Engineering student at the University of Florida.

#### License
This project is open-source and free to use under the MIT License.

#### Contact
For bugs, suggestions, or further queries, please contact the developer at shaneferrell@ufl.edu.
