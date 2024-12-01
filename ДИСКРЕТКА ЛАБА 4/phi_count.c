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

    //Вычисляется значение множества : на место X в функцию equation подставляется пустое множество
    ordered_array_set phi_empty = equation(ordered_array_set_create(1), A, B, C, universum);

    //Вычисляется значение множества : на место X в функцию equation подставляется универсум
    ordered_array_set phi_universum = equation(universum, A, B, C, universum);

    //Вычисляется значение множества : над множеством производится операция дополнения до универсума
    ordered_array_set complement_phi_universum = complement(phi_universum, universum);

    //Полученные множества выводятся на экран
    ordered_array_set_print(phi_empty);
    ordered_array_set_print(phi_universum);
    ordered_array_set_print(complement_phi_universum);

    return 0;
}