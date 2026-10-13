#ifndef PACK_H
#define PACK_H

namespace pack_detail
{
    //q1
    template <typename... Args>
    constexpr int packSize = sizeof...(Args);

    //q2
    template <int QueryIndex, typename... Args>
    struct _packIndexToType
    {
        static_assert(QueryIndex >= 0 && QueryIndex < sizeof...(Args), "The index is invalid");
    };

    template <typename T, typename... Args>
    struct _packIndexToType<0, T, Args...>
    {
        using type = T;
    };

    template <int QueryIndex, typename T, typename... Args>
    struct _packIndexToType<QueryIndex, T, Args...>: _packIndexToType<QueryIndex - 1, Args...> {};

    //conveneince alias
    template <int QueryIndex, typename... Args>
    using packIndexToType = typename _packIndexToType<QueryIndex, Args...>::type;

    //q3
    template <int Accumulated, typename QueryType, typename... Args>
    constexpr int _packTypeToIndex =-1;

    template <int Accumulated, typename QueryType, typename T, typename... Args>
    constexpr int _packTypeToIndex<Accumulated, QueryType, T, Args...> = _packTypeToIndex<Accumulated + 1, QueryType, Args...>;

    template <int Accumulated, typename QueryType, typename... Args>
    constexpr int _packTypeToIndex<Accumulated, QueryType, QueryType, Args...> = Accumulated;


    template <typename QueryType, typename... Args>
    constexpr int packTypeToIndex = _packTypeToIndex<0, QueryType, Args...>;


}

template <typename... Args>
struct Pack
{
    // q4
    static constexpr int size = pack_detail::packSize<Args...>;

    // q5
    template <int QueryIndex>
    using type = pack_detail::packIndexToType<QueryIndex, Args...>;

    // q6
    template <typename QueryType>
    static constexpr int index = pack_detail::packTypeToIndex<QueryType, Args...>;
};
#endif  // PACK_H
