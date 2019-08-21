
#ifndef modelH
#define modelH

#include <armadillo>

using namespace arma;

// Базовый класс модели для интеграторв

class TModel
{
    protected:
        // Начальные условия
        vec X0;
        // Требуемый от интегратора интервал выдачи результатов
        long double SamplingIncrement;
        // Начало и окончание времени интегрирования
        long double t0, t1;
        // Хранилище результатов
        mat Result;
        // Счётчик строк в матрице результатов
        uword N;

    public:
        // Общий конструктор моделей - инициализация
        TModel()
            : SamplingIncrement( 1e-1 )
            , t0( 0 )
            , t1( 20 )
            , N( 0 )
        {}
        // Абстрактная перегружаемая функция правых частей ДУ(Х - вектор состояния, t - независимый аргумент)
        virtual void getRight( const vec& X, long  double t, vec& Y ) = 0;
        // Получение начальных условий
        inline vec getInitialConditions() const { return X0; }
        // Порядок системы - по размерности вектора начальных условий
        inline uword getOrder() const { return X0.n_elem; }

        // Интервал выдачи результатов
        inline long double getSamplingIncrement() const { return SamplingIncrement; }

        // Управление временным интервалом интегрирования
        inline long double getT0() const { return t0; }
        inline long double getT1() const { return t1; }

        // Получение матрицы результатов
        inline mat getResult() const { return Result; }
        // Запись результатов (в этом методе в наследнике допустимо организовать запись в файл
        // вместо или вместе с наполнением матрицы результатов
        virtual void addResult( const vec& X, long double t );
        // Очистка матрицы результатов (или файла с результатами)
        virtual void clearResult();
        // Подготовка матрицы результатов для более эффективного выделения памяти
        virtual void prepareResult();
        virtual ~TModel(){}
        // выполнения какого-то действия после выполненного шага
        virtual void ActionAfterStep(const vec& X, long double t);
};


#endif
