#include <stdio.h>
#include <stdlib.h>
typedef struct {
    char name[50];
    int salary;
}Employee;
int main (){
    //1.
    int size=2;
    Employee* employees= (Employee*)malloc(size*sizeof(Employee));
    //2.
    for(int i=0;i<size;i++){
        printf("Enter %d name: ", i+1);
        scanf("%s", &employees[i].name);
        printf("Enter %d salary: ", i+1);
        scanf("%d", &employees[i].salary);
    }
    printf("\n");
    //3.
    int new_size=5;
    Employee* newone=(Employee*)realloc(employees, new_size*sizeof(Employee));
    employees = newone;
    //4.
    for(int i=size;i<new_size;i++){
        printf("Enter %d name: ", i+1);
        scanf("%s", &employees[i].name);
        printf("Enter %d salary: ", i+1);
        scanf("%d", &employees[i].salary);
    }
    //5
    printf("\n");
    for ( int i=0;i<new_size;i++){
        printf("Employee %d name: %s\n", i+1, employees[i].name);
        printf("Employee %d salary : %d\n", i+1, employees[i].salary);
    }
    //7
    free(newone);
    newone=NULL;
    return 0;
}