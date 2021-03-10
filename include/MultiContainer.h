
#include <map>
#include <set>
#include <memory>
#include <typeindex>
#include <optional>

namespace fsk
{
   struct IContainer
   {
   };

   template <typename T>
   struct Container : IContainer
   {
      std::set<T> m_values;
   };

   class MultiContainer
   {
   public:
      template <typename T>
      void Insert(const T &value)
      {
         auto itr = m_containers.find(std::type_index(typeid(T)));

         if (itr == std::cend(m_containers))
         {
            auto [ret, _] = m_containers.insert({std::type_index(typeid(T)), std::make_unique<Container<T>>()});
            itr = ret;
         }

         static_cast<Container<T> &>(*itr->second).m_values.insert(value);
      }

      template <typename T>
      std::optional<T> Find(const T &value) const
      {
         auto typeItr = m_containers.find(std::type_index(typeid(T)));

         if (typeItr == std::cend(m_containers))
         {
            return {};
         }

         const auto &values = static_cast<const Container<T> &>(*typeItr->second).m_values;

         if (auto itr = values.find(value);
             itr != std::cend(values))
         {
            return *itr;
         }

         return {};
      }

   private:
      std::map<std::type_index, std::unique_ptr<IContainer>> m_containers;
   };
}