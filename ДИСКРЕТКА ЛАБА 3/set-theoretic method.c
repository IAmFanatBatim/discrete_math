
#include "ordered_array_set\ordered_array_set.c"

ordered_array_set first_expression(ordered_array_set A, ordered_array_set B, ordered_array_set C, ordered_array_set universum) {
    ordered_array_set exp1 = intersection(A, B);
    ordered_array_set exp2 = intersection(complement(A, universum), C);
    ordered_array_set exp3 = intersection(B, C);
    ordered_array_set exp4 = join(exp1, exp2);
    ordered_array_set result = join(exp4, exp3);
    return result;
}

ordered_array_set second_expression(ordered_array_set A, ordered_array_set B, ordered_array_set C, ordered_array_set universum) {
    ordered_array_set exp1 = intersection(A, B);
    ordered_array_set exp2 = intersection(complement(exp1, universum), C);
    ordered_array_set exp3 = intersection(A, complement(C, universum));
    ordered_array_set result = join(exp2, exp3);
    return result;
}

ordered_array_set third_expression(ordered_array_set A, ordered_array_set B, ordered_array_set C, ordered_array_set universum) {
    ordered_array_set exp1 = join(A, B);
    ordered_array_set exp2 = join(exp1, complement(C, universum));
    ordered_array_set exp3 = intersection(A, complement(C, universum));
    ordered_array_set exp4 = intersection(exp3, exp2);
    ordered_array_set exp5 = join(complement(A, universum), C);
    ordered_array_set exp6 = intersection(complement(A, universum), complement(B, universum));
    ordered_array_set exp7 = intersection(exp6, C);
    ordered_array_set exp8 = intersection(exp5, exp7);
    ordered_array_set result = join(exp4, exp8);
    return result;
}

ordered_array_set fourth_expression(ordered_array_set A, ordered_array_set B, ordered_array_set C, ordered_array_set universum) {
    ordered_array_set exp1 = join(A, B);
    ordered_array_set exp2 = difference(complement(exp1, universum), complement(C, universum));
    ordered_array_set exp3 = difference(complement(C, universum), complement(A, universum));
    ordered_array_set result = join(exp2, exp3);
    return result;
}

ordered_array_set fifth_expression(ordered_array_set A, ordered_array_set B, ordered_array_set C, ordered_array_set universum) {
    ordered_array_set exp1 = difference(A, B);
    ordered_array_set exp2 = difference(A, exp1);
    ordered_array_set exp3 = intersection(C, A);
    ordered_array_set exp4 = symmetricDifference(exp2, exp3);
    ordered_array_set result =  symmetricDifference(exp4, C);
    return result;
}

int main() {
    //задаем множество-универсум и множества A, B, C в соответствии с ранее составленной таблицей
    ordered_array_set universum = ordered_array_set_create_from_array((int[]){1, 2, 3, 4, 5, 6, 7, 8}, 8);
    ordered_array_set a = ordered_array_set_create_from_array((int[]){5, 6, 7, 8 }, 4);
    ordered_array_set b = ordered_array_set_create_from_array((int[]){3, 4, 7, 8}, 4);
    ordered_array_set c = ordered_array_set_create_from_array((int[]){2, 4, 6, 8}, 4);

    //задаем массив функций, вычисляющих данные ТМВ при заданных значениях A, B, C
    ordered_array_set (*functions[5])(ordered_array_set, ordered_array_set, ordered_array_set, ordered_array_set) = {
            first_expression,
            second_expression,
            third_expression,
            fourth_expression,
            fifth_expression
    };

    //создаем массив множеств для хранения результатов вычисления данных ТМВ
    ordered_array_set results[5];

    //для каждого выражения находим значение и сохраняем его в массив results
    for (int i = 0; i < 5; i++) {
        results[i] = functions[i](a, b, c, universum);
    }

    //перебираем все возможные пары результатов, и если множества-результаты равны, выводим на экран сообщение о том, что тожественно равны соответствующие выражения
    for (int i = 0; i < 4; i++) {
        for (int j = i+1; j < 5; j++) {
            if (isEqual(results[i], results[j])) {
                printf("Expression %d and %d are identically equal\n", i+1, j+1);
            }
        }
    }
    return  0;
}
