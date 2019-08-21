//---------------------------------------------------------------------------

#include "model.h"

//---------------------------------------------------------------------------

void TModel::addResult(const vec& X, long double t )
{
    // Проверим, выходит ли счётчик строк в матрице результатов за пределы последней строки
    // Если да, то увеличим количество строк на 1
    if (N == Result.n_rows)
        Result.resize(N + 1, getOrder() + 1);
    // Поместим рез-ты в последнюю строку матрицы Result
    // Момент времени помещается в 0-ой столбец, вектор состояния - в остальные столбцы
    Result(N, 0) = t;
    for (uword i = X.n_elem; i > 0; i--)
        Result(N, i) = X[i-1];
    // Увеличим N
    N++;
}

void TModel::clearResult()
{
    // Очистим матрицу результатов и сбросим счётчик строк
    Result.set_size(0, 0);
    N = 0;
}

void TModel::prepareResult()
{
    // Зададим матрице рез-тов такой размер, чтобы поместились все значения веткора состояния
    // и соответсвующих им моментов времени на интервале [t0; t1] с шагом SamplingIncrement
    Result.resize((int)((t1 - t0)/SamplingIncrement) + 1, getOrder() + 1);
    // Сбросим счётчик строк в матрице результатов
    N = 0;
}

void TModel::ActionAfterStep(const vec &X, long double t){

}