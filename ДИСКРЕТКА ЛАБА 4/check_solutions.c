#include "ordered_array_set\ordered_array_set.c"

//Возвращает множество - левую часть данного в варианте 9 уравнения при заданных множествах X, A, B, C и универсуме universum
ordered_array_set left_part (ordered_array_set X, ordered_array_set A, ordered_array_set B, ordered_array_set C, ordered_array_set universum) {
    ordered_array_set exp1 = symmetricDifference(A, X);
    ordered_array_set exp2 = join(B, X);
    ordered_array_set exp3 = intersection(exp1, exp2);
    ordered_array_set result = difference(exp3, C);
    return result;
}

//Возвращает множество - правую часть данного в варианте 9 уравнения при заданных множествах X, A, B, C и универсуме universum
ordered_array_set right_part (ordered_array_set X, ordered_array_set A, ordered_array_set B, ordered_array_set C, ordered_array_set universum) {
    ordered_array_set exp1 = join(A, X);
    ordered_array_set exp2 = complement(exp1, universum);
    ordered_array_set exp3 = symmetricDifference(C, X);
    ordered_array_set result = join(exp2, exp3);
    return result;
}

//Возвращает множество - уравнение варианта 9 с пустой правой частью при заданных множествах X, A, B, C и универсуме universum
ordered_array_set equation (ordered_array_set X, ordered_array_set A, ordered_array_set B, ordered_array_set C, ordered_array_set universum) {
    return symmetricDifference(left_part(X, A, B, C, universum), right_part(X, A, B, C, universum));
}



int main() {
    //Задаются массивы с элементами множеств A, B, C, а также элементами универсума
    int array_a[5] = {1, 3, 5, 6, 8};
    int array_b[4] = {2, 4, 6, 9};
    int array_c[4] = {2, 6, 7, 10};
    int array_u[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    //Из них создаются непосредственно множества
    ordered_array_set A = ordered_array_set_create_from_array(array_a, 5);
    ordered_array_set B = ordered_array_set_create_from_array(array_b, 4);
    ordered_array_set C = ordered_array_set_create_from_array(array_c, 4);
    ordered_array_set universum = ordered_array_set_create_from_array(array_u, 10);

    //Задаем массив с множествами-решениями уравнения
    //Можно было бы создать отдельную переменную вместо массива, но такое решение делает программу более универсальной
    //Позволяя вставлять в массив решений больше множеств
    ordered_array_set solutions[1] = {
            ordered_array_set_create_from_array((int[6]) {2, 4, 6, 7, 9, 10}, 6)
    };
    int solutions_len = 1;

    //Создаем флаг, контролирующий, все ли решения являются истинными
    bool are_all_solutions_correct = true;

    //перебираем все решения в массиве
    for (int i = 0; i < solutions_len; i++) {
        //высчитываем значения левой и правой части уравнения
        ordered_array_set left_part_calculated = left_part(solutions[i], A, B, C, universum);
        ordered_array_set right_part_calculated = right_part(solutions[i], A, B, C, universum);
        //если они не равны, выводим сообщение об ошибочном решении на экран и устанавливаем в 0 флаг
        if (!ordered_array_set_isEqual(left_part_calculated, right_part_calculated)) {
            printf("This set isn't a solution of the equation: ");
            ordered_array_set_print(solutions[i]);
            are_all_solutions_correct = false;
        }
    }

    //Если флаг все еще истинен, выводим на экран сообщение о том, что все множества проверены и верны
    if (are_all_solutions_correct) {
        printf("All solutions are checked and correct");
    }

    //ordered_array_set_print(equation(phi_empty, A, B, C, universum));

    /*int array_a[8] = {1, 2, 3, 4, 9, 10, 11, 12};
    int array_b[8] = {1, 2, 5, 6, 9, 10, 13, 14};
    int array_c[8] = {1, 3, 5, 7, 9, 11, 13, 15};
    int array_x[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int array_u[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    ordered_array_set A = ordered_array_set_create_from_array(array_a, 8);
    ordered_array_set B = ordered_array_set_create_from_array(array_b, 8);
    ordered_array_set C = ordered_array_set_create_from_array(array_c, 8);
    ordered_array_set X = ordered_array_set_create_from_array(array_x, 8);
    ordered_array_set universum = ordered_array_set_create_from_array(array_u, 16);

    ordered_array_set_print(equation(X, A, B, C, universum));*/

    return 0;
}