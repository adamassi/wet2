#ifndef WET2_EXCEPTIONS_H
#define WET2_EXCEPTIONS_H

#include <exception>

class Exception : public std::exception {
};

class NodeAlreadyExists : public Exception {
};

class NodeDoesntExists : public Exception {
};

#endif //WET2_EXCEPTIONS_H
