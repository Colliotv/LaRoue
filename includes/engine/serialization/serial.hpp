#ifndef Serializer_hpp__
# define Serializer_hpp__

#include <memory>

#include <algorithm>

#include <list>
#include <string>

namespace laroue {
  namespace engine {
    namespace serialization {

      class Serializer;

      template<typename type, typename test = void>
      struct serialized_selector {
	template<typename _type>
	static _type& extract(_type& m) { return m; }
	using Selector = void;
	using SerialImpl = void;
	static const bool	allowed = false;
      };
      class SerialImpl {
      public:
	inline virtual ~SerialImpl() = default;

      public:
	virtual const std::string Stringify(Serializer&) const = 0;
      };

      /* --> */ class Serial {
      private:
	std::unique_ptr<SerialImpl>	impl;

      public:
	template<typename type>
	bool	is() {
	  return serialized_selector<type>::is(impl);
	}

	template<typename type>
	bool as() {
	  return serialized_selector<type>::as(impl);
	}

      public:
	template<typename type>
	Serial(type value)
	  : impl(new typename serialized_selector<type>::SerialImpl(serialized_selector<type>::extract(value)))
	{												      }

      private:
	friend class Serializer;
	inline const std::string Stringify(Serializer& s) const { return impl->Stringify(s); }
      };

    };
  };
};

# include "list.hpp"
# include "string.hpp"
# include "int.hpp"

namespace laroue {
  namespace engine {
    namespace serialization {

      template<typename type>
      struct serialized_selector<type,
				 typename std::enable_if<
				   std::is_integral<type>::value
				   && !std::is_same<type, bool>::value
				   >::type > : public serialized_selector_integer, serialized_selector<void> {
	using Selector = serialized_selector_integer;
	using SerialImpl = SerialInteger;
	static const bool	allowed = true;
      };

      template<typename type>
      struct serialized_selector<type,
				 typename std::enable_if <
				   serialized_selector< typename type::value_type >::allowed &&
				   ! std::is_same<char, typename type::value_type >::value
				   >::type > : public serialized_selector_list, serialized_selector<void> {
	using Selector = serialized_selector_list;
	using SerialImpl = SerialList;
	static const bool	allowed = true;
      };

      template<typename type>
      struct serialized_selector<type,
				 typename std::enable_if<
				   std::is_same<char, typename type::value_type >::value
				   >::type >  : public serialized_selector_string, serialized_selector<void> {
	using Selector = serialized_selector_string;
	using SerialImpl = SerialString;
	static const bool	allowed = true;
      };


      template<typename wrapper, typename type>
      struct serialized_ptr_extractor {
	static type* extract(wrapper w) { return w.get(); }
      };

      template<typename wrapper, typename type>
      struct serialized_ptr_deference {
	static type& extract(wrapper w) { return *w; }
      };

      template<typename type>
      struct serialized_selector< std::shared_ptr< type >,
				 typename std::enable_if<
				   serialized_selector< type >::allowed
				   >::type >
	: public serialized_selector< type >::Selector,
	  public serialized_ptr_deference<std::shared_ptr<type>, type >{
	using Selector = typename serialized_selector< type >::Selector;
	using SerialImpl = typename serialized_selector< type >::SerialImpl;
	static const bool	allowed = true;
      };

      template<typename type>
      struct serialized_selector< std::shared_ptr< type >,
				 typename std::enable_if<
				   serialized_selector< type* >::allowed
				   >::type >
	: public serialized_selector< type* >::Selector,
	  public serialized_ptr_extractor<std::shared_ptr<type>, type >{
	using Selector = typename serialized_selector< type >::Selector;
	using SerialImpl = typename serialized_selector< type >::SerialImpl;
	static const bool	allowed = true;
      };

      template<typename type>
      struct serialized_selector< std::unique_ptr< type >,
				  typename std::enable_if<
				    serialized_selector< type >::allowed
				    >::type >
	: public serialized_selector< type >::Selector,
	  public serialized_ptr_deference<std::shared_ptr<type>, type >{
	using Selector = typename serialized_selector< type >::Selector;
	using SerialImpl = typename serialized_selector< type >::SerialImpl;
	static const bool	allowed = true;
      };

      template<typename type>
      struct serialized_selector< std::unique_ptr< type >,
				 typename std::enable_if<
				   serialized_selector< type* >::allowed
				   >::type >
	: public serialized_selector< type* >::Selector,
	  public serialized_ptr_extractor<std::shared_ptr<type>, type >{
	using Selector = typename serialized_selector< type >::Selector;
	using SerialImpl = typename serialized_selector< type >::SerialImpl;
	static const bool	allowed = true;
      };

    };
  };
};

#endif
