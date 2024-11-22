/*
 * ‘ункци€ поиска праметра в .ini файле 
 *
 * @param section название секции
 * @param param название параметра 
 * @param default указатель на значение по умолчанию
 * @param out_buffer указатель на буффер с найденным значением
 * @param max максимальное число считываемых символов 
 * @param name им€ файла, где производитс€ поиск параметра 
 * 
 * @return кол-во считанных символов
 * 
 * @return -1 - файл не найден 
 * @return -2 - секци€ не найдена
 * @return -3 - параметр не найден 
 */

#include "incl.h"
#include "func.h"

int GetPrivateProfileString(char * section, char * param, char * defaultt, char * out_buffer, int max, char * name)
{
    int len_param = char_num(param, max); // длина заданного искомого параметра 
    int len_sec = char_num(section, max); // длина заданной искомй секции
    int len_default = char_num(defaultt, max); // длина строки по умолчанию 
    char c; // перменна€ дл€ хранени€ символа 
    char buff_section[max]; // буффер дл€ работы с секцией
    char buff_par[max]; // буффер дл€ работы с парамтером
    memset(out_buffer, '\0', sizeof(out_buffer)); // инициализируем массив после объ€влени€ 
    memset(buff_section, '\0', sizeof(buff_section)); // инициализируем масив после объ€влени€
    memset(buff_par, '\0', sizeof(buff_section)); // инициализируем массив после объ€влени€ 
    int num = 0; // количество символов в названии секции
    int num_par = 0; // количесвто символов в названии параметра
    bool match_sec = false; // флаг наличи€ секции 
    bool match_par = false; // флаг налчи€ параметра
    FILE * f_open = fopen(name, "r");

    if(f_open == 0)
        return -1;
    while((c = getc(f_open)) != EOF)
    {
        if (c != '\n') // считываем 1 строку
        {
            buff_section[num] = c;
            num++;
        }
        else
        {
            for (int i = 1; i < len_sec + 1; i++) // провер€ем им€ секции 
                                                  //(сравниваем длину имен секций и смотрим, что обе заканчиваеютс€ ']')
            
            {
                if ((buff_section[i] == section[i - 1]) && (len_sec == num-2)) // провер€ем совпадение символов секции
                {
                    match_sec = true; 
                }
                else
                { 
                    num = 0; // обнул€ем счетчик символов секции
                    match_sec = false;
                    memset(buff_par, '\0', sizeof(buff_par));
                    break;
                }
            }
            if(match_sec) //нашли нужную секцию 
            {
                while(1)
                {   
                    while((c = getc(f_open)) != '=') // считываем символы до равно 
                    {
                        if ((c == EOF) || (c == '[')) // встретили конец файла или начало новой секции
                        {
                            fclose(f_open);
                            for (int i = 0; i < len_default; i++) // записываем default в буфер 
                            {
                                out_buffer[i] = defaultt[i];
                            }
                            return -3;
                        }
                        if (( (num_par == len_param) && (c == ' ') ) || (c == '\n')) // пропуск пробелов после названи€ и пустых строк
                            continue;
                        buff_par[num_par] = c;
                        if (buff_par[num_par] == param[num_par])
                        { 
                            match_par = true;
                            num_par++;
                            continue;
                        }
                        else
                        {
                            while((c = getc(f_open)) != '\n'); // пропускаем всЄ после "="
                            match_par = false; // ставим флаг о несовпадении
                            memset(buff_par, '\0', 64); // чистим буфер дл€ проверки параметра
                            num_par = 0; // чистим счетчик кол-ва символов в параметре 
                        }                       
                    }
                    if (num_par != strlen(param)) // несовпадение длины строки парметра
                        continue; // продолжаем искать
                    if (match_par) // совпала длина и название
                    {
                        memset(buff_par, '\0', 64);
                        num_par = 0;
                        while ((c = getc(f_open)) != '\n' && c != EOF)
                        {
                            out_buffer[num_par] = c;
                            num_par++;
                        }
                        fclose(f_open);
                        return char_num(out_buffer, max); // возвращаем количество символов в найденном навзании
                    }
                }
            }
            else
            {
                num = 0;
                memset(buff_section,'\0', 64);
                continue;
            }
        }
    }
    fclose(f_open);
    for (int i = 0; i < len_default; i++) // записываем default в буфер 
    {
        out_buffer[i] = defaultt[i];
    }
    return -2; // ошибка поиска секции или параметров 
}
