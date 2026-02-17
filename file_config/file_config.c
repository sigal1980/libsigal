// file_config.c

// Create by: sigal1980

// Date: 2026-02-14

// Comment: реализация функций работы с файлами конфигураций

#include <string.h>
#include <stdlib.h>

#include "file_config.h"

static int createConfig(const char file_name[], config_t config[],
    size_t size);
static int getConfigIndex(char name[], config_t config[], size_t size);


//======= Реализации функций =====================================

// Функция загрузки файла конфигурации
int loadConfig(const char *file_name, config_t *config, size_t size){
  FILE * file;
  // Разбор строки формата:
  // %[^=] - читаем в первую переменную все символы, пока не встретим знак '=',
  // %*[=] - читаем знак '=', но никуда его не пишем,
  // %s    - читаем оставшиеся символы до символа '\n'. Он по какой-то причине
  //         переходит во вторую строку в начало.
  const char format[] = "%[^=]%*[=]%s";
  char name[MAX_NAME_LENGHT];
  char value[MAX_VALUE_LENGHT];
  int config_index;

  // Пробую открыть файл для чтения
  file = fopen(file_name, "r");
  if(file == NULL){
    // Если файл не открыт, пробуем создать его
    if(createConfig(file_name, config, size))  // если функция  вернула 1
      return 1;                                // возвращаем 1 и из этой
                                               // фукции: нет доступа к  файлу.
  }else{
    // если файл удалось открыть, читаем его построчно
    while(fscanf(file, format, name, value) == 2){
      // Так как символ новой строки оседает в самом начале вычитанных строк,
      // всех, кроме первой, то проверяем его наличие
      if(name[0] == '\n')
        // и удаляем его копированием строки саму в себя со смещением в 1 байт
        strcpy(name, name + 1);
      // Ищем совпадение поля name в массиве структур config_t с прочитанным
      // именем из файла
      config_index = getConfigIndex(name, config, size);
      // Следуя типу заносим прочитанные данные в массив. Индекс найденного
      // члена массива выдала функция getConfigIndex.
      switch(config[config_index].type){
        case INTEGER:
          // Копируем целое значение (прежде прочитанную строку переводим в int)
          config[config_index].value.int_value = atoi(value);
          break;
        case STRING:
          // Копруем строковое значение
          strcpy(config[config_index].value.str_value, value);
          break;
        default:
          break;
      }
    }

    fclose(file);
  }

  return 0;
}

//=================================================================

// Функция создания файла конфигурации по умолчанию
static int createConfig(const char file_name[], config_t config[],
    size_t size){
  FILE * file;
  // Получаем размер структуры (НЕ МАССИВА) с настройками
  size_t size_config_t = sizeof(config_t);

  file = fopen(file_name, "w");
  if(file == NULL)  // Если файл не удалось открыть, значит нет доступа
    return 1;
  
  // Делаем цикл, равый размеру массива (В ЭЛЕМЕНТАХ)
  for(int i = 0; i < size / size_config_t; i++ ){
    // Определяем тип параметра
    switch(config[i].type){
      case INTEGER:
        // если целое, то берем его из поля объединения int_value
        fprintf(file, "%s=%d\n", config[i].name, config[i].value.int_value);
        break;
      case STRING:
        // если строка, то берем его из поля объединения str_value
        fprintf(file, "%s=%s\n", config[i].name, config[i].value.str_value);
        break;
      default:
        break;
    }
  }

  fclose(file);
  return 0;
}

//====================================================================

// Функция сравнения имя параметра, прочитанного из файла с именем, которое
// хранится в массиве структур config. При совпадении возвращает индекс в
// массиве config. При отсутствии совпадений возвращает -1.
static int getConfigIndex(char name[], config_t config[], size_t size){
  size_t size_config_t = sizeof(config_t);
  int result_compare;

  // Запускаем цикл прохода по массиву структур
  for(int i = 0; i < size / size_config_t; i++){
    // Сравниваем имена из файла и массива
    result_compare = strcmp(name, config[i].name);
    if(result_compare == 0){
      // Если они равны, то возвращаем индекс в массиве
      return i;
    }
  }

  // Иначе возвращаем -1. Такого индекса точно нет ))))
  return -1;
}
