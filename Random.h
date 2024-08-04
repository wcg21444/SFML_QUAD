#pragma once
#include <random>

template<typename Ty>
concept arithmetic = std::is_arithmetic<Ty>::value;

template<arithmetic Ty>
class Random
{
    inline static std::random_device sd = std::random_device();//生成random_device对象sd做种子
    inline static std::default_random_engine rand_engine = std::default_random_engine(sd());
    std::uniform_real_distribution<> distr;
public:
    Random(Ty min, Ty max)
    {
        distr = std::uniform_real_distribution<>(min, max);
    }
    Ty getNum()
    {
        return distr(rand_engine);
    }
};