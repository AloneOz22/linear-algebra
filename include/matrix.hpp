#pragma once
#include <vector>

#include "vector.hpp"

namespace algebra {
class matrix {
private:
    std::vector<double>::size_type m_rows;
    std::vector<double>::size_type m_cols;

    std::vector<double> m_data;

public:
    matrix(
        std::vector<double>::size_type rows,
        std::vector<double>::size_type cols,
        double initial_value = 0.0
    );
    matrix(
        std::vector<double>::size_type rows,
        std::vector<double>::size_type cols,
        std::vector<double> &&data
    );

    const double &operator[](
        std::vector<double>::size_type row_index,
        std::vector<double>::size_type col_index
    ) const;
    double &operator[](
        std::vector<double>::size_type row_index,
        std::vector<double>::size_type col_index
    );

    algebra::vector operator*(const algebra::vector &right) const;
    matrix operator*(const matrix &right) const;

    const double determinant() const;
    void normalize();

    const std::vector<double>::size_type size_rows() const noexcept;
    const std::vector<double>::size_type size_cols() const noexcept;
};
}    // namespace algebra
