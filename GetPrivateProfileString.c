/*
 * ������� ������ �������� � .ini ����� 
 *
 * @param section �������� ������
 * @param param �������� ��������� 
 * @param default ��������� �� �������� �� ���������
 * @param out_buffer ��������� �� ������ � ��������� ���������
 * @param max ������������ ����� ����������� �������� 
 * @param name ��� �����, ��� ������������ ����� ��������� 
 * 
 * @return ���-�� ��������� ��������
 * 
 * @return -1 - ���� �� ������ 
 * @return -2 - ������ �� �������
 * @return -3 - �������� �� ������ 
 */

#include "incl.h"
#include "func.h"

int GetPrivateProfileString(char * section, char * param, char * defaultt, char * out_buffer, int max, char * name)
{
    int len_param = char_num(param, max); // ����� ��������� �������� ��������� 
    int len_sec = char_num(section, max); // ����� �������� ������ ������
    int len_default = char_num(defaultt, max); // ����� ������ �� ��������� 
    char c; // ��������� ��� �������� ������� 
    char buff_section[max]; // ������ ��� ������ � �������
    char buff_par[max]; // ������ ��� ������ � ����������
    memset(out_buffer, '\0', sizeof(out_buffer)); // �������������� ������ ����� ���������� 
    memset(buff_section, '\0', sizeof(buff_section)); // �������������� ����� ����� ����������
    memset(buff_par, '\0', sizeof(buff_section)); // �������������� ������ ����� ���������� 
    int num = 0; // ���������� �������� � �������� ������
    int num_par = 0; // ���������� �������� � �������� ���������
    bool match_sec = false; // ���� ������� ������ 
    bool match_par = false; // ���� ������ ���������
    FILE * f_open = fopen(name, "r");

    if(f_open == 0)
        return -1;
    while((c = getc(f_open)) != EOF)
    {
        if (c != '\n') // ��������� 1 ������
        {
            buff_section[num] = c;
            num++;
        }
        else
        {
            for (int i = 1; i < len_sec + 1; i++) // ��������� ��� ������ 
                                                  //(���������� ����� ���� ������ � �������, ��� ��� �������������� ']')
            
            {
                if ((buff_section[i] == section[i - 1]) && (len_sec == num-2)) // ��������� ���������� �������� ������
                {
                    match_sec = true; 
                }
                else
                { 
                    num = 0; // �������� ������� �������� ������
                    match_sec = false;
                    memset(buff_par, '\0', sizeof(buff_par));
                    break;
                }
            }
            if(match_sec) //����� ������ ������ 
            {
                while(1)
                {   
                    while((c = getc(f_open)) != '=') // ��������� ������� �� ����� 
                    {
                        if ((c == EOF) || (c == '[')) // ��������� ����� ����� ��� ������ ����� ������
                        {
                            fclose(f_open);
                            for (int i = 0; i < len_default; i++) // ���������� default � ����� 
                            {
                                out_buffer[i] = defaultt[i];
                            }
                            return -3;
                        }
                        if (( (num_par == len_param) && (c == ' ') ) || (c == '\n')) // ������� �������� ����� �������� � ������ �����
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
                            while((c = getc(f_open)) != '\n'); // ���������� �� ����� "="
                            match_par = false; // ������ ���� � ������������
                            memset(buff_par, '\0', 64); // ������ ����� ��� �������� ���������
                            num_par = 0; // ������ ������� ���-�� �������� � ��������� 
                        }                       
                    }
                    if (num_par != strlen(param)) // ������������ ����� ������ ��������
                        continue; // ���������� ������
                    if (match_par) // ������� ����� � ��������
                    {
                        memset(buff_par, '\0', 64);
                        num_par = 0;
                        while ((c = getc(f_open)) != '\n' && c != EOF)
                        {
                            out_buffer[num_par] = c;
                            num_par++;
                        }
                        fclose(f_open);
                        return char_num(out_buffer, max); // ���������� ���������� �������� � ��������� ��������
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
    for (int i = 0; i < len_default; i++) // ���������� default � ����� 
    {
        out_buffer[i] = defaultt[i];
    }
    return -2; // ������ ������ ������ ��� ���������� 
}
