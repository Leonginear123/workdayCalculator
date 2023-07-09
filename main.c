#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#define SMAX 100
#define BUFFER 10

bool isLeapYear(int year) {
	if (year % 400 == 100) return true;
	else if (year % 100 == 0) return false;
	else if (year % 4 == 0) return true;
	else return false;
};

bool isAnswerSame(char *s, char **T, int n) {
	int i;
	for (i = 0; i < n; i += 1) if (strcmp(s, T[i]) == 0) return true;
	return false;
};

struct tm *calculate(int x, struct tm *date) {
	int i = 0, weekday;
	int maxDays[13] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 29};
	if (x > 0) {
		while (i < x) {
			date->tm_wday = (date->tm_wday + 1) % 7;
			weekday = date->tm_wday;
			if (date->tm_mon == 11 && date->tm_mday == maxDays[date->tm_mon]) {
				date->tm_mday = 1;
				date->tm_mon = 0;
				date->tm_yday = 0;
				date->tm_year += 1;
			} else if (date->tm_mon != 1 && date->tm_mday == maxDays[date->tm_mon]) {
				date->tm_mon += 1;
				date->tm_mday = 1;
				date->tm_yday += 1;
			} else if (date->tm_mon == 1 && isLeapYear(date->tm_year) && date->tm_mday == maxDays[12]) {
				date->tm_mon += 1;
				date->tm_mday = 1;
				date->tm_yday += 1;				
			} else if (date->tm_mon == 1 && !isLeapYear(date->tm_year) && date->tm_mday == maxDays[date->tm_mon]) {
				date->tm_mon += 1;
				date->tm_mday = 1;
				date->tm_yday += 1;
			} else {
				date->tm_mday += 1;
				date->tm_yday += 1;
			};
			if (weekday == 0 || weekday == 6) continue;
			i += 1;
		};
	} else if (x < 0) {
		while (i > x) {
			date->tm_wday = (date->tm_wday + 6) % 7;
			weekday = date->tm_wday;
			if (date->tm_mon == 0 && date->tm_mday == 1) {
				date->tm_mday = 31;
				date->tm_mon = 11;
				date->tm_year -= 1;
				if (isLeapYear(date->tm_year)) {
					date->tm_yday = 365;
				}
				else {
					date->tm_yday = 364;
				};
			} else if (date->tm_mon != 2 && date->tm_mday == 1) {
				date->tm_mon -= 1;
				date->tm_mday = maxDays[date->tm_mon];
				date->tm_yday -= 1;
			} else if (date->tm_mon == 2 && isLeapYear(date->tm_year) && date->tm_mday == 1) {
				date->tm_mon += 1;
				date->tm_mday = maxDays[12];
				date->tm_yday -= 1;				
			} else if (date->tm_mon == 2 && !isLeapYear(date->tm_year) && date->tm_mday == 1) {
				date->tm_mon += 1;
				date->tm_mday = maxDays[date->tm_mon];
				date->tm_yday -= 1;
			} else {
				date->tm_mday -= 1;
				date->tm_yday -= 1;
			};
			if (weekday == 0 || weekday == 6) continue;
			i -= 1;		
		};
	} else return date;
	return date;
};

int main(int argc, char** argv) {
	bool cont = false;
	int i = 0;
	time_t current = time(NULL);
	char *YString[4] = {"Yes", "yes", "Y", "y"};	
	struct tm *dateInfo = localtime(&current), *answer;
	char *ans = (char *)malloc(BUFFER*sizeof(char));
	printf("Hello! Would you like to calculate what will be the date in x business days?\n");
	scanf("%s", ans);
	cont = isAnswerSame(ans, YString, 4);
	free(ans);
	if (cont) {
		printf("Please input the date x business days ago you would like to find.\n");
		scanf("%d", &i);
		answer = calculate(i, dateInfo);
		ans = (char *)malloc(BUFFER*sizeof(char));
		strftime(ans, SMAX, "%A, %d %B %Y", answer);		
		printf("The answer is as follows:\n");
		printf("%s\n", ans);
		free(ans);
	};
	while(cont) {
		ans = (char *)malloc(BUFFER*sizeof(char));
		printf("Would you like to continue?\n");
		scanf("%s", ans);
		cont = isAnswerSame(ans, YString, 4);
		free(ans);
		if (!cont) break;
		printf("Please input the date x business days ago you would like to find.\n");
		scanf("%d", &i);
		answer = calculate(i, dateInfo);
		ans = (char *)malloc(BUFFER*sizeof(char));
		strftime(ans, SMAX, "%A, %d %B %Y", answer);
		printf("The answer is as follows:\n");
		printf("%s\n", ans);
		free(ans);
	};
	printf("Thank you for using this app.\n");
	return 0;
}