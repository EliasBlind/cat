#ifndef WORK_STRING_H
#define WORK_STRING_H

#include <stdio.h>

// Макросы для выделения памяти для string
#define MEMORY_STAP  1000 - 7 // Не используется. Нужен был для увеличения добавленной памяти
#define START_MEMORY 16        // Размер выделенной памяти по умолчанию

typedef struct __String {
    size_t length;     // Количество букв в тексте
    size_t _itemCount; // Количество выделенных байт для текста
    char *text;
} String;


//  Работа с памятью :
extern String *NewString   (void);             // Выделяет память под sting и текст
extern String *NewSetString(const char *text); // Выделяет память под string, текст и копирование текста в string
extern String *NewCustomString(const size_t length);
extern void    FreeString  (String *data);     // Освобождает string и текст

//  Добовление текста :
extern void    AppendC     (String *data, const char *text); // Добавляет текст в string и при необходимости выделяет дополнительно память
extern void    Append      (String *data, String *insert);   // Обьеденяет строки освобождая вторю (insert)

//  Вставка в текст (Возвращают место окончания вставки текста) :
extern size_t  InsertC     (String *data, const char *text, const int index); // Происходит вставка text в string начиная с index
extern size_t  Insert      (String *data, String *insert,   const int index); // Происходит вставка string(insert) в string(data) начиная с index. После insert освобождается

// Удаление текста :
extern void    RemoveStart (String *data, const size_t removed_length);                     // Удаляет removed_length символов с начала строки
extern void    RemoveEnd   (String *data, const size_t removed_length);                     // Удаляет removed_length символов с конца строки
extern void    RemoveAt    (String *data, const size_t removed_length, const size_t index); // Удаляет removed_length символов начиная с index, не удаленные символы переносятся в начало

//  Работа с stdout :
extern int     PrintString (const String *data); // Печатает строку из string в stdout

extern size_t CountSubstringC(const String *data, const char *substring); // Щетает количество подстрок в строке
extern size_t CountSubstring(const String *data, const String *substring);

extern size_t IndexOfC(const String *data, const char *substring);
extern size_t IndexOf(const String *data, const String *substring);

extern String *Replase(String *data, char *replacement, char *to_replase);

extern String *GetSubstring(const String *data, const size_t start, const size_t end);
#endif // WORK_STRING_H
