import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;
import java.util.Scanner;

/**
 * @author hllin
 */
public class MakeQuestion {
    public static void main(String[] args) {

        Random random = new Random();
        //声明类Symbol的对象symbol
        Symbol symbol = new Symbol();
        //声明MyDC的对象evaluator
        MyDC evaluator = new MyDC();
        //声明Rational的对象r
        Rational r = new Rational();
        Scanner sc = new Scanner(System.in);
        //是否要用分数
        int ifFraNum;
        //运算符个数
        int symNum;
        //运算符
        char sym;
        //表达式中出现的随机数
        int value1, tmpValue;
        int value = 0;
        int i, j;

        FileBasicOperation.clearInfoForFile("Exercises.txt");
        FileBasicOperation.clearInfoForFile("Answers.txt");

        System.out.print("请输入要生成的题目数：");
        int x = sc.nextInt();
        outer:
        for (i = 1; i <= x; i++) {
            //系统随机生成的表达式question
            StringBuilder question = new StringBuilder();
            //生成1到2之间的随机数ifFraNum，表示是否要用分数
            ifFraNum = random.nextInt(2) + 1;
            //生成1到5之间的随机数symNum，表示运算符个数
            symNum = random.nextInt(5) + 1;

            //如果余为0，不生成分数
            if (ifFraNum % 2 == 0) {
                //生成0到9之间的随机数value，表示表达式中出现的第一个随机数
                value1 = random.nextInt(10);
                question.append(value1);
                for (j = 1; j <= symNum; j++) {
                    //产生一个运算符sym，共symNum个
                    sym = symbol.makeSymbol();
                    //将生成的随机符号存入question中
                    question.append(sym);
                    //生成0到9之间的随机数value，表示表达式中出现的随机数，共symNum个
                    tmpValue = random.nextInt(10);
                    //排除除数为0或除不到整数的情况
                    if (sym == '÷' && tmpValue == 0) {
                        tmpValue = random.nextInt(9) + 1;
                    }
                    if ((j == 1 && sym == '÷' && value1 % tmpValue != 0) || (sym == '÷' && value % tmpValue != 0)) {
                        i--;
                        continue outer;
                    }
                    value = tmpValue;
                    //将生成的随机数存入question中
                    question.append(value);
                    //排除负数情况
                    if (Calculate.calRp(Calculate.getRp(question.toString())) < 0) {
                        i--;
                        continue outer;
                    }
                }
            }
            //如果取余为1，生成分数
            else {
                for (j = 1; j <= symNum + 1; j++) {
                    //设置分子是1到3之间的随机数
                    r.setNumerator(random.nextInt(3) + 1);
                    //设置分母是4到8之间的随机数
                    r.setDenominator(random.nextInt(5) + 4);
                    //将r的分子赋值给num1
                    int num1 = r.getNumerator();
                    //将r的分母赋值给num2
                    int num2 = r.getDenominator();
                    if (j <= symNum) {
                        //产生一个运算符sym
                        sym = symbol.makeSymbol();
                        //将生成的随机数和随机符号存入question中
                        question.append(num1).append('/').append(num2).append(" ").append(sym).append(" ");
                    } else {
                        //将生成的随机数存入question中
                        question.append(num1).append('/').append(num2);
                        String tmp = evaluator.evaluate(Calculate.fractionRp(question.toString()));
                        //判断不能算出结果和负数
                        if(tmp == null){
                            i--;
                            continue outer;
                        }
                        else if (tmp.charAt(0) == '-') {
                            i--;
                            continue outer;
                        }
                    }
                }
            }

            //将生成的题目输出
            try {
                BufferedWriter out0 = new BufferedWriter(new FileWriter("Exercises.txt", true));
                out0.write(i + " " + question + " =\n");
                out0.flush();
                out0.close();
            } catch (IOException ignored) {
            }

            // 当不生成分数时
            if (ifFraNum % 2 == 0) {
                //正确答案
                int rightAns = (int) Calculate.calRp(Calculate.getRp(question.toString()));
                try {
                    BufferedWriter out1 = new BufferedWriter(new FileWriter("Answers.txt", true));
                    out1.write(i + " " + rightAns + "\n");
                    out1.flush();
                    out1.close();
                } catch (IOException ignored) {
                }
            }

            //当生成分数时
            else {
                //将question由中缀式改成后缀式
                String Question = Calculate.fractionRp(question.toString());
                //正确答案
                String rightAns1 = "";
                rightAns1 = rightAns1 + evaluator.evaluate(Question);
                try {
                    BufferedWriter out1 = new BufferedWriter(new FileWriter("Answers.txt", true));
                    out1.write(i + " " + rightAns1 + "\n");
                    out1.flush();
                    out1.close();
                } catch (IOException ignored) {
                }
            }
        }
        System.out.println("题目生成完毕！");
    }
}
