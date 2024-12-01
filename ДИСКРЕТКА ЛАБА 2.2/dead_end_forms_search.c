#include "ordered_array_set\ordered_array_set.c"
#include "C:\Users\sovac\Desktop\ОП, преимущественно лабы\second_semester\libs\data_structures\matrix\matrix.c"

//Возвращает упорядоченное множество, содержащее номера конституент, покрываемых некоторой импликантой i
ordered_array_set getCi(int i, matrix quine) {
    ordered_array_set Ci = ordered_array_set_create(quine.nCols);
    //Проходом по строке матрицы, соотвествующей импликанте с номером i, формируется множество номеров конституент, покрываемых ей.
    //Стоит отметить, что в множествах I и C нумерация импликант/конституент идет с единицы, в то время как столбцы/строки матрицы нумеруются с нуля
    //Поэтому, добавляя индекс в множество, необходимо увеличить его на 1, а используя элемент множества как индекс, уменьшить на 1
    for (int j = 0; j < quine.nCols; j++) {
        if (quine.values[i-1][j]) {
            ordered_array_set_insert(&Ci, j+1);
        }
    }
    return Ci;
}

//Возвращает функционал - массив CS, показывающий, сколько раз определенный столбец покрывается подмножеством множества конституент IS
void getCS(int *CS, ordered_array_set IS, matrix quine) {
    //Инициализирует значения элементов массива CS нулями; известно, что этих элементов будет столько же, сколько конституент - и сколько столбцов в матрице quine
    for (int i = 0; i < quine.nCols; i++) {
        CS[i] = 0;
    }
    //Для каждой импликанты из массива IS формируется множество Ci
    for (int i = 0; i < IS.size; i++) {
        ordered_array_set cur_Ci = getCi(IS.data[i], quine);
        //Перебираются элементы множества Ci, и соответсвующие им позиции массива CS увеличиваются на 1
        for (int j = 0; j < cur_Ci.size; j++) {
            CS[cur_Ci.data[j] - 1] += 1;
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
    //Для каждой импликанты из массива IS формируется множество Ci
    for (int i = 0; i < IS.size; i++) {
        bool isINecessary = false;
        ordered_array_set cur_Ci = getCi(IS.data[i], quine);
        //Перебираются элементы множества Ci, и если среди соответствующих им элементов массива CS есть хотя бы одна единица, импликанта i считается "необходимой"
        //Не забываем про особенности сдвига на единицу
        for (int j = 0; j < cur_Ci.size; j++) {
            if (CS[cur_Ci.data[j] - 1] == 1) {
                isINecessary = true;
                break;
            }
        }
        //Если нашлась хотя бы одна лишняя строка, то набор импликант IS нельзя назвать тупиковой формой
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
//Множество номеров импликант I матрицу Кайна quine
void generateAllDeadEndForms_(int cur_vector, int cur_digit, ordered_array_set I, matrix quine) {
    for (int i = 0; i <= 1; i++) {
        int plus_cur_vector = (cur_vector << 1) + i;
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
    matrix quine_matrix = createMatrixFromArray(
            (int[]) {
                    1, 0, 0, 1, 0, 0, 0, 0,
                    1, 0, 0, 0, 0, 1, 0, 0,
                    0, 0, 1, 1, 0, 0, 0, 0,
                    0, 0, 0, 0,1, 1, 0, 0,
                    0, 0, 0, 0, 1, 0, 0, 1,
                    0, 1, 1, 0, 0, 0, 1, 1

            }, 6, 8
    );

    matrix quine_matrix2 = createMatrixFromArray(
            (int[]) {
                    1, 0, 1, 1, 1,
                    0, 0, 0, 1, 1,
                    1, 1, 1, 1, 0
            }, 3, 5
    );

    generateAllDeadEndForms(quine_matrix);
}