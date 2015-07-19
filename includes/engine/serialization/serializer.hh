#ifndef Serializer_hh__
# define Serializer_hh__

# include <memory>
# include <list>
# include <map>
# include <string>

# include <typeinfo>

# include <ostream>

namespace laroue {
  namespace engine {
    namespace serialization {

      class Serial;

      class Serializer {	
      protected:
	std::string	_serialized;

      public:
	virtual ~Serializer() = default;
	Serializer() = default;

      protected:
	static const std::string	nameById(const std::type_info&);

      public:
	friend std::ostream&		operator << (std::ostream&, const Serializer&);
	const Serial&			operator << (const Serial&);

      protected:
	const std::string		serialize(const Serial&);

      public:
	virtual std::string	Object(const std::type_info&, const std::map< std::string, std::unique_ptr<Serial> >&) = 0;
	virtual std::string	List(const std::list< std::unique_ptr<Serial> >&) = 0;
	virtual std::string	Map(const std::map< std::string, std::unique_ptr<Serial> >&) = 0;

      public:
	virtual std::string	String(const std::string&) = 0;
	virtual std::string	Integer(long long) = 0;
	virtual std::string	Floating(long double) = 0;
      };

      inline std::ostream& operator << (std::ostream& stream, const Serializer& serializer) {
	return stream << serializer._serialized;
      }
    };
  };
};
#endif
