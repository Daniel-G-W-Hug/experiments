

double factorial(size_t k) {

    double result = 1.0;

    if (k > 1) {
        for (size_t i = 2; i <= k; ++i) result *= i;
    }

    return result;
}