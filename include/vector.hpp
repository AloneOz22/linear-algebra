#pragma once
#include <algorithm>
#include <functional>
#include <cmath>
#include <stdexcept>
#include <vector>

namespace algebra {
class vector {
private:
    static constexpr double eps = 1e-9;

    std::vector<double>::size_type m_size;
    std::vector<double> m_data;

public:
    vector(std::vector<double>::size_type size, double initial_value = 0.0);
    vector(std::vector<double> &&data);

    const double &operator[](std::vector<double>::size_type index) const;
    double &operator[](std::vector<double>::size_type index);

    vector operator+(const vector &right) const;
    vector operator+(const double &right) const;
    vector operator-(const vector &right) const;
    vector operator-(const double &right) const;
    double operator*(const vector &right) const;
    vector operator*(const double &right) const;
    vector operator/(const double &right) const;

    vector vector_product(const vector &right) const;
    const double norm() const noexcept;
    void normalize() noexcept;

    const std::vector<double>::size_type size() const noexcept;
};
}    // namespace algebra
