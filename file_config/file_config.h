// file_config.h

// Create by: sigal1980

// Date: 2026-02-14

// Comment: работа с файлами конфигурации

/*  
 *  Для изменения имени файла, переопределите FILE_NAME_CONFIG в приложении:
 *
 *  #define FILE_NAME_CONFIG  "<имя_файла"
 *
 *  Чтение файла конфигурации. Если такового нет, то
 *  он создается, со значениями по умолчанию, заданными в массиве config_t.
 *  Все ключи и их значения по умолчанию необходимо создать до использования
 *  функции loadConfig.
 *  Инициализация переменной:
 *    config_t config[] = {
 *      {.name = "image_width", 
 *       .type = INTEGER,
 *       .value.int_value = 128},
 *      {.name = "image_height",
 *       .type = INTEGER,
 *       .value.int_value = 64},
 *      ....,
 *      {.name = "path_to_src",
 *       .type = STRING,
 *       .value.str_value = "/home/usr/docs"}
 *    };
 * 
 * Пояснение: config - это массив из структур config_t. Первое поле структуры-
 * это название ключа параметра, второе - тип значения, третье - само значение.
 * */

#pragma once

#include <stdio.h>

// Длина имени параметра
#define MAX_NAME_LENGHT     50

// Длина значения параметра
#define MAX_VALUE_LENGHT    100

// Макс. длина строки конфигурации
#define MAX_CONFIG_STRING    (MAX_NAME_LENGHT + MAX_VALUE_LENGHT + 3)

// Перечисление с типами настроек
typedef enum{
  INTEGER,
  STRING
} config_type_t;

// Объединени для хранения значений настроек
typedef union{
  int  int_value;
  char str_value[MAX_VALUE_LENGHT];
} config_value_t;

// структура для хранения настроек
typedef struct{
  // Имя настройки
  char name[MAX_NAME_LENGHT];
  // Тип значения настройки
  config_type_t type;
  // Значение настройки
  config_value_t value;
} config_t;

//======= Функции инициализации ==========================

// Загрузка файла конфигурации
int loadConfig(const char *file_name, config_t *config, size_t size);
// Разборстроки конфигурации из файла
int parseConfigString(char * str, config_t * config, size_t size);
// Присвает значение из файла полю структуры config_t
int setConfigValue(char * name, char * value, config_t * config,
                   int config_index);

