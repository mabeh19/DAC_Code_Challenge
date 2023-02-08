#pragma once
#include <exception>
#include <string>
#include "job.hpp"

#define BAD_FILE_MSG  "Bad file"

namespace DAC
{

class BadFileException: virtual public std::exception {

protected:
        std::string error_message;      ///< Error message

public:

        /** Constructor (C++ STL string, int, int).
     *  @param msg The error message
     */
        explicit 
        BadFileException(std::string& filePath):
                error_message(BAD_FILE_MSG)
        {
                error_message.append(": ");
                error_message.append(filePath);
        }

        explicit 
        BadFileException(const char* filePath):
                error_message(BAD_FILE_MSG)
        {
                error_message.append(": ");
                error_message.append(filePath);
        }



        /** Destructor.
     *  Virtual to allow for subclassing.
     */
        virtual ~BadFileException() throw () {}

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
