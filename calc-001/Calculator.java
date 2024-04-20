import java.util.Scanner;

public class Calculator {
    public static void main(String[] args) {
        Converter converter = new Converter();
        String[] actions = {"+", "-", "/", "*"};
        String[] regexActions = {"\\+", "-", "/", "\\*"};
        Scanner scn = new Scanner(System.in);
        System.out.print("Введите выражение из 2 операндов: ");
        String exp = scn.nextLine();
        int actionIndex = -1;

        //отловить баг
        for (int i = 0; i < actions.length; i++) {
            if (exp.contains(actions[i])) {
                actionIndex = i;
                break;
            }
        }

        if (actionIndex == -1) {
            System.out.println("Некорректное выражение");
            return;
        }

        String[] data = exp.split(regexActions[actionIndex]);

        if (data.length != 2) {
            System.out.println("Некорректное количество операндов");
            return;
        }

        if (converter.isRoman(data[0]) != converter.isRoman(data[1])) {
            System.out.println("Числа должны быть в системе одной системе счисления");
            return;
        }

        int a, b;
        boolean isRoman = converter.isRoman(data[0]);
        if (isRoman) {
            a = converter.romanToInt(data[0]);
            b = converter.romanToInt(data[1]);
        } else {
            try {
                a = Integer.parseInt(data[0]);
                b = Integer.parseInt(data[1]);
            } catch (NumberFormatException e) {
                System.out.println("Некорректное количество арифметических операций");
                return;
            }
        }

        int result;
        switch (actions[actionIndex]) {
            case "+":
                result = a + b;
                break;
            case "-":
                result = a - b;
                break;
            case "*":
                result = a * b;
                break;
            default:
                if (b == 0) {
                    System.out.println("Деление на 0 невозможно");
                    return;
                }
                result = a / b;
                break;
        }

        if (isRoman) {
            System.out.println(converter.intToRoman(result));
        } else {
            System.out.println(result);
        }
    }
}
