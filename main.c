#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void menu();
void addRecord();
void displayRecord();
void deleteRecord();
void searchRecord();
void searchById();
void searchByName();
void slotBooking();
void morningSlot();
void afternoonSlot();
void eveningSlot();

struct slots
{
    char time[30];
    int seats;
} s;

struct customer
{
    int id;
    char name[30];
    char number[15];
    int BMI;
    char address[30];
    char DOJ[50];
} c;

int main()
{
    while (1)
    {
        int n;
        menu();
        printf("Enter your choice: ");
        scanf("%d", &n);
        if (n == 1)
        {
            addRecord();
        }
        if (n == 2)
        {
            deleteRecord();
        }
        if (n == 3)
        {
            displayRecord();
        }

        if (n == 4)
        {
            searchRecord();
        }

        if (n == 5)
        {
            slotBooking();
        }

        if (n == 6)
        {
            break;
        }
    }

    printf("Exited successfully\n");

    return 0;
}

// Add record
void addRecord()
{
    system("cls");
    printf("\n\n\t Add record \n\n");

    printf("Enter id of customer:");
    scanf("%d", &c.id);
    printf("Enter name of customer:");
    scanf("%s", c.name);
    printf("Enter contact number of customer:");
    scanf("%s", c.number);
    printf("Enter Body Mass Index of customer:");
    scanf("%d", &c.BMI);
    printf("Enter address of customer:");
    scanf("%s", c.address);
    printf("Enter date of joining of customer:");
    scanf("%s", c.DOJ);

    FILE *fp = fopen("customers_record.txt", "a");
    if (fp == NULL)
    {
        printf("Error opening the file\n");
        return;
    }
    fprintf(fp, "\n%d %s %s %d %s %s", c.id, c.name, c.number, c.BMI, c.address, c.DOJ);
    fclose(fp);
    printf("Record added succuessfully.\n");
}

// Display record
void displayRecord()
{
    system("cls");
    FILE *fp;
    fp = fopen("customers_record.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening the file");
        return;
    }
    printf("\n\n\t\tDisplaying customer's details\n\n");
    printf("\n\nId\t\tName\t\t Phone number\t\t BMI\t\t Address\t\t Date of Joining\n\n");
    while (!feof(fp))
    {
        fscanf(fp, "%d %s %s %d %s %s", &c.id, c.name, c.number, &c.BMI, c.address, c.DOJ);
        printf("%d\t\t %s\t\t %s\t\t %d\t\t %s\t\t %s\n", c.id, c.name, c.number, c.BMI, c.address, c.DOJ);
    }
}

// Delete record
void deleteRecord()
{
    system("cls");
    FILE *fp, *fp2;
    int id;
    int flag = 0;
    fp = fopen("customers_record.txt", "r");
    fp2 = fopen("temp.txt", "w");
    if (fp == NULL || fp2 == NULL)
    {
        printf("Error opening the file");
        return;
    }
    printf("Enter the id of the customer you want to delete: ");
    scanf("%d", &id);

    while (!feof(fp))
    {
        fscanf(fp, "%d %s %s %d %s %s", &c.id, c.name, c.number, &c.BMI, c.address, c.DOJ);
        if (c.id != id)
        {
            fprintf(fp2, "\n%d %s %s %d %s %s", c.id, c.name, c.number, c.BMI, c.address, c.DOJ);
        }
        else
        {
            flag = 1;
        }
    }
    fclose(fp);
    fclose(fp2);
    fp = fopen("customers_record.txt", "w");
    fp2 = fopen("temp.txt", "r");

    while (!feof(fp2))
    {
        fscanf(fp2, "%d %s %s %d %s %s", &c.id, c.name, c.number, &c.BMI, c.address, c.DOJ);
        fprintf(fp, "\n%d %s %s %d %s %s", c.id, c.name, c.number, c.BMI, c.address, c.DOJ);
    }

    fclose(fp);
    fclose(fp2);

    if (flag == 1)
    {
        system("cls");
        printf("Record deleted successfully");
    }
    else
    {
        system("cls");
        printf("Record not found");
    }
}

// search record
void searchRecord()
{
    int choice;
    system("cls");
    printf("\n\n\t\t Search Record\n\n");
    printf("\n\nEnter 1 to search by id\n");
    printf("Enter 2 to search by name and phone number\n\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        searchById();
        break;
    case 2:
        searchByName();
        break;
    default:
        printf("Enter the corrent choice\n");
        break;
    }
}

// search by id
void searchById()
{
    system("cls");
    printf("\n\n\t\t Searching by id\n\n");
    FILE *fp;
    int id, flag = 0;
    fp = fopen("customers_record.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening the file");
        return;
    }
    printf("Enter the id of the customer you want to search: ");
    scanf("%d", &id);

    while (!feof(fp))
    {
        fscanf(fp, "%d %s %s %d %s %s", &c.id, c.name, c.number, &c.BMI, c.address, c.DOJ);
        if (c.id == id)
        {
            printf("\nThe customer with matching id is: \n");
            printf("Id: %d\n", c.id);
            printf("Name: %s\n", c.name);
            printf("Phone number: %s\n", c.number);
            printf("Body Mass Index: %d\n", c.BMI);
            printf("Address: %s\n", c.address);
            printf("Date of Joining: %s\n", c.DOJ);
            flag = 1;
        }
    }
    if (flag == 0)
    {
        system("cls");
        printf("Record not found");
    }
    fclose(fp);
}

// search by name
void searchByName()
{
    system("cls");
    printf("\n\n\t\t Searching by name and phone number\n\n");
    FILE *fp;
    char name[30], phone[15];
    int flag = 0;
    fp = fopen("customers_record.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening the file");
        return;
    }

    printf("Enter the name of the customer you want to search: ");
    scanf("%s", name);

    printf("Enter the phone number of the same customer you want to search: ");
    scanf("%s", phone);

    for (int i = 0; i < strlen(name); i++)
    {
        name[i] = tolower(name[i]);
    }

    while (!feof(fp))
    {
        fscanf(fp, "%d %s %s %d %s %s", &c.id, c.name, c.number, &c.BMI, c.address, c.DOJ);
        for (int i = 0; i < strlen(c.name); i++)
        {
            c.name[i] = tolower(c.name[i]);
        }
        if ((strcmp(name, c.name) == 0) && (strcmp(phone, c.number) == 0))
        {
            printf("\nThe customer with matching name is: \n");
            printf("Id: %d\n", c.id);
            printf("Name: %s\n", c.name);
            printf("Phone number: %s\n", c.number);
            printf("Body Mass Index: %d\n", c.BMI);
            printf("Address: %s\n", c.address);
            printf("Date of Joining: %s\n", c.DOJ);
            flag = 1;
        }
    }

    if (flag == 0)
    {
        system("cls");
        printf("Record not found");
    }
    fclose(fp);
}

// slot booking interface
void slotBooking()
{
    system("cls");

    printf("\n\n\t\t Slog booking interface \n\n");
    int choice;
    FILE *fp;
    fp = fopen("slots.txt", "r");
    while (!feof(fp))
    {
        fscanf(fp, "%s %d", s.time, &s.seats);
        if (s.seats == 50)
        {
            printf("%s: %d (full)\n", s.time, s.seats);
        }
        else
        {
            printf("%s: %d (%d left)\n", s.time, s.seats, 50 - s.seats);
        }
    }
    printf("Enter 1 to choose morning.\n");
    printf("Enter 2 to choose afternoon.\n");
    printf("Enter 3 to choose evening.\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        morningSlot();
        break;

    case 2:
        afternoonSlot();
        break;

    case 3:
        eveningSlot();
        break;

    default:
        break;
    }
}

// morning slot
void morningSlot()
{
    system("cls");
    FILE *fp, *fp2;
    int id;
    int full = 0;
    fp = fopen("slots.txt", "r");
    fp2 = fopen("slot_temp.txt", "w");
    if (fp == NULL || fp2 == NULL)
    {
        printf("Error opening the file");
        return;
    }

    char time[30] = "morning";

    while (!feof(fp))
    {
        fscanf(fp, "%s %d", s.time, &s.seats);
        if (strcmp(s.time, time) == 0)
        {
            if (s.seats == 50)
            {
                full = 1;
                fprintf(fp2, "\n%s %d", s.time, s.seats);
            }
            else
            {
                fprintf(fp2, "\n%s %d", s.time, s.seats + 1);
            }
        }
        else
        {
            fprintf(fp2, "\n%s %d", s.time, s.seats);
        }
    }
    fclose(fp);
    fclose(fp2);
    fp = fopen("slots.txt", "w");
    fp2 = fopen("slot_temp.txt", "r");

    while (!feof(fp2))
    {
        fscanf(fp2, "%s %d", s.time, &s.seats);
        fprintf(fp, "\n%s %d", s.time, s.seats);
    }

    fclose(fp);
    fclose(fp2);

    if (full == 1)
    {
        printf("Sorry :( the seats are full, try in next slot\n");
    }
    else
    {
        printf("Slot booked successfylly :) ");
    }
}

// afternoon slot
void afternoonSlot()
{
    system("cls");
    FILE *fp, *fp2;
    int id;
    int full = 0;
    fp = fopen("slots.txt", "r");
    fp2 = fopen("slot_temp.txt", "w");
    if (fp == NULL || fp2 == NULL)
    {
        printf("Error opening the file");
        return;
    }

    char time[30] = "afternoon";

    while (!feof(fp))
    {
        fscanf(fp, "%s %d", s.time, &s.seats);
        if (strcmp(s.time, time) == 0)
        {
            if (s.seats == 50)
            {
                full = 1;
                fprintf(fp2, "\n%s %d", s.time, s.seats);
            }
            else
            {
                fprintf(fp2, "\n%s %d", s.time, s.seats + 1);
            }
        }
        else
        {
            fprintf(fp2, "\n%s %d", s.time, s.seats);
        }
    }
    fclose(fp);
    fclose(fp2);
    fp = fopen("slots.txt", "w");
    fp2 = fopen("slot_temp.txt", "r");

    while (!feof(fp2))
    {
        fscanf(fp2, "%s %d", s.time, &s.seats);
        fprintf(fp, "\n%s %d", s.time, s.seats);
    }

    fclose(fp);
    fclose(fp2);

    if (full == 1)
    {
        printf("Sorry :( the seats are full, try in next slot\n");
    }
    else
    {
        printf("Slot booked successfylly :) ");
    }
}

void eveningSlot()
{
    system("cls");
    FILE *fp, *fp2;
    int id;
    int full = 0;
    fp = fopen("slots.txt", "r");
    fp2 = fopen("slot_temp.txt", "w");
    if (fp == NULL || fp2 == NULL)
    {
        printf("Error opening the file");
        return;
    }

    char time[30] = "evening";

    while (!feof(fp))
    {
        fscanf(fp, "%s %d", s.time, &s.seats);
        if (strcmp(s.time, time) == 0)
        {
            if (s.seats == 50)
            {
                full = 1;
                fprintf(fp2, "\n%s %d", s.time, s.seats);
            }
            else
            {
                fprintf(fp2, "\n%s %d", s.time, s.seats + 1);
            }
        }
        else
        {
            fprintf(fp2, "\n%s %d", s.time, s.seats);
        }
    }
    fclose(fp);
    fclose(fp2);
    fp = fopen("slots.txt", "w");
    fp2 = fopen("slot_temp.txt", "r");

    while (!feof(fp2))
    {
        fscanf(fp2, "%s %d", s.time, &s.seats);
        fprintf(fp, "\n%s %d", s.time, s.seats);
    }

    fclose(fp);
    fclose(fp2);

    if (full == 1)
    {
        printf("Sorry :( the seats are full, try in next slot\n");
    }
    else
    {
        printf("Slot booked successfylly :) ");
    }
}

// Menu
void menu()
{
    printf("\n\n =====================================\n Fitness Club Management \n\n \n Enter 1 to add record of customers.\n Enter 2 to delete record of customer. \n Enter 3 to display record of customer. \n Enter 4 to search record of customer. \n Enter 5 to display and check time slot.  \n Enter 6 to exit \n ======================================= \n\n");
}