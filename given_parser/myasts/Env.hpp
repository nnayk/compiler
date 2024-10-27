#ifndef ENV_HPP
#define ENV_HPP
#include <memory>
#include <string>
#include "Type.hpp"
#include <fmt/core.h>
#include <fmt/format.h>

#include <iostream>
class Env;

class Entry {
public:
    std::shared_ptr<ast::Type> type;
    int is_global = 0;
    int scope = 2; // 0 = local, 1 = param, 2 = global
    // Constructor
    Entry(std::shared_ptr<ast::Type> t);
   // Virtual destructor
    virtual ~Entry() = default; // Ensure proper cleanup of derived classes
};

class AttrEntry : public Entry {
public:
    int offset; // offset in the struct
    // Constructor
    AttrEntry(std::shared_ptr<ast::Type> t, int offset): Entry(t), offset(offset) {}
};
class StructEntry : public Entry {
public:
    int size = 0; // size of struct in bytes (no padding)
    std::shared_ptr<Env> attrEnv = nullptr; // used to track struct attributes
    // Constructor
    StructEntry(std::shared_ptr<ast::Type> t,int size): Entry(t), size(size) { std::cout << "FOO";}
};
class Env {
public:
    std::unordered_map<std::string,std::shared_ptr<Entry>> bindings;
    // Constructor
    Env();
    void addBinding(const std::string &key,std::shared_ptr<Entry> entry);
    std::shared_ptr<Entry> lookup(const std::string &id);
    void display(); 
};

template <>
struct fmt::formatter<Entry> : fmt::formatter<std::string> {
	auto format(const Entry &entry, fmt::format_context &ctx) const -> decltype(ctx.out()) {
		return fmt::format_to(ctx.out(), "Entry with type: {}", *entry.type); // Assuming type can be formatted
	}
};
template<>
struct fmt::formatter<AttrEntry> : fmt::formatter<std::string> {
    auto format(const AttrEntry &attrEntry, fmt::format_context &ctx) const -> decltype(ctx.out()) {
        auto out = ctx.out();
        // Use the formatter for the base class Entry
        out = fmt::format_to(out, "AttrEntry -> ");
        fmt::formatter<Entry> entryFormatter;
        out = entryFormatter.format(attrEntry, ctx);
        // Format the offset specific to AttrEntry
        out = fmt::format_to(out, "Offset: {}\n", attrEntry.offset);
        return out;
    }
};

template<>
struct fmt::formatter<StructEntry> : fmt::formatter<std::string> {
    auto format(const StructEntry &structEntry, fmt::format_context &ctx) const -> decltype(ctx.out()) {
        auto out = ctx.out();
        // Use the formatter for the base class Entry
        out = fmt::format_to(out, "StructEntry -> ");
        fmt::formatter<Entry> entryFormatter;
        out = entryFormatter.format(structEntry, ctx);
        // Format the Env object (assuming Env has a formatter)
		out = fmt::format_to(out,"\nNumber of attributes: {}", structEntry.attrEnv->bindings.size());
        if (structEntry.attrEnv) {
			// TODO: couldn't get the fwd declaration of Env formatter to work
            //out = fmt::format_to(out, "Attributes Env:\n{}\n", *structEntry.attrEnv);
        } else {
            out = fmt::format_to(out, "Attributes Env: nullptr\n");
        }
        return out;
    }
};
template<>
struct fmt::formatter<Env> : fmt::formatter<std::string> {
   auto format(const Env &env, format_context &ctx) const ->decltype(ctx.out()) {
 // Start formatting the output
        auto out = ctx.out();
        // Format the number of bindings
        out = fmt::format_to(out, "Number of bindings: {}\n", env.bindings.size());
        // Loop through the bindings
        for (const auto& [key, entryPtr] : env.bindings) {
            // Format each key
            out = fmt::format_to(out, "Key: {}\n", key);
            // Format the entries for this key (assuming we have an appropriate formatter for Entry)
				if (auto structEntry = std::dynamic_pointer_cast<StructEntry>(entryPtr)) {
					// Format as StructEntry
					out = fmt::format_to(out, "  StructEntry: {}\n", *structEntry);
				} else if (auto attrEntry = std::dynamic_pointer_cast<AttrEntry>(entryPtr)) {
					// Format as AttrEntry
					out = fmt::format_to(out, "  AttrEntry: {}\n", *attrEntry);
				} else {
					// Default case for Entry
					out = fmt::format_to(out, "  Entry: {}\n", *entryPtr);
				}
        }
        return out;
   }
};
#endif
