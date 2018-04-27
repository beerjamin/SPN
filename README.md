# Substitution Permutation Network

**Details**
Implementation of an SPN using 4 an 8-bit block cipher with keys of a length of 32 bits.

**Substitution Step**
The substitution step uses 4-bit S-boxes applied to the lower and upper 4 bits of an 8-bit word. 
The substitution step is given by x --> ((x+1) * 7) mod (17-1).

**Permutation Step**
The substitution step uses an 8-bit P-box, which does a cyclic 2-bit left-shift of its argument.

**Rounds**
```
* Round 0 - Key step with the first (most significant) 8 bits of the key.
* Round 1 -  Substitution step followed by a permutation step follows by a key step with the next
8 bits of the key.
* Round 2 - Substitution step followed by a permutation step follows by a key step with the next
8 bits of the key.
* Round 3 - Substitution step followed by a key step with the last (least significant) 8 bits of the key.
```

**Build using cmake**
```
* cd build
* cmake ..
* make
* ./[name of executable]
```
