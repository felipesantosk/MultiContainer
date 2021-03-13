
#include <any>
#include <map>
#include <memory>
#include <optional>
#include <typeindex>

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
         auto itr = m_container.find( std::any_cast< CT::value_type >( filter ) );

         if( itr == std::cend( m_container ) )
         {
            return {};
         }

         return *itr;
      }

      CT m_container;
   };

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
