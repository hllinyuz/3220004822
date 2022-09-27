#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"Calculator.h"

int IsNumber(char *s)//判断一行输入是否为整数，是则返回该整数，否则返回0
{
    int num=0,i;
    for(i=0;s[i];i++)
        if(s[i]>='0'&&s[i]<='9'){//判断为数字
            num*=10;
            num+=s[i]-'0';
        }
        else return 0;
    return num;
}

Status IsDouble(char *s,double &num)//判断一行输入是否为数字，是则返回该数字，否则返回ERROR
{
    int i,l=0,tag=1;
    double k=10;
    num=0;
    for(i=0;s[i];i++){
        if(s[i]=='+'||s[i]=='-')
            if(i==0){
                if(s[i]=='+')tag=1;
                else if(s[i]=='-')tag=-1;
            }
            else return ERROR;
        else if(s[i]=='.')k=0.1;
        else if(s[i]>='0'&&s[i]<='9'){
            if(k==(double)10){
                num*=10;
                num+=s[i]-'0';
            }
            else if(k==(double)0.1){
                l++;
                num+=pow(k,l)*(s[i]-'0');
            }
        }
        else return ERROR;
    }
    num*=tag;
    return OK;
}

Status SimpleEstablish(List *P,int t)//逐项输入多项式A/B
{
    int i=0,k=0,ind;
    double index,input=0;
    char *s;
    s=(char*)malloc(50*sizeof(char));
    Polynomial *p,*q;
    printf("***Entering polynomial %c***\n",P[t].name);
    while(k<=0||input-k!=(double)0){
        printf("Please enter the number of terms in the polynomial:");
        scanf("%[^\n]",s);
        getchar();
        if(IsDouble(s,input)==ERROR)printf("ERROR input!! TAT\n");
        else{
            k=(int)input;
            if(input-k!=(double)0)printf("ERROR!!The number of polynomial terms cannot be decimal!! TAT\n");
            if(k<=0)printf("ERROR!!The number of polynomial terms cannot be less than 1!! TAT\n");
        }
    }
    for(i=0;i<k;i++){
        p=(Polynomial*)malloc(sizeof(Polynomial));
        if(p==NULL)return ERROR;
        p->next=NULL;
        simplecoefficient:
        printf("Please enter the coefficient of No.%d term:",i+1);
        scanf("%[^\n]",s);
        getchar();
        if(IsDouble(s,p->coefficient)==ERROR){
            printf("ERROR input!! TAT\n");
            goto simplecoefficient;
        }
        simpleindex:
        printf("Please enter the index of No.%d term:",i+1);
        scanf("%[^\n]",s);
        getchar();
        if(IsDouble(s,index)==ERROR){
            printf("ERROR input!! TAT\n");
            goto simpleindex;
        }
        ind=(int)index;
        if(index-ind!=0){
            printf("ERROR!!Exponent should be an integer!! TAT\n");
            goto simpleindex;
        }
        else p->index=ind;
        if(i==0){
            P[t].next=p;
            q=p;
        }
        else{
            q->next=p;
            q=q->next;
        }
    }
    return OK;
}

Status MathEstablish(List *P,int t)//类数学表达式输入多项式A/B
{
    int i,first=1,l=0,n=0,tag=1,sl=0,ai;
    double a=0,k=10;
    char s,*sp,*sq;
    sp=(char*)malloc(50*sizeof(char));
    Polynomial *q;
    input://输入有误，跳转至此重新输入
    s=' ';
    sl=0;
    k=10;
    first=tag=1;//first为1表示多项式正在插入第一项，tag为1表示无符号系数为正
    a=n=l=0;//重置a和l
    printf("Please enter polynomial %c in the format of ax^b+cx^-d...:\n",P[t].name);
    while(s!='\n'){
        scanf("%c",&s);
        if(s!='\n'){//50个char型内存空间填满之前循环输入
            sl++;//字符串长度
            if(sl%50==0){//内存不足，扩容
                sq=(char*)malloc((sl+50)*sizeof(char));
                if(sq==NULL)return ERROR;
                strcpy(sq,sp);//将原有的值复制到新空间
                free(sp);//若sp指向的是申请的空间，释放原空间
                sp=sq;//将sp指向新开辟的空间
            }
            sp[sl-1]=s;//添加新输入的字符
        }
        else{//输入结束在字符串末尾输入'\0'
            if(sl%50==0){//内存不足，扩容
                sq=(char*)malloc(sl*sizeof(char));
                if(sq==NULL)return ERROR;
                strcpy(sq,sp);
                free(sp);
                sp=sq;
            }
            sp[sl]='\0';
        }
    }
    for(i=0;sp[i];i++){
        if(sp[i]=='+')tag=1;
        else if(sp[i]=='-')tag=-1;
        else if(sp[i]=='.')k=0.1;//判断到小数点，更换倍率
        else if(sp[i]>='0'&&sp[i]<='9'){//判断为数字
            if(k==(double)10){//左移赋值
                a*=k;
                a+=sp[i]-'0';
            }
            else if(k==(double)0.1){
                l++;
                a+=pow(k,l)*(sp[i]-'0');//右移赋值
            }
            if(sp[i+1]){//如果下一个字符存在
                if(sp[i+1]=='x'||sp[i+1]=='X'){//下一个字符存在且为x，系数已读取完毕
                    Polynomial *p;//新建结点
                    p=(Polynomial*)malloc(sizeof(Polynomial));
                    if(p==NULL)return OVERFLOW;
                    p->coefficient=tag*a;//系数赋值
                    p->next=NULL;//将尾结点的next域置空
                    if(first==1){//如果是第一项，直接插入到表头结点的末尾
                        P[t].next=p;//将结点插入到对应的多项式中
                        q=p;//q指向多项式的尾结点
                        first=0;//将first改为0，意为非第一项
                    }
                    else{//若不是第一项
                        q->next=p;//将结点插入到对应的多项式的末尾
                        q=q->next;//q指向多项式的尾结点
                    }
                    //赋值完成后重置各变量
                    a=0;//重置系数/指数
                    l=0;//重置系数/指数的小数位数
                    k=10;//重置倍率
                    tag=1;//重置符号
                }
                else if(sp[i+1]=='+'||sp[i+1]=='-'){//下一个字符存在且为为符号，常数/指数已读取完毕
                    if(n==0){//若为常数
                        Polynomial *p;//新建结点
                        p=(Polynomial*)malloc(sizeof(Polynomial));
                        if(p==NULL)return OVERFLOW;
                        p->coefficient=tag*a;//系数赋值
                        p->index=0;//常数的指数为0
                        p->next=NULL;//将尾结点的next域置空
                        if(first==1){//如果是第一项，直接插入到表头结点的末尾
                            P[t].next=p;//将结点插入到对应的多项式中
                            q=p;//q指向多项式的尾结点
                            first=0;//将first改为0，意为非第一项
                        }
                        else{//若不是第一项
                            q->next=p;//将结点插入到对应的多项式的末尾
                            q=q->next;//q指向多项式的尾结点
                        }
                    }
                     else{//若为指数
                        ai=(int)a;
                        if(a-ai!=0){//若指数为小数，报错并跳转至重新输入
                            printf("ERROR!!Exponent should be an integer!! TAT\n");
                            goto input;
                        }
                        q->index=tag*ai;//指数赋值
                        n=0;//重置指数标记
                    }
                    //赋值完成后重置各变量
                    a=0;//重置系数/指数
                    l=0;//重置系数/指数的小数位数
                    k=10;//重置倍率
                    tag=1;//重置符号
                }
            }
        }
        else if(sp[i]=='x'||sp[i]=='X'){
            if(i==0||sp[i-1]=='-'||sp[i-1]=='+'){//若x前面为空或直接为符号，系数绝对值为1
                Polynomial *p;//新建结点
                p=(Polynomial*)malloc(sizeof(Polynomial));
                if(p==NULL)return OVERFLOW;
                p->coefficient=tag;//系数赋值
                p->next=NULL;//将尾结点的next域置空
                if(first==1){//如果是第一项，直接插入到表头结点的末尾
                    P[t].next=p;//将结点插入到对应的多项式中
                    q=p;//q指向多项式的尾结点
                    first=0;//将first改为0，意为非第一项
                }
                else{//若不是第一项
                    q->next=p;//将结点插入到对应的多项式的末尾
                    q=q->next;//q指向多项式的尾结点
                }
                //赋值完成后重置各变量
                a=0;//重置系数/指数
                l=0;//重置系数/指数的小数位数
                k=10;//重置倍率
                tag=1;//重置符号
            }
            if(sp[i+1]&&(sp[i+1]=='-'||sp[i+1]=='+'))q->index=1;//若x后面直接为符号，指数为1
        }
        else if(sp[i]=='^')n=1;//如果出现^，标记下一个数为指数
        else{
            printf("ERROR!!The input format is wrong!! TAT\n");
            goto input;
        }
    }
    if(sp[i-1]=='x'||sp[i-1]=='X')q->index=1;//如果末尾直接为x，即指数为1
    else if(n==0){//若标记为常数
        Polynomial *p;//新建结点
        p=(Polynomial*)malloc(sizeof(Polynomial));
        if(p==NULL)return OVERFLOW;
        p->coefficient=tag*a;//系数赋值
        p->index=0;//常数的指数为0
        p->next=NULL;//将尾结点的next域置空
        if(first==1){//如果是第一项，直接插入到表头结点的末尾
            P[t].next=p;//将结点插入到对应的多项式中
            q=p;//q指向多项式的尾结点
            first=0;//将first改为0，意为非第一项
        }
        else{//若不是第一项
            q->next=p;//将结点插入到对应的多项式的末尾
            q=q->next;//q指向多项式的尾结点
        }
    }
    else{//若标记为指数
        ai=(int)a;
        if(a-ai!=0){//若指数为小数，报错并跳转至重新输入
            printf("ERROR!!Exponent should be an integer!! TAT\n");
            goto input;
        }
        q->index=tag*ai;//指数赋值
        n=0;//重置指数标记
    }
    return OK;
}

Status DestroyPolynomial(List *P,int i)//销毁多项式A/B/R
{
    if(P[i].next==NULL)return OK;
    Polynomial *p,*q;
    q=P[i].next;
    P[i].next=NULL;
    while(q!=NULL){
        p=q->next;
        free(q);
        q=p;
    }
    return OK;
}

Status SimpleOutput(List *P,int i)//以n, c1,e1, c2,e2, ..., cn,en的格式输出多项式A/B/R
{
    if(P[i].next==NULL)return ERROR;
    int k=0;
    Polynomial *p,*q;
    k=0;
    p=q=P[i].next;
    while(q!=NULL){
        k++;
        q=q->next;
    }
    printf("%c:%d , ",P[i].name,k);
    while(p!=NULL){
        if(p!=P[i].next)printf(" , ");
        printf("%lf,%d",p->coefficient,p->index);
        p=p->next;
    }
    printf("\n");
    return OK;
}

Status ArrangePolynomial(List *P,int i)//整理多项式，合并同类项，并以指数由大到小排序
{
    if(P[i].next==NULL)return ERROR;
    Polynomial *p,*q,*s,*t;
    int max;
    if(P[i].next->next==NULL){//多项式只有一项
        if(P[i].next->coefficient==(double)0)P[i].next->index=0;//若多项式只有一项且系数为0，置指数也为0
        return OK;
    }
    q=P[i].next;//q开始指向多项式的首项，后来指向有序区的最后一项
    while(q->coefficient==(double)0){//多项式首项系数为0
        if(q->next!=NULL){//q不为最后一项，删除q结点
            P[i].next=q->next;
            free(q);
            q=P[i].next;
        }
        else{//q为最后一项
            P[i].next->index=0;//若多项式只有一项且系数为0，置指数也为0
            return OK;
        }
    }
    p=q->next;//p指向无序区的第一项
    max=P[i].next->index;
    while(p!=NULL){
        if(p->coefficient==(double)0){//p结点的系数为0，删除该结点
            q->next=p->next;
            free(p);
            p=q->next;
        }
        else if(p->index<q->index){//p结点的指数比有序区的指数都小，已经有序
            p=p->next;
            q=q->next;
        }
        else if(p->index>max){//p结点的指数比首项大，插入到头结点的下一结点，更新max的值
            max=p->index;
            q->next=p->next;
            p->next=P[i].next;
            P[i].next=p;
            p=q->next;
        }
        else if(p->index==max){//p结点的指数跟首项一样大，系数累加到首项，去掉p结点
            P[i].next->coefficient+=p->coefficient;
            q->next=p->next;
            free(p);
            p=q->next;
        }
        else{//p结点的指数不比首项大
        /*  P[i]|name|->|系数|指数|->......->|系数|指数|->|系数|指数|->......->|系数|指数|->|系数|指数|->......
                              max                s           t                    q           p             */
            s=P[i].next;
            t=s->next;
            while(t!=p){//将p结点与有序区逐一比较
                if(p->index>t->index){//p结点的指数比t结点的指数大，插入到t结点的前一结点
                    q->next=p->next;
                    p->next=t;
                    s->next=p;
                    p=q->next;
                    break;
                }
                else if(p->index==t->index){//p结点的指数跟t结点的指数一样大，系数累加到t结点，去掉p结点
                    t->coefficient+=p->coefficient;
                    q->next=p->next;
                    free(p);
                    p=q->next;
                    break;
                }
                else{//p结点的指数比t结点的指数小，将t向后指
                    s=s->next;
                    t=t->next;
                }
            }
        }
    }
    return OK;
}

Status MathOutput(List *P,int i)//以类数学表达式的格式输出多项式A/B/R
{
    Polynomial *p;
    p=P[i].next;
    printf("%c:",P[i].name);
    while(p!=NULL){
        if(p->coefficient==(double)0){
            if(p==P[i].next)printf("0");
        }
        else if(p->coefficient==(double)1.0){
            if(p!=P[i].next)printf("+");
            if(p->index==0)printf("1");
        }
        else if(p->coefficient==(double)-1.0){
            printf("-");
            if(p->index==0)printf("1");
        }
        else if(p->coefficient>=0&&p!=P[i].next)printf("+%lf",p->coefficient);
        else printf("%lf",p->coefficient);
        if(p->index!=0){
            if(p->index==1)printf("x");
            else printf("x^%d",p->index);
        }
        p=p->next;
    }
    printf("\n");
    return OK;
}

Status Plus(List *P)//计算A+B，结果存入R
{
    if(P[0].next==NULL||P[1].next==NULL){
        if(P[0].next==NULL)printf("ERROR!!Polynomial A is empty. TAT\n");
        if(P[1].next==NULL)printf("ERROR!!Polynomial B is empty. TAT\n");
        return ERROR;
    }
    Polynomial *p,*q,*s,*t;
    p=P[0].next;
    q=P[1].next;
    if(p->index>q->index){//p结点的指数比q结点的指数大，先将p结点复制到R的首项中
        s=(Polynomial*)malloc(sizeof(Polynomial));
        if(s==NULL)return OVERFLOW;
        s->next=NULL;
        s->coefficient=p->coefficient;
        s->index=p->index;
        P[2].next=s;
        p=p->next;
    }
    else if(p->index==q->index){//p、q结点的指数值相等，相加，若系数不为0，将运算结果存到R的首项中
        if(p->coefficient+q->coefficient!=0){
            s=(Polynomial*)malloc(sizeof(Polynomial));
            if(s==NULL)return OVERFLOW;
            s->next=NULL;
            s->coefficient=p->coefficient+q->coefficient;
            s->index=p->index;
            P[2].next=s;
        }
        p=p->next;
        q=q->next;
    }
    else if(p->index<q->index){//p结点的指数比q结点的指数小，先将q结点复制到R的首项中
        s=(Polynomial*)malloc(sizeof(Polynomial));
        if(s==NULL)return OVERFLOW;
        s->next=NULL;
        s->coefficient=q->coefficient;
        s->index=q->index;
        P[2].next=s;
        q=q->next;
    }
    t=P[2].next;
    while(p!=NULL||q!=NULL){
        if(p==NULL||p->coefficient==(double)0){//若A中每一项均复制完成，B中还有剩余项，或A为0，将B中的多项式复制到R的末尾
            while(q!=NULL){
                s=(Polynomial*)malloc(sizeof(Polynomial));
                if(s==NULL)return OVERFLOW;
                s->next=NULL;
                s->coefficient=q->coefficient;
                s->index=q->index;
                t->next=s;
                q=q->next;
                t=t->next;
            }
            return OK;
        }
        else if(q==NULL||q->coefficient==(double)0){//若B中每一项均复制完成，A中还有剩余项，或B为0，将A中的多项式复制到R的末尾
            while(p!=NULL){
                s=(Polynomial*)malloc(sizeof(Polynomial));
                if(s==NULL)return OVERFLOW;
                s->next=NULL;
                s->coefficient=p->coefficient;
                s->index=p->index;
                t->next=s;
                p=p->next;
                t=t->next;
            }
            return OK;
        }
        else{//若A、B均未复制完成，按指数大小降序复制
            if(p->index>q->index){//p结点的指数比q结点的指数大，先将p结点复制到R的首项中
                s=(Polynomial*)malloc(sizeof(Polynomial));
                if(s==NULL)return OVERFLOW;
                s->next=NULL;
                s->coefficient=p->coefficient;
                s->index=p->index;
                t->next=s;
                p=p->next;
                t=t->next;
            }
            else if(p->index==q->index){//p、q结点的指数值相等，相加，若系数不为0，将运算结果存到R的首项中
                if(p->coefficient+q->coefficient!=0){
                    s=(Polynomial*)malloc(sizeof(Polynomial));
                    if(s==NULL)return OVERFLOW;
                    s->next=NULL;
                    s->coefficient=p->coefficient+q->coefficient;
                    s->index=p->index;
                    t->next=s;
                    t=t->next;
                }
                p=p->next;
                q=q->next;
            }
            else if(p->index<q->index){//p结点的指数比q结点的指数小，先将q结点复制到R的首项中
                s=(Polynomial*)malloc(sizeof(Polynomial));
                if(s==NULL)return OVERFLOW;
                s->next=NULL;
                s->coefficient=q->coefficient;
                s->index=q->index;
                t->next=s;
                q=q->next;
                t=t->next;
            }
        }
    }
    if(P[2].next==NULL){//若A、B均为0或A+B结果为0，并未存入R
        s=(Polynomial*)malloc(sizeof(Polynomial));
        if(s==NULL)return OVERFLOW;
        s->next=NULL;
        s->coefficient=0;
        s->index=0;
        P[2].next=s;
    }
    return OK;
}

Status Minus(List *P)//计算A-B，结果存入R
{
    if(P[0].next==NULL||P[1].next==NULL){
        if(P[0].next==NULL)printf("ERROR!!Polynomial A is empty. TAT\n");
        if(P[1].next==NULL)printf("ERROR!!Polynomial B is empty. TAT\n");
        return ERROR;
    }
    Polynomial *p,*q,*s,*t;
    p=P[0].next;
    q=P[1].next;
    if(p->index>q->index){//p结点的指数比q结点的指数大，先将p结点复制到R的首项中
        s=(Polynomial*)malloc(sizeof(Polynomial));
        if(s==NULL)return OVERFLOW;
        s->next=NULL;
        s->coefficient=p->coefficient;
        s->index=p->index;
        P[2].next=s;
        p=p->next;
    }
    else if(p->index==q->index){//p、q结点的指数值相等，相减，若系数不为0，将运算结果存到R的首项中
        if(p->coefficient-q->coefficient!=0){
            s=(Polynomial*)malloc(sizeof(Polynomial));
            if(s==NULL)return OVERFLOW;
            s->next=NULL;
            s->coefficient=p->coefficient-q->coefficient;
            s->index=p->index;
            P[2].next=s;
        }
        p=p->next;
        q=q->next;
    }
    else if(p->index<q->index){//p结点的指数比q结点的指数小，先将q结点的系数取负，复制到R的首项中
        s=(Polynomial*)malloc(sizeof(Polynomial));
        if(s==NULL)return OVERFLOW;
        s->next=NULL;
        s->coefficient=(-1)*q->coefficient;
        s->index=q->index;
        P[2].next=s;
        q=q->next;
    }
    t=P[2].next;
    while(p!=NULL||q!=NULL){
        if(p==NULL||p->coefficient==(double)0){//若A中每一项均复制完成，B中还有剩余项，或A为0，将B中的多项式复制到R的末尾
            while(q!=NULL){
                s=(Polynomial*)malloc(sizeof(Polynomial));
                if(s==NULL)return OVERFLOW;
                s->next=NULL;
                s->coefficient=(-1)*q->coefficient;
                s->index=q->index;
                t->next=s;
                q=q->next;
                t=t->next;
            }
            return OK;
        }
        else if(q==NULL||q->coefficient==(double)0){//若B中每一项均复制完成，A中还有剩余项，或B为0，将A中的多项式复制到R的末尾
            while(p!=NULL){
                s=(Polynomial*)malloc(sizeof(Polynomial));
                if(s==NULL)return OVERFLOW;
                s->next=NULL;
                s->coefficient=p->coefficient;
                s->index=p->index;
                t->next=s;
                p=p->next;
                t=t->next;
            }
            return OK;
        }
        else{//若A、B均未复制完成，按指数大小降序复制
            if(p->index>q->index){//p结点的指数比q结点的指数大，先将p结点复制到R的首项中
                s=(Polynomial*)malloc(sizeof(Polynomial));
                if(s==NULL)return OVERFLOW;
                s->next=NULL;
                s->coefficient=p->coefficient;
                s->index=p->index;
                t->next=s;
                p=p->next;
                t=t->next;
            }
            else if(p->index==q->index){//p、q结点的指数值相等，相减，若系数不为0，将运算结果存到R的首项中
                if(p->coefficient-q->coefficient!=0){
                    s=(Polynomial*)malloc(sizeof(Polynomial));
                    if(s==NULL)return OVERFLOW;
                    s->next=NULL;
                    s->coefficient=p->coefficient-q->coefficient;
                    s->index=p->index;
                    t->next=s;
                    t=t->next;
                }
                p=p->next;
                q=q->next;
            }
            else if(p->index<q->index){//p结点的指数比q结点的指数小，先将q结点的系数取负，复制到R的首项中
                s=(Polynomial*)malloc(sizeof(Polynomial));
                if(s==NULL)return OVERFLOW;
                s->next=NULL;
                s->coefficient=(-1)*q->coefficient;
                s->index=q->index;
                t->next=s;
                q=q->next;
                t=t->next;
            }
        }
    }
    if(P[2].next==NULL){//若A、B均为0或A-B结果为0，并未存入R
        s=(Polynomial*)malloc(sizeof(Polynomial));
        if(s==NULL)return OVERFLOW;
        s->next=NULL;
        s->coefficient=0;
        s->index=0;
        P[2].next=s;
    }
    return OK;
}

double Calculate(List *P,int i)//计算f(x)，结果直接返回
{
    double x,s=0;
    Polynomial *p;
    char *t;
    t=(char*)malloc(50*sizeof(char));
    p=P[i].next;
    inputx:
    printf("Please input: x=");
    scanf("%[^\n]",t);
    getchar();
    if(IsDouble(t,x)==ERROR){
        printf("ERROR input!! TAT\n");
        goto inputx;
    }
    while(p!=NULL){
        s+=p->coefficient*pow(x,p->index);
        p=p->next;
    }
    return s;
}

Status Derivative(List *P,int i)//计算A'/B'，结果存入R
{
    if(P[i].next==NULL)return ERROR;
    Polynomial *p,*q,*t;
    if(P[i].next->index==0)P[i].next=P[i].next->next;
    t=P[i].next;
    /*先在多项式R中插入值为0的项，便于后面的运作*/
    p=(Polynomial*)malloc(sizeof(Polynomial));
    if(p==NULL)return OVERFLOW;
    p->coefficient=0;
    p->index=0;
    p->next=NULL;
    q=P[2].next=p;
    while(t!=NULL){
        if(t->index!=0){
            p=(Polynomial*)malloc(sizeof(Polynomial));
            if(p==NULL)return ERROR;
            p->coefficient=t->coefficient*t->index;
            p->index=t->index-1;
            p->next=NULL;
            q->next=p;
            q=q->next;
            t=t->next;
        }
        else t=t->next;
    }
    return OK;
}

Status Multiply(List *P)//计算A*B，结果存入R
{
    Polynomial *p,*q,*s,*t;
    p=P[0].next;
    q=P[1].next;
    /*先在多项式R中插入值为0的项，便于后面t指针的运作*/
    s=(Polynomial*)malloc(sizeof(Polynomial));
    if(s==NULL)return ERROR;
    s->coefficient=0;
    s->index=0;
    s->next=NULL;
    t=P[2].next=s;
    while(p!=NULL){
        q=P[1].next;
        while(q!=NULL){
            s=(Polynomial*)malloc(sizeof(Polynomial));
            if(s==NULL)return ERROR;
            s->coefficient=p->coefficient*q->coefficient;//系数相乘
            s->index=p->index+q->index;//指数相加
            s->next=NULL;
            t->next=s;
            t=t->next;
            q=q->next;
        }
        p=p->next;
    }
    return OK;
}
