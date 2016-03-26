***************************************************************************Lab 2Author: Zheng LuoEmail: luozheng@wustl.edu******************************************************************************************************************Part One:Implement the Table***************************************
***************************************1. Test cases ***************************************---------------Case1: ---------------Test just compare two characters without maskInput File: case1-pattern:accccatacccase1-corpus:actcagataOutput:M = 2
CORPUS: 9 bases
PATTERN: 10 bases
0 0 ac
0 7 ac
3 4 ca
6 5 at
7 6 ta---------------Case2: ---------------Test just compare two characters with maskInput File: case2-pattern:accccatacccase2-corpus:actcagata
case2-mask:xxacOutput:M = 2
CORPUS: 9 bases
PATTERN: 10 bases
MASK: 4 bases
3 4 ca
6 5 at
7 6 ta---------------Case3: ---------------Test 5 characters without maskInput File:Output:---------------Case3: ---------------Test 5 characters without maskInput File:case3-pattern:ggtataccattagcccccatacccatatacase3-corpus:aggcacattagaccccagatactacccatOutput:
M = 5
CORPUS: 29 bases
PATTERN: 29 bases
5 7 catta
6 8 attag
12 14 cccca
22 19 taccc
23 20 accca
24 15 cccat
24 21 cccat
---------------Case4: ---------------Test 5 characters with maskInput File:case4-pattern:ggtataccattagcccccatacccatatacase4-corpus:aggcacattagaccccagatactacccat
case2-mask:tactactactccttccccatacOutput:
M = 5
CORPUS: 29 bases
PATTERN: 29 bases
MASK: 22 bases
5 7 catta
6 8 attag
22 19 taccc
23 20 accca

*******************************************2. Lab2 implementation brief description*******************************************
In the Class of the StringTable I used

int n to store the number of records in the talbe
int m to store the the number of slots
Record **hashTable to used to store the record

When the (double)n/m > 0.25, I will call the doubleSizeAndReHash() to rehash everything
in the Previous Table to the double sized new table.

For the hash function, I choose the base hash function:
h(k) = int(m * (k * A - (int)(k * A))) which A = (sqrt(5.0) - 1)/2

For the step hash function, I choose
h(k) = int(m * (k * A - (int)(k * A))) which A = sqrt(3.0)/2
When return the value, I will alway return the odd number, then I return the value like
this: return ((h_k % 2 == 0)? h_k + 1:h_k)

Then we will know that the value step hash function return will be relatively prime to the m, because m is the power of 2. This will generate more hash choice for the hash table.


***************************************Part Two: Improve the Talbe***************************************

************************************************************1. Use extra value to speed up searches brief documentation************************************************************

In the Record Class, I add an attribute to HashValue to the class, when do the string comparison, the code will avoid full comparison of two strings when their hash value
differ.

The code is this:

if ((k == hashTable[s_k]->toHashValue) &&
                 (strncmp(r->key,hashTable[s_k]->key,matchLength) == 0))

It checks the value first, if it is the same, then compare the string.


************************************************************2. Dynamic Size the hash table************************************************************
In the Class of the StringTable I used

int n to store the number of records in the talbe
int m to store the the number of slots
Record **hashTable to used to store the record

When the (double)n/m > 0.25, I will call the doubleSizeAndReHash() to rehash everything
in the Previous Table to the double sized new table.

In the constructor of the StringTable I initial the value of the attribute:

StringTable::StringTable(int maxSize, int imatchLength)
: matchLength(imatchLength),n(0),m(2)
{
    // Create an empty table big enough to hold maxSize records
    hashTable = new Record* [m];
    // Set all the entry null when initialized
    for (int i = 0; i < m; i++)
    {
        hashTable[i] = NULL;
    }
}

When the old  table is full, I will call the doubleSizeAndReHash().

void StringTable::doubleSizeAndReHash()
{
    int oldM = m; // value to store the old m
    m = m * 2; // double the value m
    Record **oldHashTable = hashTable; // old table
    Record **doubleSizedHashTable = new Record* [m]; // double sized table
    // Set all the entry null when initialized
    for (int i = 0; i < m; i++)
    {
        doubleSizedHashTable[i] = NULL;
    }
    // find the entry and re hash into the new table
    for (int i = 0; i < oldM; i++)
    {
        if (oldHashTable[i] != NULL)
        {
            // Calculate the key for hashing
            int k = toHashKey(oldHashTable[i]->key);
            // calulate the value of the hash functuion
            int s_k = baseHash(k);
            // hash the previous record
            for (int j = 0; j < m; j++)
            {
                if (doubleSizedHashTable[s_k] == NULL)
                {
                    doubleSizedHashTable[s_k] = oldHashTable[i];
                    break;
                }
                // if the table[s_k] is not NULL, calculate the multiplicative hashing
                else
                {
                    s_k = (s_k + stepHash(k)) % m;
                    
                }
            }
        }
    }
    // delete the oldHashTalbe
    delete [] oldHashTable;
    // assign the double sized table to the hashTable
    hashTable = doubleSizedHashTable;
}



