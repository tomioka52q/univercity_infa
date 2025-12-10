#include "pch.h"
#include "CppUnitTest.h"
#include "..\\ConsoleApplicationOtladka\\Calculator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(CalculatorTests)
    {
    public:

        // 1. Корректный случай для R
        TEST_METHOD(TestCalculateR_Valid)
        {
            double x = 4.0;
            double y = 9.0;

            double result = calculate_R(x, y);

            // ожидаемое значение
            double expected = std::sqrt(x * y) / std::fabs(1.0 / std::cos(x));

            Assert::AreEqual(expected, result, 1e-10);
        }

        // 2. Корректный случай для S
        TEST_METHOD(TestCalculateS_Valid)
        {
            double x = 4.0;

            double result = calculate_S(x);
            double expected = (PI / 2.0) * (std::log(x) / std::log(5.0));

            Assert::AreEqual(expected, result, 1e-10);
        }

        // 3. Проверка C = max(R, S)
        TEST_METHOD(TestCalculateC)
        {
            double R = 10.0;
            double S = 5.0;
            double result = calculate_C(R, S);
            Assert::AreEqual(R, result);

            R = 3.0;
            S = 7.0;
            result = calculate_C(R, S);
            Assert::AreEqual(S, result);
        }

        // 4. Некорректный x для R (x <= 0)
        TEST_METHOD(TestCalculateR_NegativeX_Throws)
        {
            auto func = []()
                {
                    calculate_R(-1.0, 1.0);
                };

            Assert::ExpectException<std::invalid_argument>(func);
        }

        // 5. Некорректное произведение x * y < 0
        TEST_METHOD(TestCalculateR_NegativeProduct_Throws)
        {
            auto func = []()
                {
                    calculate_R(1.0, -2.0);
                };

            Assert::ExpectException<std::invalid_argument>(func);
        }

        // 6. cos(x) около нуля (деление на ноль)
        TEST_METHOD(TestCalculateR_CosZero_Throws)
        {
            double x = PI / 2.0;   // cos(x) ≈ 0

            auto func = [x]()
                {
                    calculate_R(x, 1.0);
                };

            Assert::ExpectException<std::invalid_argument>(func);
        }

        // 7. Некорректный x для S (x <= 0)
        TEST_METHOD(TestCalculateS_NegativeX_Throws)
        {
            auto func = []()
                {
                    calculate_S(-3.0);
                };

            Assert::ExpectException<std::invalid_argument>(func);
        }
    };
}
