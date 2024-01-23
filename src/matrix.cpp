#include "matrix.hpp"

algebra::matrix::matrix(
    std::vector<double>::size_type cols,
    std::vector<double>::size_type rows,
    double initial_value
)
    : m_rows(rows), m_cols(cols) {
    m_data = std::vector<double>(cols * rows, initial_value);
}

algebra::matrix::matrix(
    std::vector<double>::size_type rows,
    std::vector<double>::size_type cols,
    std::vector<double> &&data
)
    : m_rows(rows), m_cols(cols) {
    if (data.size() != rows * cols) {
        throw std::invalid_argument("Incorrect matrix initial data size!\n");
    }
    std::swap(m_data, data);
}

const double &algebra::matrix::operator[](
    std::vector<double>::size_type row_index,
    std::vector<double>::size_type col_index
) const {
    if (row_index >= m_rows || col_index >= m_cols) {
        throw std::out_of_range("Indeces points out of matrix!\n");
    }
    return m_data[row_index * m_cols + col_index];
}

double &algebra::matrix::operator[](
    std::vector<double>::size_type row_index,
    std::vector<double>::size_type col_index
) {
    if (row_index >= m_rows || col_index >= m_cols) {
        throw std::out_of_range("Indeces points out of matrix!\n");
    }
    return m_data[row_index * m_cols + col_index];
}

algebra::vector algebra::matrix::operator*(const algebra::vector &right) const {
    if (m_rows != right.size() || m_cols != right.size()) {
        throw std::invalid_argument("Invalid dimensions in matrix-vector "
                                    "product!\n");
    }
    algebra::vector result(right.size());
#pragma omp parallel for reduction(+ : result[row])
    for (auto row = 0; row < m_rows; row++) {
#pragma omp parallel for
        for (auto col = 0; col < m_cols; col++) {
            result[row] += (*this)[row, col] * right[col];
        }
    }
    return result;
}

algebra::matrix algebra::matrix::operator*(const matrix &right) const {
    if (this->m_cols != right.m_rows) {
        throw std::invalid_argument("Invalid dimensions in matrix-matrix "
                                    "product!\n");
    }
    algebra::matrix result(m_rows, right.m_cols);
    for (auto i = 0; i < this->m_rows; i++) {
        for (auto j = 0; j < right.m_cols; j++) {
            for (auto k = 0; k < right.m_rows; k++) {
                result[i, j] += (*this)[i, k] * right[k, j];
            }
        }
    }
    return result;
}

const double algebra::matrix::determinant() const
{
    if(m_rows != m_cols)
    {
        throw std::invalid_argument("Can't calculate determinant for nonsquare matrix!\n");
    }
    if (m_rows == 2)
    {
        return (*this)[0, 0] * (*this)[1, 1] - (*this)[0, 1] * (*this)[1, 0];
    }
    else
    {
        //TODO: Заглушка. Дописать рекуррентную формулу
        return 0;
    }
}

void algebra::matrix::normalize() {
    std::vector<double> vector_norms(m_cols, 0.0);
    double norm = 0.0;
    for (auto col = 0; col < m_cols; col++) {
        for (auto row = 0; row < m_rows; row++) {
            vector_norms[col] += pow((*this)[row, col], 2);
        }
    }
    std::transform(
        begin(vector_norms),
        end(vector_norms),
        begin(vector_norms),
        [&norm](double &value) {
            double vec_norm = sqrt(value);
            norm += vec_norm;
            return vec_norm;
        }
    );
    std::transform(
        begin(m_data),
        end(m_data),
        begin(m_data),
        [&norm](double &value) { return value / norm; }
    );
}

const std::vector<double>::size_type
algebra::matrix::size_rows() const noexcept {
    return m_rows;
}
const std::vector<double>::size_type
algebra::matrix::size_cols() const noexcept {
    return m_cols;
}
