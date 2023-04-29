# ASS2_DSA_JAVM
DATA STRUCTURES AND ALGORITHMS (CO2003)

Requirement: Assignment 2 Version 1.0.0

1 EXPECTED OUTCOME

    After completing this assignment, students will be able to:
    
      • Implement AVL tree data structure.
      
      • Apply AVL tree data structure to solve problems.
      
2 INSTRUCTION

The object to be implemented in this assignment is the stack frame of the JAVM virtual machine. Each test case is a function, which contains instructions of the JAVM virtual machine to be executed on the stack frame.

To complete this assignment, you should follow these steps:

      • Read the JAVM’s specification (version 1.1.x).
      
      • Download initial.zip and unzip it.
      
      • The unzipped folder should include these files: main.cpp, errors.h, constants.h, StackFrame.h and StackFrame.cpp.
      
      • Modify the initial code in StackFrame.h and StackFrame.cpp as required in the specification.
      
      • Sample testcases and expected results are attached in testcase and solution folder. (after unzip initial.zip)
      
Important notes:

      • Use C++ 11 standard to compile the program. For example, with g++ compiler:
      
      $ g++ main.cpp StackFrame.cpp -o main -std=c++11
      
      • DO NOT modify main.cpp, errors.h and constants.h
      
      • DO NOT import any libraries other than ones imported in the initial code of StackFrame.h and StackFrame.cpp.
      
      • Make sure the StackFrame class is declared, and this class should have at least one public instance method void run(string filename) defined in StackFrame.h and StackFrame.cpp
