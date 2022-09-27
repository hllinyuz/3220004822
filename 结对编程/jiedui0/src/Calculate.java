import java.util.Stack;

public class Calculate {
    //计算后缀式的值
    static Stack<Character> stack = new Stack<>();

    //参数rp：后缀式
    public static float calRp(String rp) {
        Stack<Float> v = new Stack<>();
        char[] arr = rp.toCharArray();
        // 如果是操作数，则推到堆栈
        for (Character ch : arr) {
            if (ch >= '0' && ch <= '9') v.push((float) (ch - '0'));

                // 如果是运算符，则计算结果
                // 在堆栈中有前2个操作数的情况下，将结果推送到堆栈中

            else v.push(getV(ch, v.pop(), v.pop()));
        }
        //返回值return：表达式结果
        return v.pop();
    }

    //将中缀式转换为后缀式
    //参数s：中缀形式的字符串
    public static String getRp(String s) {
        char[] arr = s.toCharArray();
        StringBuilder out = new StringBuilder();

        //从左到右扫描中缀式
        for (char ch : arr) {
            if (ch == ' ') continue;
            // 如果是操作数，则直接输出
            if (ch >= '0' && ch <= '9') {
                out.append(ch);
                continue;
            }

            //如果遇到“+”或“-”，则从堆栈中弹出运算符，直到遇到“（”，然后输出，并进栈。
            if (ch == '+' || ch == '-') {
                while (!stack.empty() && (stack.peek() != '('))
                    out.append(stack.pop());
                stack.push(ch);
                continue;
            }

            //如果是“*”或“÷”，则退栈并输出，直到优先级较低或“（”将运算符进栈
            if (ch == '*' || ch == '÷') {
                while (!stack.empty() && (stack.peek() == '*' || stack.peek() == '÷'))
                    out.append(stack.pop());
                stack.push(ch);
                continue;
            }

            //如果遇到“（”，则直接进栈
            if (ch == '(') stack.push(ch);

            //如果遇到“）”一直退栈输出，直到退到“（”，弹出“（”
            if (ch == ')') {
                while (!stack.empty() && stack.peek() != '(')
                    out.append(stack.pop());
                stack.pop();
            }
        }
        while (!stack.empty()) out.append(stack.pop());
        //返回值return：后缀形式的字符串
        return out.toString();
    }


    public static float getV(char op, float f1, float f2) {
        if (op == '+') {

            return f2 + f1;
        } else if (op == '-') return f2 - f1;
        else if (op == '*') return f2 * f1;
        else if (op == '÷') return f2 / f1;
        else return (float) -0;
    }

    //将含有分数的中缀式转换为后缀式
    //参数s：中缀形式的字符串
    public static String fractionRp(String s) {
        char[] arr = s.toCharArray();
        int len = arr.length;
        StringBuilder out = new StringBuilder();
        //从左到右扫描中缀式
        for (int i = 0; i < len - 2; i++) {
            char ch = arr[i];
            char ch1 = arr[i + 1];
            char ch2 = arr[i + 2];
            if (ch == ' ') continue;
            // 如果是分数，则直接输出
            if (ch >= '0' && ch <= '9' && ch1 == '/' && ch2 >= '0' && ch2 <= '9') {
                out.append(ch);
                out.append(ch1);
                out.append(ch2);
                out.append(" ");
                continue;
            }

            //如果遇到“+”或“-”，则从堆栈中弹出运算符，直到遇到“（”，然后输出，并进栈。
            if (ch == '+' || ch == '-') {
                while (!stack.empty() && (stack.peek() != '('))
                    out.append(stack.pop()).append(" ");
                stack.push(ch);
                continue;
            }

            //如果是“*”或“÷”，则退栈并输出，直到优先级较低或“（”将运算符进栈
            if (ch == '*' || ch == '÷') {
                while (!stack.empty() && (stack.peek() == '*' || stack.peek() == '÷'))
                    out.append(stack.pop()).append(" ");
                stack.push(ch);
                continue;
            }

            //如果遇到“（”，则直接进栈
            if (ch == '(') stack.push(ch);


            if (ch == ')') { //如果遇到“）”一直退栈输出，直到退到“（”，弹出“（”
                while (!stack.empty() && stack.peek() != '(')
                    out.append(stack.pop());
                stack.pop();
            }
        }
        while (!stack.empty()) out.append(stack.pop());
        return out.toString();//返回值return：后缀形式的字符串
    }


}
