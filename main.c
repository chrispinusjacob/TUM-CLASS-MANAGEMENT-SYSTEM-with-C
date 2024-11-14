#include <stdio.h>
#include <string.h>

int main() {
    int choice;

    do {
        // Display menu
        printf("\nStudent Management System - Application Module\n");
        printf("1. Add Available Course\n");
        printf("2. Apply for Course\n");
        printf("3. Approve/Decline Applications\n");
        printf("4. List Available Courses\n");
        printf("5. List Successful Applicants\n");
        printf("6. List Unsuccessful Applicants\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            // Add available courses
            FILE *file = fopen("courses.txt", "a");
            char courseName[100];
            int courseId;

            printf("Enter Course ID: ");
            scanf("%d", &courseId);
            printf("Enter Course Name: ");
            scanf(" %[^\n]%*c", courseName); // Reads input with spaces

            fprintf(file, "%d,%s\n", courseId, courseName);
            fclose(file);

            printf("Course added successfully!\n");

        } else if (choice == 2) {
            // Apply for course
            FILE *file = fopen("applications.txt", "a");
            int studentId, courseId, score;
            char studentName[50];

            printf("Enter Student ID: ");
            scanf("%d", &studentId);
            printf("Enter Student Name: ");
            scanf(" %[^\n]%*c", studentName);
            printf("Enter Course ID: ");
            scanf("%d", &courseId);
            printf("Enter Score: ");
            scanf("%d", &score);

            fprintf(file, "%d,%s,%d,%d\n", studentId, studentName, courseId, score);
            fclose(file);

            printf("Application submitted successfully!\n");

        } else if (choice == 3) {
            // Approve/Decline applications based on score
            FILE *file = fopen("applications.txt", "r");
            FILE *approved = fopen("approved.txt", "w");
            FILE *declined = fopen("declined.txt", "w");
            char line[150];
            int threshold = 50; // Example score threshold for approval

            while (fgets(line, sizeof(line), file)) {
                int studentId, courseId, score;
                char studentName[50];
                sscanf(line, "%d,%[^,],%d,%d", &studentId, studentName, &courseId, &score);

                if (score >= threshold) {
                    fprintf(approved, "%d,%s,%d,%d\n", studentId, studentName, courseId, score);
                } else {
                    fprintf(declined, "%d,%s,%d,%d\n", studentId, studentName, courseId, score);
                }
            }

            fclose(file);
            fclose(approved);
            fclose(declined);

            printf("Applications processed successfully!\n");

        } else if (choice == 4) {
            // List available courses
            FILE *file = fopen("courses.txt", "r");
            char line[150];

            printf("Available Courses:\n");
            printf("Course ID\tCourse Name\n");
            while (fgets(line, sizeof(line), file)) {
                int courseId;
                char courseName[100];
                sscanf(line, "%d,%[^\n]", &courseId, courseName);
                printf("%d\t\t%s\n", courseId, courseName);
            }
            fclose(file);

        } else if (choice == 5) {
            // List successful applicants
            FILE *file = fopen("approved.txt", "r");
            char line[150];

            printf("Successful Applicants:\n");
            printf("Student ID\tStudent Name\tCourse ID\tScore\n");
            while (fgets(line, sizeof(line), file)) {
                int studentId, courseId, score;
                char studentName[50];
                sscanf(line, "%d,%[^,],%d,%d", &studentId, studentName, &courseId, &score);
                printf("%d\t\t%s\t\t%d\t\t%d\n", studentId, studentName, courseId, score);
            }
            fclose(file);

        } else if (choice == 6) {
            // List unsuccessful applicants
            FILE *file = fopen("declined.txt", "r");
            char line[150];

            printf("Unsuccessful Applicants:\n");
            printf("Student ID\tStudent Name\tCourse ID\tScore\n");
            while (fgets(line, sizeof(line), file)) {
                int studentId, courseId, score;
                char studentName[50];
                sscanf(line, "%d,%[^,],%d,%d", &studentId, studentName, &courseId, &score);
                printf("%d\t\t%s\t\t%d\t\t%d\n", studentId, studentName, courseId, score);
            }
            fclose(file);

        } else if (choice != 7) {
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 7);

    printf("Exiting... Goodbye!\n");
    return 0;
}
