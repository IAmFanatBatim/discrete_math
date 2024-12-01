#include "ordered_array_set\ordered_array_set.c"
#include "matrix\matrix.c"


//Возвращает функционал - массив CS, показывающий, сколько раз определенный столбец покрывается подмножеством множества конституент IS
void getCS(int *CS, ordered_array_set IS, matrix quine) {
    //Инициализирует значения элементов массива CS нулями; известно, что этих элементов будет столько же, сколько конституент - и сколько столбцов в матрице quine
    for (int i = 0; i < quine.nCols; i++) {
        CS[i] = 0;
    }
    //Перебираются все импликанты из массива IS
    for (int cur_i_ind = 0; cur_i_ind < IS.size; cur_i_ind++) {
        //Для каждой импликанты перебираются все конституенты, и если они покрываются выбранной импликантой, соответствующие им позиции массива CS увеличиваются на 1
        //Стоит отметить, что в множестве I нумерация импликант идет с единицы, в то время как строки матрицы нумеруются с нуля
        //Поэтому, используя элемент множества как индекс, его необходимо уменьшить на 1
        for (int cur_const_ind = 0; cur_const_ind < quine.nCols; cur_const_ind++) {
            if (quine.values[IS.data[cur_i_ind]-1][cur_const_ind]) {
                CS[cur_const_ind] += 1;
            }
        }
    }
}

//Возвращает 1, если функционал CS указывает на то, что объединение подмножества множества импликант IS является тупиковой формой, и 0 в противном случае
bool isISASolution (int *CS, ordered_array_set IS, matrix quine) {
    //Если в массиве CS есть хотя бы один ноль, значит, не все столбцы покрыты данным множеством импликант IS; возвращается 0
    if (linearSearch_(CS, quine.nCols, 0) != quine.nCols) {
        return false;
    }
    //Далее нужно проверить, у каждой ли импликанты есть хотя бы одна конституента, покрываемая только ей, т. е. есть ли на позициях, за которые она отвечает, хотя бы одна единица
    bool is_dead_end_form = true;
    //Перебираются все импликанты из массива IS
    for (int cur_i_ind = 0; cur_i_ind < IS.size; cur_i_ind++) {
        bool isINecessary = false;
        //Для каждой импликанты перебираются все конституенты, и если они покрываются выбранной импликантой
        //и соответствующие им позиции массива CS равны 1, вхождение строки в тупиковую форму обязательно
        for (int cur_const_ind = 0; cur_const_ind < quine.nCols; cur_const_ind++) {
            if (quine.values[IS.data[cur_i_ind]-1][cur_const_ind] && CS[cur_const_ind] == 1) {
                isINecessary = true;
                break;
            }
        }
        //Если нашлась хотя бы одна необязательная строка, то набор импликант IS нельзя назвать тупиковой формой
        if (!isINecessary) {
            is_dead_end_form = false;
            break;
        }
    }
    return is_dead_end_form;
}

//Возвращает подмножество множества set, заданное двоичным вектором vector
ordered_array_set createSubsetByBinaryVector(ordered_array_set set, int vector) {
    assert (1<<set.size > vector);
    ordered_array_set result = ordered_array_set_create(set.capacity);
    for (int i = 0; i < set.capacity; i++) {
        if (vector >> i & 1) {
            ordered_array_set_insert(&result, set.data[i]);
        }
    }
    ordered_array_set_shrinkToFit(&result);
    return result;
}

//Выводит на экран все номера импликант, объединение которых даст тупиковую форму Кантора
//Рекурсивная функция, опирающаяся на каждой итерации на текущий двоичный вектор, задающий подмножество, номер формируемого разряда,
//Множество номеров импликант I матрицу Квайна quine
void generateAllDeadEndForms_(int cur_vector, int cur_digit, ordered_array_set I, matrix quine) {
    for (int i = 0; i <= 1; i++) {
        int plus_cur_vector = (cur_vector << 1) + i;
        //Если полученный вектор достиг нужной длины, генерируется подмножество IS, на его основе создается функционал CS
        //Если функционал указывает на то, что IS - решение, то IS выводится на экран
        if (cur_digit == I.size) {
            ordered_array_set cur_IS = createSubsetByBinaryVector(I, plus_cur_vector);
            int cur_CS[quine.nCols];
            getCS(cur_CS, cur_IS, quine);
            if (isISASolution(cur_CS, cur_IS, quine)) {
                ordered_array_set_print(cur_IS);
            }
        } else {
            generateAllDeadEndForms_(plus_cur_vector, cur_digit+1, I, quine);
        }
    }
}

//Выводит на экран все номера импликант, объединение которых даст тупиковую форму Кантора
//Обертка функции generateAllDeadEndForms_, начинающая работу с пустым стартовым вектором cur_vector, номером обрабатываемого разряда 1
//и множеством импликант I, сгенерированным на основе переданной матрицы Квайна
void generateAllDeadEndForms(matrix quine) {
    if (quine.nCols == 0 || quine.nRows == 0) {
        printf("It's not a quine matrix.");
    } else {
        ordered_array_set I = ordered_array_set_create(quine.nRows);
        for (int i = 1; i <= quine.nRows; i++) {
            ordered_array_set_insert(&I, i);
        }
        generateAllDeadEndForms_(0, 1, I, quine);
    }
}

int main () {
    matrix quine_arbitrary = createMatrixFromArray(
            (int[]) {
                    1, 0, 1, 1, 1,
                    0, 0, 0, 1, 1,
                    1, 1, 1, 1, 0
            }, 3, 5
    );
    matrix quine_from_manual = createMatrixFromArray(
            (int[]) {
                    1, 0, 0, 1, 0, 0, 0, 0,
                    1, 0, 0, 0, 0, 1, 0, 0,
                    0, 0, 1, 1, 0, 0, 0, 0,
                    0, 0, 0, 0,1, 1, 0, 0,
                    0, 0, 0, 0, 1, 0, 0, 1,
                    0, 1, 1, 0, 0, 0, 1, 1

            }, 6, 8
    );

    matrix quine_from_lab_1_2 = createMatrixFromArray(
            (int[]) {
                    1, 1, 0, 0, 0,
                    0, 0, 1, 1, 0,
                    0, 1, 0, 0, 1,
                    0, 0, 0, 1, 1

            }, 4, 5
    );

    matrix quine_arbitrary_one_solution = createMatrixFromArray(
            (int[]) {
                    1, 1, 0, 1, 0, 0,
                    0, 0, 1, 0, 0, 1,
                    0, 1, 1, 0, 1, 0
            }, 3, 6
    );

    printf("Solutions of arbitrary quine matrix:\n");
    generateAllDeadEndForms(quine_arbitrary);
    printf("\nSolutions of quine matrix from manual:\n");
    generateAllDeadEndForms(quine_from_manual);
    printf("\nSolutions of quine matrix from lab 2.1, variant 9:\n");
    generateAllDeadEndForms(quine_from_lab_1_2);
    printf("\nSolutions of arbitrary quine matrix with one solution:\n");
    generateAllDeadEndForms(quine_arbitrary_one_solution);
}