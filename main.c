#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ----------- Data structure -----------
struct TodoItem
{
    char text[50];
    int completed; // 0 = not done, 1 = done
};

// Global array in memory (optional, for current session)
struct TodoItem todo[100];
int todoCount = 0;

// ----------- Utility to clear stdin buffer -----------
void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* discard extra characters */
    }
}

// ----------- Add a new to-do item -----------
void addTodo(void)
{
    clearInputBuffer(); // make sure scanf leftovers are gone
    printf("Enter To-do: ");

    if (fgets(todo[todoCount].text, sizeof(todo[todoCount].text), stdin) == NULL)
    {
        printf("Input error.\n");
        return;
    }
    // Remove trailing newline from fgets
    todo[todoCount].text[strcspn(todo[todoCount].text, "\n")] = '\0';
    todo[todoCount].completed = 0;

    FILE *file = fopen("todo.txt", "a"); // append mode
    if (!file)
    {
        perror("Unable to open todo.txt");
        return;
    }
    fprintf(file, "%s|%d\n", todo[todoCount].text, todo[todoCount].completed);
    fclose(file);

    todoCount++;
    printf("Todo added successfully!\n");
}

// ----------- List all to-do items -----------
void listTodo(void)
{
    FILE *file = fopen("todo.txt", "r");
    if (!file)
    {
        printf("No todos yet (todo.txt missing).\n");
        return;
    }

    struct TodoItem t;
    int index = 1;
    printf("\n--- Current To-do List ---\n");
    while (fscanf(file, "%49[^|]|%d\n", t.text, &t.completed) == 2)
    {
        printf("%d. %s  [Done: %s]\n",
               index++,
               t.text,
               t.completed ? "Yes" : "No");
    }
    if (index == 1)
    {
        printf("(empty)\n");
    }
    fclose(file);
}

// ----------- Menu loop -----------
void displayMenu(void)
{
    int running = 1;
    while (running)
    {
        printf("\n-- To-do Application --\n");
        printf("1. Add to-do\n");
        printf("2. List to-dos\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        int choice;
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice)
        {
        case 1:
            addTodo();
            break;
        case 2:
            listTodo();
            break;
        case 3:
            printf("Goodbye!\n");
            running = 0;
            break;
        default:
            printf("Invalid choice.\n");
        }
    }
}

// ----------- Main entry point -----------
int main(void)
{
    displayMenu();
    return 0;
}