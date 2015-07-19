#ifndef Json_hh__
# define Json_hh__

# include "serializer.hh"

namespace laroue {
  namespace engine {
    namespace serialization {

      class JSONSerialization : public Serializer {
      private:
	unsigned int	level;
	
      public:
	using Serializer::Serializer;
	virtual ~JSONSerialization() = default;
	
      public:
	std::string	Object(const std::type_info&, const std::map< std::string, std::unique_ptr<Serial> >&);
	std::string	List(const std::list< std::unique_ptr<Serial> >&);
	std::string	Map(const std::map< std::string, std::unique_ptr<Serial> >&);

      public:
	std::string	String(const std::string&);
	std::string	Integer(long long);
	std::string	Floating(long double);
      };

    };
  };
};

#endif
