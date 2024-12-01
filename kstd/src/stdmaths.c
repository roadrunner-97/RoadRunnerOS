#include "stdmaths.h"

int power(int base, int power)
{
    if(power == 0)
    {
        return 1;
    }
    int result = base;
    while(power > 1)
    {
        result *= base;
        power--;
    }
    return result;
}