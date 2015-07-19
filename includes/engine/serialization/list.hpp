#ifndef Serializer_list_hpp__
# define Serializer_list_hpp__

namespace laroue {
  namespace engine {
    namespace serialization {

      class SerialList : public SerialImpl {
      private:
	friend struct serialized_selector_list;
	std::list< std::unique_ptr<Serial> >	value;

      public:
	const std::string Stringify(Serializer&) const override;

      public:
	template<typename type>
	SerialList(const type& list) { std::for_each(list.begin(), list.end(),
					      [this] (typename type::const_reference v)
					      { value.emplace_back(new Serial(v)); }); }
	SerialList() = default;
	~SerialList() final = default;
      };
      struct serialized_selector_list {};

    };
  };
};

#endif
