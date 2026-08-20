#include<stdio.h>
struct Time {
    int hours;
    int minutes;
    int seconds;
};
struct Time sumTime(struct Time t1 , struct Time t2) {
    struct Time result;  
    int sumSeconds = t1.seconds + t2.seconds;
    int sumMinutes = t1.minutes + t2.minutes;

    result.seconds = sumSeconds % 60;
    sumMinutes += sumSeconds / 60;
    result.minutes = sumMinutes % 60;
    result.hours = t1.hours + t2.hours + (sumMinutes / 60);
    return result;
}
int compareTime(struct Time t1 , struct Time t2) {
    if(t1.hours != t2.hours) {
        return (t1.hours > t2.hours) ? 1 : -1;
    }
    if(t1.minutes != t2.minutes) {
        return (t1.minutes > t2.minutes) ? 1 : -1;
    }
    if(t1.seconds != t2.seconds) {
        return (t1.seconds > t2.seconds) ? 1 : -1;
    }
    return 0;
}
int main() {
    struct Time t1;
    struct Time t2;
    printf("Enter Time 1:\n");
    printf(" Hours: ");
    scanf("%d", &t1.hours);
    printf(" Minutes: ");
    scanf("%d", &t1.minutes);
    printf(" Seconds: ");
    scanf("%d", &t1.seconds);
    printf("Enter Time 2:\n");
    printf(" Hours: ");
    scanf("%d", &t2.hours);
    printf(" Minutes: ");
    scanf("%d", &t2.minutes);
    printf(" Seconds: ");
    scanf("%d", &t2.seconds);
    printf("\nTime 1: %dh %dm %ds\n", t1.hours, t1.minutes, t1.seconds);
    printf("Time 2: %dh %dm %ds\n", t2.hours, t2.minutes, t2.seconds);
    
    struct Time sum = sumTime(t1,t2);
    printf("The sum of times is : %dh %dm  %ds\n", sum.hours,sum.minutes,sum.seconds);
    
    int com = compareTime(t1,t2);
    if (com == 1) {
        printf("Time 1 is greater than Time 2\n");
    }else if (com == -1) {
        printf("Time 2 is greater than Time 1\n");
    }else {
        printf("Time 1 is equal to Time 2\n");
    }
    return 0;
}