// file_config.c

// Create by: sigal1980

// Date: 2026-02-14

// Comment: реализация функций работы с файлами конфигураций

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "file_config.h"


//======= Реализации функций =====================================

//================================================================

// Функция загрузки файла конфигурации
int loadConfig(const char * file_name, config_t * config, size_t size){
  FILE * file;
  char read_line[MAX_CONFIG_STRING];
  int param_count = size / sizeof(config_t);

  // Пробую открыть файл для чтения
  file = fopen(file_name, "r");
  if(file == NULL){
    // Возвращаем 1, если не получилось открыть файл
    return 1;
  }else{
    // Если файл открыт, то читаем его, пока не встретим EOF(конец файла)
    while(fgets(read_line, MAX_NAME_LENGHT + MAX_VALUE_LENGHT + 2,
                file) != NULL){
      // Разбираем строку. Если строка пустая, комментарий или содержит
      // неподдерживаемые символы, то пропускаем ее.
      if(parseConfigString(read_line, config, size))
        continue;
      
    }
    
    // Закрываем файл
    fclose(file);
  }

  return 0;
}

//=================================================================

// Функция разбора параметров
int parseConfigString(char * str, config_t * config, size_t size){
  int len = strlen(str);
  int param_count = size / sizeof(config_t);
  // Стока формата.
  // %[^=] - читаем строку до "=" и пишем в поле "name".
  // %*[=] - читаем знак "=", никуда не сохраняем.
  // %s    - читаем строку до конца и пишем во временную переменную.
  char str_format[] = "%[^=]%*[=]%s";
  char param_name[MAX_NAME_LENGHT + 2];
  char param_value[MAX_VALUE_LENGHT + 2];

  // Если строка пустая, то возвращаем 1
  if((len == 1) && (str[0] == '\n'))
    return 1;
  // Если строка начинается с символа '#' (комментарий), то возвращаем 1
  if(strcspn(str, "#") == 0)
    return 1;
  // Если строка содержит неподдерживаемые символы, то возвращаем 1
  if(strcspn(str, "#!?.,+-/*`@$%^&()_[]{}:;|\\<>") != len)
    return 1;

  // Разбор строки
  // Убираем символ новой строки
  str[len - 1] = '\0';
  // Разбираем строку по переменным. Если распознано значений меньше, чем
  // ожидалось, то возвращаем 1.
  if(sscanf(str, str_format, &param_name, &param_value) < 2)
    return 1;
  // Ищем совпадение имен параметров
  for(int i = 0; i < param_count; i++){
    if(strcmp(config[i].name, param_name) != 0)
      continue;
    // Если имя параметра из config равно имени из файла, то устанавливаем
    // значеие из файл в config.value
    if(setConfigValue(param_name, param_value, config, i))
      return 1;
    
  }

  return 0;
}

//=================================================================

int setConfigValue(char * name, char * value, config_t * config,
                   int config_index){
  char * endptr;

  // Проверяем тип значения
  switch(config[config_index].type){
    case INTEGER:
      config[config_index].value.int_value = (int) strtol(value, &endptr, 0);
      break;
    case STRING:
      stpcpy(config[config_index].value.str_value, value);
      break;
    default:
      return 1;
      break;
  }

  return 0;
}
