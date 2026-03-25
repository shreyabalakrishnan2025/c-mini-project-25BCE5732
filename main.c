#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Expense {
    char date[20];
    char category[20];
    float amount;
    char note[100];
};

void addExpense();
void showAll();
void monthlyTotal();
void categoryTotal();
void searchByDate();
void searchByCategory();

float budget = 5000;

/* ── helper: read a validated integer in [min,max] ── */
int readInt(const char *prompt, int min, int max)
{
    int val;
    while (1) {
        printf("%s (%d-%d): ", prompt, min, max);
        fflush(stdout);
        if (scanf("%d", &val) != 1) {
            printf("Invalid input\n");
            while (getchar() != '\n');
            continue;
        }
        if (val < min || val > max) {
            printf("Enter a value between %d and %d\n", min, max);
            continue;
        }
        return val;
    }
}

int main()
{
    printf("Expense Tracker Started\n");
    int choice;

    while (1)
    {
        printf("\n===== Expense Tracker =====\n");
        printf("1 Add Expense\n");
        printf("2 Show All Expenses\n");
        printf("3 Monthly Total\n");
        printf("4 Category Total\n");
        printf("5 Search by Date\n");
        printf("6 Search by Category\n");
        printf("7 Exit\n");

        printf("Enter choice: ");
        fflush(stdout);

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice)
        {
            case 1: addExpense();        break;
            case 2: showAll();           break;
            case 3: monthlyTotal();      break;
            case 4: categoryTotal();     break;
            case 5: searchByDate();      break;
            case 6: searchByCategory();  break;
            case 7: exit(0);
            default: printf("Invalid choice\n");
        }
    }
}

void addExpense()
{
    struct Expense e;

    FILE *fp = fopen("expenses.txt", "a");
    if (fp == NULL) {
        printf("File error\n");
        return;
    }

    /* ── structured date entry (only change from original) ── */
    int year  = readInt("Enter year",  2000, 2100);
    int month = readInt("Enter month", 1,    12);

    /* max days for the given month */
    int maxDay = 31;
    if (month == 2)
        maxDay = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? 29 : 28;
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        maxDay = 30;

    int day = readInt("Enter day", 1, maxDay);
    sprintf(e.date, "%04d-%02d-%02d", year, month, day);

    printf("Enter category: ");
    fflush(stdout);
    scanf("%19s", e.category);

    printf("Enter amount: ");
    fflush(stdout);
    if (scanf("%f", &e.amount) != 1 || e.amount <= 0) {
        printf("Invalid amount\n");
        fclose(fp);
        return;
    }

    printf("Enter note: ");
    fflush(stdout);
    scanf("%99s", e.note);

    fprintf(fp, "%s %s %.2f %s\n", e.date, e.category, e.amount, e.note);
    fclose(fp);

    printf("Expense added successfully\n");
}

void showAll()
{
    struct Expense e;

    FILE *fp = fopen("expenses.txt", "r");
    if (fp == NULL) {
        printf("No records found\n");
        return;
    }

    printf("\nDate       Category   Amount  Note\n");
    while (fscanf(fp, "%s %s %f %s", e.date, e.category, &e.amount, e.note) != EOF)
        printf("%s %s %.2f %s\n", e.date, e.category, e.amount, e.note);

    fclose(fp);
}

void monthlyTotal()
{
    struct Expense e;

    FILE *fp = fopen("expenses.txt", "r");
    if (fp == NULL) {
        printf("No data available\n");
        return;
    }

    /* use same structured entry so format always matches */
    int year  = readInt("Enter year",  2000, 2100);
    int month = readInt("Enter month", 1,    12);

    char prefix[8];
    sprintf(prefix, "%04d-%02d", year, month);

    float total = 0;
    while (fscanf(fp, "%s %s %f %s", e.date, e.category, &e.amount, e.note) != EOF)
        if (strncmp(e.date, prefix, 7) == 0)
            total += e.amount;

    printf("Monthly expense = %.2f\n", total);
    if (total > budget)
        printf("WARNING Budget exceeded\n");

    fclose(fp);
}

void categoryTotal()
{
    struct Expense e;

    FILE *fp = fopen("expenses.txt", "r");
    if (fp == NULL) {
        printf("No data available\n");
        return;
    }

    char category[20];
    float total = 0;

    printf("Enter category: ");
    fflush(stdout);
    scanf("%19s", category);

    while (fscanf(fp, "%s %s %f %s", e.date, e.category, &e.amount, e.note) != EOF)
        if (strcmp(e.category, category) == 0)
            total += e.amount;

    printf("Total expense for %s = %.2f\n", category, total);
    fclose(fp);
}

void searchByDate()
{
    struct Expense e;

    FILE *fp = fopen("expenses.txt", "r");
    if (fp == NULL) {
        printf("No data available\n");
        return;
    }

    /* build the search date the same structured way */
    int year  = readInt("Enter year",  2000, 2100);
    int month = readInt("Enter month", 1,    12);

    int maxDay = 31;
    if (month == 2)
        maxDay = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? 29 : 28;
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        maxDay = 30;

    int day = readInt("Enter day", 1, maxDay);

    char date[20];
    sprintf(date, "%04d-%02d-%02d", year, month, day);

    int found = 0;
    while (fscanf(fp, "%s %s %f %s", e.date, e.category, &e.amount, e.note) != EOF)
    {
        if (strcmp(e.date, date) == 0) {
            printf("%s %s %.2f %s\n", e.date, e.category, e.amount, e.note);
            found = 1;
        }
    }

    if (!found)
        printf("No records found\n");

    fclose(fp);
}

void searchByCategory()
{
    struct Expense e;

    FILE *fp = fopen("expenses.txt", "r");
    if (fp == NULL) {
        printf("No data available\n");
        return;
    }

    char category[20];
    int found = 0;

    printf("Enter category: ");
    fflush(stdout);
    scanf("%19s", category);

    while (fscanf(fp, "%s %s %f %s", e.date, e.category, &e.amount, e.note) != EOF)
    {
        if (strcmp(e.category, category) == 0) {
            printf("%s %s %.2f %s\n", e.date, e.category, e.amount, e.note);
            found = 1;
        }
    }

    if (!found)
        printf("No records found\n");

    fclose(fp);
}