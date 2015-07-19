#include <algorithm>

#include "engine/serialization/json.hh"
#include "engine/serialization/serializable.hh"

namespace laroue {
  namespace engine {
    namespace serialization {

      std::string	JSONSerialization::Object(const std::type_info& type_info, const std::map< std::string, std::unique_ptr<Serial> >& object) {
	std::string	serialized(
				   "{\n" +
				   std::string(level, '\t') + "\"type\" : \"" + Serializer::nameById(type_info) + "\"\n" +
				   std::string(level, '\t') + "\"object\" : "
				   );
	std::size_t	end = object.size();

	std::for_each(object.begin(), object.end(), [this, &end, &serialized]
		      (typename std::remove_const< typename std::remove_reference<decltype(object)>::type >::type::const_reference pair) -> void {
			serialized += std::string(level, '\t' ) + '"' + pair.first + "\" : " + Serializer::serialize(*(pair.second)) + (end ? ",\n" : ","); --end;
		      });
	serialized += "}\n";
	return serialized;
      }

      std::string	JSONSerialization::List(const std::list< std::unique_ptr<Serial> >& list) {
	std::string	serialized("[\n");
	std::size_t	end = list.size();

	std::for_each(list.begin(), list.end(), [this, &end, &serialized]
		      (typename std::remove_const< typename std::remove_reference< decltype(list) >::type >::type::const_reference value) -> void {
			serialized += std::string(level, '\t') + '"' + Serializer::serialize(*value) + (end ? ",\n" : "\n"); -- end;
		      });
	return serialized +  "}\n";
      }
      
      std::string	JSONSerialization::Map(const std::map< std::string, std::unique_ptr<Serial> >& map) {
	std::string	serialized("{[\n");
	std::size_t	end = map.size();

	std::for_each(map.begin(), map.end(), [this, &end, &serialized]
		      (typename std::remove_const< typename std::remove_reference<decltype(map)>::type >::type::const_reference pair) -> void {
			serialized += std::string(level, '\t' ) + '"' + pair.first + "\" : " + Serializer::serialize(*(pair.second)) + (end ? ",\n" : ","); --end;
		      });
	serialized += "]}\n";
	return serialized;
      }

      
      std::string	JSONSerialization::String(const std::string& string) {return '"' + string + '"';}
      std::string	JSONSerialization::Integer(long long value) {return std::to_string( value );}
      std::string	JSONSerialization::Floating(long double value) {return std::to_string ( value ) ;}

      
    };
  };
};
