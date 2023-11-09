#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

double calculateMean(const std::vector<double> &numbers)
{
    return std::accumulate(numbers.begin(), numbers.end(), 0.0) / numbers.size();
}

double calculateMedian(std::vector<double> numbers)
{
    size_t size = numbers.size();
    if (size == 0)
    {
        return 0; // Undefined, really.
    }
    sort(numbers.begin(), numbers.end());
    if (size % 2 == 0)
    {
        return (numbers[size / 2 - 1] + numbers[size / 2]) / 2;
    }
    else
    {
        return numbers[size / 2];
    }
}

double calculateStandardDeviation(const std::vector<double> &numbers, double mean)
{
    double sum = 0.0;
    for (auto num : numbers)
    {
        sum += (num - mean) * (num - mean);
    }
    return std::sqrt(sum / numbers.size());
}

int main()
{
    std::vector<double> numbers;
    double inputNum;
    char choice;

    std::cout << "Statistics Calculator" << std::endl;
    std::cout << "Enter numbers (type '0' when you finish): " << std::endl;

    do
    {
        std::cin >> inputNum;
        if (inputNum != 0)
        {
            numbers.push_back(inputNum);
        }
    } while (inputNum != 0);

    if (numbers.empty())
    {
        std::cout << "No numbers were entered." << std::endl;
        return 0;
    }

    double mean = calculateMean(numbers);
    double median = calculateMedian(numbers);
    double stdDev = calculateStandardDeviation(numbers, mean);

    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Median: " << median << std::endl;
    std::cout << "Standard Deviation: " << stdDev << std::endl;

    return 0;
}
