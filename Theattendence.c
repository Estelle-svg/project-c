#include<stdio.h>
struct Time {
    int hours;
    int minutes;
    int seconds;
};
struct Attendence {
    char name[50];
    struct Time time;
};
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
struct Attendence getLastest(struct Attendence attendance[5]) {
    struct Attendence latest = attendance[0];
    for(int i = 0; i < 5; i++) {
        if(compareTime(attendance[i].time, latest.time) == 1) {
        latest = attendance[i];
        }
    }   
    return latest;
}
int main() {
    struct Attendence attendance[5];
    for(int i = 0; i < 5; i++) {
        printf("Student %d\n", i+1);
        printf("Enter name: ");
        scanf("%s", attendance[i].name);
        printf("Enter Time: ");
        scanf("%d:%d:%d",
        &attendance[i].time.hours,
        &attendance[i].time.minutes,
        &attendance[i].time.seconds);
    }
    printf("The latest student is: %s", getLastest(attendance));
return 0;
}