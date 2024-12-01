#ifndef INC_ARRAY_H
#define INC_ARRAY_H

#include <stddef.h>
#include <stdbool.h>

//совершает обмен значениями переменных по адресам a и b, тип данных которых имеет размер type_size
void swapVoid (void *a, void *b, int type_size);

//возвращает сумму всех элементов массива a размера n, не превышающую максимум для типа int
int getSmallSum(int *a, int n);

//возвращает сумму всех элементов массива a размера n
long long getSum(int *a, int n);

//возвращает максимальный элемент массива a размера n
int getMax(int *a, int n);

//возвращает минимальный элемент массива a размера n
int getMin(int *a, int n);

//возвращает 1, если каждый элемент массива a размера n уникален, и 0 в противном случае
bool isUnique(int *a, int n);

//возвращает 1, если массив a размера n отсортирован по неубыванию, и 0 в противном случае
bool isNonDescendingSorted(int *a, int n);

//возвращает расстояние точки в n-мерном пространстве, координаты которой хранятся в массиве a размера n, от начала координат
float getDistance(int *a, int n);

//возвращает скалярное произведение векторов в n-мерном пространстве, координаты которых хранятся в массивах a и b размера n
double getScalarProduct(int *a, int *b, int n);

//возвращает длину вектора в n-мерном пространстве, координаты которого хранятся в массиве a размера n
double getVectorLength(int *a, int n);

//возвращает косинус угла между векторами в n-мерном пространстве, координаты которых хранятся в массивах a и b размера n
double getCosine(int *a, int *b, int n);

//возвращает количество элементов в отсортированном массиве a размера n без учета дубликатов
int countNUnique(long long *a, int n);

//возвращает количество элементов value в массиве a размера n
int countValues(const int *a, int n, int value);

//ввод массива a размера n
void inputArray_(int *a , size_t n);
//вывод массива a размера n
void outputArray_(const int *a, size_t n);
//возвращает значение первого вхождения элемента x
//в массиве a размера n при его наличии, иначе - n
size_t linearSearch_(const int *a, const size_t n, int x);

//возвращает позицию вхождения элемента x
//в отсортированном массиве a размера n при его наличии, иначе - SIZE_MAX
size_t binarySearch_(const int *a, const size_t n, int x);
//возвращает позицию первого элемента равного или большего x
//в отсортированном массиве a размера n
//при отсутствии такого элемента возвращает n
size_t binarySearchMoreOrEqual_(const int *a, const size_t n, int x);

//вставка элемента со значением value в массив data размера n на позицию pos
void insert_ (int *a, size_t *n, size_t pos, int value);
//добавление элемента value в конец массива data размера n
void append_ (int *a, size_t *n, int value);
//удаление из массива data размера n элемента на позиции pos с сохранением порядка оставшихся элементов
void deleteByPosSaveOrder_ (int *a, size_t *n, size_t pos);
//удаление из массива data размера n элемента на позиции pos без сохранения порядка оставшихся элементов
//размер массива data уменьшается на единицу
void deleteByPosUnsaveOrder_ (int *a, size_t *n, size_t pos);


//возвращает значение ’истина’ если все элементы массива data размера n соответствует функции-предикату predicate
//иначе - ’ложь’
int all_(const int* a, size_t n, int (*predicate)(int));
//возвращает значение ’истина’ если хотя бы один элемент
//массива data размера n соответствует функции-предикату predicate
//иначе - ’ложь’
int any_(const int *a, size_t n, int (*predicate)(int));
//применяет функцию predicate ко всем элементам массива source
//размера n и сохраняет результат в массиве dest размера n
void forEach_(const int * source, int * dest, size_t n, const int (*predicate)(int));
//возвращает количество элементов массива data размера n
//удовлетворяющих функции-предикату predicate
int countIf_(const int * a, size_t n, int (*predicate)(int));

//удаляет из массива data размера n все элементы, удовлетворяющие
//функции-предикату deletePredicate, записывает в n новый размер массива
void deleteIf_(int * a, size_t * n, int (*deletePredicate)(int));

#endif

