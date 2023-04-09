//This file contains the functions for the edit cart menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

void removeItemsFromSeller(struct item cart[], int cartItemCount)
{
    long sellerid;
    int found = 0;

    printf("Enter Seller ID of items to remove:");
    do
    {
        sellerid = getLong();
        if (sellerid < 1)
            printf("Please input a positive number:");
    }
    while (sellerid < 1);

    for (int i = 0; i < cartItemCount; i++)
    {
        if (cart[i].sellerid == sellerid)
        {
            found = 1;
            i = cartItemCount;
        }
    }

    if (found == 0)
    {
        printf("Seller ID not found! Returning to edit cart menu\n");
        return;
    }

    for (int i = 0; i < cartItemCount; i++)
    {
        if (sellerid == cart[i].sellerid)
            cart[i].quantity = 0;
    }
    printf("Items from seller removed from cart!\n");

}
void removeSpecificItem(struct item cart[], int cartItemCount)
{
    long productid;
    int found = 0;

    printf("Enter Product ID of item to remove:");
    do
    {
        productid = getLong();
        if (productid < 1)
            printf("Please input a positive number:");
    }
    while (productid < 1);

    for (int i = 0; i < cartItemCount; i++)
    {
        if (cart[i].productid == productid)
        {
            found = 1;
            i = cartItemCount;
        }
    }

    if (found == 0)
    {
        printf("Product ID not found! Returning to edit cart menu\n");
        return;
    }

    for (int i = 0; i < cartItemCount; i++)
    {
        if (productid == cart[i].productid)
            cart[i].quantity = 0;
    }
    printf("Item removed from cart!\n");

}
void editQuantity(struct item cart[], int cartItemCount, struct item items[], int itemCount)
{
    long productid;
    long quantity;
    int found = 0;
    int productIndex;
    int cartProductIndex;

    printf("Enter Product ID of item to edit quantity:");
    do
    {
        productid = getLong();
        if (productid < 1)
            printf("Please input a positive number:");
    }
    while (productid < 1);

    for (int i = 0; i < cartItemCount; i++)
    {
        if (cart[i].productid == productid)
        {
            found = 1;
            cartProductIndex = i;
            i = cartItemCount;
        }
    }

    if (found == 0)
    {
        printf("Product ID not found! Returning to edit cart menu\n");
        return;
    }

    for (int i = 0; i < itemCount; i++)
    {
        if (productid == items[i].productid)
        {
            productIndex = i;
            i = itemCount;
        }
    }

    if (items[productIndex].quantity <= 0)
    {
        printf("Product is out of stock! Removing from cart\n");
        cart[cartProductIndex].quantity = 0;
    }

    printf("Number of items in stock: %ld\n", items[productIndex].quantity);
    printf("Input new quantity:");
    do
    {
        quantity = getLong();
        if (quantity <= 0)
        {
            printf("Please input a positive quantity:");
        }
        else if (quantity > items[productIndex].quantity)
        {
            printf("Entered quantity is not available. Please try again:");
        }
    }
    while(quantity <= 0 || items[productIndex].quantity < quantity);
    printf("\nProduct quantity changed!\n");
    printf("New Quantity:%ld\n", quantity);

    cart[cartProductIndex].quantity = quantity;

}

int editCartMenu(struct item cart[], int cartItemCount, struct item items[], int itemCount)
{
    int choice = 0;
    long sellers[10];
    int sellerCount = 0;

    printf("\nProducts in Cart\n");

    for (int i = 0; i < cartItemCount; i++)
    {
        sellers[i] = cart[i].sellerid;
        sellerCount++;
    }

    for (int i = 0; i < sellerCount; i++)
    {
        for (int j = i+1; j < sellerCount; j++)
        {
            if (sellers[i] == sellers[j])
            {
                for (int k = j; k < sellerCount-1; k++)
                {
                    sellers[k] = sellers[k+1];
                }
                sellerCount--;
                j--;
            }
        }
    }

    for (int i = 0; i < sellerCount; i++)
    {
        printf("\nSeller ID: %ld\n", sellers[i]);
        printf("Product ID\t\t Item Name\t\t Category\t\t Quantity\t\t Unit Price\n");
        for (int j = 0; j < cartItemCount; j++)
        {
            if (sellers[i] == cart[j].sellerid)
            {
                printf("%ld %s %s %ld %lf\n", cart[j].productid, cart[j].name, cart[j].category, cart[j].quantity, cart[j].price);
            }
        }
    }

    while (choice != 4)
    {
        printf("\nEdit Cart Menu\n\n");
        printf("[1] Remove All Items from Seller\n");
        printf("[2] Remove Specific Item\n");
        printf("[3] Edit Quantity\n");
        printf("[4] Exit\n");

        printf("\nSelect an option:");
        choice = getLong();

        switch (choice) {
            case 1:
                removeItemsFromSeller(cart, cartItemCount);
                cartItemCount = sortCart(cart, cartItemCount);
                break;
            case 2:
                removeSpecificItem(cart, cartItemCount);
                cartItemCount = sortCart(cart, cartItemCount);
                break;
            case 3:
                editQuantity(cart, cartItemCount, items, itemCount);
                cartItemCount = sortCart(cart, cartItemCount);
                break;
            case 4:
                break;
            default:
                printf("Please select from the listed options\n");
                break;
        }
    }

    return cartItemCount;

}
