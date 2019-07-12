#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>

class FizzBuzz final {
    using chr = std::char_traits<char>;

  public:
    constexpr explicit FizzBuzz(std::uint_fast8_t i)
    : _i{ i }
    , _is_multiple{ [i, this]() constexpr {
        auto offset_ptr =  _s;
        auto is_multiple = false;

        if (i % 3 == 0) {
            is_multiple = true;
            offset_ptr[0] = 'F';
            offset_ptr[1] = 'i';
            offset_ptr[2] = 'z';
            offset_ptr[3] = 'z';
            offset_ptr[4] = '\0';
            offset_ptr += chr::length("Fizz");   
        }
        if (i % 5 == 0) {
            is_multiple = true;
            offset_ptr[0] = 'B';
            offset_ptr[1] = 'u';
            offset_ptr[2] = 'z';
            offset_ptr[3] = 'z';
            offset_ptr[4] = '\0';
        }

        return is_multiple;
    }() } {}

    [[nodiscard]]
    constexpr auto is_fizz() const -> bool {
        return _is_multiple &&
               'F' == _s[0] &&
               '\0' == _s[chr::length("Fizz")];
    }

    [[nodiscard]]
    constexpr auto is_buzz() const -> bool {
        return _is_multiple && 'B' == _s[0];
    }

    [[nodiscard]]
    constexpr auto is_fizzbuzz() const -> bool {
        return _is_multiple && 'B' == _s[chr::length("Fizz")];
    }

    [[nodiscard]]
    constexpr auto is_fizz_or_buzz() const -> bool {
        return _is_multiple && ('F' == _s[0] || 'B' == _s[0]);
    }

    friend auto operator<<(std::ostream &os, FizzBuzz const& fb)
        -> std::ostream&
    {
        if (fb._is_multiple) {
            return os << fb._s;
        }
        return os << static_cast<unsigned int>(fb._i);
    }

   private:
    union {
        std::uint_fast8_t const _i;
        char _s[1 + chr::length("FizzBuzz")];
    };
    bool const _is_multiple;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    assert(FizzBuzz{3}.is_fizz());
    assert(FizzBuzz{5}.is_buzz());
    assert(FizzBuzz{15}.is_fizzbuzz());
    assert(FizzBuzz{27}.is_fizz_or_buzz());

    for (auto i = std::uint_fast8_t{ 1 }; i < 100; ++i) {
        std::cout << FizzBuzz{ i } << '\n';
    }
}
