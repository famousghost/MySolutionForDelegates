#pragma once
#include <vector>
#include <map>
#include <type_traits>

template<typename R, typename... A>
R return_type(R(*)(A...));

template<typename C, typename R, typename... A>
R return_type(R(C::*)(A...));

template<typename Func>
class DelegateFunc
{
public:

    template<typename... Args>
    void Invoke(Args... args)
    {
        for (auto& delegate : funcDelegates)
        {
            delegate(args...);
        }
    }

    void Register(Func func)
    {
        funcDelegates.push_back(func);
    }

    template<typename... Args>
    std::vector<decltype(return_type(Func()))> InvokeRet(Args... args)
    {
        std::vector<decltype(return_type(Func()))> result;
        for (auto& delegate : funcDelegates)
        {
            result.push_back(delegate(args...));
        }
        return result;
    }

    void Unregister(Func func)
    {
        for (int i = 0; i < funcDelegates.size(); ++i)
        {
            if (func == funcDelegates[i])
            {
                funcDelegates[i] = funcDelegates[funcDelegates.size() - 1];
                funcDelegates.pop_back();
                return;
            }
        }
    }
private:
    std::vector<Func> funcDelegates;
};

template<typename Type, typename Func>
class DelegateMethod
{
public:
    template<typename... Args>
    void Invoke(Args... args)
    {
        for (auto& delegate : classDelegates)
        {
            for (auto& func : delegate.second)
            {
                (delegate.first->*func)(args...);
            }
        }
    }

    template<typename... Args>
    std::vector<decltype(return_type(Func()))> InvokeRet(Args... args)
    {
        std::vector<decltype(return_type(Func()))> result;
        for (auto& delegate : classDelegates)
        {
            for (auto& func : delegate.second)
            {
                result.push_back((delegate.first->*func)(args...));
            }
        }
        return result;
    }

    void Register(Type type, Func func)
    {
        classDelegates[type].push_back(func);
    }

    void Unregister(Type type, Func func)
    {
        auto it = classDelegates.find(type);

        for (int i = 0; i < it->second.size(); ++i)
        {
            if (func == it->second[i])
            {
                it->second[i] = it->second[it->second.size() - 1];
                it->second.pop_back();
                return;
            }
        }
    }

private:
    std::map<Type, std::vector<Func>> classDelegates;
};
