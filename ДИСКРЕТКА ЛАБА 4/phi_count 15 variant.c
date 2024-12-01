#include "ordered_array_set\ordered_array_set.c"

//Возвращает множество - левую часть данного в варианте 15 уравнения при заданных множествах X, A, B, C и универсуме universum
ordered_array_set left_part (ordered_array_set X, ordered_array_set A, ordered_array_set B, ordered_array_set C, ordered_array_set universum) {
    ordered_array_set exp1 = intersection(A, X);
    ordered_array_set exp2 = join(exp1, B);
    ordered_array_set exp3 = difference(C, X);
    ordered_array_set result = intersection(exp2, exp3);
    return result;
}

//Возвращает множество - правую часть данного в варианте 15 уравнения при заданных множествах X, A, B, C и универсуме universum
ordered_array_set right_part (ordered_array_set X, ordered_array_set A, ordered_array_set B, ordered_array_set C, ordered_array_set universum) {
    ordered_array_set exp1 = complement(X, universum);
    ordered_array_set exp2 = difference(A, X);
    ordered_array_set exp3 = intersection(exp2, C);
    ordered_array_set result = join(exp1, exp3);
    return result;
}

//Возвращает множество - уравнение варианта 15 с пустой правой частью при заданных множествах X, A, B, C и универсуме universum
ordered_array_set equation (ordered_array_set X, ordered_array_set A, ordered_array_set B, ordered_array_set C, ordered_array_set universum) {
    return symmetricDifference(left_part(X, A, B, C, universum), right_part(X, A, B, C, universum));
}


int main() {
    //Задаются массивы с элементами множеств A, B, C, а также элементами универсума
    int array_a[5] = {1, 2, 5, 8, 9};
    int array_b[6] = {1, 2, 6, 7, 9, 10};
    int array_c[5] = {2, 4, 6, 9, 10};
    int array_u[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    //Из них создаются непосредственно множества
    ordered_array_set A = ordered_array_set_create_from_array(array_a, 5);
    ordered_array_set B = ordered_array_set_create_from_array(array_b, 6);
    ordered_array_set C = ordered_array_set_create_from_array(array_c, 5);
    ordered_array_set universum = ordered_array_set_create_from_array(array_u, 10);

    //Вычисляется значение множества phi(empty): на место X в функцию equation подставляется пустое множество
    ordered_array_set phi_empty = equation(ordered_array_set_create(1), A, B, C, universum);

    //Вычисляется значение множества phi(U): на место X в функцию equation подставляется универсум
    //Потом над значением функции equation производится операция дополнения до универсума
    ordered_array_set complement_phi_universum = complement(equation(universum, A, B, C, universum), universum);

    //Полученные множества выводятся на экран
    ordered_array_set_print(phi_empty);
    ordered_array_set_print(complement_phi_universum);

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