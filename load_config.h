// load_config.h

// Create by: sigal1980

// Date: 2026-02-14

// Comment: инициализация приложения

/*
 *  Инициализация включает чтение файла конфигурации. Если такового нет, то
 *  он создается, со значениями по умолчанию.
 *  Все ключи и их значения по умолчанию необходимо создать до использования
 *  функции loadConfig. Она опирается на глобальную переменную config (тип
 *  config_t).
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

// определяем имя файла настроек
#define FILE_NAME_CONFIG    "bmp-editor.conf"

// Длина имени параметра
#define MAX_NAME_LENGHT     50

// Длина значения параметра
#define MAX_VALUE_LENGHT    100

// Перечисление с типами настроек
typedef enum{
  INTEGER,
  STRING
} config_type_t;

typedef union{
  int int_value;
  char str_value[MAX_VALUE_LENGHT];
} config_value_t;

// структура для хранения настроек
typedef struct{
  char name[MAX_NAME_LENGHT];
  config_type_t type;
  config_value_t value;
} config_t;

// Конфиурация по умолчанию. полное определение в app_init.c
extern config_t config[];


//======= Функции инициализации ==========================

// Загрузка файла конфигурации
int loadConfig(const char file_name[], config_t config[],
                size_t size);


