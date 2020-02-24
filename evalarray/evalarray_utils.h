#ifndef EVALARRAYHELPER_H
#define EVALARRAYHELPER_H

#include <array>
#include <cstddef>
#include <type_traits>

namespace Eval {

template<class U, class H = void>
struct HasValueType
{
    static constexpr bool value = false;
};

template<class U>
struct HasValueType<U, std::enable_if_t<std::is_same_v<typename U::value_type,typename U::value_type>>>
{
    static constexpr bool value = true;
};

class EvalarrayHelper
{
private:
    template<size_t i, class U>
    static size_t get_size(const U& obj)
    {
        if constexpr (i == 0)
            return obj.size();
        else
            return obj.begin() == obj.end() ? 0 : get_size<i-1>(*obj.begin());
    }

    template<class U, class H = void>
    struct findValueType
    {
        using value_type = U;
    };

    template<class U>
    struct findValueType<U, std::enable_if_t<HasValueType<U>::value>>
    {
        using value_type = typename findValueType<typename U::value_type>::value_type;
    };

    template<class U, class H = void>
    struct findNDim
    {
        static constexpr size_t value = 0;
    };

    template<class U>
    struct findNDim<U,std::enable_if_t<HasValueType<U>::value>>
    {
        static constexpr size_t value = 1 + findNDim<typename U::value_type>::value;
    };

public:
    template<class U>
    using value_type = typename findValueType<U>::value_type;

    template<class U>
    static constexpr size_t n_dim = findNDim<U>::value;

    template<class U, size_t... Is>
    static auto make_size_array(const U& obj, std::index_sequence<Is...> seq)
    {
        std::array<size_t, seq.size()> result;
        ((result[Is] = get_size<Is>(obj)), ...);
        return result;
    }
};
}

#endif // EVALARRAYHELPER_H
