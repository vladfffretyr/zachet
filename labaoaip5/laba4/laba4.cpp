#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

struct Chisla {
    double num;
    int n;
    Chisla* next;
};

struct Znak {
    char sign;
    Znak* next;
};

Chisla* stackNumbers = NULL;
Znak* stackSigns = NULL;

bool check(string);
void polandNote(string, Chisla**, Znak**);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string uravnenie="";
    
    while (1) {
        cout << "Введите выражение: ";
        cin>>uravnenie;
        if (check(uravnenie) == false) {
            cout << "Выражение не верно" << endl;
            
        }
        else {
            cout << "Выражение верно " << endl;
            cout << "Результат в постфиксной записи: " ;
            polandNote(uravnenie, &stackNumbers, &stackSigns);
            cout << endl << "Результат вычисления выражения: " << stackNumbers->num << endl;
            stackNumbers = NULL;
            stackSigns = NULL;

        }
    }
}

bool check(string uravn) {
    int shSkobak = 0;
    bool proovSkobok = false;
    for (int i = 0; i < uravn.size(); i++) {
        switch (uravn[i])
        {

            case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
                if (i + 1 != uravn.size()) {

                    switch (uravn[i+1])
                    {
                        case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':  case '+':case '-':case '*':case '/':case')':case'.':
                            break;

                        default:
                            cout << "false цифра" << i + 1 << endl;
                            return false;
                            break;
                    
                    }
                }
                break;

            case '+':case '-':case '*':case '/':
                if (i + 1 != uravn.size()) {
                    switch (uravn[i + 1])
                    {
                        case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':  case '(':
                            break;

                        default:
                            cout << "false знак" << i + 1 << endl;
                            return false;
                            break;

                    }
                }
                else {
                    return false;
                }
                break;

            case '(':
                if (i + 1 != uravn.size()) {
                    for (int j = i + 1; j < uravn.size();j++) {
                        if (uravn[j] == ')') {
                            if (shSkobak == 0) {
                                j = uravn.size() + 1;
                                proovSkobok = true;
                            }
                            else shSkobak--;
                        }
                        else if (uravn[j] == '(') {
                            shSkobak++;
                        }
                    }
                    if (proovSkobok == true) proovSkobok = false;
                    else { 
                        cout << "false скобка (" << i + 1 << endl;
                        return false; 
                    }
                    switch (uravn[i + 1])
                    {
                    case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '(':
                        break;

                    default:
                        cout << "false скобка (  -> "<< i + 1 << endl;
                        return false;
                        break;

                    }
                }
                else {
                    return false;
                }
                break;

            case ')':
                if (i + 1 != uravn.size()) {
                    switch (uravn[i + 1])
                    {
                    case '+':case '-':case '/':case '*':case ')':
                        break;

                    default:
                        cout << "false скобка )   " << i + 1  << endl;
                        return false;
                        break;

                    }

                    for (int j = i + 1; j >= 0; j--) {
                        if (uravn[j] == '(') {
                            j = -2;
                            proovSkobok = true;
                        }
                        
                    }
                    if (proovSkobok == true) proovSkobok = false;
                    else {
                        cout << "false скобка )  " << i + 1  << endl;
                        return false;
                    }
                }
                break;


            case '.':
                if (i + 1 != uravn.size()) {
                    switch (uravn[i + 1])
                    {
                    case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
                        break;

                    default:
                        cout << "false . -> " << i + 1 << endl;
                        return false;
                        break;

                    }
                }
                else {
                    return false;
                }
                break;
            default:
                break;
        }
    }
}

void polandNote(string urav, Chisla** numb, Znak** sign) {
    string saveNum = "";
    double actionNum = 0;
    Chisla* saveChisla = (*numb);
    Znak* saveZnak = (*sign);
    int shCount = 0;
    int saveN = -1;
    bool proov = false;
    for (int i = 0; i < urav.size();i++) {
        switch (urav[i])
        {
        case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '0':
            for (int j = i; j < urav.size(); j++) {
                saveNum += urav[j];
                i = j;
                if (urav[j+1] == '+' or urav[j+1] == '-' or urav[j+1] == '/' or urav[j+1] == '*' or urav[j+1] == '(' or urav[j+1] == ')') {
                    j = urav.size()+1;
                }
            }
            saveChisla = (*numb);
            (*numb) = new Chisla;
            (*numb)->num= atof(saveNum.c_str());
            saveNum = "";
            shCount++;
            (*numb)->n = shCount;
            (*numb)->next = saveChisla;
            break;

        case '+':case '-':case '*':case '/':case ')':case '(':
            if ((*sign) == NULL) {
                saveZnak = (*sign);
                (*sign) = new Znak;
                (*sign)->sign = urav[i];
                (*sign)->next = saveZnak;
            }
            else if (((*sign)->sign=='+' or (*sign)->sign == '-') and (urav[i] == '/' or urav[i] == '*')) {
                saveZnak = (*sign);
                (*sign) = new Znak;
                (*sign)->sign = urav[i];
                (*sign)->next = saveZnak;
            }
            else if (urav[i] == '(' or (*sign)->sign == '(') {

                saveZnak = (*sign);
                (*sign) = new Znak;
                (*sign)->sign = urav[i];
                (*sign)->next = saveZnak;
            }

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////

            else if ((((*sign)->sign == '/' or (*sign)->sign == '*') and (urav[i] == '+' or urav[i] == '-')) or(((*sign)->sign == '/' or (*sign)->sign == '*') and (urav[i] == '*' or urav[i] == '/'))) {
                actionNum = (*numb)->num;
                (*numb) = (*numb)->next;
                if ((*sign)->sign == '/') {
                    if (saveN == -1) {
                        saveN = (*numb)->n;
                        cout << (*numb)->num << " " << actionNum << "/ ";
                    }
                    else if ((*numb)->n != saveN) {
                        cout << (*numb)->num << " " << actionNum << "/ ";
                        proov = true;
                    }
                    else if((*numb)->n== saveN and proov == false){
                        cout << actionNum << "/ ";
                    }
                    else if ((*numb)->n == saveN and proov == true) {
                        cout << "/ ";
                        proov = false;
                    }
                    (*numb)->num /= actionNum;
                    (*sign) = (*sign)->next;
                    i--;
                }
                else if ((*sign)->sign == '*') {
                    if (saveN == -1) {
                        saveN = (*numb)->n;
                        cout << (*numb)->num << " " << actionNum << "* ";
                    }
                    else if ((*numb)->n != saveN) {
                        cout << (*numb)->num << " " << actionNum << "* ";
                        proov = true;
                    }
                    else if ((*numb)->n == saveN and proov == false) {
                        cout << actionNum << "* ";
                    }
                    else if ((*numb)->n == saveN and proov == true) {
                        cout << "* ";
                        proov = false;
                    }
                    (*numb)->num *= actionNum;
                    (*sign) = (*sign)->next;
                    i--;
                }
            }
            else if (((*sign)->sign == '+' or (*sign)->sign == '-') and (urav[i] == '+' or urav[i] == '-')) {
                
                actionNum = (*numb)->num;
                (*numb) = (*numb)->next;
                
                if ((*sign)->sign == '+') {
                    if (saveN == -1) {
                        saveN = (*numb)->n;
                        cout << (*numb)->num << " " << actionNum << "+ ";
                    }
                    else if ((*numb)->n != saveN) {
                        cout << (*numb)->num << " " << actionNum << "+ ";
                        proov = true;
                    }
                    else if ((*numb)->n == saveN and proov == false) {
                        cout << actionNum << "+ ";
                    }
                    else if ((*numb)->n == saveN and proov == true) {
                        cout << "+ ";
                        proov = false;
                    }
                    (*numb)->num += actionNum;
                    (*sign) = (*sign)->next;
                    i--;
                }
                else if ((*sign)->sign == '-') {
                    if (saveN == -1) {
                        saveN = (*numb)->n;
                        cout << (*numb)->num << " " << actionNum << "- ";
                    }
                    else if ((*numb)->n != saveN) {
                        cout << (*numb)->num << " " << actionNum << "- ";
                        proov = true;
                    }
                    else if ((*numb)->n == saveN and proov == false) {
                        cout << actionNum << "- ";
                    }
                    else if ((*numb)->n == saveN and proov == true) {
                        cout << "- ";
                        proov = false;
                    }
                    (*numb)->num -= actionNum;
                    (*sign) = (*sign)->next;
                    i--;
                }
            }
            else if (urav[i] == ')') {
                while ((*sign)->sign != '(') {
                        actionNum = (*numb)->num;
                        (*numb) = (*numb)->next;
                        if ((*sign)->sign == '/') {
                            if (saveN == -1) {
                                saveN = (*numb)->n;
                                cout << (*numb)->num << " " << actionNum << "/ ";
                            }
                            else if ((*numb)->n != saveN) {
                                cout << (*numb)->num << " " << actionNum << "/ ";
                                proov = true;
                            }
                            else if ((*numb)->n == saveN and proov == false) {
                                cout << actionNum << "/ ";
                            }
                            else if ((*numb)->n == saveN and proov == true) {
                                cout << "/ ";
                                proov = false;
                            }
                            (*numb)->num /= actionNum;
                        }
                        else if ((*sign)->sign == '*') {
                            if (saveN == -1) {
                                saveN = (*numb)->n;
                                cout << (*numb)->num << " " << actionNum << "* ";
                            }
                            else if ((*numb)->n != saveN) {
                                cout << (*numb)->num << " " << actionNum << "* ";
                                proov = true;
                            }
                            else if ((*numb)->n == saveN and proov == false) {
                                cout << actionNum << "* ";
                            }
                            else if ((*numb)->n == saveN and proov == true) {
                                cout << "* ";
                                proov = false;
                            }
                            (*numb)->num *= actionNum;
                        }
                        else if ((*sign)->sign == '+') {
                            if (saveN == -1) {
                                saveN = (*numb)->n;
                                cout << (*numb)->num << " " << actionNum << "+ ";
                            }
                            else if ((*numb)->n != saveN) {
                                cout << (*numb)->num << " " << actionNum << "+ ";
                                proov = true;
                            }
                            else if ((*numb)->n == saveN and proov == false) {
                                cout << actionNum << "+ ";
                            }
                            else if ((*numb)->n == saveN and proov == true) {
                                cout << "+ ";
                                proov = false;
                            }
                            (*numb)->num += actionNum;
                        }
                        else if ((*sign)->sign == '-') {
                            if (saveN == -1) {
                                saveN = (*numb)->n;
                                cout << (*numb)->num << " " << actionNum << "- ";
                            }
                            else if ((*numb)->n != saveN) {
                                cout << (*numb)->num << " " << actionNum << "- ";
                                proov = true;
                            }
                            else if ((*numb)->n == saveN and proov == false) {
                                cout << actionNum << "- ";
                            }
                            else if ((*numb)->n == saveN and proov == true) {
                                cout << "- ";
                                proov = false;
                            }
                            (*numb)->num -= actionNum;
                        }
                        (*sign) = (*sign)->next;
                }
                (*sign) = (*sign)->next; 
            }
            break;

            default:
                break;
        }
    }
    while ((*sign) != NULL) {
        actionNum = (*numb)->num;
        (*numb) = (*numb)->next;
        if ((*sign)->sign == '/') {
            if (saveN == -1) {
                saveN = (*numb)->n;
                cout << (*numb)->num << " " << actionNum << "/ ";
            }
            else if ((*numb)->n != saveN) {
                cout << (*numb)->num << " " << actionNum << "/ ";
                proov = true;
            }
            else if ((*numb)->n == saveN and proov == false) {
                cout << actionNum << "/ ";
            }
            else if ((*numb)->n == saveN and proov == true) {
                cout << "/ ";
                proov = false;
            }
            (*numb)->num /= actionNum;
        }
        else if ((*sign)->sign == '*') {
            if (saveN == -1) {
                saveN = (*numb)->n;
                cout << (*numb)->num << " " << actionNum << "* ";
            }
            else if ((*numb)->n != saveN) {
                cout << (*numb)->num << " " << actionNum << "* ";
                proov = true;
            }
            else if ((*numb)->n == saveN and proov == false) {
                cout << actionNum << "* ";
            }
            else if ((*numb)->n == saveN and proov == true) {
                cout << "* ";
                proov = false;
            }
            (*numb)->num *= actionNum;
        }
        else if ((*sign)->sign == '+') {
            if (saveN == -1) {
                saveN = (*numb)->n;
                cout << (*numb)->num << " " << actionNum << "+ ";
            }
            else if ((*numb)->n != saveN) {
                cout << (*numb)->num << " " << actionNum << "+ ";
                proov = true;
            }
            else if ((*numb)->n == saveN and proov == false) {
                cout << actionNum << "+ ";
            }
            else if ((*numb)->n == saveN and proov == true) {
                cout << "+ ";
                proov = false;
            }
            (*numb)->num += actionNum;
        }
        else if ((*sign)->sign == '-') {
            if (saveN == -1) {
                saveN = (*numb)->n;
                cout << (*numb)->num << " " << actionNum << "- ";
            }
            else if ((*numb)->n != saveN) {
                cout << (*numb)->num << " " << actionNum << "- ";
                proov = true;
            }
            else if ((*numb)->n == saveN and proov == false) {
                cout << actionNum << "- ";
            }
            else if ((*numb)->n == saveN and proov == true) {
                cout << "- ";
                proov = false;
            }
            (*numb)->num -= actionNum;
        }
        (*sign) = (*sign)->next;
    }
}
