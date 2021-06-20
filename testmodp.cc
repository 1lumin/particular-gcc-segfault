module;

#include <functional>
#include <vector>
#include <variant>
#include <array>

export module testmodp;

export template<typename... Ts> // must be a template with args used in meta_variant for error to occur
struct testmodp{
    typedef std::variant<Ts...> meta_variant;
    std::vector<meta_variant> meta_gs;
};
