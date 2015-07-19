#ifndef Serializable_hh__
# define Serializable_hh__

# include <string>
# include <typeinfo>

namespace laroue {
  namespace engine {
    namespace serialization {

      class SerializedObject;
      class Serializer;
      class Serializable;
      
      class SerializableIndex {
	friend class Serializable;
      private:
	inline static std::map<const std::type_info*, std::string>&	gIdName() {
	  static std::map<const std::type_info*, std::string>	IdName;
	  return IdName;
	}

	inline static std::map<const std::type_info*,
			       std::function<Serializable*(SerializedObject)> >& gIdNew() {
	  static std::map<const std::type_info*,
			  std::function<Serializable*(SerializedObject)> > IdNew;
	  return IdNew;
	}

	inline static std::map<std::string,
			       std::function<Serializable*(SerializedObject)> >& gNameNew() {
	  static std::map<std::string,
			  std::function<Serializable*(SerializedObject)> > NameNew;
	  return NameNew;
	}

      };
      
      class Serializable {
      private:
	friend class Serializer;
	static const std::string	nameById(const std::type_info& ti) {
	  return SerializableIndex::gIdName()[&ti];
	}

      private:
	static Serializable*		allocateById(const std::string&);
	static Serializable*		allocateByName(const std::string&);

      };
    };
  };
};

#endif
