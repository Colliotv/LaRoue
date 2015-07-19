#include <iostream>
#include "engine/serialization/serial.hpp"
#include "engine/serialization/json.hh"
#include "engine/serialization/serializer.hh"

int main() {
  laroue::engine::serialization::Serial s( std::shared_ptr<std::string> {} );
  laroue::engine::serialization::JSONSerialization();
}
