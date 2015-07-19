#include "engine/serialization/serializer.hh"
#include "engine/serialization/serializable.hh"
#include "engine/serialization/serial.hpp"

namespace laroue {
  namespace engine {
    namespace serialization {

      const std::string		Serializer::nameById(const std::type_info& ti) {
	return Serializable::nameById(ti);
      }

      const Serial&		Serializer::operator <<(const Serial& serial) {
	_serialized += serialize(serial);
	return serial;
      }

      const std::string		Serializer::serialize(const Serial& serial) {
	return serial.Stringify(*this);
      }
      
    };
  };
};
