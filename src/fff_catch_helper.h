#ifndef fff_catch_helper_H
#define fff_catch_helper_H

#include "catch.hpp"
/*
 *  FFF helper macros && matchers for Catch.
 */

template<typename T>
class IsBetweenMatcher : public Catch::MatcherBase<T> {
    T m_begin, m_end;
public:
    virtual ~IsBetweenMatcher() {}
    IsBetweenMatcher( T begin, T end ) : m_begin( begin ), m_end( end ) {}

    virtual bool match( T const& i ) const override {
        return i >= m_begin && i <= m_end;
    }

    virtual std::string describe() const {
        std::ostringstream ss;
        ss << "is between " << m_begin << " and " << m_end;
        return ss.str();
    }
};

template<typename T>
class EqualToMatcher : public Catch::MatcherBase<T> {
    T m_value;
public:
    virtual ~EqualToMatcher() {}
    EqualToMatcher( T value ) : m_value( value ) {}

    virtual bool match( T const& i ) const override {
        return i == m_value;
    }

    virtual std::string describe() const {
        std::ostringstream ss;
        ss << "is equal to " << m_value;
        return ss.str();
    }
};

template<typename T>
class EqualToMatcher<T*> : public Catch::MatcherBase<const T*> {
    T* m_value;
public:
    virtual ~EqualToMatcher() {}
    EqualToMatcher( T* value ) : m_value( value ) {}

    virtual bool match( const T* i ) const override {
        return i == m_value;
    }

    virtual std::string describe() const {
        std::ostringstream ss;
        ss << "is equal to " << m_value;
        return ss.str();
    }
};

template<typename T>
class NotEqualToMatcher : public Catch::MatcherBase<T> {
    T m_value;
public:
    virtual ~NotEqualToMatcher() {}
    NotEqualToMatcher( T value ) : m_value( value ) {}

    virtual bool match( T const& i ) const override {
        return i != m_value;
    }

    virtual std::string describe() const {
        std::ostringstream ss;
        ss << "is not equal to " << m_value;
        return ss.str();
    }
};

template<typename T>
class NotEqualToMatcher<T*> : public Catch::MatcherBase<const T*> {
    T* m_value;
public:
    virtual ~NotEqualToMatcher() {}
    NotEqualToMatcher( T* value ) : m_value( value ) {}

    virtual bool match( const T* i ) const override {
        return i != m_value;
    }

    virtual std::string describe() const {
        std::ostringstream ss;
        ss << "is not equal to " << m_value;
        return ss.str();
    }
};

template<typename T>
class IsGreaterThanMatcher : public Catch::MatcherBase<T> {
    T m_value;
public:
    virtual ~IsGreaterThanMatcher() {}
    IsGreaterThanMatcher( T value ) : m_value( value ) {}

    virtual bool match( T const& i ) const override {
        return i > m_value;
    }

    virtual std::string describe() const {
        std::ostringstream ss;
        ss << "is greater than " << m_value;
        return ss.str();
    }
};

template<typename T>
class IsSmallerThanMatcher : public Catch::MatcherBase<T> {
    T m_value;
public:
    virtual ~IsSmallerThanMatcher() {}
    IsSmallerThanMatcher( T value ) : m_value( value ) {}

    virtual bool match( T const& i ) const override {
        return i < m_value;
    }

    virtual std::string describe() const {
        std::ostringstream ss;
        ss << "is smaller than " << m_value;
        return ss.str();
    }
};

// The builder functions
template<typename T>
inline IsBetweenMatcher<T> IsBetween( T begin, T end ) {
    return IsBetweenMatcher<T>( begin, end );
}

template<typename T>
inline EqualToMatcher<T> IsEqualTo( T value ) {
    return EqualToMatcher<T>( value );
}

template<typename T>
inline NotEqualToMatcher<T> IsNotEqualTo( T value ) {
    return NotEqualToMatcher<T>( value );
}

template<typename T>
inline IsGreaterThanMatcher<T> IsGreaterThan( T value ) {
    return IsGreaterThanMatcher<T>( value );
}

template<typename T>
inline IsSmallerThanMatcher<T> IsSmallerThan( T value ) {
    return IsSmallerThanMatcher<T>( value );
}

/*
 *  MATCHER MACROS
 */
#define CHECK_THAT_F(function_, matcher_)               CHECK_THAT(function_ ## _fake, matcher_)
#define REQUIRE_THAT_F(function_, matcher_)             REQUIRE_THAT(function_ ## _fake, matcher_)

#define CHECK_CALLCOUNT(function_, matcher_)            CHECK_THAT(function_ ## _fake.call_count, matcher_)
#define REQUIRE_CALLCOUNT(function_, matcher_)          CHECK_THAT(function_ ## _fake.call_count, matcher_)

#define CHECK_ARG(arg_, function_, matcher_)             CHECK_THAT(function_ ## _fake.arg ## arg_ ## _val, matcher_)
#define REQUIRE_ARG(arg_, function_, matcher_)           REQUIRE_THAT(function_ ## _fake.arg ## arg_ ## _val, matcher_)

/*
 * SETTERS
 */
#define SET_RETURN(function_, value_)                   function_ ## _fake.return_val = (value_)
#define SET_RETURNS(function_, array_)                  SET_RETURN_SEQ(function_, (array_).data(), (array_).size())


/* 
 *  ORDERINGS
 */
#define REQUIRE_CALLED_IN_ORDER(index_, function_)      REQUIRE(fff.call_history[index_] == ((void *) function_))
#define CHECK_CALLED_IN_ORDER(index_, function_)        CHECK(fff.call_history[index_] == ((void *) function_))

/*  Internal macros for use with REQUIRE_CALLORDER && REQUIRE_CALLORDER_FROM  */
#define _NUM_ARGS2(X,X64,X63,X62,X61,X60,X59,X58,X57,X56,X55,X54,X53,X52,X51,X50,X49,X48,X47,X46,X45,X44,X43,X42,X41,X40,X39,X38,X37,X36,X35,X34,X33,X32,X31,X30,X29,X28,X27,X26,X25,X24,X23,X22,X21,X20,X19,X18,X17,X16,X15,X14,X13,X12,X11,X10,X9,X8,X7,X6,X5,X4,X3,X2,X1,N,...) N
#define NUM_ARGS(...) _NUM_ARGS2(0, __VA_ARGS__ ,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)

#define _REQUIRE_CALLORDER_1(index_, function_)         REQUIRE_CALLED_IN_ORDER(index_, function_)

#define _REQUIRE_CALLORDER_2(index_, function_, ...)    REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_1(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_3(index_, function_, ...)    REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_2(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_4(index_, function_, ...)    REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_3(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_5(index_, function_, ...)    REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_4(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_6(index_, function_, ...)    REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_5(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_7(index_, function_, ...)    REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_6(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_8(index_, function_, ...)    REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_7(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_9(index_, function_, ...)    REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_8(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_10(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_9(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_11(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_10(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_12(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_11(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_13(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_12(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_14(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_13(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_15(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_14(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_16(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_15(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_17(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_16(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_18(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_17(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_19(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_18(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_20(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_19(index_ + 1, __VA_ARGS__)

#define _REQUIRE_CALLORDER_N3(index_, N, ...)           _REQUIRE_CALLORDER_ ## N(index_, __VA_ARGS__)
#define _REQUIRE_CALLORDER_N2(index_, N, ...)           _REQUIRE_CALLORDER_N3(index_, N, __VA_ARGS__)


/*  Internal macros for use with CHECK_CALLORDER && CHECK_CALLORDER_FROM  */
#define _CHECK_CALLORDER_1(index_, function_)           CHECK_CALLED_IN_ORDER(index_, function)

#define _CHECK_CALLORDER_2(index_, function_, ...)      CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_1(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_3(index_, function_, ...)      CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_2(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_4(index_, function_, ...)      CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_3(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_5(index_, function_, ...)      CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_4(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_6(index_, function_, ...)      CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_5(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_7(index_, function_, ...)      CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_6(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_8(index_, function_, ...)      CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_7(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_9(index_, function_, ...)      CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_8(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_10(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_9(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_11(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_10(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_12(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_11(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_13(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_12(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_14(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_13(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_15(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_14(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_16(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_15(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_17(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_16(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_18(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_17(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_19(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_18(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_20(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_19(index_ + 1, __VA_ARGS__)

#define _CHECK_CALLORDER_N3(index_, N, ...)             _CHECK_CALLORDER_ ## N(index_, __VA_ARGS__)
#define _CHECK_CALLORDER_N2(index_, N, ...)             _CHECK_CALLORDER_N3(index_, N, __VA_ARGS__)


/*  Fail if the function was not called in this particular order.  */
#define REQUIRE_CALLORDER_FROM(index_, ...)             _REQUIRE_CALLORDER_N2(index_, NUM_ARGS(__VA_ARGS__), __VA_ARGS__)
#define REQUIRE_CALLORDER(...)                          REQUIRE_CALLORDER_FROM(0, __VA_ARGS__)

/*  Fail if the function was not called in this particular order, but continue.  */
#define CHECK_CALLORDER_FROM(index_, ...)               _CHECK_CALLORDER_N2(index_, NUM_ARGS(__VA_ARGS__), __VA_ARGS__)
#define CHECK_CALLORDER(...)                            CHECK_CALLORDER_FROM(0, __VA_ARGS__)


#endif
