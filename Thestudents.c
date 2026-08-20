#include <stdio.h>
struct Student{
    char student_name[50];
    int student_id;
    float student_scores[5];
};
double getScoreAverage (struct Student student) {
    double sum = 0;
    int i = 0;
    for( i = 0; i < 5; i++) {
        sum += student.student_scores[i];
    }
    double average = sum / i;
    return average;
}
int main() {
    struct Student s1 = {"meymey", 20, {65,67,75,80,54}};
    struct Student s2 = {"prathpi", 13, {89,78,82,85,90}};
    printf("Student name: %s\n", s1.student_name);
    printf("Student id: %d\n", s1.student_id);
    printf("Student average: %.2f\n", getScoreAverage(s1));
    printf("Student name: %s\n", s2.student_name);
    printf("Student id: %d\n", s2.student_id);
    printf("Student average: %.2f\n", getScoreAverage(s2));
    return 0;
}