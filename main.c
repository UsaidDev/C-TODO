#include <stdio.h>
#include <time.h>
#include <string.h>

struct Todo_Items
{
    char todo_item[50];
    int total_completed;
    char Date[20];
};

void ClearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

int addTodo(){
    struct Todo_Items todo;
    printf("Welcome to to-do\n");
    printf("Enter To-do: ");
    fgets(todo.todo_item, sizeof(todo.todo_item), stdin);
    todo.todo_item[strcspn(todo.todo_item, "\n")] = '\0';

    time_t currentTime;
    time(&currentTime);

    // printf("Item: %s\n", todo.todo_item);
    // printf("Current time: %s", ctime(&currentTime));
    return 0;    
}

// int listTodo(){

//     return 0;
// }

int main (){
    int choice;
    printf("Please select the number:\n");
    printf("1:Add todo\n");
    printf("2:List todo\n");
    printf("3:Update todo\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    ClearInputBuffer();
    switch (choice)
    {
    case 1:
        addTodo();
        break;
    case 2:
        printf("List todo not implemented yet.\n");
        break;
    case 3:
        printf("Update todo not implemented yet.\n");
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }
    return 0;
}