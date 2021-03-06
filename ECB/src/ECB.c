/*
_______________________________________________________________________

+++++ Implementation of a simple substitution-permutation network +++++
_______________________________________________________________________

Substitution Step: Uses 4-bit S-Boxes applied to the lower and upper
4 bits of an 8-bit work. The 4-bit chunks are seen as natural numbers
via their binary encoding
The substitution is given by: x --> ((x+1)*7)mod(17-1).
_______________________________________________________________________

Permutation Step: Uses an 8-bit P-Box which does a cyclic 2-bit 
left-shift of its argument
_______________________________________________________________________

*/

#include "ECB.h"

int main()
{	
	unsigned char s[] = "aba";
	unsigned int a = 0x98267351;
    	partA(s,a); 
	return 0;
}



