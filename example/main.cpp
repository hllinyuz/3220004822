#include "Calculator.cpp"
#include "Calculator.h"

int main()
{
    int num, input;
    char *s;
    s = (char *)malloc(50 * sizeof(char));
    List P[4];
    P[0].name = 'A';                          //多项式A
    P[1].name = 'B';                          //多项式B
    P[2].name = 'R';                          //多项式R（运算结果）
    P[0].next = P[1].next = P[2].next = NULL; //将多项式置空
    while (TRUE)
    {
        system("CLS");
        printf("******************************************************************************************\n");
        printf("*                           Unary Sparse Polynomial Calculator                           *\n");
        printf("******************************************************************************************\n");
        printf("*     1 Enter polynomial A/B term by term                                                *\n");
        printf("*     2 Enter polynomial A/B as a mathematical expression                                *\n");
        printf("*     3 Destroy the polynomial A/B/Result/All                                            *\n");
        printf("*     4 Output the number of terms, coefficients and exponents of polynomial A/B/Result  *\n");
        printf("*     5 Output polynomial A/B/Result in a format similar to mathematical expressions     *\n");
        printf("*     6 Exchange polynomials A and B                                                     *\n");
        printf("*     7 Calculate A+B                                                                    *\n");
        printf("*     8 Calculate A-B                                                                    *\n");
        printf("*     9 Calculate A*B                                                                    *\n");
        printf("*    10 Calculate the value of polynomial A/B at x                                       *\n");
        printf("*    11 Calculate the derivative function of polynomial A/B                              *\n");
        printf("*    12 Exit                                                                             *\n");
        printf("******************************************************************************************\n");
        printf("Please select a number: ");
        scanf("%[^\n]", s);
        getchar();
        num = IsNumber(s);
        if (num == 0 || num > 12)
        {
            printf("Wrong num!! 0_0\n");
            system("PAUSE");
            continue;
        }
        switch (num)
        {
        case 1:
        {
            printf("****Enter polynomial A/B term by term****\n");
            printf("**\t1:Polynomial A\n**\t2:Polynomial B\n");
            printf("Please select the polynomial to establish:");
            scanf("%[^\n]", s);
            getchar();
            input = IsNumber(s);
            if (input == 0 || input > 2)
            {
                printf("Wrong num!! 0_0\n");
                system("PAUSE");
                break;
            }
            if (P[input - 1].next != NULL)
            {
                printf("Polynomial %c already exists! 0_0\n", P[input - 1].name);
                system("PAUSE");
                break;
            }
            SimpleEstablish(P, input - 1);
            ArrangePolynomial(P, input - 1);
            printf("Successfully established polynomial %c! ^_^\n", P[input - 1].name);
            system("PAUSE");
            break;
        }
        case 2:
        {
            printf("****Enter polynomial A/B as a mathematical expression****\n");
            printf("**\t1:Polynomial A\n**\t2:Polynomial B\n");
            printf("Please select the polynomial to establish:");
            scanf("%[^\n]", s);
            getchar();
            input = IsNumber(s);
            if (input == 0 || input > 2)
            {
                printf("Wrong num!! 0_0\n");
                system("PAUSE");
                break;
            }
            if (P[input - 1].next != NULL)
            {
                printf("Polynomial %c already exists! 0_0\n", P[input - 1].name);
                system("PAUSE");
                break;
            }
            MathEstablish(P, input - 1);
            ArrangePolynomial(P, input - 1);
            printf("Successfully established polynomial %c! ^_^\n", P[input - 1].name);
            system("PAUSE");
            break;
        }
        case 3:
        {
            printf("****Destroy the polynomial A/B/Result/All****\n");
            printf("**\t1:Polynomial A\t3:Polynomial Result\n**\t2:Polynomial B\t4:All Polynomials\n");
            printf("Please select the polynomial to destroy:");
            scanf("%[^\n]", s);
            getchar();
            input = IsNumber(s);
            if (input == 0 || input > 4)
            {
                printf("Wrong num!! 0_0\n");
                system("PAUSE");
                break;
            }
            switch (input)
            {
            case 1:
            {
                if (P[0].next == NULL)
                    printf("Polynomial A does not exists! 0_0\n");
                else
                {
                    DestroyPolynomial(P, 0);
                    printf("Polynomial A destroyed successfully! ^_^\n");
                }
                break;
            }
            case 2:
            {
                if (P[1].next == NULL)
                    printf("Polynomial B does not exists! 0_0\n");
                else
                {
                    DestroyPolynomial(P, 1);
                    printf("Polynomial B destroyed successfully! ^_^\n");
                }
                break;
            }
            case 3:
            {
                if (P[2].next == NULL)
                    printf("Polynomial Result does not exists! 0_0\n");
                else
                {
                    DestroyPolynomial(P, 2);
                    printf("Polynomial Result destroyed successfully! ^_^\n");
                }
                break;
            }
            case 4:
            {
                int i;
                for (i = 0; i < 3; i++)
                {
                    if (P[i].next == NULL)
                        printf("Polynomial %c does not exists! 0_0\n", P[i].name);
                    else
                    {
                        DestroyPolynomial(P, i);
                        printf("Polynomial %c destroyed successfully! ^_^\n", P[i].name);
                    }
                }
                break;
            }
            }
            system("PAUSE");
            break;
        }
        case 4:
        {
            printf("****Output the number of terms, coefficients and exponents of polynomial A/B/Result****\n");
            printf("**\t1:Polynomial A\t3:Polynomial Result\n**\t2:Polynomial B\t4:All Polynomials\n");
            printf("Please select the polynomial to output:");
            scanf("%[^\n]", s);
            getchar();
            input = IsNumber(s);
            if (input == 0 || input > 4)
            {
                printf("Wrong num!! 0_0\n");
                system("PAUSE");
                break;
            }
            switch (input)
            {
            case 1:
            {
                if (P[0].next == NULL)
                    printf("Polynomial A does not exists! 0_0\n");
                else
                    SimpleOutput(P, 0);
                break;
            }
            case 2:
            {
                if (P[1].next == NULL)
                    printf("Polynomial B does not exists! 0_0\n");
                else
                    SimpleOutput(P, 1);
                break;
            }
            case 3:
            {
                if (P[2].next == NULL)
                    printf("Polynomial Result does not exists! 0_0\n");
                else
                    SimpleOutput(P, 2);
                break;
            }
            case 4:
            {
                int i;
                for (i = 0; i < 3; i++)
                {
                    if (P[i].next == NULL)
                        printf("Polynomial %c does not exists! 0_0\n", P[i].name);
                    else
                        SimpleOutput(P, i);
                }
                break;
            }
            }
            system("PAUSE");
            break;
        }
        case 5:
        {
            printf("****Output polynomial A/B/Result in a format similar to mathematical expressions****\n");
            printf("**\t1:Polynomial A\t3:Polynomial Result\n**\t2:Polynomial B\t4:All Polynomials\n");
            printf("Please select the polynomial to output:");
            scanf("%[^\n]", s);
            getchar();
            input = IsNumber(s);
            if (input == 0 || input > 4)
            {
                printf("Wrong num!! 0_0\n");
                system("PAUSE");
                break;
            }
            switch (input)
            {
            case 1:
            {
                if (P[0].next == NULL)
                    printf("Polynomial A does not exists! 0_0\n");
                else
                    MathOutput(P, 0);
                break;
            }
            case 2:
            {
                if (P[1].next == NULL)
                    printf("Polynomial B does not exists! 0_0\n");
                else
                    MathOutput(P, 1);
                break;
            }
            case 3:
            {
                if (P[2].next == NULL)
                    printf("Polynomial Result does not exists! 0_0\n");
                else
                    MathOutput(P, 2);
                break;
            }
            case 4:
            {
                int i;
                for (i = 0; i < 3; i++)
                {
                    if (P[i].next == NULL)
                        printf("Polynomial %c does not exists! 0_0\n", P[i].name);
                    else
                        MathOutput(P, i);
                }
                break;
            }
            }
            system("PAUSE");
            break;
        }
        case 6:
        {
            printf("****Exchange polynomials A and B****\n");
            if (P[0].next == NULL || P[1].next == NULL)
            {
                if (P[0].next == NULL)
                    printf("Polynomial A does not exists! 0_0\n");
                if (P[1].next == NULL)
                    printf("Polynomial B does not exists! 0_0\n");
            }
            else
            {
                Polynomial *p;
                p = P[0].next;
                P[0].next = P[1].next;
                P[1].next = p;
                printf("Exchange polynomial A and B successfully! ^_^\n");
            }
            system("PAUSE");
            break;
        }
        case 7:
        {
            printf("****Calculate A+B****\n");
            if (P[0].next == NULL || P[1].next == NULL)
            {
                if (P[0].next == NULL)
                    printf("Polynomial A does not exists! 0_0\n");
                if (P[1].next == NULL)
                    printf("Polynomial B does not exists! 0_0\n");
            }
            else
            {
                DestroyPolynomial(P, 2);
                Plus(P);
                ArrangePolynomial(P, 2);
                printf("The result of A+B has been stored in the polynomial Result! ^_^\n");
                MathOutput(P, 2);
            }
            system("PAUSE");
            break;
        }
        case 8:
        {
            printf("****Calculate A-B****\n");
            if (P[0].next == NULL || P[1].next == NULL)
            {
                if (P[0].next == NULL)
                    printf("Polynomial A does not exists! 0_0\n");
                if (P[1].next == NULL)
                    printf("Polynomial B does not exists! 0_0\n");
            }
            else
            {
                DestroyPolynomial(P, 2);
                Minus(P);
                ArrangePolynomial(P, 2);
                printf("The result of A-B has been stored in the polynomial Result! ^_^\n");
                MathOutput(P, 2);
            }
            system("PAUSE");
            break;
        }
        case 9:
        {
            printf("****Calculate A*B****\n");
            if (P[0].next == NULL || P[1].next == NULL)
            {
                if (P[0].next == NULL)
                    printf("Polynomial A does not exists! 0_0\n");
                if (P[1].next == NULL)
                    printf("Polynomial B does not exists! 0_0\n");
            }
            else
            {
                DestroyPolynomial(P, 2);
                Multiply(P);
                ArrangePolynomial(P, 2);
                printf("The result of A*B has been stored in the polynomial Result! ^_^\n");
                MathOutput(P, 2);
            }
            system("PAUSE");
            break;
        }
        case 10:
        {
            printf("****Calculate the value of polynomial A/B at x****\n");
            printf("**\t1:Polynomial A\n**\t2:Polynomial B\n");
            printf("Please select the polynomial to be calculated:");
            scanf("%[^\n]", s);
            getchar();
            input = IsNumber(s);
            if (input == 0 || input > 2)
            {
                printf("Wrong num!! 0_0\n");
                system("PAUSE");
                break;
            }
            if (P[input - 1].next == NULL)
            {
                printf("Polynomial %c does not exists! 0_0\n", P[input - 1].name);
                system("PAUSE");
                break;
            }
            printf("The value of polynomial %c at x is %lf\n", P[input - 1].name, Calculate(P, input - 1));
            system("PAUSE");
            break;
        }
        case 11:
        {
            printf("****Calculate the derivative function of polynomial A/B****\n");
            printf("**\t1:Polynomial A\n**\t2:Polynomial B\n");
            printf("Please select the polynomial that requires derivative:");
            scanf("%[^\n]", s);
            getchar();
            input = IsNumber(s);
            if (input == 0 || input > 2)
            {
                printf("Wrong num!! 0_0\n");
                system("PAUSE");
                break;
            }
            if (P[0].next == NULL)
            {
                printf("Polynomial A does not exists! 0_0\n");
                system("PAUSE");
                break;
            }
            DestroyPolynomial(P, 2);
            Derivative(P, input - 1);
            ArrangePolynomial(P, 2);
            printf("The result of %c' has been stored in the polynomial Result! ^_^\n", P[input - 1].name);
            MathOutput(P, 2);
            system("PAUSE");
            break;
        }
        case 12:
        {
            printf("Thanks for your using!! ^_^\n");
            system("PAUSE");
            goto end;
        }
        }
    }
end:
    return 0;
}