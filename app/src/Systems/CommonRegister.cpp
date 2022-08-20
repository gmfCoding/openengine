class CommonRegister
{
    public:
    template<typename T, typename U>
    static bool Common()
    {
        U::Register<T>();
        return true;
    }

    template<typename T>
    static void Register()
    {
        U::Register<T>();
    }
};


template<typename T, typename U>
struct RegisteringClass {
    inline static const bool autoRegister = CommonRegister::Common<T, U>();
};

#define REGISTER_CLASS() REGISTER_CLASS_T(decltype(*this))

#define REGISTER_CLASS_R(R) REGISTER_CLASS_T_R(decltype(*this), R)

#define REGISTER_CLASS_T(type) REGISTER_CLASS_T_R(type, CommonRegister)

#define REGISTER_CLASS_T_R(T, R) \
const void* registeringMethod() const { \
    return &RegisteringClass<T, R>::autoRegister; \
}