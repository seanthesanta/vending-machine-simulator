#include <stdio.h>
#include <string.h>

//#define DEBUG_productLeft
//#define DEBUG_fgets
#define DEBUG_strcpy

int readInt()
{
    int input;
    scanf("%d", &input);
    return input;
}

void readProductInformation()
{
    printf("(1) The displayed products are:\n");
    printf("A. Juice ($10)\n");
    printf("B. Cola ($6)\n");
    printf("C. Tea ($5)\n");
    printf("D. Water ($8)\n");
    printf("E. Coffee ($7)\n");

    return;
}

void updateEnoughMoney(char* enoughMoney, int depositedMoney)
{
    memset(enoughMoney, ' ', sizeof(enoughMoney));

    if (depositedMoney >= 5) enoughMoney[2] = 'O';
    if (depositedMoney >= 6) enoughMoney[1] = 'O';
    if (depositedMoney >= 7) enoughMoney[4] = 'O';
    if (depositedMoney >= 8) enoughMoney[3] = 'O';
    if (depositedMoney >= 10) enoughMoney[0] = 'O';

    return;
}

void updateAvailableProduct(char* availableProduct, int* productLeft)
{
    memset(availableProduct, ' ', sizeof(availableProduct));
    for (int i = 0; i < 5; i++) if (productLeft[i] <= 0) availableProduct = 'X';

    return;
}

void insertCoin(char* enoughMoney, int* insertedCoins, int* depositedMoney)
{
    // Reset enoughMoney
    memset(enoughMoney, ' ', sizeof(enoughMoney));

    // Indicator whether the user does not want to continue inserting coins
    int quit = 0;

    // Loop till user does not want to insert more coins
    while (!quit)
    {
        // Menu
        printf("(2) Which coin would you like to insert?\n");
        printf("1. $1\n");
        printf("2. $2\n");
        printf("3. $5\n");
        printf("4. $10\n");
        printf("0. Go back\n");
        printf("Your choice: ");

        // User input
        switch(readInt())
        {
        case 1:
            *depositedMoney += 1;
            *insertedCoins += 1;
            printf("You have inserted $1.\n");
            break;
        case 2:
            *depositedMoney += 2;
            *insertedCoins += 2;
            printf("You have inserted $2.\n");
            break;
        case 3:
            *depositedMoney += 5;
            *insertedCoins += 5;
            printf("You have inserted $5.\n");
            break;
        case 4:
            *depositedMoney += 10;
            *insertedCoins += 10;
            printf("You have inserted $10.\n");
            break;
        case 0:
            quit = 1;
            break;
        default:
            break;
        }

        updateEnoughMoney(enoughMoney, *depositedMoney);

        // Machine status
        status(enoughMoney, *depositedMoney);
    }

    return;
}

void pressProductButton(char* availableProduct, char* enoughMoney, int* productLeft, int* depositMoney)
{
    // Reset availableProduct
    memset(availableProduct, ' ', sizeof(availableProduct));

    // Indicator whether the user wants to continue buying
    int quit = 0;

    while (!quit)
    {
        #ifdef DEBUG_productLeft
        for (int i = 0; i < 5; i++) printf("%d\n", productLeft[i]);
        printf("\n");
        #endif // DEBUG_productLeft

        // Menu
        printf("(3) Which product button would you like to press?\n");
        printf("1. A\n");
        printf("2. B\n");
        printf("3. C\n");
        printf("4. D\n");
        printf("5. E\n");
        printf("0. Go back\n");
        printf("Your choice: ");

        // User input
        switch(readInt())
        {
        case 1:
            printf("You have pressed button A.\n");
            *depositMoney -= 10;
            productLeft[0]--;
            break;
        case 2:
            printf("You have pressed button B.\n");
            *depositMoney -= 6;
            productLeft[1]--;
            break;
        case 3:
            printf("You have pressed button C.\n");
            *depositMoney -= 5;
            productLeft[2]--;
            break;
        case 4:
            printf("You have pressed button D.\n");
            *depositMoney -= 8;
            productLeft[3]--;
            break;
        case 5:
            printf("You have pressed button E.\n");
            *depositMoney -= 7;
            productLeft[4]--;
            break;
        case 0:
            quit = 1;
            break;
        default:
            break;
        }

        updateAvailableProduct(availableProduct, productLeft);
        updateEnoughMoney(enoughMoney, *depositMoney);

        // Machine status
        status(availableProduct, *depositMoney);
    }

    return;
}

void pressReturnButton(char* availableProduct, int* depositedMoney)
{
    if (*depositedMoney > 1) printf("$%d have been returned\n", *depositedMoney);
    else printf("$%d has been returned\n", *depositedMoney);
    *depositedMoney = 0;
    status(availableProduct, *depositedMoney);

    return;
}

void readChar(char* input)
{
    scanf("%s", input);
}

void openServiceMenu(int* availableProduct, int* productLeft, int* insertedCoins, int* depositedMoney, int* price, char* name, const int NO_OF_PRODUCT, const int MAX_PRODUCT_PRICE, const int MAX_STRING_SIZE)
{
    printf("Opening service menu. Access code is required.\nEnter access code: ");
    // If incorrect code entered, back to main menu
    if (readInt() != 1110)
    {
        printf("Incorrect code!\n");
        status(availableProduct, *depositedMoney);
        return;
    }
    // Else open sub-menu
    else
    {
        //Indicator to quit
        int quit = 0;

        while (!quit)
        {
            // Menu
            printf("(9) What would you like to do?\n");
            printf("1. Inspect machine status\n");
            printf("2. Withdraw inserted coins\n");
            printf("3. Refill product\n");
            printf("4. Change product\n");
            printf("0. Go back\n");
            printf("Your choice: ");

            // Declare variable for input
            char input[20];

            // User input
            switch(readInt())
            {
            case 1:
                printf("(9-1) Machine status\n");
                printf("Amount of inserted coins: $%d\n", *insertedCoins);
                printf("Product information:\n");
                if (productLeft[0] > 0) printf("A. Juice ($10) (%d left)\n", productLeft[0]);
                else printf("A. Juice ($10) (sold out)\n");
                if (productLeft[1] > 0) printf("B. Cola ($6) (%d left)\n", productLeft[1]);
                else printf("B. Cola ($6) (sold out)\n");
                if (productLeft[2] > 0) printf("C. Tea ($5) (%d left)\n", productLeft[2]);
                else printf("C. Tea ($5) (sold out)\n");
                if (productLeft[3] > 0) printf("D. Water ($8) (%d left)\n", productLeft[3]);
                else printf("D. Water ($8) (sold out)\n");
                if (productLeft[4] > 0) printf("E. Coffee ($7) (%d left)\n", productLeft[4]);
                else printf("E. Coffee ($7) (sold out)\n");
                break;
            case 2:
                printf("(9-2) Inserted coins are being withdrawn.\n");
                if (*depositedMoney > 1) printf("$%d are withdrawn.\n", *depositedMoney);
                else printf("$%d is withdrawn.\n");
                *depositedMoney = 0;
                break;
            case 3:
                printf("(9-3) Which product would you like to refill?\n");
                printf("1. A\n");
                printf("2. B\n");
                printf("3. C\n");
                printf("4. D\n");
                printf("5. E\n");
                printf("0. Go back\n");
                printf("Your choice: ");

                switch(readInt())
                {
                case 1:
                    productLeft[0] = NO_OF_PRODUCT;
                    printf("You have refilled product A to full.\n");
                    break;
                case 2:
                    productLeft[1] = NO_OF_PRODUCT;
                    printf("You have refilled product B to full.\n");
                    break;
                case 3:
                    productLeft[2] = NO_OF_PRODUCT;
                    printf("You have refilled product C to full.\n");
                    break;
                case 4:
                    productLeft[3] = NO_OF_PRODUCT;
                    printf("You have refilled product D to full.\n");
                    break;
                case 5:
                    productLeft[4] = NO_OF_PRODUCT;
                    printf("You have refilled product E to full.\n");
                    break;
                case 0:
                    break;
                default:
                    break;
                }
                break;
            case 4:
                printf("(9-4) Which product would you like to change?\n");
                printf("1. A\n");
                printf("2. B\n");
                printf("3. C\n");
                printf("4. D\n");
                printf("5. E\n");
                printf("0. Go back\n");
                printf("Your choice: ");
                switch(readInt())
                {
                case 1:
                    printf("(9-4-1) Changing product\n");
                    printf("Enter new product name: ");
                    readChar(input);

                    printf("%s", name[0]);
                    for (int i = 0; i < strlen(input); i++) name[0][i] = input[i];
                    printf("%s", name[0]);

                    printf("Enter new product price: ");
                    price[0] = readInt();
                    printf("The new product A has been filled to full.\n");
                    productLeft[0] = NO_OF_PRODUCT;
                    break;
                default:
                    break;
                }
                break;
            case 0:
                quit = 1;
                break;
            default:
                break;
            }
        }
    }
}

void status(char* infoProduct, int depositedMoney)
{
    printf("*---------------------------*\n");
    printf("|      Vending Machine      |\n");
    printf("*---------------------------*\n");
    printf("|   A    B    C    D    E   |\n");
    printf("|  $10  $ 6  $ 5  $ 8  $ 7  |\n");
    printf("|  [%c]  [%c]  [%c]  [%c]  [%c]  |\n", *infoProduct, *(infoProduct+1), *(infoProduct+2), *(infoProduct+3), *(infoProduct+4));
    printf("*---------------------------*\n");
    printf("|                    [$ %d]  |\n", depositedMoney);
    printf("|                           |\n");
    printf("|           [===]           |\n");
    printf("*---------------------------*\n");
    printf("\n");
}

int main()
{
    const int MAX_PRODUCT_PRICE = 10;
    const int NO_OF_PRODUCT = 5;
    const int MAX_STRING_SIZE = 20;
    const int MAX_PRODUCT_LEFT = 10;

    // Machine data
    int insertedCoins = 0;

    //Initial product names and product prices as in the project guideline
    int price[5] = {10, 6, 5, 8, 7};
    char name[5][20] = {"Juice", "Cola", "Tea", "Water", "Coffee"};

    int productLeft[5];
    for (int i = 0; i < 5; i++) productLeft[i] = MAX_PRODUCT_LEFT;

    #ifdef DEBUG_productLeft
    for (int i = 0; i < 5; i++) printf("%d ", productLeft[i]);
    printf("\n");
    #endif // DEBUG_productLeft

    char availableProduct[5], enoughMoney[5];
    memset(availableProduct, ' ', sizeof(availableProduct));
    memset(enoughMoney, ' ', sizeof(enoughMoney));

    // Amount of money deposited
    int depositedMoney = 0;

    // Whether the user quit or not
    int quit = 0;

    //Initial status
    status(availableProduct, depositedMoney);

    // Main loop
    while (!quit)
    {
        // Menu
        printf("What would you like to do?\n");
        printf("1. Read product information\n");
        printf("2. Insert coin\n");
        printf("3. Press product button\n");
        printf("4. Press return button\n");
        printf("9. Open service menu (code required)\n");
        printf("0. Quit\n");
        printf("Your choice: ");

        switch (readInt())
        {
        case 1:
            readProductInformation();
            break;
        case 2:
            insertCoin(enoughMoney, &insertedCoins, &depositedMoney);
            break;
        case 3:
            pressProductButton(availableProduct, enoughMoney, productLeft, &depositedMoney);
            break;
        case 4:
            pressReturnButton(availableProduct, &depositedMoney);
            break;
        case 9:
            openServiceMenu(availableProduct, productLeft, &insertedCoins, &depositedMoney, price, name, NO_OF_PRODUCT, MAX_PRODUCT_PRICE, MAX_STRING_SIZE);
            break;
        case 0:
            quit = 1;
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
        printf("\n");
    }

    return 0;
}
