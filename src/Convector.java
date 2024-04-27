import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import java.io.FileReader;

public interface Convector  {
    double convector(String code_cur, double rub);
}

/*
* Класс JSON отвечает как за чтение данных из файла,
* так и за конвертацию валюты. Это делает его ответственным
* за множество различных задач, что противоречит принципу
* единственной ответственности (Single Responsibility Principle).
*
* Класс JSON открыт для изменений, поскольку он напрямую зависит от конкретного файла,
* если структура файла изменится, класс придётся переписывать (Open/Closed Principle).
*
* Класс JSON зависит от конкретной реализации (файл "exchange_rate.json"),
* что противоречит принципу инверсии зависимостей (Dependency Inversion Principle).
*/

class JSON implements Convector{
    public double convector(String code_cur, double rub) {
        // Переменная для хранения результата конвертации
        double currency = 0;
        try {
            JSONParser parser = new JSONParser();
            JSONObject jsonObject = (JSONObject) parser.parse(new FileReader("exchange_rate.json"));
            // Проверка наличия кода валюты в файле
            if (jsonObject.containsKey(code_cur)) {
                // Получение курса обмена
                double rate = Double.parseDouble(jsonObject.get(code_cur).toString());
                currency = rub / rate;

            }
            // Сообщение об ошибке, если валюта не найдена и завершение программы
            else {
                System.out.println("Валюта не найдена в обменных курсах");
                System.exit(0);
            }
        } catch (Exception e) {
            // Вывод информации о возникшем исключении
            e.printStackTrace();
        }
        return currency;
    }
}