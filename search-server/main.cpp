// Решите загадку: Сколько чисел от 1 до 1000 содержат как минимум одну цифру 3?
// Напишите ответ здесь:
#include <iostream>
#include <string>

using namespace std;

int main()
{   int countNum=0;
    string number;
    for (int i=1;i<=1000;i++)
    { number=to_string(i);
            if (number.find('3')) ++countNum;        
    }
     cout<<countNum<<endl;
    return 0;
}
// Закомитьте изменения и отправьте их в свой репозиторий.
