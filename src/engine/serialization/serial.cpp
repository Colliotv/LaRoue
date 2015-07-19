#include "engine/serialization/serial.hpp"
#include "engine/serialization/serializer.hh"

namespace laroue {
  namespace engine {
    namespace serialization {

      const std::string SerialInteger::Stringify(Serializer& serializer) const {
	return serializer.Integer(value);
      }

      const std::string SerialList::Stringify(Serializer& serializer) const {
	return serializer.List(value);
      }

      const std::string SerialString::Stringify(Serializer& serializer) const {
	return serializer.String(value);
      }

    };
  };
};
