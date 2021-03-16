#pragma once

#include <any>
#include <vector>

namespace fsk
{
   struct IContainer
   {
      virtual void Insert( const std::any &object ) = 0;
      virtual std::any Find( const std::any &filter ) = 0;
   };

   template< typename CT > struct Container : IContainer
   {
      void Insert( const std::any &object ) override
      {
         m_container.insert( std::any_cast< CT::value_type >( object ) );
      }

      std::any Find( const std::any &filter ) override
      {
         const auto itr = std::find( std::cbegin( m_container ), std::cend( m_container ),
                                     std::any_cast< CT::value_type >( filter ) );

         return ( itr == std::cend( m_container ) ) ? std::any() : *itr;
      }

      CT m_container;
   };
} // namespace fsk
