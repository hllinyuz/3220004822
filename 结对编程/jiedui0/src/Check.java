import java.io.*;
import java.util.Arrays;

/**
 * @author hllin
 */
public class Check {
    public static void main(String[] args) {
        String[] correct = new String[0];
        String[] wrong = new String[0];
        String[] tmp;
        String[] tmp1;
        int num1 = 0;
        int num2 = 0;
        try {
            BufferedReader in1 = new BufferedReader(new FileReader("Answers.txt"));
            BufferedReader in2 = new BufferedReader(new FileReader("Ans.txt"));
            String str1, str2;
            //比较两个str是否相等
            while ((str1 = in1.readLine()) != null && (str2 = in2.readLine()) != null) {
                if (str1.equals(str2)) {
                    //分割tmp
                    tmp = str1.split(" ");
                    //数组长度加1
                    correct = Arrays.copyOf(correct, correct.length + 1);
                    //取题号赋值数组
                    correct[num1] = tmp[0];
                    num1++;
                } else {
                    tmp1 = str2.split(" ");
                    wrong = Arrays.copyOf(wrong, wrong.length + 1);
                    wrong[num2] = tmp1[0];
                    num2++;
                }
            }

        } catch (IOException ignored) {
        }

        try {
            BufferedWriter out1 = new BufferedWriter(new FileWriter("Grades.txt"));
            out1.write("Correct:" + num1 + Arrays.toString(correct) + "\n");
            out1.write("Wrong:" + num2 + Arrays.toString(wrong) + "\n");
            out1.close();
            System.out.println("判卷完毕");
        } catch (IOException ignored) {

        }
    }
}
