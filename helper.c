//This file contains the input and helper functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "structures.h"

void getString(char dest[], int destsize)
{
    char buffer[1024];
    long len;
    int success;

    success = 0;
    while (success == 0)
    {
        fgets(buffer, 1024, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        len = strlen(buffer);
        if (len > destsize)
        {
            printf("Input too long! Please try again:");
        }
        else
        {
            success = 1;
        }

    }
    if (destsize > 1)
        strcpy(dest, buffer);
    else
        *dest = buffer[0];
}

long getLong(void)
{
    char buffer[1024];
    char *convert;
    long number;
    int success;

    do
    {
       fgets(buffer, 1024, stdin);

       errno = 0;
       number = strtol(buffer, &convert, 10);

       if (errno == ERANGE)
       {
           printf("Input is too large for integer. Please try again:");
           success = 0;
       }
       else if (convert == buffer)
       {
           printf("Input was not fully converted. Please try again:");
           success = 0;
       }
       else if (*convert && *convert != '\n')
       {
           printf("Input was not fully converted. Please try again:");
           success = 0;
       }
       else
       {
           success = 1;
       }

    }
    while (success == 0);

    return number;

}

double getDouble(void)
{
    char buffer[1024];
    char *convert;
    double number;
    int success;

    do
    {
        fgets(buffer, 1024, stdin);

        errno = 0;
        number = strtod(buffer, &convert);

        if (errno == ERANGE)
        {
            printf("Input is too large for long integer. Please try again:");
            success = 0;
        }
        else if (convert == buffer)
        {
            printf("Input was not fully converted. Please try again:");
            success = 0;
        }
        else if (*convert && *convert != '\n')
        {
            printf("Input was not fully converted. Please try again:");
            success = 0;
        }
        else
        {
            success = 1;
        }

    }
    while (success == 0);

    return number;

}

void sortUsers(struct user users[], int userCount)
{
    int min ;
    struct user temp;

    for (int i = 0; i < userCount-1; i++)
    {
        min = i;
        for (int j = i+1; j < userCount; j++)
        {
            if (users[j].userid < users[min].userid)
                min = j;
        }
        if (min != i)
        {
            temp = users[i];
            users[i] = users[min];
            users[min] = temp;
        }

    }
}

void sortItems(struct item items[], int itemCount)
{
    int min;
    struct item temp;

    for (int i = 0; i < itemCount-1; i++)
    {
        min = i;
        for (int j = i+1; j < itemCount; j++)
        {
            if (items[j].productid < items[min].productid)
                min = j;
        }
        if (min != i)
        {
            temp = items[i];
            items[i] = items[min];
            items[min] = temp;
        }

    }

}

int sortCart(struct item items[], int cartItemCount)
{
    int min;
    int max;
    struct item temp;
    int newCartItemCount = 0;

    for (int i = 0; i < cartItemCount; i++)
    {
        max = i;
        for (int j = i+1; j < cartItemCount; j++)
        {
            if (items[j].quantity > items[max].quantity)
                max = j;
        }
        if (max != i)
        {
            temp = items[i];
            items[i] = items[max];
            items[max] = temp;
        }
    }

    for (int i = 0; i < cartItemCount; i++)
    {
        if (items[i].quantity > 0)
            newCartItemCount++;
    }

    for (int i = 0; i < newCartItemCount; i++)
    {
        min = i;
        for (int j = i+1; j < newCartItemCount; j++)
        {
            if (items[j].sellerid < items[min].sellerid)
                min = j;
        }
        if (min != i)
        {
            temp = items[i];
            items[i] = items[min];
            items[min] = temp;
        }

    }


    for (int i = 0; i < newCartItemCount; i++)
    {
        min = i;
        for (int j = i+1; j < newCartItemCount; j++)
        {
            if (items[j].sellerid == items[min].sellerid && items[j].productid < items[min].productid)
                min = j;
        }
        if (min != i)
        {
            temp = items[i];
            items[i] = items[min];
            items[min] = temp;
        }

    }


    return newCartItemCount;

}

/* No longer needed, itemCount and items array is automatically appended if addNewItem() returns 1 for successfully adding an item
int getTotalItemsFromUsers(struct user users[], int userCount, struct item items[])
{
    int totalItemCount = 0;

    for (int i = 0; i < userCount; i++)
    {
        for (int j = 0; j < users[i].userItemCount; j++)
        {
            items[totalItemCount] = users[i].items[j];
            totalItemCount++;
        }
    }

    return totalItemCount;

}
*/
