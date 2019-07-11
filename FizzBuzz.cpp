#include <cassert>
#include <cstdint>
#include <iostream>

class FizzBuzz final {
   public:
    explicit constexpr FizzBuzz(std::uint_fast8_t i)
    : _i{ i }
    , _is_multiple{ [=, this]() constexpr {
        auto offset_ptr =  _s;
        auto is_multiple = false;

        if (i % 3 == 0) {
            is_multiple = true;
            offset_ptr[0] = 'F';
            offset_ptr[1] = 'i';
            offset_ptr[2] = 'z';
            offset_ptr[3] = 'z';
            offset_ptr[4] = '\0';
            offset_ptr += -1 + sizeof("Fizz") / sizeof(char);
        }
        if (i % 5 == 0) {
            is_multiple |= true;
            offset_ptr[0] = 'B';
            offset_ptr[1] = 'u';
            offset_ptr[2] = 'z';
            offset_ptr[3] = 'z';
            offset_ptr[4] = '\0';
        }

        return is_multiple;
    }() } {}

    [[nodiscard]]
    constexpr bool is_fizz() const {
        return _is_multiple &&
               'F' == _s[0] &&
               '\0' == _s[-1 + sizeof("Fizz") / sizeof(char)];
    }

    [[nodiscard]]
    constexpr bool is_buzz() const {
        return _is_multiple && 'B' == _s[0];
    }

    [[nodiscard]]
    constexpr bool is_fizzbuzz() const {
        return _is_multiple && 'B' == _s[-1 + sizeof("Fizz") / sizeof(char)];
    }

    [[nodiscard]]
    constexpr bool is_fizz_or_buzz() const {
        return _is_multiple && ('F' == _s[0] || 'B' == _s[0]);
    }

    friend std::ostream& operator<<(std::ostream& os, FizzBuzz const& fb) {
        if (fb._is_multiple) {
            return os << fb._s;
        }
        return os << static_cast<unsigned int>(fb._i);
    }

   private:
    union {
        std::uint_fast8_t const _i;
        char _s[sizeof("FizzBuzz") / sizeof(char)];
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
