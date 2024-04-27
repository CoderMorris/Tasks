import java.util.Scanner;
public class Menu {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        JSON json = new JSON();
        double rub;
        String code_cur;
        System.out.print("Введите сумму в рублях для обмена валюты: ");
        do{
            rub = sc.nextDouble();
        }while(rub<0 || rub > 1_000_000);
        System.out.print("Введите код валюты: ");
        do{
            code_cur = sc.nextLine();
        }while(code_cur.length()==0);
        double currency = json.convector(code_cur, rub);
        System.out.println("Вы можете купить " + String.format("%.2f ", currency) + code_cur);
    }
}
