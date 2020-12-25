#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
using namespace std;

//c++根式化简 https://blog.csdn.net/cjz2005/article/details/104380795

bool is_square(unsigned a) //是否是平方数 是则true
{
    return (sqrt(a) - int(sqrt(a)) == 0);
}
bool is_prime(unsigned a) //是否是质数 是则true
{
    unsigned i=2;
    while(i < a)
    {                   //判断该数是否有公因数
        if(a % i == 0)//
            break;
        i++;
    }
    if(i==a)
        return true;
    else
        return false;
}
int result[2];
int *simple(unsigned int radicand)    //radicand 被开方数
            //化简
{
    if(is_square(radicand))
    {
        if(radicand == 0)  //被开方数不为零
        {   
            result[0] = 1;
            result[1] = 0;
            return result;
        }
        else
        {
            result[0] = 1;//如果delta是平方数，result[0] = 1,即下文中的 coe_delta       
            result[1] = sqrt(radicand);
            return result;
        }
    }
    unsigned int coefficient = 1;
    for(int i = 2;i < radicand;i++)
    {
        if(radicand <= 1 )
        {
            result[0] = 1;  
            result[1] = 1;
            return result;
        }
            if(!is_prime(i))
            continue;
        unsigned int k = 0;
        unsigned int r = radicand;
        while(radicand % i == 0)
        {
            radicand /= i;
            ++k;
        }
        radicand = r;
        if(k >= 2)
        {
            coefficient *= pow(i,k / 2);//coefficient 系数
            radicand /= pow(i,k - k % 2);
        }
    }
    result[0] = coefficient;
    result[1] = radicand;
    return result;
}
void reduction(int &a,int &b)
{
    int smallest = min(abs(a),abs(b));
    for(int i = 2;i <= smallest;i++)
    {
        if(a % i == 0 && b % i == 0)
        {
            a /= i;
            b /= i;
            i--;
        }
    }
}
void reduction(int &a,int &b,int &c)
{
    int small = min(abs(a),abs(b));
    int smallest = min(small,abs(c));
    for(int i = 2;i <= smallest;i++)
    {
        if(a % i == 0 && b % i == 0 && c % i == 0)
        {
            a /= i;
            b /= i;
            c /= i;
            i--;
        }
    }
}
void equation(int a,int b,int c)
{
    int delta = pow(b,2) - 4*a*c;
    if(delta < 0)
        cout << "方程无实数根" << endl;
    if(delta == 0)
        cout << "x1=x2=" << (-b / 2*a) << endl;
    if(delta > 0)
    {
        int coe_delta = simple(delta)[0];
        int denominator = 2*a;//如果不约分，denominator不会为1
        string x1,x2;
        if(coe_delta == 1)//coe_delta == 1有两种情况，一种是delta是平方数，另一种即根式系数为1，在结果中无法约分，也无需打印
        {
            if(is_square(delta))//b=0也不影响结果，b已经被加到 numerator_x1 numerator_x2
            {
                int delta_square = sqrt(delta);
                int numerator_x1 = -b + delta_square;
                int numerator_x2 = -b - delta_square;
                int denominator_bak = denominator;
                reduction(numerator_x1,denominator);
                if(denominator == 1)
                    x1 = to_string(numerator_x1);
                else
                    x1 = to_string(numerator_x1) + "/" + to_string(denominator);
                denominator = denominator_bak; 
                reduction(numerator_x2,denominator);
                if(denominator == 1)
                    x2 = to_string(numerator_x2);
                else
                    x2 = to_string(numerator_x2) + "/" + to_string(denominator);
            }
            else
            {
                if(b == 0)
                {
                    x1 = "√" + to_string(simple(delta)[1]) + "/" + to_string(denominator);
                    x2 = "√" + to_string(simple(delta)[1]) + "/" + to_string(denominator);
                }
                else
                {
                    x1 = "(" + to_string(-b) + "+" + "√" + to_string(simple(delta)[1]) + ")" + "/" + to_string(denominator);
                    x2 = "(" + to_string(-b) + "-" + "√" + to_string(simple(delta)[1]) + ")" + "/" + to_string(denominator);
                }
            }
        }
        else  //如果coe_delta不为1,那么delta不会是平方数，参见simple()，此时在结果中要约分
        {
            if(b == 0)
            {
                reduction(coe_delta,denominator);
                if(denominator == 1)
                {
                    if(coe_delta == 1)
                    {
                        x1 = "√" + to_string(simple(delta)[1]);
                        x2 = "√" + to_string(simple(delta)[1]); 
                    }
                    else
                    {
                        x1 = to_string(coe_delta) + "√" + to_string(simple(delta)[1]);
                        x2 = to_string(coe_delta) + "√" + to_string(simple(delta)[1]); 
                    }
                }
                else 
                {
                    if(coe_delta == 1)
                    {
                        x1 = "√" + to_string(simple(delta)[1]) + "/" + to_string(denominator);
                        x2 = "√" + to_string(simple(delta)[1]) + "/" + to_string(denominator); 
                    }
                    else
                    {
                        x1 = to_string(coe_delta) + "√" + to_string(simple(delta)[1]) + "/" + to_string(denominator);
                        x2 = to_string(coe_delta) + "√" + to_string(simple(delta)[1]) + "/" + to_string(denominator); 
                    }
                }
            }
            else 
            {
                reduction(b,coe_delta,denominator);
                if(denominator == 1)
                {
                    if(coe_delta == 1)
                    {
                        x1 = to_string(-b) + "+" + "√" + to_string(simple(delta)[1]);
                        x2 = to_string(-b) + "-" + "√" + to_string(simple(delta)[1]); 
                    }
                    else 
                    {
                        x1 = to_string(-b) + "+" + to_string(coe_delta) + "√" + to_string(simple(delta)[1]);
                        x2 = to_string(-b) + "-" + to_string(coe_delta) + "√" + to_string(simple(delta)[1]); 
                    }
                }
                else
                {
                    if(coe_delta == 1)
                    {
                        x1 = "(" + to_string(-b) + "+" + "√" + to_string(simple(delta)[1]) + ")" + "/" + to_string(denominator);
                        x2 = "(" + to_string(-b) + "-" + "√" + to_string(simple(delta)[1]) + ")" + "/" + to_string(denominator); 
                    }
                    else
                    {
                        x1 = "(" + to_string(-b) + "+" + to_string(coe_delta) + "√" + to_string(simple(delta)[1]) + ")" + "/" + to_string(denominator);
                        x2 = "(" + to_string(-b) + "-" + to_string(coe_delta) + "√" + to_string(simple(delta)[1]) + ")" + "/" + to_string(denominator); 
                    }
                }
            }
        }
        cout << "x1=" << x1 << endl << "x2=" << x2 << endl;
    }
}
int main()
{
    int a,b,c;a=b=c=0;
    while(true)
    {
        cout << "输入a,b,c:" ;
        cin >> a >> b >> c;
        if(a == 0 & b == 0 && c == 0)
        {
            cout << "请输入正确的值。" << endl;
            break;
        }
        else
            equation(a,b,c);
    }
}
