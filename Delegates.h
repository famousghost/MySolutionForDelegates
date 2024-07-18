#include <iostream>
#include <memory>
#include <vector>

template<typename Func>
struct Function
{

};

template<typename RetType, typename... Args>
struct Function<RetType(Args...)>
{
public:
    using ReturnType = RetType;

    template<typename F>
    Function(F f, const std::string& p_name, size_t p_typeAddress, size_t p_funcAddress)
        :m_func(new Func<F>(std::forward<F>(f))),
        m_name(p_name),
        m_typeAddress(p_typeAddress),
        m_funcAddress(p_funcAddress)
    {

    }

    RetType operator()(Args&&... args)
    {
        return (*m_func)(std::forward<Args>(args)...);
    }

    size_t GetFuncAddress() const
    {
        return m_funcAddress;
    }

    size_t GetTypeAddress() const
    {
        return m_typeAddress;
    }

    std::string GetName() const
    {
        return m_name;
    }
private:

    struct Concept
    {
        virtual ~Concept() {}
        virtual RetType operator()(Args&&... args) = 0;
    };

    template<typename F>
    struct Func : public Concept
    {
        Func(F&& f)
            :f(std::forward<F>(f))
        {

        }
        RetType operator()(Args&&... args)
        {
            return f(std::forward<Args>(args)...);
        }
        F f;
    };
    std::unique_ptr<Concept> m_func;
    std::string m_name;
    size_t m_typeAddress;
    size_t m_funcAddress;
};

template<typename F>
class Delegate
{
public:
#define REGISTER_METHOD(CLASS_TYPE, FUNC)\
            Register(CLASS_TYPE, FUNC, #FUNC)\

    template<typename ClassType, typename Func>
    void Register(ClassType* type, Func func, const std::string& p_functionName)
    {
        std::string name = typeid(ClassType).name();
        name += typeid(Func).name();
        name += p_functionName;

        int index = 0;
        if(!CheckIfMethodExists(type, func, name, index))
        {
            auto lambda = [type, func](auto&&... args) {return (type->*func)(std::forward<decltype(args)&&>(args)...); };
            m_funcs.push_back(Function<F>{lambda, name, (size_t)type, 0});
        }
    }

#define REGISTER_FUNC(FUNC)\
            Register(FUNC, #FUNC)\

    void Register(F func, const std::string& p_functionName)
    {
        std::string name = typeid(F).name();
        name += p_functionName;
        int index = 0;
        if (!CheckIfFuncExists(func, name, index))
        {
            auto lambda = [func](auto&&... args) {return func(std::forward<decltype(args)&&>(args)...); };
            m_funcs.push_back(Function<F>{lambda, name, 0, (size_t)(func)});
        }
    }

#define UNREGISTER_METHOD(CLASS_TYPE, FUNC)\
            Unregister(CLASS_TYPE, FUNC, #FUNC)\

    template<typename ClassType, typename Func>
    void Unregister(ClassType* type, Func func, const std::string& p_functionName)
    {
        std::string name = typeid(ClassType).name();
        name += typeid(Func).name();
        name += p_functionName;
        int index = 0;
        if (CheckIfMethodExists(type, func, name, index))
        {
            m_funcs.erase(m_funcs.begin() + index);
        }
    }

#define UNREGISTER_FUNC(FUNC)\
            Unregister(FUNC, #FUNC)

    void Unregister(F func, const std::string& p_functionName)
    {
        std::string name = typeid(F).name();
        name += p_functionName;
        int index = 0;
        bool found = CheckIfFuncExists(func, name, index);
        if (found)
        {
            m_funcs.erase(m_funcs.begin() + index);
        }
    }

    template<typename ClassType, typename Func>
    bool CheckIfMethodExists(ClassType* type, Func func, const std::string& p_name, int& index)
    {
        for (int i = 0; i < m_funcs.size(); ++i)
        {
            if (m_funcs[i].GetName() == p_name
                && m_funcs[i].GetTypeAddress() == (size_t)type)
            {
                return true;
            }
            index++;
        }
        return false;
    }

    template<typename Func>
    bool CheckIfFuncExists(Func func, const std::string& p_name, int& index)
    {
        for (int i = 0; i < m_funcs.size(); ++i)
        {
            if (m_funcs[i].GetName() == p_name
                && m_funcs[i].GetFuncAddress() == (size_t)func)
            {
                return true;
            }
            index++;
        }
        return false;
    }

    void UnregisterAll()
    {
        m_funcs.clear();
    }

    template<typename... Args>
    void Invoke(Args&&... args)
    {
        for (auto& func : m_funcs)
        {
            func(std::forward<Args>(args)...);
        }
    }
    
    template<typename... Args>
    auto InvokeRet(Args&&... args)
    {
        std::vector<decltype(m_funcs)::value_type::ReturnType> m_values;
        for (auto& func : m_funcs)
        {
            m_values.push_back(func(std::forward<Args>(args)...));
        }
        return m_values;
    }

private:
    std::vector<Function<F>> m_funcs;
};