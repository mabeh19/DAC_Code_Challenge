#pragma once
#include <exception>
#include <string>
#include "job.hpp"

#define ERR_MSG  "Circular dependency detected"

namespace DAC
{

class CircularDependencyException: virtual public std::exception {

protected:
        std::string error_message;      ///< Error message

public:

        /** Constructor (C++ STL string, int, int).
     *  @param msg The error message
     */
        explicit 
        CircularDependencyException():
                error_message(ERR_MSG)
        {}

        explicit CircularDependencyException(std::vector<Job> unsolvedDeps): error_message(ERR_MSG)
        {
                error_message.append("\nThe following jobs couldn't be solved:");
                for (Job j : unsolvedDeps) {
                        if (!j.IsSolved()) {
                                error_message.append("\n");
                                error_message.append(j.ToStringVerbose());
                                
                        }
                }
        }

        /** Destructor.
     *  Virtual to allow for subclassing.
     */
        virtual ~CircularDependencyException() throw () {}

        /** Returns a pointer to the (constant) error description.
     *  @return A pointer to a const char*. The underlying memory
     *  is in possession of the Except object. Callers must
     *  not attempt to free the memory.
     */
        virtual const char* what() const throw () {
                return error_message.c_str();
        }

#if 0
        /** Returns error number.
     *  @return #error_number
     */
        virtual int getErrorNumber() const throw() {
                return error_number;
        }

        /**Returns error offset.
     * @return #error_offset
     */
        virtual int getErrorOffset() const throw() {
                return error_offset;
        }
#endif
};
}
