#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef unsigned char BYTE;

#define CHAR_BITS 8
#define LAST(k,n) ((k) & ((1<<(n))-1))
#define MID(k,m,n) LAST((k)>>(m),((n)-(m)))

void print_hex(unsigned char *s);
void permutation_step(unsigned char *s);
void key_step(unsigned char *text, unsigned int value, int round);
void substitution_step(unsigned char *s);
void formula(unsigned int *a);
void substitution(unsigned char *text);
void shifting(unsigned char *s);
void round0(unsigned char *s, unsigned int a);
void round1(unsigned char *s, unsigned int a);
void round2(unsigned char *s, unsigned int a);
void round3(unsigned char *s, unsigned int a);
void partA(unsigned char *text, unsigned int a);


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

void substitution_step(unsigned char *s){
    while(*s){
        substitution(s);
        (*s++);
    }
}

void key_step(unsigned char *text, unsigned int value, int round) {
    BYTE a,b,c,d;
    d=(value&0xFF); //extract first byte
    c=((value>>8)&0xFF); //extract second byte
    b=((value>>16)&0xFF); //extract third byte
    a=((value>>24)&0xFF); //extract fourth byte
    const unsigned char enc[4] = {a,b,c,d};
    int i;
    for (i = 0; i < 3; i++) {
        text[i] ^= enc[round];
    }
}

void permutation_step(unsigned char *s){
    while(*s){
        shifting(s);
        (*s++);
    }
}

void print_hex(unsigned char *s)
{
  while(*s){
    printf("%02x", (unsigned int) *s++);
    }
  printf("\n");
}

void round0(unsigned char *s, unsigned int a){
    key_step(s, a, 0);
}

void round1(unsigned char *s, unsigned int a){
    substitution_step(s);
    permutation_step(s);
    key_step(s, a, 1);
}

void round2(unsigned char *s, unsigned int a){
    substitution_step(s);
    permutation_step(s);
    key_step(s, a, 2);    
}

void round3(unsigned char *s, unsigned int a){
    substitution_step(s);
    key_step(s, a, 3);    
}


void partA(unsigned char *text, unsigned int a){
    round0(text, a);
    round1(text, a);
    round2(text, a);
    round3(text, a);
    print_hex(text);
}