//
// Created by smyrf on 29.09.2017.
//

#ifndef UNTITLED_INCLUDE_AND_CONSTANTS_H
#define UNTITLED_INCLUDE_AND_CONSTANTS_H
#include <stdio.h> // подключаем все необходимые библиотеки
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <math.h>



int In() //ввод с защитой от юзера
{
    int RightNumber = 0 ;
    while(scanf( "%d" , &RightNumber ) != 1 )
    {
        printf( "Uncorect datatype, print once more_" ) ;
        while( getchar() != '\n' ) ;
    }
    return RightNumber ;
}


int BinaryNumbers( int n , int l ) // преобразование 10 го числа к двоичному
{
    n = abs( n ) ;
    for( int i = l ; i >= 0 ; i-- )
    {
        printf( "%d" , ( n >> i ) & 1) ;
    }
    printf("   ") ;
    return 0 ;
}


int Exponentiation( int  Number, int Exponent ) // возведение в степень
{
    int Result = Number ;
   for( int i = 0 ; i < Exponent ; i++ )
   {
       Result = Result * Number ;
   }
    return Result ;
}

int BinaryLength( int Number )// подсчет количества разрядов в двоичной форме 10 го числа
{
    int Length = 0 ;
    Number = abs( Number ) ;
    while( Number > 0 )
    {
        Number = Number >> 1 ;
        Length ++ ;
    }
    return Length - 1 ;
}

int StringToNumber( char *String )//преобразование строки в число
{
    int Number = 0 ;  //конечное число
    int i = 0 ; //счетчик
    int Sign = 0 ; //знак
    if ( String[i] == '-' ) //определяем знак
    {
        Sign = 1 ;
        i ++ ;
    }
    while ( String[ i ] >= 0x30 && String[ i ] <= 0x39 ) //преобразовываем на основе ASKII
    {
        Number = Number + ( String[ i ] & 0x0F );
        Number = Number * 10 ;
        i ++ ;
    }
    Number = Number / 10 ;
    if ( Sign == 1 )
        Number = -Number ; //разбираемся со знаком
    return Number ;
}

char* NumberToString( int Number ) // преобразование числа в строку
{
    char* String = ( char* )malloc( 255 * sizeof( char ) ) , t , *Temp;// делаем Два указателя из одного сразу массив, и переменную для обмена
    int i = 0 , k = Number ,  Sign = 0 ; // считчик, копия числа , и опрделитель знака
    if( k < 0 ) //определяем знак
    {
        Sign = 1 ;
        k = -k ;
    }
    do {
        t = k % 10 ; //разбираем копию числа
        k = k / 10 ;
        String[ i ] = t | 0x30 ; //преобразовываем на основе ASKII
        i ++ ;
    }while( k > 0 ) ;
    if ( Sign == 1 )//разбираемяся со знаком
    {
        String[ i ] = '-' ;
        i ++ ;
    }
    Temp = ( char* )malloc( i * sizeof( char ) );// т.к. строка перевернута создаем еще одну для удобства переворачивания
    k = 0 ;
    i -- ;
    while( i >= 0 )// переыорачиваем строку
    {
        Temp[ k ] = String [ i ] ;
        i ++ ;
        k -- ;
    }
    Temp[ k ] = '\0' ;
    return Temp ;
}















#endif //UNTITLED_INCLUDE_AND_CONSTANTS_H
