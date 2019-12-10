#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char* name;
    int price;
    int number;

    //Product status: ' ' means nothing, 'O' means available to purchase, 'X' means out of stock
    char status;
} Product;

void initializeProduct(Product *product, int initialPrice, int initialNumber, char* initialName)
{
    product->price = initialPrice;
    product->number = initialNumber;
    product->status = ' ';
    product->name = (char*) malloc(21 * sizeof(char));
    strcpy(product->name, initialName);
}

void changeProduct(Product *product, int newPrice, char* newName)
{
    free(product->name);
    product->name = (char*) malloc(21 * sizeof(char));
    strcpy(product->name, newName);
    product->price = newPrice;
    product->number = 10;
}

void freeProduct(Product *product)
{
    free(product->name);
    product->name = NULL;
    product->price = 0;
}

typedef struct
{
    int depositedMoney, revenue;
    char chosenProduct;
} Machine;

void initializeMachine(Machine *machine)
{
    //Initialize machine data
    machine->depositedMoney = 0;
    machine->revenue = 0;
    machine->chosenProduct = '='; // '=' is the default status, 'A' -> 'E' indicates the product being chosen by user
}

int readInteger()
{
    int input;
    scanf("%d", &input);
    return input;
}

void status(Product *products, Machine machine)
{
    printf("*---------------------------*\n");
    printf("|      Vending Machine      |\n");
    printf("*---------------------------*\n");
    printf("|   A    B    C    D    E   |\n");
    printf("|  $%d  $ %d  $ %d  $ %d  $ %d  |\n", products[0].price, products[1].price, products[2].price, products[3].price, products[4].price);
    printf("|  [%c]  [%c]  [%c]  [%c]  [%c]  |\n", products[0].status, products[1].status, products[2].status, products[3].status, products[4].status);
    printf("*---------------------------*\n");
    if (machine.depositedMoney/10 != 0)
    printf("|                    [$%c%c]  |\n", (machine.depositedMoney/10 + 48), (machine.depositedMoney%10 + 48));
    else
    printf("|                    [$ %c]  |\n", (machine.depositedMoney%10 + 48));
    printf("|                           |\n");
    printf("|           [=%c=]           |\n", machine.chosenProduct);
    printf("*---------------------------*\n");
}

void readProductInformation(Product *products)
{
    printf("\n");
    printf("(1) The displayed products are:\n");
    printf("A. %s ($%d)\n", products[0].name, products[0].price);
    printf("B. %s ($%d)\n", products[1].name, products[1].price);
    printf("C. %s ($%d)\n", products[2].name, products[2].price);
    printf("D. %s ($%d)\n", products[3].name, products[3].price);
    printf("E. %s ($%d)\n", products[4].name, products[4].price);
    return;
}

void changeStatus(Product *products, Machine machine)
{
    for (int i = 0; i < 5; i++)
    {
        if (products[i].price > machine.depositedMoney) products[i].status = ' ';
        else products[i].status = 'O';
        if (products[i].number <= 0) products[i].status = 'X';
    }
}

void insertCoins(Machine *machine, Product *products)
{
    // Indicator whether the user does not want to continue inserting coins
    int quit = 0;

    // Loop till user does not want to insert more coins
    while (!quit)
    {
        // Menu
        printf("\n");
        printf("(2) Which coin would you like to insert?\n");
        printf("1. $1\n");
        printf("2. $2\n");
        printf("3. $5\n");
        printf("4. $10\n");
        printf("0. Go back\n");
        printf("Your choice:");

        // User input
        switch(readInteger())
        {
        case 1:
            machine->depositedMoney += 1;
            printf("You have inserted $1.\n");
            printf("\n");
            changeStatus(products, *machine);
            status(products, *machine);
            break;
        case 2:
            machine->depositedMoney += 2;
            printf("You have inserted $2.\n");
            printf("\n");
            changeStatus(products, *machine);
            status(products, *machine);
            break;
        case 3:
            machine->depositedMoney += 5;
            printf("You have inserted $5.\n");
            printf("\n");
            changeStatus(products, *machine);
            status(products, *machine);
            break;
        case 4:
            machine->depositedMoney += 10;
            printf("You have inserted $10.\n");
            printf("\n");
            changeStatus(products, *machine);
            status(products, *machine);
            break;
        case 0:
            quit = 1;
            printf("Going back!\n");
            printf("\n");
            changeStatus(products, *machine);
            status(products, *machine);
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }
    return;
}

int canBuy(Machine machine, Product product)
{
    return (product.price <= machine.depositedMoney && product.number > 0); // Return 0 if user cannot buy and vice versa
}

void pressProductButton(Machine *machine, Product *products)
{
    // Indicator whether to quit the loop
    int quit = 0;

    while (!quit)
    {
        // Menu
        printf("\n");
        printf("(3) Which product button would you like to press?\n");
        printf("1. A\n");
        printf("2. B\n");
        printf("3. C\n");
        printf("4. D\n");
        printf("5. E\n");
        printf("0. Go back\n");
        printf("Your choice:");

        // User input
        switch(readInteger())
        {
        case 1:
            printf("You have pressed button A.\n");
            if (canBuy(*machine, products[0]))
            {
                machine->depositedMoney -= 10;
                machine->revenue += 10;
                (products)->number--;
                machine->chosenProduct = 'A';
            }
            else machine->chosenProduct = '=';
            quit = 1;
            break;
        case 2:
            printf("You have pressed button B.\n");
            if (canBuy(*machine, products[1]))
            {
                machine->depositedMoney -= 6;
                machine->revenue += 6;
                (products+1)->number--;
                machine->chosenProduct = 'B';
            }
            else machine->chosenProduct = '=';
            quit = 1;
            break;
        case 3:
            printf("You have pressed button C.\n");
            if (canBuy(*machine, products[2]))
            {
                machine->depositedMoney -= 5;
                machine->revenue += 5;
                (products+2)->number--;
                machine->chosenProduct = 'C';
            }
            else machine->chosenProduct = '=';
            quit = 1;
            break;
        case 4:
            printf("You have pressed button D.\n");
            if (canBuy(*machine, products[3]))
            {
                machine->depositedMoney -= 8;
                machine->revenue += 8;
                (products+3)->number--;
                machine->chosenProduct = 'D';
            }
            else machine->chosenProduct = '=';
            quit = 1;
            break;
        case 5:
            printf("You have pressed button E.\n");
            if (canBuy(*machine, products[4]))
            {
                machine->depositedMoney -= 7;
                machine->revenue += 7;
                (products+4)->number--;
                machine->chosenProduct = 'E';
            }
            else machine->chosenProduct = '=';
            quit = 1;
            break;
        case 0:
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    printf("\n");
    changeStatus(products, *machine);
    status(products, *machine);

    // Reset chosenProduct to default
    machine->chosenProduct = '=';

    return;
}

void pressReturnButton(Product *products, Machine *machine)
{
    printf("\n");
    printf("(4) Return button is pressed.\n");
    printf("$%d has been returned.\n", machine->depositedMoney);
    machine->depositedMoney = 0;
    printf("\n");
    changeStatus(products, *machine);
    status(products, *machine);
    return;
}

void openServiceMenu(Product *products, Machine *machine)
{
    // Checking authorization
    printf("(9) Opening service menu. Access code is required.\n");
    printf("Enter access code:");
    if (readInteger() != 1110)
    {
        printf("Incorrect code!\n");
        status(products, *machine);
        return;
    }
    else printf("Correct code!\n");

    // Indicator whether to terminate the loop
    int quit = 0;

    while (!quit)
    {
        printf("(9) What would you like to do?\n");
        printf("1. Inspect machine status\n");
        printf("2. Withdraw all money\n");
        printf("3. Refill product\n");
        printf("4. Change product\n");
        printf("0. Go back\n");
        printf("Your choice:");

        //User input
        switch(readInteger())
        {
        case 1:
            printf("\n");
            printf("(9-1) Machine status\n");
            printf("Amount of revenue: $%d\n", machine->revenue);
            printf("Amount of inserted coins: $%d\n", machine->depositedMoney);
            printf("Product information:\n");
            for (int i = 0; i < 5; i++)
            {
                if (products[i].number > 0)
                    printf("%c. %s ($%d) (%d left)\n", i+65, products[i].name, products[i].price, products[i].number);
                else
                    printf("%c. %s ($%d) (sold out)\n", i+65, products[i].name, products[i].price);
            }
            printf("\n");
            break;
        case 2:
            printf("\n");
            printf("(9-2) All money is being withdrawn.\n");
            printf("$%d is withdrawn.\n", machine->depositedMoney + machine->revenue);
            machine->revenue = 0;
            machine->depositedMoney = 0;
            printf("\n");
            break;
        case 3:
            printf("\n");
            printf("(9-3) Which product would you like to refill?\n");
            printf("1. A\n");
            printf("2. B\n");
            printf("3. C\n");
            printf("4. D\n");
            printf("5. E\n");
            printf("0. Go back\n");
            printf("Your choice:");

            // User input
            int toRefill = readInteger();
            (products+toRefill-1)->number = 10;
            printf("You have refilled product %c to full.\n", 65+toRefill-1);
            printf("\n");
            break;
        case 4:
            printf("\n");
            printf("(9-4) Which product would you like to change?\n");
            printf("1. A\n");
            printf("2. B\n");
            printf("3. C\n");
            printf("4. D\n");
            printf("5. E\n");
            printf("0. Go back\n");
            printf("Your choice:");

            // User input
            int toChange = readInteger();
            printf("You are changing product %c.\n", 65+toChange-1);
            printf("\n");
            char newName[21]; int newPrice;
            printf("Enter new product name:"); scanf("%s", newName);
            printf("Enter new product price:"); scanf("%d", &newPrice);
            changeProduct(products+toChange-1, newPrice, newName);

            printf("The new product %c has been filled to full.\n", 65+toChange-1);
            printf("\n");

            break;
        case 0:
            quit = 1;
            printf("Going back!\n");
            status(products, *machine);
            break;
        default:
            break;
        }
    }
}

int main()
{
    Machine machine;
    initializeMachine(&machine);

    Product products[5];
    initializeProduct(&products[0], 10, 5, "Juice");
    initializeProduct(&products[1], 6, 1, "Cola");
    initializeProduct(&products[2], 5, 2, "Tea");
    initializeProduct(&products[3], 8, 1, "Water");
    initializeProduct(&products[4], 7, 9, "Coffee");

    // Whether the user quit or not
    int quit = 0;

    //Initial status
    status(products, machine);

    // Main loop
    while (!quit)
    {
        // Menu
        printf("\n");
        printf("What would you like to do?\n");
        printf("1. Read product information\n");
        printf("2. Insert coin\n");
        printf("3. Press product button\n");
        printf("4. Press return button\n");
        printf("9. Open service menu (code required)\n");
        printf("0. Quit\n");
        printf("Your choice:");

        switch (readInteger())
        {
        case 1:
            readProductInformation(products);
            break;
        case 2:
            insertCoins(&machine, products);
            break;
        case 3:
            pressProductButton(&machine, products);
            break;
        case 4:
            pressReturnButton(products, &machine);
            break;
        case 9:
            openServiceMenu(products, &machine);
            break;
        case 0:
            quit = 1;
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    // Free the dynamic memory allocated for the products data
    for (int i = 0; i < 5; i++) freeProduct(products+i);

    return 0;
}
