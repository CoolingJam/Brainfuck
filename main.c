#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Size of the brainfuck array
#define arraySize 30000

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Not enough arguments. Usage: <file>");
        return 1;
    }
    if (argc > 2) {
        printf("Too many arguments. Usage: <file>");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) { 
        printf("Cannot read file");
        return 1;
    }

    char data[arraySize] = { 0 };
    char instructions[arraySize] = { 0 };
    int dataPointer = 0;
    int instructionPointer = 0;
    int loopDepth = 0;

    char line[arraySize] = { 0 };
    while(fgets(line, arraySize, file) != NULL) {
        strcat(instructions, line);
    }
    fclose(file);

    while(instructions[instructionPointer]) {
        switch(instructions[instructionPointer]) {
            case '>':
                dataPointer++;
                break;
            case '<':
                dataPointer--;
                break;
            case '+':
                data[dataPointer]++;
                break;
            case '-':
                data[dataPointer]--;
                break;
            case '.':
                printf("%c", data[dataPointer]);
                break;
            case ',':
                scanf("%c", &data[dataPointer]);
                break;
            case ';':
                printf("Debug statement indeed\n");
                break;
            case '[':
                if (!data[dataPointer]) {
                    instructionPointer++;
                    while(true) {
                        char instruction = instructions[instructionPointer];
                        if (instruction == ']' && loopDepth == 0) break;
                        if (instruction == ']') {
                            loopDepth--;
                        } else if (instruction == '[') {
                            loopDepth++;
                        }
                        instructionPointer++;
                    }
                }
                break;
            case ']':
                if (data[dataPointer]) {
                    while(true) {
                        char instruction = instructions[instructionPointer];
                        if (instruction == '[') {
                            loopDepth--;
                        } else if (instruction == ']') {
                            loopDepth++;
                        }
                        if (instruction == '[' && loopDepth == 0) {
                            break;
                        }
                        instructionPointer--;
                    }
                }
                break;
        }
        instructionPointer++;
    }

}