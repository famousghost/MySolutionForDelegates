#pragma once
#include <vector>
#include <map>
#include <type_traits>
#include <functional>
#include <iostream>

template<typename R, typename... A>
R return_type(R(*)(A...));

template<typename C, typename R, typename... A>
R return_type(R(C::*)(A...));

template<typename T>
struct ClassOf {};

template<typename Return, typename Class, typename... Args>
struct ClassOf < Return(Class::*)(Args...) > {
    using type = Class;
};

template< typename T>
using ClassOf_t = typename ClassOf<T>::type;

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

template<typename Func>
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

    void Register(ClassOf_t<decltype(Func())>* type, Func func)
    {
        classDelegates[type].push_back(func);
    }

    void Unregister(ClassOf_t<decltype(Func())>* type, Func func)
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
    std::map<ClassOf_t<decltype(Func())>*, std::vector<Func>> classDelegates;
};

template<typename LambdaType, typename Type, typename Func>
class Lambda
{
public:
    Lambda(LambdaType lambdaType, Type* type, Func func)
        :lambdaType(lambdaType), type(type), func(func)
    {
    }

    template<typename... Args>
    void operator()(Args... args)
    {
        lambdaType(args...);
    }

    bool operator==(const Lambda& lambda)
    {
        return this->func == lambda->func;
    }

    bool operator!=(const Lambda& lambda)
    {
        return !operator==(lambda);
    }
    LambdaType lambdaType;
    Type* type;
    Func func;
};

template<typename FuncStruct>
class Delegate
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

    template<typename Type, typename Func>
    void Register(Type* type, Func func)
    {
        auto lambda = [type, func](auto... args) { (type->*func)(args...); };
        auto f = Lambda<std::function<FuncStruct>, Type, Func>(lambda, type, func);
        funcDelegates.push_back(f);
    }

    template<typename Type, typename Func>
    void Unregister(Type* type, Func func)
    {
        for (int i = 0; i < funcDelegates.size(); ++i)
        {
            std::string str = funcDelegates[i].target_type().name();
            std::string str2 = typeid(func).name();
            std::string str3 = typeid(*type).name();
            std::string classSubString = "";
            if (str.find(str2) != std::string::npos)
            {
                if (str.find(str3) != std::string::npos)
                {
                    if ((type == funcDelegates[i].target<Lambda<std::function<FuncStruct>, Type, Func>>()->type))
                    {
                        if (func == funcDelegates[i].target<Lambda<std::function<FuncStruct>, Type, Func>>()->func)
                        {
                            funcDelegates[i] = funcDelegates[funcDelegates.size() - 1];
                            funcDelegates.pop_back();
                            return;
                        }
                    }
                }
            }
        }
    }

    void UnregisterAll()
    {
        funcDelegates.clear();
    }
private:
    std::vector<std::function<FuncStruct>> funcDelegates;
};