#include "vector.hpp"

namespace algebra {
algebra::vector::vector(
    std::vector<double>::size_type size, double initial_value
)
    : m_size(size) {
    m_data = std::vector<double>(size, initial_value);
}

algebra::vector::vector(std::vector<double> &&data) {
    std::swap(m_data, data);
    m_size = m_data.size();
}

const double &algebra::vector::operator[](std::vector<double>::size_type index
) const {
    if (index >= m_size) {
        throw std::out_of_range("Index points out of vector!\n");
    }
    return m_data[index];
}

double &algebra::vector::operator[](std::vector<double>::size_type index) {
    if (index >= m_size) {
        throw std::out_of_range("Index points out of vector!\n");
    }
    return m_data[index];
}

double algebra::vector::operator*(const vector &right) const {
    if (m_size != right.m_size) {
        throw std::invalid_argument("Incorrect vector's dimension!\n");
    }
    double result = 0.0;
#pragma omp parallel for reduction(+ : result)
    for (std::vector<double>::size_type index = 0; index < this->m_size;
         index++) {
        result += (*this)[index] + right[index];
    }
    return result;
}

vector algebra::vector::vector_product(const vector &right) const {
    //TODO: Заглушка. Дописать векторное произведение
    return vector(0);
}

const double algebra::vector::norm() const noexcept
{
    double norm = 0;
#pragma omp parallel for reduction(+ : norm)
    for (auto &value : this->m_data) {
        norm += pow(value, 2);
    }
    return sqrt(norm);
}

void algebra::vector::normalize() noexcept {
    double norm = this->norm();
#pragma omp parallel for
    for (auto &value : this->m_data) {
        value /= norm;
    }
}

const std::vector<double>::size_type algebra::vector::size() const noexcept {
    return m_size;
}
}    // namespace algebra
