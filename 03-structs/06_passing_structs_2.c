#include <stdio.h>

struct car {
    char *name;
    float price;
    int speed;
};

void set_price(struct car *c, float p)
{
    c->price = p;
} 

int main(void)
{
    struct car saturn = {.speed=175, .name="Saturn SL/2"};

    // Pass a pointer to this struct car, along with a new
    // more realistic price:
    set_price(&saturn, 799.99);

    printf("Price: %f\n", saturn.price);

    return 0;
}