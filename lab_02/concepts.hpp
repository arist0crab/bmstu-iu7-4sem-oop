#pragma once

#include <concepts>
#include <type_traits>
#include <ranges>

template <typename T>
concept MatrixElement = requires(T a, T b) 
{
    { a + b } -> std::convertible_to<T>;
    { a - b } -> std::convertible_to<T>;
    { a * b } -> std::convertible_to<T>;
    { a / b } -> std::convertible_to<T>;
    { a += b } -> std::same_as<T&>;
    { a -= b } -> std::same_as<T&>;
    { a *= b } -> std::same_as<T&>;
    { a /= b } -> std::same_as<T&>;
    T(0);
};

template <typename From, typename To>
concept ConvertibleTo = std::convertible_to<From, To>;

template <typename T, typename U>
concept HasCommon = std::common_with<T, U>;

template <typename T, typename U>
concept EqualityComparable = requires(T t, U u)
{
    { t == u } noexcept -> std::same_as<bool>;
    { t != u } noexcept -> std::same_as<bool>;
    { u == t } noexcept -> std::same_as<bool>;
    { u != t } noexcept -> std::same_as<bool>;
};

template <MatrixElement T>
class Matrix;

template <typename M>
concept isMatrix = requires {
    typename std::remove_cvref_t<M>::value_type;
} && std::same_as<Matrix<typename std::remove_cvref_t<M>::value_type>, std::remove_cvref_t<M>>;

template <typename M>
concept MatrixContainer = 
    std::copy_constructible<M> && std::move_constructible<M> && std::destructible<M> && requires(M m) {
        typename std::remove_reference_t<M>::value_type;
        typename std::remove_reference_t<M>::reference;
        typename std::remove_reference_t<M>::const_reference;
        typename std::remove_reference_t<M>::size_type;
        typename std::remove_reference_t<M>::iterator;
        typename std::remove_reference_t<M>::const_iterator;
        typename std::remove_reference_t<M>::difference_type;
        
        { m.begin() } noexcept -> std::same_as<typename std::remove_reference_t<M>::iterator>;
        { m.end() } noexcept -> std::same_as<typename std::remove_reference_t<M>::iterator>;
        { m.cbegin() } noexcept -> std::same_as<typename std::remove_reference_t<M>::const_iterator>;
        { m.cend() } noexcept -> std::same_as<typename std::remove_reference_t<M>::const_iterator>;
        { m.rows() } noexcept -> std::same_as<typename std::remove_reference_t<M>::size_type>;
        { m.cols() } noexcept -> std::same_as<typename std::remove_reference_t<M>::size_type>;
        { m.size() } noexcept -> std::same_as<typename std::remove_reference_t<M>::size_type>;
        { m.is_empty() } noexcept -> std::same_as<bool>; 
    };

template <typename C, typename T>
concept ConvertibleContainer =
    !isMatrix<C> && std::ranges::range<C> && ConvertibleTo<std::ranges::range_value_t<C>, T>;

template <typename C, typename T>
concept CommonContainer =
    !isMatrix<C> && std::ranges::range<C> && HasCommon<std::ranges::range_value_t<C>, T>;

template <typename C, typename T>
concept EqualityComparableContainer =
    !isMatrix<C> && std::ranges::range<C> && EqualityComparable<std::ranges::range_value_t<C>, T>;

template <typename R>
concept Range = std::ranges::input_range<R>;

template <typename R, typename T>
concept ConvertibleRange =
    !isMatrix<R> && Range<R> && ConvertibleTo<std::ranges::range_value_t<R>, T>;

template <typename R, typename T>
concept CommonRange =
    !isMatrix<R> && Range<R> && HasCommon<std::ranges::range_value_t<R>, T>;   

template <typename R, typename T>
concept EqualityComparableRange =
    !isMatrix<R> && Range<R> && EqualityComparable<std::ranges::range_value_t<R>, T>;

template <typename It>
concept InputIterator = std::input_iterator<It>;

template <typename It, typename T>
concept ConvertibleInputIterator = InputIterator<It> && ConvertibleTo<typename std::iterator_traits<It>::value_type, T>;

template <typename It, typename T>
concept EqualityComparableInputIterator = InputIterator<It> && EqualityComparable<typename std::iterator_traits<It>::value_type, T>;

template <typename S, typename It>
concept Sentinel = std::sentinel_for<S, It>;

template <typename M1, typename M2>
concept SameSizeMatrices = isMatrix<M1> && isMatrix<M2> && requires(M1 m1, M2 m2) {
    { m1.rows() } -> std::convertible_to<typename std::remove_cvref_t<M1>::size_type>;
    { m1.cols() } -> std::convertible_to<typename std::remove_cvref_t<M1>::size_type>;
    { m2.rows() } -> std::convertible_to<typename std::remove_cvref_t<M2>::size_type>;
    { m2.cols() } -> std::convertible_to<typename std::remove_cvref_t<M2>::size_type>;
    requires std::same_as<decltype(m1.rows()), decltype(m2.rows())>;
    requires std::same_as<decltype(m1.cols()), decltype(m2.cols())>;
};

template <typename M1, typename M2>
concept MultipliableMatrices = isMatrix<M1> && isMatrix<M2> && requires(M1 m1, M2 m2) {
    { m1.cols() } -> std::convertible_to<typename std::remove_cvref_t<M1>::size_type>;
    { m2.rows() } -> std::convertible_to<typename std::remove_cvref_t<M2>::size_type>;
    requires std::same_as<decltype(m1.cols()), decltype(m2.rows())>;
};

template <typename T>
concept ArithmeticScalar = std::is_arithmetic_v<T> && MatrixElement<T>;