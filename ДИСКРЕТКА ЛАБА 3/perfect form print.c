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

ordered_array_set pasha_one(ordered_array_set A, ordered_array_set B, ordered_array_set C, ordered_array_set universum) {
    ordered_array_set exp1 = join(A, B);
    ordered_array_set exp2 = join(complement(A, universum), complement(B, universum));
    ordered_array_set exp3 = intersection(exp2, complement(C, universum));
    ordered_array_set result =  intersection(exp1, exp3);
    return result;
}

ordered_array_set pasha_two(ordered_array_set A, ordered_array_set B, ordered_array_set C, ordered_array_set universum) {
    ordered_array_set exp1 = join(A, B);
    ordered_array_set exp2 = join(complement(A, universum), B);
    ordered_array_set exp3 = intersection(exp2, complement(B, universum));
    ordered_array_set exp4 = join(exp3, complement(C, universum));
    ordered_array_set result =  intersection(exp1, exp4);
    return result;
}

//Выводит конституенту из len множеств по заданному ее номеру - двоичному числу, где 0 - множества с дополнением, 1 - множества без дополнений
void printConstitution(int len, int number) {
    printf("(");
    for (int i = 0; i < len; i++) {
        if ((number >> (len-1-i) & 1) == 0) {
            printf("!");
        }
        printf("%c", 'A' + i);
        if (i != len-1) {
            printf(" ");
        }
    }
    printf(")");
}


int main() {
    //создаем массив функций, в котором по порядку идут данные в условии теоретико-множественные выражения
    ordered_array_set (*functions[5])(ordered_array_set, ordered_array_set, ordered_array_set, ordered_array_set) = {
            first_expression,
            second_expression,
            third_expression,
            fourth_expression,
            fifth_expression
    };

    ordered_array_set (*pasha_functions[2])(ordered_array_set, ordered_array_set, ordered_array_set, ordered_array_set) = {
            pasha_one,
            pasha_two
    };

    //создаем массив из двух элементов
    ordered_array_set nilAndOne[2];
    //первый элемент - пустое множество
    nilAndOne[0] = ordered_array_set_create_from_array((int[]) {}, 0);
    //второй элемент - множество с одним элементом, единицей
    //так как результат выражения, операнды в котором - только пустое множество и универсум, может быть только пустым множеством или универсумом, одного элемента в универсуме хватит
    nilAndOne[1] = ordered_array_set_create_from_array((int[]) {1}, 1);

    //перебираем все функции в массиве функций
    for (int i_exp = 0; i_exp < 2; i_exp++) {
        //для каждой функции перебираем все возможные номера конституент
        for (int cur_const_ind = 0; cur_const_ind < 8; cur_const_ind++) {
            //высчитываем значение этой функции, когда вместо первичных термов с дополнением в нее подставлено пустое множество, а вместо первичных термов без дополнения - универсум
            //есть ли у множества дополнение или нет - определяем по соответствующему разряду в номере конституенты, cur_const_ind
            ordered_array_set i_cur_const = (pasha_functions[i_exp])(nilAndOne[(cur_const_ind >> 2) & 1], nilAndOne[(cur_const_ind >> 1) & 1], nilAndOne[cur_const_ind & 1], nilAndOne[1]);
            //если значение функции - универсум, соотвествующая конституента войдет в совершенную НФК
            //выводим ее на экран, отделив от следующей табуляцией
            if (isEqual(i_cur_const, nilAndOne[1])) {
                printConstitution(3, cur_const_ind);
                printf("\t");
            }
        }
        //отделим совершенную НФК одной функции от совершенной НФК другой переносом строки
        printf("\n");
    }
    return  0;
}
