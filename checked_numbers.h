//
// Created by appolinariya on 17.10.16.
//

#ifndef CHECKED_NUMBERS_CHECKED_NUMBERS_H
#define CHECKED_NUMBERS_CHECKED_NUMBERS_H

#include <assert.h>
#include <limits>

struct tag_s {
};

struct tag_u {
};

template <bool T>
struct traits {
    typedef tag_s tag;
};

template <>
struct traits <false> {
    typedef tag_u tag;
};


template <typename T>
T check_add(T left, T right, tag_s) {
    assert((left >= 0 && (right <= 0 || left <= std::numeric_limits<T>::max() - right)) ||
                   (left < 0 && (right >= 0 || left >= std::numeric_limits<T>::min() - right)));
    return left + right;
}

template <typename T>
T check_add(T left, T right, tag_u) {
    assert(right >= 0 && left <= std::numeric_limits<T>::max() - right);
    return left + right;
}

template <typename T>
T check_sub(T left, T right, tag_s) {
    assert((left >= 0 && (right >= 0 || left <= std::numeric_limits<T>::max() + right)) ||
                   (right < 0 || left >= std::numeric_limits<T>::min() + right));
    return left - right;
}

template <typename T>
T check_sub(T left, T right, tag_u) {
    assert(right >= 0 && left >= right);
    return left - right;
}

template <typename T>
T check_mul(T left, T right, tag_s) {
    assert((left == 0 || right == 0) ||
                   (left < 0 && ((right > 0 && left >= std::numeric_limits<T>::min() / right) ||
                           (left >= std::numeric_limits<T>::max() / right))) ||
                   (left > 0 && ((right > 0 && left <= std::numeric_limits<T>::max() / right) ||
                           (right >= std::numeric_limits<T>::min() / left))));
    return left * right;
}

template <typename T>
T check_mul(T left, T right, tag_u) {
    assert(right == 0 || left <= std::numeric_limits<T>::max() / right);
    return left * right;
}

template <typename T>
T check_div(T left, T right, tag_s) {
    assert(right != 0 && ((left <= 0 && ((right > 0 && (right > 1 || left >= std::numeric_limits<T>::min() * right))
                                         || (right < -1 || left >= std::numeric_limits<T>::max() * right)))
                          || ((right > 0 && (right > 1 || left <= std::numeric_limits<T>::max() * right))
                              || (right < -1 || left <= std::numeric_limits<T>::min() * right))));
    return left / right;
}

template <typename T>
T check_div(T left, T right, tag_u) {
    assert(right >= 0 && (right > 1 || left <= std::numeric_limits<T>::max() * right));
    return left / right;
}


template <typename T>
T check_unary(T right, tag_s) {
    assert(right != std::numeric_limits<T>::min());
    return  -right;
}

template <typename T>
T check_unary(T right, tag_u) {
    assert(right == 0);
    return -right;
}


template <typename T>
struct checked {
    checked() : value() {
    }

    checked(T v) : value(v) {
    }

    checked(checked<T>& other) : value(other.value) {
    }

    checked operator+=(checked& other) {
        value = check_add(value, other.value, typename traits<std::numeric_limits<T>::is_signed>::tag());
        return *this;
    }

    checked operator-=(checked& other) {
        value = check_sub(value, other.value, typename traits<std::numeric_limits<T>::is_signed>::tag());
        return *this;
    }

    checked operator*=(checked& other) {
        value = check_mul(value, other.value, typename traits<std::numeric_limits<T>::is_signed>::tag());
        return *this;
    }

    checked operator/=(checked& other) {
        value = check_div(value, other.value, typename traits<std::numeric_limits<T>::is_signed>::tag());
        return *this;
    }
    checked operator-() {
        value = check_unary(value, typename traits<std::numeric_limits<T>::is_signed>::tag());
        return *this;
    }

    checked operator+(checked& other) {
        checked *tmp = new checked(check_add(value,other.value, typename traits<std::numeric_limits<T>::is_signed>::tag()));
        return *tmp;
    }

    checked operator-(checked& other) {
        checked *tmp = new checked(check_sub(value,other.value, typename traits<std::numeric_limits<T>::is_signed>::tag()));
        return *tmp;
    }

    checked operator*(checked& other) {
        checked *tmp = new checked(check_mul(value,other.value, typename traits<std::numeric_limits<T>::is_signed>::tag()));
        return *tmp;
    }

    checked operator/(checked& other) {
        checked *tmp = new checked(check_div(value,other.value, typename traits<std::numeric_limits<T>::is_signed>::tag()));
        return *tmp;
    }
    void write() {
        std::cout << value;
    }
private:
    T value;
};

#endif //CHECKED_NUMBERS_CHECKED_NUMBERS_H
