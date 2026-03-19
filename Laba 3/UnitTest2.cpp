#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication1/ConsoleApplication1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SortingTests
{
    TEST_CLASS(SortTests)
    {
    public:

        // 1. Тест сортировки расческой
        TEST_METHOD(TestCombSort)
        {
            int arr[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
            int expected[] = { 2, 24, 45, 66, 75, 90, 170, 802 };
            int n = 8;

            combSort(arr, n);

            for (int i = 0; i < n; i++) {
                Assert::AreEqual(expected[i], arr[i], L"Элементы не совпадают");
            }
        }

        // 2. Тест быстрой сортировки
        TEST_METHOD(TestQuickSort)
        {
            int arr[] = { 5, 1, 9, 3, 7 };
            int n = 5;

            quickSort(arr, 0, n - 1);

            bool isSorted = std::is_sorted(arr, arr + n);
            Assert::IsTrue(isSorted, L"Массив после QuickSort не отсортирован");
        }

        // 3. Тест поразрядной сортировки
        TEST_METHOD(TestRadixSort)
        {
            std::vector<int> data = { 10, 5, 2, 8 };
            std::vector<int> expected = { 2, 5, 8, 10 };

            radixSort(data);

            Assert::AreEqual(expected.size(), data.size(), L"Размеры векторов разные");

            for (size_t i = 0; i < data.size(); i++) {
                Assert::AreEqual(expected[i], data[i]);
            }
        }
    };
}
