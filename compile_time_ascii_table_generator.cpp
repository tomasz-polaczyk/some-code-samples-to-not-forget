#include <type_traits>
#include <utility>
#include <array>
#include <string_view>

template<typename T, size_t... S>
std::array<std::result_of_t<T(size_t)>, sizeof...(S)> make_array(T&& type, std::index_sequence<S...>)
{
    return std::array<std::result_of_t<T(size_t)>, sizeof...(S)> { type(S)... };
}

template<size_t N, typename T>
std::array<std::result_of_t<T(size_t)>, N> make_array(T&& type)
{
    return make_array(std::forward<T>(type), std::make_index_sequence<N>());
}

namespace ASCII
{

constexpr static size_t ASCIITableSize = 128;

struct Char
{
    Char(int val) : key(val), value(val) { }
    
    char key;
    int  value;
};

const static auto make_ascii_table()
{
    return make_array<ASCIITableSize>([](size_t index) { return Char(index); });
}

} // namespace ASCII

int main()
{
    return ASCII::make_ascii_table()[65].key;
}

