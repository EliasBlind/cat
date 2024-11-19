#include "../include/work_string.h"
#include "../include/memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Test (Функции для тестирования кода кототрые я удалю)
// start //=====================================================================================================================================

// Валидация индекса
static void __IndexValidate(String *data, const int index){
    if (index < 0 || index > data->length) {
        if(index < 0)
            fprintf(stderr, "Index less then zero, index = %d\n", index);
        else
            fprintf(stderr, "Index is out of line boundaries, index = %d, text length = %zu\n", index, data->length);
        exit(1);
    }
}
// end //=======================================================================================================================================

// Технические функции (Функции которые используются толлько в других функциях)
// start //=====================================================================================================================================
// Отчистка строки

static void __ClearText(char *text, const size_t start_point, const size_t end_point) {
    for (size_t i = start_point; i < end_point; i++)
        text[i] = 0;
}

static char *__CreateText(const char *text, size_t create_length) {
    create_length++;
    char *buffer = get_calloc( sizeof(*buffer), create_length );
    const size_t text_length = strlen(text);
    for (size_t i = 0; i < text_length; i++)
        buffer[i] = text[i];
    __ClearText(buffer, text_length, create_length);
    return buffer;
}

// Для выделение/освобождение памяти для string и текста в нем
static String *__CreateInside(const char *insetr_text) {
    String *buffer = get_malloc( sizeof(*buffer) );
    const size_t text_lenght = strlen(insetr_text),
                 create_length = text_lenght * 2 + START_MEMORY;
    buffer->length = text_lenght;
    buffer->_itemCount = create_length;
    buffer->text = __CreateText(insetr_text, create_length);
    return buffer;
}

static String *__CustomCreateInside(const size_t length) {
    String *buffer = get_malloc( sizeof(*buffer) );
    const size_t create_length = length + START_MEMORY;
    buffer->length = 0;
    buffer->_itemCount = create_length;
    buffer->text = __CreateText("", create_length);
    return buffer;
}

// Добовляет память к строке
static void __IncreaseMemory(String *data, const size_t added_memory) {
    data->_itemCount += added_memory;
    char *buffer = __CreateText(data->text, data->_itemCount);
    free(data->text);
    data->text = buffer;
}

// При необходимости добовляет память к строке
static void __IncreaseMemoryIfNeeded(String *data, const char *text) {
    const size_t text_lenght = data->length + strlen(text);
    if (text_lenght > data->_itemCount)
        __IncreaseMemory(data, text_lenght);
}

// Удаляет конец строки если она больше необходимого размера
static void __RemoveEndIfNeeded(String *data, const size_t real_text_lenght) {
    if (data->length < real_text_lenght) {
        // Удаление "избыточной" длинны строки
        __ClearText(data->text, data->length, real_text_lenght);
    }
}

static int __StartsWith(const char *data, const char *substring) {
    int result = 1;
    size_t substring_length = strlen(substring);
    for (size_t i = 0; i < substring_length; i++) {
        if(data[i] != substring[i]){
            result = 0;
            break;
        }
    }
    return result;
}

// end //=======================================================================================================================================

// Выделение/освобождение памяти для string и текста в нем
// start //=====================================================================================================================================

// Выдиление памяти для string и установка базовых значений
String *NewString() {
    return __CreateInside("");
}

// Выдиление памяти для string и копированием в неё текста
String *NewSetString(const char *text) {
    return __CreateInside(text);
}

String *NewCustomString(const size_t length) {
    return __CustomCreateInside(length);
}

// Освобождение текста и string
void FreeString(String *data) {
    free(data->text);
    free(data);
}
// end //=======================================================================================================================================


// Основные функции :
// start //=====================================================================================================================================

// Добовляет текст в конец string
void AppendC(String *data,  const char *added_text) {
    __IncreaseMemoryIfNeeded(data, added_text); // Добовляет память при необходимости
    size_t text_lenght = data->length + strlen(added_text); // Новая длинна string
    // Копирование added_text в конец
    for (size_t i = data->length, j = 0; i < text_lenght; i++, j++)
        data->text[i] = added_text[j];
    data->length = text_lenght;
}

// Обьеденяет строки освобождая втрою (insert)String
void Append(String *data, String *insert)
{
    AppendC(data, insert->text);
}

// Удаляет removed_length символов с начала строки
void RemoveStart(String *data, const size_t removed_length) {
    __IndexValidate(data, removed_length);
    size_t transfer_location = 0; // Место копирования не удаленного текста
    for (size_t i = removed_length /*Начало не удаленного текста */; i < data->length; i++, transfer_location++) {
        data->text[transfer_location] = data->text[i];
        data->text[i] = 0; // Удаление скопиравнного символа
    }
    data->length -= removed_length;
    // Удаляет текста который небыл заменен копией, но должен быть удален
    __RemoveEndIfNeeded(data, transfer_location);
}

// Удаляет removed_length символов с конца строки
void RemoveEnd(String *data, const size_t removed_length) {
    __IndexValidate(data, removed_length);
    // Удаление нескольких текстов с конца
    for (size_t i = data->length - removed_length; i < data->length; i++)
        data->text[i] = 0;
    data->length -= removed_length;
}

// Удаляет removed_length символов начиная с index, не удаленные символы переносятся в начало
void RemoveAt(String *data, const size_t removed_length, const size_t index) {
    __IndexValidate(data, index);
    __IndexValidate(data, index + removed_length);
    size_t transfer_location = index;
    // Соединение не удаленных частей
    for (size_t i = index + removed_length; i < data->length; i++, transfer_location++) {
        data->text[transfer_location] = data->text[i];
        data->text[i] = 0; // Удаление скопираванного символа
    }
    data->length -= removed_length;
    // Удаляет текста который небыл заменен копией, но должен быть удален
    __RemoveEndIfNeeded(data, transfer_location);
}

// Происходит вставка text в string начиная с index
size_t InsertC(String *data, const char *text, const int index) {
    __IndexValidate(data, index);
    __IncreaseMemoryIfNeeded(data, text);
    size_t text_length = strlen(text);
    // Перенос текста с начала до места всавки. Переносится на размер вставляемого текста
    for (int i = data->length - 1; i >= index; i--)
        data->text[i + text_length + 0] = data->text[i];
    data->length += text_length;
    size_t transfer_location = 0;
    // Копирование текста в освобожденное место
    for (int i = index; i < index + text_length; i++, transfer_location++)
        data->text[i] = text[transfer_location];
    return transfer_location; // Возвращает конец вставки текста
}

// Происходит вставка string(insert) в string(data) начиная с index. После insert освобождается
size_t Insert(String *data, String *insert, const int index) {
    size_t transfer_location = InsertC(data, insert->text, index);
    FreeString(insert);
    return transfer_location; // Возвращает конец вставки текста
}

// Вывод текста в stdout
int PrintString(const String *data) {
    return printf("%s\n", data->text);
}

// Test zone
size_t CountSubstringC(const String *data, const char *substring) {
    const size_t substring_length = strlen(substring);
    size_t counter = 0;
    long verification_area = (long)data->length - (long)substring_length;
    for (size_t i = 0; (long)i < verification_area; i++) {
        String *buffer = GetSubstring(data, i, i + substring_length);
        if (__StartsWith(buffer->text, substring))
            counter++;
        FreeString(buffer);
    }
    return counter;
}

size_t CountSubstring(const String *data, const String *substring) {
    return CountSubstringC(data, substring->text);
}

size_t IndexOfC(const String *data, const char *substring) {
    size_t substring_length = strlen(substring);
    size_t index = 0;
    while ( index < data->length) {
        String *buffer = GetSubstring(data, index, index + substring_length);
        if(__StartsWith(buffer->text, substring))
            break;
        FreeString(buffer);
        index++;
    }
    return index;
}

size_t IndexOf(const String *data, const String *substring) {
    return IndexOfC(data, substring->text);
}

String *Replase(String *data, char *replacement, char *to_replase) {
    size_t items = CountSubstringC(data, replacement);
    for (size_t i = 0; i < items; i++) {
        size_t index = IndexOfC(data, replacement);
        RemoveAt(data, strlen(replacement), index);
        InsertC(data, to_replase, index);
    }
    return data;
}

String *GetSubstring(const String *data, const size_t start, const size_t end) {
    String *buffer = NewCustomString(end - start);
    for (size_t i = start, j = 0; i < end; i++, j++) {
        buffer->text[j] = data->text[i];
    }
    return buffer;
}

// end //=======================================================================================================================================
