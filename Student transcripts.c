#include <stdio.h>

// Constants for the number of years, semesters, and subjects
#define NUM_YEARS 4
#define NUM_SEMESTERS 2
#define NUM_SUBJECTS 8

// Function prototypes
char assignGrade(float mark);
float calculateMean(float marks[], int num_subjects);
void printSemesterTranscript(int year, int semester, float marks[], char grades[], float mean_mark, char mean_grade);
void printYearTranscript(int year, float marks[], char grades[], float mean_mark, char mean_grade);
void printFinalTranscript(float overall_mean, char overall_grade);

int main() {
    // Arrays to store marks and grades
    float marks[NUM_YEARS][NUM_SEMESTERS][NUM_SUBJECTS];
    char grades[NUM_YEARS][NUM_SEMESTERS][NUM_SUBJECTS];
    float semester_means[NUM_YEARS][NUM_SEMESTERS];
    float year_means[NUM_YEARS];

    float overall_marks[NUM_YEARS * NUM_SEMESTERS * NUM_SUBJECTS];
    int total_subjects = 0;

    // Input marks for each year, semester, and subject
    for (int year = 0; year < NUM_YEARS; year++) {
        for (int semester = 0; semester < NUM_SEMESTERS; semester++) {
            printf("Enter marks for Year %d, Semester %d:\n", year + 1, semester + 1);
            for (int subject = 0; subject < NUM_SUBJECTS; subject++) {
                do {
                    printf("  Subject %d (0-100): ", subject + 1);
                    scanf("%f", &marks[year][semester][subject]);
                    if (marks[year][semester][subject] < 0 || marks[year][semester][subject] > 100) {
                        printf("Invalid mark. Please enter a value between 0 and 100.\n");
                    }
                } while (marks[year][semester][subject] < 0 || marks[year][semester][subject] > 100);

                // Assign grades based on the mark
                grades[year][semester][subject] = assignGrade(marks[year][semester][subject]);
            }
            // Calculate the mean grade for the semester
            float semester_marks[NUM_SUBJECTS];
            for (int subject = 0; subject < NUM_SUBJECTS; subject++) {
                semester_marks[subject] = marks[year][semester][subject];
                overall_marks[total_subjects++] = marks[year][semester][subject];
            }
            float semester_mean = calculateMean(semester_marks, NUM_SUBJECTS);
            char semester_grade = assignGrade(semester_mean);
            semester_means[year][semester] = semester_mean;

            // Print the semester transcript
            printSemesterTranscript(year + 1, semester + 1, marks[year][semester], grades[year][semester], semester_mean, semester_grade);
        }

        // Calculate the mean grade for the year
        float year_marks[NUM_SEMESTERS * NUM_SUBJECTS];
        int index = 0;
        for (int semester = 0; semester < NUM_SEMESTERS; semester++) {
            for (int subject = 0; subject < NUM_SUBJECTS; subject++) {
                year_marks[index++] = marks[year][semester][subject];
            }
        }
        float year_mean = calculateMean(year_marks, NUM_SEMESTERS * NUM_SUBJECTS);
        char year_grade = assignGrade(year_mean);
        year_means[year] = year_mean;

        // Print the year transcript
        printYearTranscript(year + 1, year_marks, grades[year][0], year_mean, year_grade);
        printf("Year %d Mean Grade: %.2f (%c)\n", year + 1, year_mean, year_grade);
        printf("-------------------------\n");
    }

    // Calculate and print the final transcript
    float overall_mean = calculateMean(overall_marks, total_subjects);
    char overall_grade = assignGrade(overall_mean);
    printFinalTranscript(overall_mean, overall_grade);

    return 0;
}

// Function to assign grades based on marks
char assignGrade(float mark) {
    if (mark >= 71) return 'A';
    if (mark >= 61) return 'B';
    if (mark >= 51) return 'C';
    if (mark >= 41) return 'D';
    if (mark >= 31) return 'E';
    return 'F'; // Failing grade
}

// Function to calculate the mean of marks
float calculateMean(float marks[], int num_subjects) {
    float sum = 0;
    for (int i = 0; i < num_subjects; i++) {
        sum += marks[i];
    }
    return sum / num_subjects;
}

// Function to print the transcript for a specific semester
void printSemesterTranscript(int year, int semester, float marks[], char grades[], float mean_mark, char mean_grade) {
    printf("\nYear %d, Semester %d Transcript:\n", year, semester);
    printf("Subject\tMark\tGrade\n");
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        printf("%d\t%.2f\t%c\n", i + 1, marks[i], grades[i]);
    }
    printf("Mean Mark: %.2f\n", mean_mark);
    printf("Mean Grade: %c\n", mean_grade);
    printf("-------------------------\n");
}

// Function to print the transcript for a specific year
void printYearTranscript(int year, float marks[], char grades[], float mean_mark, char mean_grade) {
    printf("\nYear %d Transcript:\n", year);
    printf("Subject\tMark\tGrade\n");
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        printf("%d\t%.2f\t%c\n", i + 1, marks[i], grades[i]);
    }
    printf("Mean Mark: %.2f\n", mean_mark);
    printf("Mean Grade: %c\n", mean_grade);
    printf("-------------------------\n");
}

// Function to print the final transcript
void printFinalTranscript(float overall_mean, char overall_grade) {
    printf("\nFinal Transcript:\n");
    printf("Overall Mean Mark: %.2f\n", overall_mean);
    printf("Overall Mean Grade: %c\n", overall_grade);
    printf("-------------------------\n");
}
