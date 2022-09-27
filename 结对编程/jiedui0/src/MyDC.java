import java.util.Stack;
import java.util.StringTokenizer;

public class MyDC {
    /**
     * constant for addition symbol
     */
    private final char ADD = '+';
    /**
     * constant for subtraction symbol
     */
    private final char SUBTRACT = '-';
    /**
     * constant for multiplication symbol
     */
    private final char MULTIPLY = '*';
    /**
     * constant for division symbol
     */
    private final char DIVIDE = '÷';
    /**
     * the stack
     */
    private final Stack<String> stack;//存放操作数的栈
    private Rational op1, op2;   //r1,r2

    public MyDC() {
        stack = new Stack<>();
    }

    public String evaluate(String expr) {
        String r1, r2, result = null;
        String token;
        //划分表达式
        StringTokenizer tokenizer = new StringTokenizer(expr);
        while (tokenizer.hasMoreTokens()) {
            //将算数表达式分解
            token = tokenizer.nextToken();
            //见下方isOperator方法,当是运算符的时候进入if语句
            if (isOperator(token)) {
                r2 = stack.pop();
                op2 = tranIntoRational(r2);
                r1 = stack.pop();
                op1 = tranIntoRational(r1);
                //见下方evaSingleOp方法
                result = evalSingleOp(token.charAt(0), op1, op2);
                //将计算结果压栈
                result = stack.push(result);
            } else {
                //操作数入栈
                stack.push(token);
            }
        }
        //输出结果
        return result;
    }

    //判断是否为运算符,注意用equal语句比较字符串
    private boolean isOperator(String token) {
        return token.equals("+") || token.equals("-") ||
                token.equals("*") || token.equals("÷");
    }

    //分数运算
    private String evalSingleOp(char operation, Rational op1, Rational op2) {
        Rational result = new Rational();
        result.setNumerator(0);
        result.setDenominator(1);
        switch (operation) {
            case ADD -> result = op1.add(op2);
            case SUBTRACT -> result = op1.sub(op2);
            case MULTIPLY -> result = op1.mul(op2);
            case DIVIDE -> result = op1.div(op2);
            default -> System.out.println("Error!");
        }
        return result.toString();
    }

    //将String类型转换成Rational类型
    public Rational tranIntoRational(String s) {
        Rational r = new Rational();
        String token1, token2;
        //把操作数以"/"为标记分割开来
        StringTokenizer tokenizer1 = new StringTokenizer(s, "/");
        //分子
        token1 = tokenizer1.nextToken();
        //如果有第二个元素就把token1放在分子的位置，token2放在分母的位置
        if (tokenizer1.hasMoreTokens()) {
            //分母
            token2 = tokenizer1.nextToken();
            //设置分子
            r.setNumerator(Integer.parseInt(token1));
            //设置分母
            r.setDenominator(Integer.parseInt(token2));
        }
        //如果没有第二个元素就把token1放在分子的位置，分母固定为1
        else {
            r.setNumerator(Integer.parseInt(token1));
            r.setDenominator(1);
        }
        return r;
    }
}
