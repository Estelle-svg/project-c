#include <stdio.h>
int inputAssignment() {
    int grade;
    scanf("%d", &grade);
    return grade;
}
double Average(int grades[];int num){
    double sum=0;
    for( int i=0;i<num;i++){
        sum+=grades[i];
    } return sum / num;
}
double FinalGrade(double average, int mid, int final) {
    double finalScore= (average * 0.40) + ( mid * 0.25) + (final * 0.35);
    return finalScore;
}
int main () {
    int numAssignment;
    int midterm,final;
    printf("Final Grade Calculator\n");
    printf("How many assignments? \n\n");
    scanf("%d", &numAssignment);
    int assignment[numAssignment];
    for ( int i=0;i< numAssignment;i++){
        printf("Enter Grade for assignment %d: \n",i+1);
        assignment[i]=inputAssignment();
    }
    printf("Enter midterm exam grade: ")
}