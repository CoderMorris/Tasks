//Импортируем класс TreeMap из пакета java.util для создания ассоциативных массивов
import java.util.TreeMap;
public class Converter {
    // Создаем TreeMap для хранения римских чисел и их эквивалентов в арабской системе
    TreeMap<Character, Integer> romanKeyMap = new TreeMap<>();
    // Создаем TreeMap для хранения арабских чисел и их эквивалентов в римской системе
    TreeMap<Integer, String> arabianKeyMap = new TreeMap<>();
    public Converter() {
        romanKeyMap.put('I', 1);
        romanKeyMap.put('V', 5);
        romanKeyMap.put('X', 10);
        romanKeyMap.put('L', 50);
        romanKeyMap.put('C', 100);
        romanKeyMap.put('D', 500);
        romanKeyMap.put('M', 1000);
        romanKeyMap.put('i', 1);
        romanKeyMap.put('v', 5);
        romanKeyMap.put('x', 10);
        romanKeyMap.put('l', 50);
        romanKeyMap.put('c', 100);
        romanKeyMap.put('d', 500);
        romanKeyMap.put('m', 1000);

        arabianKeyMap.put(1000, "M");
        arabianKeyMap.put(900, "CM");
        arabianKeyMap.put(500, "D");
        arabianKeyMap.put(400, "CD");
        arabianKeyMap.put(100, "C");
        arabianKeyMap.put(90, "XC");
        arabianKeyMap.put(50, "L");
        arabianKeyMap.put(40, "XL");
        arabianKeyMap.put(10, "X");
        arabianKeyMap.put(9, "IX");
        arabianKeyMap.put(5, "V");
        arabianKeyMap.put(4, "IV");
        arabianKeyMap.put(1, "I");
    }

    // Метод для проверки, является ли входная строка римским числом
    public boolean isRoman(String number){
        // Возвращает true, если первый символ строки - ключ в TreeMap romanKeyMap
        return romanKeyMap.containsKey(number.charAt(0));
    }

    // Метод для преобразования арабского числа в римское
    public String intToRoman(int number) {
        // Строка для хранения результата преобразования
        String roman = "";
        // Переменная для хранения ключа из TreeMap arabianKeyMap
        int arabianKey;
        do {
            // Получаем ближайший больший ключ из TreeMap arabianKeyMap
            arabianKey = arabianKeyMap.floorKey(number);
            // Добавляем соответствующее римское число к результату
            roman += arabianKeyMap.get(arabianKey);
            // Уменьшаем арабское число на значение найденного ключа
            number -= arabianKey;
        } while (number != 0);
        return roman;
    }

    // Метод для преобразования римского числа в арабское
    public int romanToInt(String s) {
        // Получаем индекс последнего символа в строке
        int end = s.length() - 1;
        // Преобразуем строку в массив символов
        char[] arr = s.toCharArray();
        // Переменная для хранения значения римского числа в арабской системе
        int arabian;
        // Получаем значение для последнего символа из TreeMap romanKeyMap
        int result = romanKeyMap.get(arr[end]);
        for (int i = end - 1; i >= 0; i--) {
            // Получаем значение для текущего символа из TreeMap romanKeyMap
            arabian = romanKeyMap.get(arr[i]);
            // Если текущее значение меньше следующего, вычитаем его из результата
            if (arabian < romanKeyMap.get(arr[i + 1])) {
                result -= arabian;
            }
            // В противном случае прибавляем его к результату
            else {
                result += arabian;
            }
        }
        return result;
    }
}
