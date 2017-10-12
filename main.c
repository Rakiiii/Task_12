#include "Include_and_constants.h"
#include <windef.h>

struct Machines //делаем структуру для храненияданных о каждом объекте
{
    int First ; //время обработки на первой машины
    int Second ; //время обработки на второй машине
    int Number ; //номер детали
    int Check ; //флаг
} ;

void FindOptimalRaw()
{
    int Check = 0 , Min = 0 , Num = 0 ; //инициализируем : временный флаг , временный номер , мин занчение
    printf( "Set amount of items_\n" ) ;
    int AmountOfMachines = In() ; //получаем значение деталей
    int *Order = ( int* )malloc( AmountOfMachines * sizeof( int ) ) ; //выделяем время под массив для порядка
    for( int i = 0 ; i < AmountOfMachines ; i ++ )
        Order[ i ] = 0 ; //обнуляем массив для хранения порядка
    struct Machines *Raw = ( struct Machines* )malloc( AmountOfMachines * sizeof( struct Machines ) ) ;
    //выделяем память под массив для хранения информации о деталях
    for( int i = 0 ; i < AmountOfMachines ; i ++ ) //читаем инфу о деталях
    {
        printf( "Add working time of %d item on the first machine_\n" , i + 1 ) ;
        Raw[ i ].First = In() ; //читаем время обработки  детали на первом станке
        printf( "Add working time of %d item on the second machine_\n" , i + 1 ) ;
        Raw[ i ].Second = In() ; //читаем время обработки  детали на втором станке
        Raw[ i ].Number = i + 1 ; //запоминаем номер
        Raw[ i ].Check = 1 ; //превращяем флаг в еденицу
    }
    for( int i = 0 ; i < AmountOfMachines ; i ++ )
    {
        Min = Exponentiation( 10 , 29 ) ; //делаем мин значение бблизкое к масималюному
        //Exponentiation описан в include and constants
        for( int j = 0 ; j < AmountOfMachines ; j ++ )
        {
            if( ( Raw[ j ].First < Min || Raw[ j ].Second < Min ) && Raw[ j ].Check == 1 ) //ищем минимальное значение среди первого и второго с флагом в еденицу
            {
                if( Raw[ j ].First <= Raw[ j ].Second ) //если первое меньше второго то ставим его в начало
                {
                    Min = Raw[ j ].First ;
                    Num = Raw[ j ].Number ;
                    Check = 1 ; //если флаг 1 то ставим в начало
                }
                else
                {
                    Min = Raw[ j ].Second ;
                    Num = Raw[ j ].Number ;
                    Check = 0 ; //если флаг ноль то ставим в конец
                }
            }
        }
        Raw[ Num - 1 ].Check = 0 ;
        if ( Check > 0 )
        {
            for( int k = 0 ; k < AmountOfMachines ; k ++ ) //ищем первое свободное место для номера с начала
            {
                if( Order [ k ] == 0 )
                {
                    Order[ k ] = Num ;
                    break ;
                }
            }
        }
        else
        {
            for( int k = AmountOfMachines ; k > 0 ; k -- ) //ищем первое свободное место с конца
            {
                if( Order [ k ] == 0 )
                {
                    Order[ k ] = Num ;
                    break ;
                }
            }
        }
    }
    printf( "The best order is:" ) ; //вывродим порядок
    for( int i = 0 ; i < AmountOfMachines ; i ++ ) printf( "%d" , Order[ i ] ) ;
    printf( "\nGant's graphic\nMachine 1|" ) ; //рисуем график ганта
    int count = 0 ; //для красоты считаем количество символов в нижней строчке, тк она всегда длинне верхней
    for( int i = 0 ; i < AmountOfMachines ; i ++ ) //рисуем первую строчу просто печатая нужные цифры в нужном порядке
    {
        for (int j = 0 ; j < Raw[ Order[ i ] - 1 ].First ; j ++ ) printf( "%d", Order[ i ] ) ;
    }
    printf( "\nMachine 2|" ) ;
    for( int i = 0 ; i < AmountOfMachines ; i ++ )
    {
        if( i > 0 ) //для следующих после первого в порядке
        {
            int j = 0 ; //машина простаивает когда предыдущая деталь обработанна ,а новая еще нет
            while( j < ( Raw[ Order [ i ] - 1 ].First - Raw[ Order[ i - 1 ] - 1 ].Second ) ) //вычисляем это время
            {
                printf( "-" );
                j ++ ;
                count ++ ;
            }
        }
        else //для первой детали
        {
            for( int j = 0 ; j < Raw[ 0 ].First ; j ++ )
            {
                printf( "-" ) ;
                count ++ ;
            }

        }
        for( int k = 0 ; k < Raw[ Order [ i ] - 1 ].Second ; k ++ ) //печатаем время выполнения на второй машине
        {
            printf( "%d" , Order[ i ] ) ;
            count ++ ;
        }

    }
    printf( "\n\t" ) ;
    for( int i = 0 ; i < count + 2 ; i ++ ) printf( "-" ) ; //для красоты
    printf( "\n\tTimeline\n\n\n" ) ;
}

int main() //меню
{
    while (TRUE)
    {
        system( "cls" ) ;
        printf( "1.Find optimal raw\n2.Exit\n" ) ;
        char Choose = getch() ;
        switch ( Choose )
        {
            case '1' :
                system( "cls" ) ;
                FindOptimalRaw() ;
                printf( "Press any button to restart the programme_" ) ;
                getch() ;
                break ;
            case '2' :
                return 0 ;
            default :
                break ;
        }
    }
}