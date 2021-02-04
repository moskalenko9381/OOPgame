#ifndef PLAYERSTRATEGY_H
#define PLAYERSTRATEGY_H
#include <iostream>

class Player;
class CellObject;

class PlayerStrategy
{
public:
    virtual ~PlayerStrategy(){};
    virtual void algorithm(CellObject* object, Player& player) const = 0;
    virtual const std::type_info& getStrategyType() = 0;
};

class WeaponStrategy: public PlayerStrategy{
    public:
        ~WeaponStrategy(){};
         void algorithm(CellObject* object, Player& player) const override;
         const std::type_info& getStrategyType() override{
                return typeid(WeaponStrategy);
         }
};

class CoinStrategy: public PlayerStrategy{
    public:
        ~CoinStrategy(){};
         void algorithm(CellObject* object, Player& player) const override;
         const std::type_info& getStrategyType() override{
                return typeid(CoinStrategy);
         }
};

class ExitStrategy: public PlayerStrategy{
    public:
        ~ExitStrategy(){};
         void algorithm(CellObject* object, Player& player) const override;
         const std::type_info& getStrategyType() override{
                return typeid(ExitStrategy);
         }
};

class WallStrategy: public PlayerStrategy{
    public:
        ~WallStrategy(){};
         void algorithm(CellObject* object, Player& player) const override;
         const std::type_info& getStrategyType() override{
                return typeid(WallStrategy);
         }
};

class VortexStrategy: public PlayerStrategy{
    public:
        ~VortexStrategy(){};
         void algorithm(CellObject* object, Player& player) const override;
         const std::type_info& getStrategyType() override{
                return typeid(VortexStrategy);
         }
};


#endif // PLAYERSTRATEGY_H
