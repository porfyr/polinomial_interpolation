#include <functional>
#include <QtMath>

using func_delegate = std::function<double(double)>;

class My_algorithms {
public:
    static func_delegate final_func_builder(int size, double * x_values, double * y_values) {
        func_delegate * basic_polinomials = new func_delegate[size];
        for (int i = 0; i < size; ++i)
            basic_polinomials[i] = create_basic_polinomial(size, x_values, i);
        return [size, x_values, y_values, basic_polinomials](double x) -> double {
            double result = 0.0;
            for (int i = 0; i < size; ++i)
                result += (double)y_values[i] * basic_polinomials[i](x);
            return result;
        };
    }

    static func_delegate custom_function_builder() {
        return [](double x) -> double {
            return 1.0 / (1.0 + 25.0 * x*x);
        };
    }
//    static func_delegate custom_function_builder() {
//        return [](double x) -> double {
//            return qLn(x + 2.0);
//        };
//    }
private:
    static func_delegate create_basic_polinomial(int size, double * x_values, int i) {
        return [size, x_values, i](double x) -> double {
            double result  = 1.0,
                divider = 1.0;
            for (int j = 0; j < size; ++j) {
                if (j != i) {
                    result *= (x - x_values[j]);
                    divider *= (x_values[i] - x_values[j]);
                }
            }

            return result/divider;
        };
    }
};

/*
 * Невдалі спроби декларацій функціонального типу
*/
// struct build_basic_binomial {
//     int size, i;
//     int * x_values;
//
//     build_basic_binomial(int size, int * x_values, int i) :
// }
// typedef double (*Basic_binomial)(int);

//void get_int_args(int argc, char ** argv, int &a, int &b) {
//    bool ok_a, ok_b;
//    if (argc == 3) {
//        a = (int)argv[1][0] - 48;
//        b = (int)argv[2][0] - 48;
//    } else if (argc == 2) {
//        a = (int)argv[1][0] - 48;
//        b = 0;
//    } else {
//        std::cout << "Не ввів аргументи, прописую в a і b дефолтні 0\n";
//        a = 0, b = 0;
//    }
//}

/*
 * Сам алгоритм (дві наступні функції)
*/


//Polinomial_funcs_delegate create_basic_polinomial(int size, int * x_values, int i) {
//    return [size, x_values, i](double x) -> double {
//        double result  = 1.0,
//            divider = 1.0;
//        for (int j = 0; j < size; ++j) {
//            if (j != i) {
//                result *= (x - x_values[j]);
//                divider *= (x_values[i] - x_values[j]);
//            }
//        }

//        return result/divider;
//    };
//}

//auto final_func_builder(int size, int * x_values, int * y_values) {
//    Polinomial_funcs_delegate * basic_polinomials = new Polinomial_funcs_delegate[size];
//    for (int i = 0; i < size; ++i)
//        basic_polinomials[i] = create_basic_polinomial(size, x_values, i);
//    return [size, x_values, y_values, basic_polinomials](double x) -> double {
//        double result = 0.0;
//        for (int i = 0; i < size; ++i)
//            result += (double)y_values[i] * basic_polinomials[i](x);
//        return result;
//    };
//}

//int main(int argc, char ** argv)
//{
//    int size = 4;
//    int x_values[] = {0, 2, 3, 5},
//        y_values[] = {0, 1, 3, 2};

//    int a, b;
//    get_int_args(argc, argv, a, b);

//    Polinomial_funcs_delegate L = final_func_builder(size, x_values, y_values);

//    for (int i = 0; i < size; ++i)
//        std::cout << L(x_values[i]) << "\n";

//    return 0;
//}
