#ifndef Serializer_string_hpp__
# define Serializer_string_hpp__

namespace laroue {
  namespace engine {
    namespace serialization {

      class SerialString : public SerialImpl {
      private:
	friend struct serialized_selector_string;
	std::string	value;

      public:
	const std::string Stringify(Serializer&) const override;

      public:
	SerialString(const std::string& string) : value(string) {}
	SerialString() = default;
	~SerialString() final = default;
      };
      struct serialized_selector_string {};

    };
  };
};

#endif
