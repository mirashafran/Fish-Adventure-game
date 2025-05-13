#include <stdexcept>
#include <iostream>

// Exception class for texture loading errors
class LoadException : public std::runtime_error {
    public:
        explicit LoadException(const std::string& filename) : std::runtime_error("Failed to load: " + filename) {}
};

