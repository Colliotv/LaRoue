#ifndef Serialized_int_hpp__
# define Serialized_int_hpp__

namespace laroue {
  namespace engine {
    namespace serialization {

      class SerialInteger : public SerialImpl {
      private:
	friend struct serialized_selector_integer;
	long long	value;

      public:
	const std::string Stringify(Serializer&) const override;

      public:
	SerialInteger() = default;
	~SerialInteger() final = default;
	SerialInteger(int);
      };
      struct serialized_selector_integer {};

    };
  };
};

#endif
