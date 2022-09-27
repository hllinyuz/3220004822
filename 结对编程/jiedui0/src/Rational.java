public class Rational {
    //分子
    int numerator = 1;
    //分母
    int denominator = 1;

    int getNumerator() {   //输出分子
        return numerator;
    }

    //设置分子
    void setNumerator(int a) {
        //计算最大公约数
        int c = f(Math.abs(a), denominator);
        numerator = a / c;
        denominator = denominator / c;
        if (numerator < 0 && denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    int getDenominator() {    //输出分母
        return denominator;
    }

    //设置分母
    void setDenominator(int b) {
        //计算最大公约数
        int c = f(numerator, Math.abs(b));
        numerator = numerator / c;
        denominator = b / c;
        if (numerator < 0 && denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        } else if (numerator > 0 && denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    //求a,b的最大公约数
    int f(int a, int b) {
        if (a == 0) {
            //c为分母不能为0
            return 1;
        }
        //令a>b
        if (a < b) {
            int c = a;
            a = b;
            b = c;
        }
        int r = a % b;
        while (r != 0) {
            a = b;
            b = r;
            r = a % b;
        }
        return b;
    }

    //加法运算
    Rational add(Rational r) {
        //返回有理数r的分子
        int a = r.getNumerator();
        //返回有理数r的分母
        int b = r.getDenominator();
        //计算出新分子
        int newNumerator = numerator * b + denominator * a;
        //计算出新分母
        int newDenominator = denominator * b;
        Rational result = new Rational();
        result.setNumerator(newNumerator);
        result.setDenominator(newDenominator);
        return result;
    }

    //减法运算
    Rational sub(Rational r) {
        int a = r.getNumerator();
        int b = r.getDenominator();
        int newNumerator = numerator * b - denominator * a;
        int newDenominator = denominator * b;
        Rational result = new Rational();
        result.setNumerator(newNumerator);
        result.setDenominator(newDenominator);
        return result;
    }

    //乘法运算
    Rational mul(Rational r) {
        int a = r.getNumerator();
        int b = r.getDenominator();
        int newNumerator = numerator * a;
        int newDenominator = denominator * b;
        Rational result = new Rational();
        result.setNumerator(newNumerator);
        result.setDenominator(newDenominator);
        return result;
    }

    //除法运算
    Rational div(Rational r) {
        int a = r.getNumerator();
        int b = r.getDenominator();
        Rational result = new Rational();
        if (a == 0) {
            System.out.println("分母不能为0");
            result.setNumerator(0);
            System.exit(0);
        } else {
            int newNumerator = numerator * b;
            int newDenominator = denominator * a;
            result.setNumerator(newNumerator);
            result.setDenominator(newDenominator);
        }
        return result;
    }

    //输出计算结果
    public String toString() {
        String result;

        if (numerator == 0) {
            result = "0";
        } else {
            if (denominator == 1)
                result = numerator + "";
            else
                result = numerator + "/" + denominator;
        }
        return result;
    }

}

