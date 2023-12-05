#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int extract_calibration_value_from_test_input_file_line(char* line)
{
    char calibrationValue[3] = { '0', '0', '\0' };
    char lastSeenNumber = -1;

    for (int i = 0; i < strlen(line); i += 1) {
        char lineChar = line[i];

        if (!isdigit(lineChar)) {
            continue;
        }

        if (lastSeenNumber == -1) {
            lastSeenNumber = lineChar;
            calibrationValue[0] = lastSeenNumber;

            continue;
        }

        lastSeenNumber = lineChar;
    }

    calibrationValue[1] = lastSeenNumber;

    return atoi(calibrationValue);
}

int extract_calibration_values_from_file_and_sum_them(FILE* filePath)
{
    int sum = 0;

    // Read out file line by line and extract the calibration code from it
    int lineBufferLength = 100;
    char line[lineBufferLength];

    while(fgets(line, lineBufferLength, filePath)) {
        sum += extract_calibration_value_from_test_input_file_line(line);
    }

    return sum;
}

/**
 * Advent of code day 1
 *
 * @link https://adventofcode.com/2023/day/1
 */
int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Expected only 1 parameter, the test input file.");

        return 1;
    }

    char* testInputFilePath = argv[1];
    FILE* testInputFileStream = fopen(testInputFilePath, "r");

    if (testInputFileStream == NULL) {
        printf("Could not find test input file.");

        return 1;
    }

    printf(
        "Sum of all calibration values within input file: %d\n",
        extract_calibration_values_from_file_and_sum_them(testInputFileStream)
    );

    return 0;
}
