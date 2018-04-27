#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef unsigned char BYTE;

#define CHAR_BITS 8
#define LAST(k,n) ((k) & ((1<<(n))-1))
#define MID(k,m,n) LAST((k)>>(m),((n)-(m)))

void print_hex(unsigned char *s);
void formula(unsigned int *a);
void substitution(unsigned char *text);
void shifting(unsigned char *s);
void populate(unsigned char *text,  unsigned char enc[]);
void chaining_mode(unsigned char *text, unsigned int IV, unsigned int key);


void shifting(unsigned char *s){
    *s = (*s << 2) | (*s >> (CHAR_BITS - 2));
}

void substitution(unsigned char *text){
    
    unsigned int a, c;
    a = MID(*text,4,8);
    c = MID(*text,0,4);
    formula(&a);
    formula(&c);
    *text = a << 4 | c;
}

void formula(unsigned int *a){
    *a = ((*a+1)*7)%(17-1);
}

void print_hex(unsigned char *s)
{
  while(*s){
    printf("%02x", (unsigned int) *s++);
    }
  printf("\n");
}

void populate(unsigned char *text,  unsigned char enc[]){
    int i = 1;
    while (*text){
        enc[i] = *text;
        *text++;
        i++;
    }
}

void chaining_mode(unsigned char *text, unsigned int IV, unsigned int key) {
    BYTE a,b,c,d;
    d=(key&0xFF); //extract first byte
    c=((key>>8)&0xFF); //extract second byte
    b=((key>>16)&0xFF); //extract third byte
    a=((key>>24)&0xFF); //extract fourth byte
     unsigned char enc[4] = {a,b,c,d};
     unsigned char populated[800];
    populate(text, populated);
    int counter = 0;
    int i = 0;
    while(*text){
        if (i == 0){
            *text ^= IV;
            *text ^= enc[0];
            substitution(text);
            shifting(text);
            *text ^= enc[1];
            substitution(text);
            shifting(text);
            *text ^= enc[2];
            substitution(text);
            *text ^= enc[3];
            //printf("Value of text before increment: %d\n", *text);
            populated[0] = *text;
            //printf("Populated[0]: %d\n", populated[0]);
            (*text++);
            //printf("Value of text after increment: %d\n", *text);
            i++;
        }
        else if (i != 0){
            //printf("Value of text: %d\n", *text);
            //printf("value of populated: %d\n", populated[counter]);
            *text ^= populated[counter];
            //printf("Value of text after xor: %d\n", *text);
            *text ^= enc[0];
            substitution(text);
            shifting(text);
            *text ^= enc[1];
            substitution(text);
            shifting(text);
            *text ^= enc[2];
            substitution(text);
            counter++;
            *text ^= enc[3];
            populated[counter] = *text;
            (*text++);
        }
    }
}

/*
void substitution_step(unsigned char *s){
    while(*s){
        substitution(s);
        (*s++);
    }
}
*/
