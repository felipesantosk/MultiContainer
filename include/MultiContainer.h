#pragma once

#include "Container.h"

#include <map>
#include <memory>
#include <optional>
#include <typeindex>

namespace fsk
{
   class MultiContainer
   {
    public:
      template< typename CT > void InsertTypeSlot()
      {
         m_containers[std::type_index( typeid( CT::value_type ) )] = std::make_unique< Container< CT > >();
      }

      template< typename T > void Insert( const T &value )
      {
         auto itr = m_containers.find( std::type_index( typeid( T ) ) );

         if( itr != std::cend( m_containers ) )
         {
            itr->second->Insert( value );
         }
      }

      template< typename T > std::optional< T > Find( const T &value ) const
      {
         auto typeItr = m_containers.find( std::type_index( typeid( T ) ) );

         if( typeItr == std::cend( m_containers ) )
         {
            return {};
         }

         auto obj = typeItr->second->Find( value );

         if( obj.has_value() )
         {
            return std::any_cast< T >( obj );
         }

         return {};
      }

    private:
      std::map< std::type_index, std::unique_ptr< IContainer > > m_containers;
   };
} // namespace fsk
