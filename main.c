#include "Include_and_constants.h"
#include <windef.h>

struct Machines
{
    int First;
    int Second;
    int Number;
    int Check;
};

void FindOptimalRaw()
{
    int Check = 0 , Min = 0 , Num = 0;
    printf("Set amount of machines_\n");
    int AmountOfMachines = In();
    int *Order = (int*)malloc( AmountOfMachines * sizeof( int ) );
    for(int i = 0 ; i < AmountOfMachines ; i++)Order[ i ] = 0;
    struct Machines *Raw = (struct Machines*)malloc( AmountOfMachines * sizeof( struct Machines ) );
    for(int i = 0 ; i < AmountOfMachines ; i++ )
    {
        printf("Add working time of %d item on the first machine_\n" , i + 1 );
        Raw[ i ].First = In();
        printf("Add working time of %d item on the second machine_\n" , i + 1 );
        Raw[ i ].Second = In();
        Raw[ i ].Number = i + 1;
        Raw[ i ].Check = 1;
    }
    for( int i = 0 ; i < AmountOfMachines ; i++ )
    {
        Min = Exponentiation( 10 , 29 );
        for(int j = 0 ; j < AmountOfMachines ; j++)
        {
            if( ( Raw[ j ].First < Min || Raw[ j ].Second < Min ) && Raw[ j ].Check == 1 )
            {
                if( Raw[ j ].First <= Raw[ j ].Second ){Min = Raw[ j ].First ; Num = Raw[ j ].Number ; Check = 1;}
                else {Min = Raw[ j ].Second ; Num = Raw[ j ].Number ; Check = 0;}
            }
        }
        Raw[ Num - 1 ].Check = 0;
        if (Check > 0)
        {
            for(int k = 0 ; k < AmountOfMachines ; k++)
            {
                if( Order [ k ] == 0 ){Order[ k ] = Num; break;}
            }
        }
        else
        {
            for( int k = AmountOfMachines ; k > 0 ; k-- ){
                if( Order [ k ] == 0 ){Order[ k ] = Num; break;}
            }
        }
    }
    printf("The best order is:");
    for(int i = 0 ; i < AmountOfMachines ; i++ )printf("%d" , Order[ i ]);
    printf("\nGant's graphic\n");
    int LostTime = 0;
    for( int i = 0 ; i < AmountOfMachines ; i++)
    {
        printf("Process%d|" , Order [ i ] );
        for( int j = 0 ; j < LostTime ; j++ )printf("-");
        for( int j = 0 ; j < (Raw[ Order [ i ] - 1 ].First + Raw[ Order [ i ] - 1 ].Second ) ; j++ )printf("%d" , i + 1 );
        if(i > 0) LostTime = LostTime + Raw[ Order [ i ] - 1 ].First + Raw[ Order[ i - 1 ] - 1 ].Second;
        else LostTime = Raw[ 0 ].First;
        printf("\n");
    }
    printf("\t|");
    for(int i = 0 ; i <= LostTime ; i++ )printf("_");
    printf("\n\tWorking time\n");
}

int main()
{
    while (TRUE)
    {
        system("cls");
        printf("1.Find optimal raw\n2.Exit\n");
        char Choose = getch();
        switch (Choose)
        {
            case '1' :
                system("cls");
                FindOptimalRaw();
                printf("Press any button to restart the programme_");
                getch();
                break;
            case '2' :
                return 0;
            default:
                break;
        }
    }
}