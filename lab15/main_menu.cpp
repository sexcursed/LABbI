#include "main_menu.h"
#include "name.h"
#include "person.h"
#include "city.h"
#include "cat.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <limits>
#include <map>
#include <memory>
#include <cctype>

std::random_device rd;
std::mt19937 gen(rd());

void clear_input() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string random_string(const std::vector<std::string>& options) {
    std::uniform_int_distribution<> dist(0, options.size() - 1);
    return options[dist(gen)];
}

int random_int(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

bool has_digits(const std::string& str) {
    for (char c : str) {
        if (std::isdigit(c)) {
            return true;
        }
    }
    return false;
}

std::string input_name_field(const std::string& field_name, bool allow_empty) {
    std::string input;
    while (true) {
        std::cout << "Введите " << field_name << ": ";
        std::getline(std::cin, input);
        
        if (allow_empty && input.empty()) {
            return input;
        }
        
        if (!allow_empty && input.empty()) {
            std::cout << "Ошибка: поле не может быть пустым!\n";
            continue;
        }
        
        if (has_digits(input)) {
            std::cout << "Ошибка: " << field_name << " не может содержать цифры!\n";
            continue;
        }
        
        bool only_spaces = true;
        for (char c : input) {
            if (!std::isspace(c)) {
                only_spaces = false;
                break;
            }
        }
        
        if (only_spaces) {
            if (allow_empty) {
                return "";
            } else {
                std::cout << "Ошибка: поле не может состоять только из пробелов!\n";
                continue;
            }
        }
        
        break;
    }
    return input;
}

std::string input_city_name(const std::string& field_name) {
    std::string input;
    while (true) {
        std::cout << "Введите " << field_name << ": ";
        std::getline(std::cin, input);
        
        if (input.empty()) {
            std::cout << "Ошибка: название города не может быть пустым!\n";
            continue;
        }
        
        if (has_digits(input)) {
            std::cout << "Ошибка: название города не может содержать цифры!\n";
            continue;
        }
        
        bool only_spaces = true;
        for (char c : input) {
            if (!std::isspace(c)) {
                only_spaces = false;
                break;
            }
        }
        
        if (only_spaces) {
            std::cout << "Ошибка: название города не может состоять только из пробелов!\n";
            continue;
        }
        
        break;
    }
    return input;
}

int input_height() {
    int height;
    while (true) {
        std::cout << "Введите рост (100 < height < 210): ";
        std::cin >> height;
        
        if (std::cin.fail()) {
            std::cout << "Ошибка: рост должен быть целым числом, а не буквами!\n";
            clear_input();
        } else if (height <= 100 || height >= 210) {
            std::cout << "Ошибка: рост должен быть в диапазоне от 100 до 210 см!\n";
        } else {
            clear_input();
            return height;
        }
    }
}

void demo_task_1() {
    std::cout << "\n=== Демонстрация задания 1.3 ===\n\n";
    Name name_1;
    name_1.set_first_name("Клеопатра");
    Name name_2("Пушкин", "Александр", "Сергеевич");
    Name name_3("Маяковский", "Владимир");
    
    name_1.print();
    name_2.print();
    name_3.print();
}

void demo_task_2() {
    std::cout << "\n=== Демонстрация задания 2.2 ===\n\n";
    Name name_1;
    name_1.set_first_name("Клеопатра");
    Name name_2("Пушкин", "Александр", "Сергеевич");
    Name name_3("Маяковский", "Владимир");
    
    std::shared_ptr<Person> kleo = std::make_shared<Person>(name_1, 152);
    std::shared_ptr<Person> pushkin = std::make_shared<Person>(name_2, 167);
    std::shared_ptr<Person> mayak = std::make_shared<Person>(name_3, 189);
    
    kleo->print();
    pushkin->print();
    mayak->print();
    
    std::cout << "\n=== Демонстрация задания 2.3 ===\n\n";
    
    std::shared_ptr<Person> ivan = std::make_shared<Person>(Name("Чудов", "Иван"),167);
    std::shared_ptr<Person> petr = std::make_shared<Person>(Name("Чудов", "Петр"),165,ivan);
    std::shared_ptr<Person> boris = std::make_shared<Person>(Name("","Борис"),166,petr);
    
    ivan->print();
    petr->print();
    boris->print();
}

void demo_task_3() {
    std::cout << "\n=== Демонстрация задания 3.3 ===\n\n";
    City a("А"), b("Б"), c("В"), d("Г"), e("Д"), f("Е");
    a.add_path(&b,5);
    a.add_path(&f,1);
    a.add_path(&d,6);
    b.add_path(&a,5);
    b.add_path(&c,3);
    c.add_path(&b,3);
    c.add_path(&d,4);
    d.add_path(&c,4);
    d.add_path(&e,2);
    d.add_path(&a,6);
    e.add_path(&f,2);
    f.add_path(&e,2);
    f.add_path(&b,1);
    a.print();
    b.print();
    c.print();
    d.print();
    e.print();
    f.print();
}

void demo_task_4() {
    std::cout << "\n=== Демонстрация задания 4.6 ===\n\n";
    std::shared_ptr<Person> lev = std::make_shared<Person>("Лев", 170);
    std::shared_ptr<Person> sergey = std::make_shared<Person>(Name("Пушкин", "Сергей"), 168, lev);
    std::shared_ptr<Person> alex = std::make_shared<Person>("Александр", 167, sergey);
    
    lev->print();
    sergey->print();
    alex->print();
}

void demo_task_5() {
    std::cout << "\n=== Демонстрация задания 5.2 ===\n\n";
    Cat cat("Барсик");
    cat.meow();
    cat.meow(3);
}

Name input_name_manual() {
    std::string second = input_name_field("фамилию", true);
    std::string first = input_name_field("имя", true);
    std::string patronymic = input_name_field("отчество", true);
    return Name(second, first, patronymic);
}

Person input_person_manual(const std::vector<std::shared_ptr<Person>>& persons, int index) {
    std::cout << "\n--- Ввод данных для Person " << index + 1 << " ---\n";
    
    std::string second = input_name_field("фамилию", true);
    std::string first = input_name_field("имя", true);
    std::string patronymic = input_name_field("отчество", true);
    Name name(second, first, patronymic);
    
    int height = input_height();
    
    int father_index;
    while (true) {
        std::cout << "Введите номер отца (0 - если нет, от 1 до " << index << "): ";
        std::cin >> father_index;
        
        if (std::cin.fail()) {
            std::cout << "Ошибка: введите целое число!\n";
            clear_input();
            continue;
        }
        
        if (father_index == 0) {
            clear_input();
            break;
        }
        
        if (father_index < 0) {
            std::cout << "Ошибка: номер отца не может быть отрицательным!\n";
            continue;
        }
        
        if (father_index > index) {
            std::cout << "Ошибка: отца с номером " << father_index << " не существует! ";
            std::cout << "Доступны номера от 1 до " << index << " (или 0 - если нет отца)\n";
            continue;
        }
        
        if (father_index == index + 1) {
            std::cout << "Ошибка: нельзя указать самого себя в качестве отца!\n";
            continue;
        }
        
        clear_input();
        break;
    }
    
    std::shared_ptr<Person> father = nullptr;
    if (father_index > 0 && father_index <= index) {
        father = persons[father_index - 1];
    }
    
    return Person(name, height, father);
}

Person input_person_random(const std::vector<std::shared_ptr<Person>>& persons, int index) {
    std::vector<std::string> first_names = {"Александр", "Дмитрий", "Максим", "Иван", "Петр", "Сергей", "Владимир", "Андрей", "Алексей", "Михаил"};
    std::vector<std::string> second_names = {"Иванов", "Петров", "Сидоров", "Кузнецов", "Смирнов", "Волков", "Морозов", "Новиков", "Козлов", "Лебедев"};
    std::vector<std::string> patronymics = {"Александрович", "Дмитриевич", "Иванович", "Петрович", "Сергеевич", "Владимирович", "Андреевич"};
    
    std::string second = random_string(second_names);
    std::string first = random_string(first_names);
    std::string patronymic = random_string(patronymics);
    Name name(second, first, patronymic);
    
    int height = random_int(150, 200);
    
    std::shared_ptr<Person> father = nullptr;
    if (index > 0 && random_int(0, 2) == 0) {
        std::uniform_int_distribution<> dist(0, index - 1);
        father = persons[dist(gen)];
    }
    
    return Person(name, height, father);
}

void input_cities_manual() {
    int n;
    std::cout << "Введите количество городов: ";
    std::cin >> n;
    clear_input();
    
    std::vector<City> cities;
    for (int i = 0; i < n; i++) {
        std::string name = input_city_name("название города " + std::to_string(i + 1));
        cities.emplace_back(name);
    }
    
    std::cout << "\nВведите связи между городами (для завершения введите 0 0 0):\n";
    std::cout << "Формат: from_city_index to_city_index cost\n";
    
    while (true) {
        int from, to, cost;
        std::cin >> from >> to >> cost;
        if (from == 0 && to == 0 && cost == 0) break;
        if (from >= 1 && from <= n && to >= 1 && to <= n && cost > 0) {
            cities[from - 1].add_path(&cities[to - 1], cost);
        } else {
            std::cout << "Неверный ввод, попробуйте снова\n";
        }
    }
    clear_input();
    
    std::cout << "\n=== Результат ===\n";
    for (auto& city : cities) {
        city.print();
    }
}

void input_cities_random() {
    int n;
    std::cout << "Введите количество городов: ";
    std::cin >> n;
    clear_input();
    
    std::vector<City> cities;
    std::vector<std::string> city_names = {"Москва", "Санкт-Петербург", "Новосибирск", "Екатеринбург", "Казань", "Нижний Новгород", "Челябинск", "Самара", "Омск", "Ростов-на-Дону"};
    
    for (int i = 0; i < n; i++) {
        std::string name = (i < 10) ? city_names[i] : "Город" + std::to_string(i + 1);
        cities.emplace_back(name);
    }
    
    int connections = random_int(n, n * 2);
    for (int i = 0; i < connections; i++) {
        int from = random_int(0, n - 1);
        int to = random_int(0, n - 1);
        if (from != to) {
            int cost = random_int(1, 20);
            cities[from].add_path(&cities[to], cost);
        }
    }
    
    std::cout << "\n=== Результат ===\n";
    for (auto& city : cities) {
        city.print();
    }
}

void input_cities_from_file() {
    std::string filename;
    std::cout << "Введите имя файла: ";
    std::getline(std::cin, filename);
    
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Ошибка открытия файла!\n";
        return;
    }
    
    int n;
    file >> n;
    file.ignore();
    
    std::vector<City> cities;
    for (int i = 0; i < n; i++) {
        std::string name;
        std::getline(file, name);
        
        if (has_digits(name)) {
            std::cout << "Предупреждение: название города \"" << name << "\" содержит цифры. Исправлено на: Город" << i+1 << "\n";
            name = "Город" + std::to_string(i+1);
        }
        
        if (name.empty()) {
            name = "Город" + std::to_string(i+1);
        }
        
        cities.emplace_back(name);
    }
    
    int from, to, cost;
    while (file >> from >> to >> cost) {
        if (from >= 1 && from <= n && to >= 1 && to <= n) {
            cities[from - 1].add_path(&cities[to - 1], cost);
        }
    }
    file.close();
    
    std::cout << "\n=== Результат ===\n";
    for (auto& city : cities) {
        city.print();
    }
}

void input_cats_manual() {
    int n;
    std::cout << "Введите количество котов: ";
    std::cin >> n;
    clear_input();
    
    std::vector<Cat> cats;
    for (int i = 0; i < n; i++) {
        std::string name = input_name_field("имя кота " + std::to_string(i + 1), false);
        cats.emplace_back(name);
    }
    
    std::cout << "\n=== Коты мяукают ===\n";
    int meows;
    std::cout << "Сколько раз мякнуть: ";
    std::cin >> meows;
    for (auto& cat : cats) {
        cat.meow(meows);
    }
    clear_input();
}

void input_cats_random() {
    int n;
    std::cout << "Введите количество котов: ";
    std::cin >> n;
    clear_input();
    
    std::vector<std::string> cat_names = {"Барсик", "Мурзик", "Рыжик", "Снежок", "Васька", "Тиша", "Маркиз", "Симба", "Кузя", "Персик"};
    std::vector<Cat> cats;
    
    for (int i = 0; i < n; i++) {
        std::string name = cat_names[random_int(0, cat_names.size() - 1)];
        if (n > 1) {
            name += std::to_string(i + 1);
        }
        cats.emplace_back(name);
    }
    
    std::cout << "\n=== Коты мяукают ===\n";
    for (auto& cat : cats) {
        cat.meow(random_int(1, 5));
    }
}

void input_cats_from_file() {
    std::string filename;
    std::cout << "Введите имя файла: ";
    std::getline(std::cin, filename);
    
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Ошибка открытия файла!\n";
        return;
    }
    
    std::vector<Cat> cats;
    std::string name;
    while (std::getline(file, name)) {
        if (!name.empty()) {
            if (has_digits(name)) {
                std::cout << "Предупреждение: имя кота \"" << name << "\" содержит цифры. Цифры будут проигнорированы.\n";
                std::string clean_name;
                for (char c : name) {
                    if (!std::isdigit(c)) {
                        clean_name += c;
                    }
                }
                if (clean_name.empty()) {
                    clean_name = "Кот";
                }
                cats.emplace_back(clean_name);
            } else {
                cats.emplace_back(name);
            }
        }
    }
    file.close();
    
    std::cout << "\n=== Коты мяукают ===\n";
    for (auto& cat : cats) {
        cat.meow(random_int(1, 5));
    }
}

int choose_input_method() {
    std::cout << "\nВыберите способ ввода данных:\n";
    std::cout << "1 - Ручной ввод\n";
    std::cout << "2 - Случайные данные\n";
    std::cout << "3 - Из файла\n";
    std::cout << "Ваш выбор: ";
    
    int choice;
    std::cin >> choice;
    clear_input();
    return choice;
}

void handle_task_1() {
    std::cout << "\n--- Задание 1.3: ---\n";
    std::cout << "1 - Показать пример из задания\n";
    std::cout << "2 - Ввести свои данные\n";
    std::cout << "Ваш выбор: ";
    
    int choice;
    std::cin >> choice;
    clear_input();
    
    if (choice == 1) {
        demo_task_1();
    } else if (choice == 2) {
        int n;
        std::cout << "Сколько объектов Name создать? ";
        std::cin >> n;
        clear_input();
        
        int method = choose_input_method();
        std::vector<Name> names;
        
        for (int i = 0; i < n; i++) {
            if (method == 1) {
                std::cout << "\n--- Name " << i + 1 << " ---\n";
                names.push_back(input_name_manual());
            } else if (method == 2) {
                std::vector<std::string> first_names = {"Анна", "Мария", "Екатерина", "Ольга", "Татьяна", "Наталья", "Ирина", "Светлана"};
                std::vector<std::string> second_names = {"Соколова", "Лебедева", "Козлова", "Новикова", "Морозова", "Петрова", "Сидорова"};
                std::vector<std::string> patronymics = {"Алексеевна", "Владимировна", "Дмитриевна", "Ивановна", "Петровна", "Сергеевна"};
                
                std::string second = random_string(second_names);
                std::string first = random_string(first_names);
                std::string patronymic = random_string(patronymics);
                names.emplace_back(second, first, patronymic);
            } else if (method == 3) {
                std::string filename;
                std::cout << "Введите имя файла: ";
                std::getline(std::cin, filename);
                std::ifstream file(filename);
                if (file) {
                    std::string second, first, patronymic;
                    file >> second >> first >> patronymic;
                    
                    if (has_digits(second) || has_digits(first) || has_digits(patronymic)) {
                        std::cout << "Предупреждение: данные из файла содержат цифры. Цифры будут удалены.\n";
                        std::string clean_second, clean_first, clean_patronymic;
                        for (char c : second) if (!std::isdigit(c)) clean_second += c;
                        for (char c : first) if (!std::isdigit(c)) clean_first += c;
                        for (char c : patronymic) if (!std::isdigit(c)) clean_patronymic += c;
                        names.emplace_back(clean_second, clean_first, clean_patronymic);
                    } else {
                        names.emplace_back(second, first, patronymic);
                    }
                    file.close();
                } else {
                    std::cout << "Ошибка открытия файла!\n";
                    names.emplace_back("", "", "");
                }
            }
        }
        
        std::cout << "\n=== Результат ===\n";
        for (auto& name : names) {
            name.print();
        }
    }
}

void handle_task_2() {
    std::cout << "\n--- Задания 2.2 и 2.3:---\n";
    std::cout << "1 - Показать пример из задания\n";
    std::cout << "2 - Ввести свои данные\n";
    std::cout << "Ваш выбор: ";
    
    int choice;
    std::cin >> choice;
    clear_input();
    
    if (choice == 1) {
        demo_task_2();
    } else if (choice == 2) {
        int n;
        std::cout << "Сколько объектов Person создать? ";
        std::cin >> n;
        clear_input();
        
        int method = choose_input_method();
        std::vector<std::shared_ptr<Person>> persons;
        
        for (int i = 0; i < n; i++) {
            if (method == 1) {
                persons.push_back(std::make_shared<Person>(input_person_manual(persons, i)));
            } else if (method == 2) {
                persons.push_back(std::make_shared<Person>(input_person_random(persons, i)));
            } else if (method == 3) {
                std::string filename;
                std::cout << "Введите имя файла: ";
                std::getline(std::cin, filename);
                std::ifstream file(filename);
                if (file) {
                    std::string second, first, patronymic;
                    int height, father_idx;
                    file >> second >> first >> patronymic >> height >> father_idx;
                    
                    if (has_digits(second) || has_digits(first) || has_digits(patronymic)) {
                        std::cout << "Предупреждение: данные из файла содержат цифры. Цифры будут удалены.\n";
                        std::string clean_second, clean_first, clean_patronymic;
                        for (char c : second) if (!std::isdigit(c)) clean_second += c;
                        for (char c : first) if (!std::isdigit(c)) clean_first += c;
                        for (char c : patronymic) if (!std::isdigit(c)) clean_patronymic += c;
                        second = clean_second;
                        first = clean_first;
                        patronymic = clean_patronymic;
                    }
                    
                    if (height <= 100 || height >= 210) {
                        std::cout << "Предупреждение: рост " << height << " вне допустимого диапазона (100-210). Установлено значение 170.\n";
                        height = 170;
                    }
                    
                    Name name(second, first, patronymic);
                    std::shared_ptr<Person> father = (father_idx > 0 && father_idx <= i) ? persons[father_idx - 1] : nullptr;
                    persons.push_back(std::make_shared<Person>(name, height, father));
                    file.close();
                } else {
                    std::cout << "Ошибка открытия файла!\n";
                    persons.push_back(std::make_shared<Person>(Name(), 170, nullptr));
                }
            }
        }
        
        std::cout << "\n=== Результат ===\n";
        for (auto& person : persons) {
            person->print();
        }
    }
}

void handle_task_3() {
    std::cout << "\n--- Задание 3.3: Класс City ---\n";
    std::cout << "1 - Показать пример из задания\n";
    std::cout << "2 - Ввести свои данные\n";
    std::cout << "Ваш выбор: ";
    
    int choice;
    std::cin >> choice;
    clear_input();
    
    if (choice == 1) {
        demo_task_3();
    } else if (choice == 2) {
        int method = choose_input_method();
        
        if (method == 1) {
            input_cities_manual();
        } else if (method == 2) {
            input_cities_random();
        } else if (method == 3) {
            input_cities_from_file();
        }
    }
}

void handle_task_4() {
    std::cout << "\n--- Задание 4.6: ---\n";
    std::cout << "1 - Показать пример из задания\n";
    std::cout << "2 - Ввести свои данные\n";
    std::cout << "Ваш выбор: ";
    
    int choice;
    std::cin >> choice;
    clear_input();
    
    if (choice == 1) {
        demo_task_4();
    } else if (choice == 2) {
        handle_task_2();
    }
}

void handle_task_5() {
    std::cout << "\n--- Задание 5.2: ---\n";
    std::cout << "1 - Показать пример из задания\n";
    std::cout << "2 - Ввести свои данные\n";
    std::cout << "Ваш выбор: ";
    
    int choice;
    std::cin >> choice;
    clear_input();
    
    if (choice == 1) {
        demo_task_5();
    } else if (choice == 2) {
        int method = choose_input_method();
        
        if (method == 1) {
            input_cats_manual();
        } else if (method == 2) {
            input_cats_random();
        } else if (method == 3) {
            input_cats_from_file();
        }
    }
}