#ifndef _GRIB_MAP_HPP_
#define _GRIB_MAP_HPP_

#include <map>
#include <type_traits>
#include <initializer_list>
#include <xutility>
#include <algorithm>

namespace grib {

	template<typename T1, typename T2>
	struct enable_if_underlying_is_same {
		typedef T1 underlying_type;
		typedef T2 enum_type;
		typedef typename std::enable_if<
			std::is_same<underlying_type, std::underlying_type<enum_type>::type>::value
		>::type type;
	};


	template<typename TKey, typename TVal, template<typename...> typename TMapType>
	class enumkey_map : public TMapType<TKey, TVal> {
	public:
		typedef enumkey_map<TKey, TVal, TMapType> _Myt;
		typedef TMapType<TKey, TVal> _Mybase;
		typedef typename _Mybase::key_type key_type;
		typedef typename _Mybase::mapped_type mapped_type;

		typedef typename _Mybase::value_compare value_compare;
		typedef typename _Mybase::allocator_type allocator_type;
		typedef typename _Mybase::size_type size_type;
		typedef typename _Mybase::difference_type difference_type;
		typedef typename _Mybase::pointer pointer;
		typedef typename _Mybase::const_pointer const_pointer;
		typedef typename _Mybase::reference reference;
		typedef typename _Mybase::const_reference const_reference;
		typedef typename _Mybase::iterator iterator;
		typedef typename _Mybase::const_iterator const_iterator;
		typedef typename _Mybase::reverse_iterator reverse_iterator;
		typedef typename _Mybase::const_reverse_iterator
			const_reverse_iterator;
		typedef typename _Mybase::value_type value_type;


		template<typename TEnumKey>
		using enum_value_type = struct std::pair<std::add_const<TEnumKey>::type, value_type::second_type>;


		using _Mybase::_Mybase;

		template<
			typename TEnumKey,
			typename = enable_if_underlying_is_same<key_type, TEnumKey>::type>
		enumkey_map(const std::initializer_list<enum_value_type<TEnumKey>>& _EnumIlist) : 
			_Mybase()
		{
			insert(_EnumIlist);
		};

		template<typename _Iter>
		void insert_enumkey(_Iter _First, _Iter _Last) {
			_DEBUG_RANGE(_First, _Last);
			for (; _First != _Last; ++_First) {
				auto item = std::make_pair<key_type, mapped_type>(static_cast<key_type>(_First->first), _First->second);
				emplace_hint(end(), item);
			}
		};

		template<
			typename TEnumKey,
		>
			void insert(std::initializer_list<enum_value_type<TEnumKey>> _Ilist) {
			insert_enumkey(_Ilist.begin(), _Ilist.end());
		};

		template<
			typename TEnumKey,
			typename = std::enable_if<std::is_same<key_type, std::underlying_type<TEnumKey>::type>::value>::type>
			inline mapped_type& operator[](const TEnumKey& _EnumKeyval) {
			return _Mybase::operator[](static_cast<key_type>(_EnumKeyval));
		};
	};

};	//-- namespace grib --

#endif	//-- _GRIB_MAP_HPP_ --
