#ifndef EXTRAFFIC_DATABASE_HPP
#define EXTRAFFIC_DATABASE_HPP


#include <boost/noncopyable.hpp>


namespace extraffic
{
namespace database
{


class Database : public boost::noncopyable
{
    public:
        Database();
        ~Database();
};


} // namespace database
} // namespace extraffic


#endif // EXTRAFFIC_DATABASE_HPP
