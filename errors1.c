#include "shell.h"

/**/
int stringToInteger(char *str) {
int index = 0;
unsigned long int result = 0;

if (*str == '+')
str++;
for (index = 0; str[index] != '\0'; index++) {
if (str[index] >= '0' && str[index] <= '9') {
result *= 10;
result += (str[index] - '0');
if (result > INT_MAX)
return -1;
} else {
return -1;
}
}
return (int)result;
}

void printErrorMessage(info_t *info, char *errorString) {
    print(info->filename);
    print(": ");
    printDecimal(info->lineCount, STDERR_FILENO);
    print(": ");
    print(info->arguments[0]);
    print(": ");
    print(errorString);
}

int printDecimal(int number, int fd) {
    int (*putCharacter)(char) = putchar;
    int i, count = 0;
    unsigned int absoluteValue, current;

    if (fd == STDERR_FILENO)
        putCharacter = eputchar;

    if (number < 0) {
        absoluteValue = -number;
        putCharacter('-');
        count++;
    } else {
        absoluteValue = number;
    }
    
    current = absoluteValue;
    for (i = 1000000000; i > 1; i /= 10) {
        if (absoluteValue / i) {
            putCharacter('0' + current / i);
            count++;
        }
        current %= i;
    }
    
    putCharacter('0' + current);
    count++;
    return count;
}

char *convertToBase(long int num, int base, int flags) {
    static char *array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0) {
        n = -num;
        sign = '-';
    }
    
    array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;
    
    return ptr;
}

void removeComments(char *buffer) {
    int index;

    for (index = 0; buffer[index] != '\0'; index++) {
        if (buffer[index] == '#' && (!index || buffer[index - 1] == ' ')) {
            buffer[index] = '\0';
            break;
        }
    }
}
