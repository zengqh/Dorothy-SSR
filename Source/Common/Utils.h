/* Copyright (c) 2016 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#pragma once

NS_DOROTHY_BEGIN

/** @brief Helper macros to define setters and getters */
#define PROPERTY(varType, funName) \
public: varType get##funName() const; \
public: void set##funName(varType var)

#define PROPERTY_REF(varType, funName) \
public: const varType& get##funName() const; \
public: void set##funName(const varType& var)

#define PROPERTY_VIRTUAL(varType, funName) \
public: varType get##funName() const; \
public: virtual void set##funName(varType var)

#define PROPERTY_VIRTUAL_REF(varType, funName) \
public: const varType& get##funName() const; \
public: virtual void set##funName(const varType& var)

#define PROPERTY_READONLY_VIRTUAL(varType, funName) \
public: virtual varType get##funName() const

#define PROPERTY_READONLY(varType, funName) \
public: varType get##funName() const

#define PROPERTY_READONLY_REF(varType, funName) \
public: const varType& get##funName() const

#define PROPERTY_READONLY_BOOL(funName) \
public: bool is##funName() const

#define PROPERTY_READONLY_CLASS(varType, funName) \
public: static varType get##funName()

#define PROPERTY_READONLY_CALL(varType, funName) \
public: varType get##funName()

#define PROPERTY_BOOL(funName) \
public: bool is##funName() const; \
public: void set##funName(bool var)

/** @brief Code block for condition check.
	@example Use it as below.

	BLOCK_START
	...
	BREAK_IF(flag)
	...
	BREAK_UNLESS(flag2)
	...
	BLOCK_END
*/
#define BLOCK_START do {
#define BREAK_IF(cond) if (cond) break;
#define BREAK_UNLESS(cond) if (!cond) break;
#define BLOCK_END } while (false);

/** @brief A better Enum.
	@example Use it as below.

	ENUM_START(MyFlag)
	{
		FlagOne = 1,
		FlagTwo,
		FlagThree
	}
	ENUM_END(MyFlag)

	MyFlag flag = MyFlag::FlagTwo;
*/
#define ENUM_START(x) struct x \
{ \
public: \
	enum xEnum

#define ENUM_END(x) ;\
	inline x() { } \
	inline x(const xEnum value):_value(value) { } \
	explicit inline x(int value):_value((xEnum)value) { } \
	inline void operator=(const xEnum inValue) \
	{ \
		_value = inValue; \
	} \
	inline operator xEnum() const \
	{ \
		return _value; \
	} \
private: \
	xEnum _value; \
};

/** @brief Compiler compact macros */
#ifdef __GNUC__
	#define DORA_UNUSED __attribute__ ((unused))
#else
	#define DORA_UNUSED
#endif

#define DORA_UNUSED_PARAM(unusedparam) (void)unusedparam
#define DORA_DUMMY do {} while (0)

/** @brief Short name for Slice used for argument type */
typedef const Slice& String;

/** @brief Helper function to add create style codes for oObject derivations.
 The added create(...) functions accept the same argument with the class constructors.
 @example Use it as below.

 // Add the macro in subclass of Object
 class MyItem : public Object
 {
 	public:
		MyItem();
		MyItem(int value);
		virtual bool init() override;
		CREATE_FUNC(MyItem)
 };
 
 // Use the create functions
 auto itemA = MyItem::create();
 auto itemB = MyItem::create(998);
 */
#define CREATE_FUNC(type) \
template<class... Args> \
static type* create(Args&&... args) \
{ \
    type* item = new type(std::forward<Args>(args)...); \
    if (item && item->init()) \
    { \
        item->autorelease(); \
    } \
    else \
    { \
        delete item; \
        item = nullptr; \
    } \
	return item; \
}

/** @brief Helper function to iterate a std::tuple.
 @example Use it as below.

 // I have a tuple
 auto item = std::make_tuple(998, 233, "a pen");

 // I have a handler
 struct Handler
 {
 	template<typename T>
 	void operator()(const T& element)
 	{
 		cout << element << "\n";
 	}
 };

 // Em, start iteration
 Tuple::foreach(item, Handler());
 */
namespace Tuple {
	template<typename TupleT, size_t Size>
	struct TupleHelper
	{
		template<typename Func>
		static void foreach(const TupleT& item, Func&& func)
		{
			TupleHelper<TupleT, Size - 1>::foreach(item, func);
			func(std::get<Size - 1>(item));
		}
	};
	template<typename TupleT>
	struct TupleHelper<TupleT, 0>
	{
		template<typename Func>
		static void foreach(const TupleT&, Func&&)
		{ }
	};
	template<typename TupleT, typename Func>
	inline int foreach(const TupleT& item, Func&& func)
	{
		TupleHelper<TupleT, std::tuple_size<TupleT>::value>::foreach(item, func);
		return (int)std::tuple_size<TupleT>::value;
	}
} // namespace Tuple

/* Short names for C++ casts */
#define s_cast static_cast
#define r_cast reinterpret_cast
#define c_cast const_cast
#define d_cast dynamic_cast

#ifndef FLT_EPSILON
	#define FLT_EPSILON 1.192092896e-07F
#endif // FLT_EPSILON

/** @brief Helper functions to hash string in compile time for use of
 string switch case.
 @example Use it as below.

 string extension = "png";
 switch (Switch::hash(extension))
 {
 	case "xml"_hash:
 		// ...
 		break;
 	case "cpp"_hash:
 		// ...
 		break;
 	default:
		// ...
 		break;
 }
 */
namespace Switch {
	inline constexpr std::size_t hash(char const* input)
	{
		return *input ? *input + 33ull * hash(input + 1) : 5381;
	}
	inline std::size_t hash(const char* input, int size, int index)
	{
		return index < size ? input[index] + 33ull * hash(input, size, index + 1) : 5381;
	}
	inline std::size_t hash(String str)
	{
		return hash(str.rawData(), s_cast<int>(str.size()), 0);
	}
	namespace Literals
	{
		inline std::size_t constexpr operator"" _hash(const char* s, size_t)
		{
			return hash(s);
		}
	}
} // namespace Switch

/** @brief Helpers for number comparision */
#ifdef min
	#undef min
#endif
#ifdef max
	#undef max
#endif
template <class T>
inline T Clamp(T value, T minVal, T maxVal)
{
	auto pair = std::minmax(minVal, maxVal);
	return std::max(std::min(value, pair.second), pair.first);
}

/** @brief Dorothy`s type system for lua and
 be the alternative for dynamic_cast.
 */
extern int doraType;

template <class T>
int DoraType()
{
	static int type = doraType++;
	return type;
}

#define DORA_TYPE(type) \
public: int getDoraType() const \
{ \
	return DoraType<type>(); \
}

#define DORA_TYPE_BASE(type) \
public: virtual int getDoraType() const \
{ \
	return DoraType<type>(); \
}

#define DORA_TYPE_OVERRIDE(type) \
public: virtual int getDoraType() const override \
{ \
	return DoraType<type>(); \
}

template <class OutT, class InT>
OutT* DoraCast(InT* obj)
{
	return (obj && obj->getDoraType() == DoraType<OutT>()) ? s_cast<OutT*>(obj) : nullptr;
}

#define LuaType DoraType

NS_DOROTHY_END