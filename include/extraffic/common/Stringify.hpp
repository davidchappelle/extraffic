#ifndef EXTRAFFIC_COMMON_STRINGIFY_HPP
#define EXTRAFFIC_COMMON_STRINGIFY_HPP


#include <cstddef>


namespace extraffic
{
namespace common
{


// This class provides a means to generically stringify types.
// It uses a fixed size buffer on the stack to perform the
// stringification and therefore can be used where once wants
// to avoid calling malloc (if required).
//
// TYPE
//
//     The object type being stringified.
//
// STORAGE_SIZE
//
//     The maximum length of the string to hold the stringified
//     representation of the object including the null terminator.
//
template <class TYPE, const size_t STORAGE_SIZE>
class Stringify
{
    private:
        // Storage for the resulting string including space
        // for the null terminator.
        char m_storage[STORAGE_SIZE];

    protected:
        // Returns a pointer to the underlying storage.
        inline char* storage()
        {
            return m_storage;
        }

        // Returns the storage size including the byte reserved
        // for null terminating the string.
        size_t storage_size() const
        {
            return sizeof(m_storage);
        }

        // Each derived stringfy type must implement this and
        // provide the conversion of the type into a string
        // placed into the memory location provided by storage().
        virtual const char* stringify(const TYPE* type) = 0;

    public:
        Stringify()
        {
            m_storage[0] = '\n';
        }

        virtual ~Stringify()
        {
        }

        inline const char* to_string(const TYPE& type)
        {
            return stringify(&type);
        }

        inline const char* to_string(const TYPE* type)
        {
            return stringify(type);
        }
};


} // namespace common
} // namespace extraffic


#endif
