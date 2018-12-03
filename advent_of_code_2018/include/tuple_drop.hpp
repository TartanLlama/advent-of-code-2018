#pragma once

#include <tuple>
#include <type_traits>

namespace tl {
	namespace detail {
		template <class Tuple, std::size_t First, std::size_t... Idx, decltype(std::get<0>(std::declval<Tuple>()), 0)=0 >
		auto tuple_drop(Tuple&& t, std::index_sequence<First, Idx...>) {
			return std::make_tuple(std::get<Idx>(std::forward<Tuple>(t))...);
		}
		template <class Tuple, std::size_t First, std::size_t... Idx, decltype(std::declval<Tuple>().get<0>(), 0)=0 >
		auto tuple_drop(Tuple&& t, std::index_sequence<First, Idx...>) {
			return std::make_tuple(std::forward<Tuple>(t).get<Idx>()...);
		}
	}
	template <class Tuple>
	auto tuple_drop(Tuple&& t) {
		return detail::tuple_drop(std::forward<Tuple>(t), std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{});
	}
}