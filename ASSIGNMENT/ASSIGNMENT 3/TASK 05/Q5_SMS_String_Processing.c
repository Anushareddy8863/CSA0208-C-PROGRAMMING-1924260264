/* Q5 - Processing Text Without the Library
   Compile: gcc Q5_SMS_String_Processing.c -o q5
   Run: ./q5
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h> /* Used only in the comparison demonstration below. */

int word_count(const char s[]) {
    int count=0, inside=0;
    for(int i=0;s[i]!='\0';i++) {
        if(!isspace((unsigned char)s[i])) {
            if(!inside) count++;
            inside=1;
        } else inside=0;
    }
    return count;
}
int is_palindrome(const char s[]) {
    int left=0,right=0;
    while(s[right]!='\0') right++;
    right--;
    while(left<right) {
        while(left<right && !isalpha((unsigned char)s[left])) left++;
        while(left<right && !isalpha((unsigned char)s[right])) right--;
        if(tolower((unsigned char)s[left]) !=
           tolower((unsigned char)s[right])) return 0;
        left++; right--;
    }
    return 1;
}
void uppercase_manual(char s[]) {
    for(int i=0;s[i]!='\0';i++)
        if(s[i]>='a' && s[i]<='z') s[i]=(char)(s[i]-'a'+'A');
}
void reverse_manual(char s[]) {
    int n=0;
    while(s[n]!='\0') n++;
    for(int i=0;i<n/2;i++) {
        char t=s[i]; s[i]=s[n-1-i]; s[n-1-i]=t;
    }
}
int main(void) {
    printf("Words: %d\n",word_count(" Meet at the library at 5 PM "));
    printf("%d %d\n",is_palindrome("Madam, I'm Adam"),is_palindrome("Hello"));
    printf("Tab-separated words: %d\n",word_count("one\ttwo\tthree"));

    char message[100]="Good morning students";
    uppercase_manual(message);
    printf("Uppercase: %s\n",message);
    reverse_manual(message);
    printf("Reversed: %s\n",message);

    /* Safe input example: fgets prevents unbounded input. */
    char input[100];
    printf("Enter a short feedback message (optional): ");
    if(fgets(input,sizeof input,stdin)) {
        input[strcspn(input,"\n")]='\0';
        printf("Input has %d words\n",word_count(input));
    }
    return 0;
}
