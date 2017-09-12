#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
using namespace std;
 
string removeComments(string prgrm)
{
    int n = prgrm.length();
    string reslt;
 
    /*булевые переменные, индикаторы того, находится ли программа
     сейчас "внутри" однострочного/многострочного комментария */
    bool single_line_comment = false;
    bool multiple_line_comment = false;
 
 
    
    for (int i=0; i<n; i++)
    {
        // Находясь внутри однострочного комментария, программа доходит до его конца
        if (single_line_comment == true && prgrm[i] == '\n')
            single_line_comment = false;
 
        // Находясь внутри многострочного комментария, программа доходит до его конца
        else if  (multiple_line_comment == true && prgrm[i] == '*' && prgrm[i+1] == '/')
            multiple_line_comment = false,  i++;
 
        // Если мы находимся внутри комментария
        else if (single_line_comment || multiple_line_comment)
            continue;
 
        /* Проверка, находится ли программа в данный момент внутри комментариев,
         и соответствующее присваивание значени  булевым переменным */
        else if (prgrm[i] == '/' && prgrm[i+1] == '/')
            single_line_comment = true, i++;
        else if (prgrm[i] == '/' && prgrm[i+1] == '*')
            multiple_line_comment = true,  i++;
 
        // Если мы находимся вне комментария - добавить данный символ в результирующий string, который будет записан в итоговую версию программы
        else  
          reslt += prgrm[i];
              }
    return reslt;
}
 

int main(int argc, char *argv[])
{   
    
    fstream fread(argv[1]);//файл, откуда читается
    ofstream fwrite(argv[2]);//файл, куда записывается
    string prgrm((istreambuf_iterator<char>(fread)),
                 istreambuf_iterator<char>());//для удобства файл исходной программы записывается в string
    string rslt;//в эту переменную типа string будет записан файл программы с удалёнными комментами
    
    
    rslt = removeComments(prgrm);
    
    fwrite << rslt;//записываю итоговую программу в файл
    fwrite.close();
    fread.close();
    return 0;
}
