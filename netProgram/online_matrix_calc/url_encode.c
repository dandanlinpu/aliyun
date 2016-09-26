#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
unsigned char ToHex(unsigned char x)   
{   
    return  x > 9 ? x + 55 : x + 48;   
}  
  
unsigned char FromHex(unsigned char x)   
{   
    unsigned char y;  
    if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;  
    else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;  
    else if (x >= '0' && x <= '9') y = x - '0';  
    else return -1;  
    return y;  
}  
  
std::string UrlEncode(const std::string& str)  
{  
    std::string strTemp = "";  
    size_t length = str.length();  
    for (size_t i = 0; i < length; i++)  
    {  
        if (isalnum((unsigned char)str[i]) ||   
            (str[i] == '-') ||  
            (str[i] == '_') ||   
            (str[i] == '.') ||   
            (str[i] == '~'))  
            strTemp += str[i];  
        else if (str[i] == ' ')  
            strTemp += "+";  
        else  
        {  
            strTemp += '%';  
            strTemp += ToHex((unsigned char)str[i] >> 4);  
            strTemp += ToHex((unsigned char)str[i] % 16);  
        }  
    }  
    return strTemp;  
}  
  
std::string UrlDecode(const std::string& str)  
{  
    std::string strTemp = "";  
    size_t length = str.length();  
    for (size_t i = 0; i < length; i++)  
    {  
        if (str[i] == '+') strTemp += ' ';  
        else if (str[i] == '%')  
        {  
            //assert(i + 2 < length);  
            unsigned char high = FromHex((unsigned char)str[++i]);  
            unsigned char low = FromHex((unsigned char)str[++i]);  
            strTemp += high*16 + low;  
        }  
        else strTemp += str[i];  
    }  
    return strTemp;  
}  
/*
int main(){
   char str[]="/calc?matrix1=%5B1+2+3%7C4+5+6%5D&matrix2=%5B7+8%7C10+11%7C55+100%5D&operation=multiply";
   string str_dec=UrlDecode(str);
   char str_res[100];
   strcpy(str_res,str_dec.data());
   cout<<"str_dec:"<<str_dec<<endl;
   //calc?matrix1=[1 2 3|4 5 6]&matrix2=[7 8|10 11|55 100]&operation=multiply
   char delim[]="[]";
   char *token=strtok(str_res,delim);
   char *matrix1=strtok(NULL,delim);
   token=strtok(NULL,delim);
   char *matrix2=strtok(NULL,delim);
   cout<<matrix1<<endl;
   cout<<matrix2<<endl;

 
   return 0;

}*/
