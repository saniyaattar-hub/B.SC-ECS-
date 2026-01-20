/***************************************************************
 * Program Name : Student Result System
 * Description  : This program accepts roll number, name, and
 *                marks of five subjects for 10 students.
 *                It calculates total and average marks,
 *                displays the result in tabular format,
 *                finds top 3 rank holders based on average,
 *                and identifies the highest scorer of each
 *                subject with student name.
 *
 * Author       : Saniya
 * Date         : 04 January 2026
 * Version      : 1.0
 ***************************************************************/

#include <stdio.h>

#define STUDENTS 10
#define SUBJECTS 5

/* Structure to store student details */
typedef struct {
    int roll;
    char name[30];
    int marks[SUBJECTS];
    int total;
    float average;
} Student;

/* Function declarations */
void acceptData(Student s[]);
void displayTable(Student s[]);
void displayTopThree(Student s[]);
void displaySubjectToppers(Student s[]);

int main(void) {
    Student s[STUDENTS];

    /* Accept input and calculate results */
    acceptData(s);

    /* Display result system in tabular format */
    displayTable(s);

    /* Display first three rank holders */
    displayTopThree(s);

    /* Display subject-wise highest scores */
    displaySubjectToppers(s);

    return 0;
}

/*-------------------------------------------------------------
 * Function Name : acceptData
 * Purpose       : Accept student details and calculate total
 *                 and average marks
 *------------------------------------------------------------*/
void acceptData(Student s[]) {
    for (int i = 0; i < STUDENTS; i++) {
        s[i].total = 0;

        printf("\nEnter details of Student %d\n", i + 1);

        printf("Roll No : ");
        scanf("%d", &s[i].roll);

        printf("Name    : ");
        scanf(" %[^\n]", s[i].name);

        /* Logic: Accept marks and calculate total */
        for (int j = 0; j < SUBJECTS; j++) {
            printf("Marks of Subject %d: ", j + 1);
            scanf("%d", &s[i].marks[j]);
            s[i].total += s[i].marks[j];
        }

        /* Logic: Calculate average marks */
        s[i].average = s[i].total / (float)SUBJECTS;
    }
}

/*-------------------------------------------------------------
 * Function Name : displayTable
 * Purpose       : Display student result in tabular format
 *------------------------------------------------------------*/
void displayTable(Student s[]) {
    printf("\n================ RESULT SYSTEM =================\n");
    printf("Roll\tName\t\tTotal\tAverage\n");
    printf("------------------------------------------------\n");

    for (int i = 0; i < STUDENTS; i++) {
        printf("%d\t%-10s\t%d\t%.2f\n",
               s[i].roll, s[i].name, s[i].total, s[i].average);
    }
}

/*-------------------------------------------------------------
 * Function Name : displayTopThree
 * Purpose       : Find and display first 3 rank students
 *------------------------------------------------------------*/
void displayTopThree(Student s[]) {
    Student temp;

    /* Logic: Sort students based on average marks (descending) */
    for (int i = 0; i < STUDENTS - 1; i++) {
        for (int j = i + 1; j < STUDENTS; j++) {
            if (s[i].average < s[j].average) {
                temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }

    printf("\n============= TOP 3 RANK HOLDERS =============\n");
    for (int i = 0; i < 3; i++) {
        printf("Rank %d : %s (Average = %.2f)\n",
               i + 1, s[i].name, s[i].average);
    }
}

/*-------------------------------------------------------------
 * Function Name : displaySubjectToppers
 * Purpose       : Find highest marks of each subject
 *------------------------------------------------------------*/
void displaySubjectToppers(Student s[]) {
    int max, index;

    printf("\n========= SUBJECT-WISE HIGHEST SCORES =========\n");

    /* Logic: Compare marks subject-wise */
    for (int j = 0; j < SUBJECTS; j++) {
        max = s[0].marks[j];
        index = 0;

        for (int i = 1; i < STUDENTS; i++) {
            if (s[i].marks[j] > max) {
                max = s[i].marks[j];
                index = i;
            }
        }

        printf("Subject %d : %s (%d Marks)\n",
               j + 1, s[index].name, max);
    }
}
