import java.util.Random;

//随机产生运算符
public class Symbol {
    char p;

    char makeSymbol() {
        Random random = new Random();
        //生成1到4之间的随机数m，分别表示+-*÷四则运算
        int m = random.nextInt(4) + 1;
        switch (m) {
            case 1 -> p = '+';
            case 2 -> p = '-';
            case 3 -> p = '*';
            case 4 -> p = '÷';
        }
        return p;
    }
}
