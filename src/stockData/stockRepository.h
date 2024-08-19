#ifndef STOCKREPOSITORY_H
#define STOCKREPOSITORY_H

#include <list>
#include <memory>

#include "components/component.h"

namespace StockData
{
    class StockRepository final
    {
    public:
        using stockListType = std::list<std::shared_ptr<Component::Component>>;

    public:
        template <typename T>
        static int GetCountOfType() noexcept
        {
            if (stockList.empty())
            {
                FillStockList();
            }

            int count = 0;

            for (const auto& component : stockList)
            {
                if (dynamic_cast<const T*>(component.get()))
                {
                    count++;
                }
            }

            return count;
        }

        static const stockListType GetListOfType(const Component::ComponentType type) noexcept;

        static inline int GetTotalCount() noexcept
        {
            if (stockList.empty())
            {
                FillStockList();
            }

            return stockList.size();
        }

        static inline const stockListType& GetStockList() noexcept
        {
            if (stockList.empty())
            {
                FillStockList();
            }

            return stockList;
        }

    private:
        static void FillStockList() noexcept;
        static void AddToStockListByType(const Component::ComponentType type, const QStringList& substring) noexcept;

    private:
        static inline stockListType stockList;
    };
}
#endif // !STOCKREPOSITORY_H
