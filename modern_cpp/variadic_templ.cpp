#include <iostream>
#include <typeinfo>

template<typename T>
auto adder(T v)-> decltype(v)
{
    return v;
}

template <typename T, typename... Args>
auto adder(T first, Args... args) -> T
{
    return first + adder(args...);
}

//from http://eli.thegreenplace.net/2014/variadic-templates-in-c/
template<class... Ts> struct tuple{};

template <class T, class... Ts>
struct tuple<T, Ts...> : tuple<Ts...>
{
    tuple(T head, Ts... ts) : tuple <Ts...>(ts...), tail(head){}

    T tail;
};


template <size_t, class> struct elem_type_holder;

template <class T, class... Ts>
struct elem_type_holder<0, tuple<T, Ts...>>
{
   using type = T;
};

template <size_t k, class T, class... Ts>
struct elem_type_holder<k, tuple<T, Ts...>>
{
    using type = typename elem_type_holder<k-1, tuple<Ts...>>::type;
};


template <size_t k, class... Ts>
typename std::enable_if< k == 0, typename elem_type_holder<0, tuple<Ts...>>::type&>::type
get(tuple<Ts...>& t)
{
    return t.tail;
}

template <size_t k,class T,  class... Ts>
typename std::enable_if< k != 0, typename elem_type_holder<k, tuple<T, Ts...>>::type&>::type
get(tuple<T, Ts...>& t)
{
    tuple<Ts...>& base = t;
    return get<k-1>(base);
}

template <typename T>
std::ostream& operator<< (std::ostream& os, const tuple<T>& rhs)
{
    return  os <<rhs.tail << std::endl;
}

template <typename... rest>
std::ostream& operator<< (std::ostream& os, const tuple<rest...>& rhs)
{
    return os <<rhs;

}

template <typename first, typename... rest>
std::ostream& operator<< (std::ostream& os, const tuple<first, rest...>& rhs)
{
    os <<rhs.tail <<" - ";
    const tuple<rest...>& t = rhs;
    return os <<t;
}


int main(int argc, const char *argv[])
{
    auto sum = adder(1,1,1,1,1);
    std::cout << sum <<std::endl;
    auto sum_str = adder(std::string("hello "),std::string(" world "));
    std::cout <<sum_str <<std::endl;
    auto sum_mixed = adder(1.0,1.1,1,1,1);
    std::cout <<sum_mixed <<std::endl;

    tuple<double, uint64_t, const char*> tup(12.2, 42, "big");
    tuple<double, uint64_t, const char*, double> quad(1.5, 2 , "then", 15.05);

    std::cout << "tuple before assign " << tup <<std::endl;
    get<1>(tup) = 104;
    std::cout << "tuple after assign " << tup <<std::endl;

    std::cout << "quadruple " << quad <<std::endl;

    typename elem_type_holder<1, tuple<double, int, const char*>>::type foo;

    std::cout <<typeid(foo).name()<<std::endl;


    return 0;
}
