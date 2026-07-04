#include "malloc.h"

/* met un bit spécifique à 1 */
INLINE
inline void setBit(unsigned long *bitmap, size_t bitPos)
{
    bitmap[bitPos / 64] |= (1UL << (bitPos % 64)); 
}

/* met un bit spécifique à 0 */
INLINE
inline void clearBit(unsigned long *bitmap, size_t bitPos)
{
    bitmap[bitPos / 64] &= ~(1UL << (bitPos % 64));
}

/* check si un bit est à 1 ou 0 (false si 0, true si 1) */
INLINE
inline bool checkBit(unsigned long *bitmap, size_t bitPos)
{
    return bitmap[bitPos / 64] & (1UL << (bitPos % 64));
}

/* cherche le prochain bit à 0 dans la bitmap et renvoie l'index */
char getNextIndex(t_zone *zone)
{
    for (unsigned char i = zone->first_free_index + 1; i < 128; i++)
    {
        if (!checkBit(zone->bitmap, i))
            return i;
    }
    return -1;
}