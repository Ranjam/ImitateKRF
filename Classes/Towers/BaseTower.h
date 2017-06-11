#ifndef __BASETOWER_H__
#define __BASETOWER_H__

#include "cocos2d.h"
#include "Monsters/Monster.h"

USING_NS_CC;

class BaseTower: public Sprite {

public:
	enum TowerType {
		ARCHER, MILITIA, MAGE, BOMBARD, UNDEFINED
	};

public:
	explicit BaseTower(TowerType type = UNDEFINED, 
			  std::string name = "", 
			  int level = 0,
			  float scope = 0,
			  float next_scope = 0,
			  float rate = 0,
			  float power = 0,
			  int upgrade_price = 0,
			  int selling_price = 0,
			  Monster *nearest_monster = nullptr);
	~BaseTower();

	bool init() override;


private:
	// tower type
	CC_SYNTHESIZE(TowerType, type_, Type);
	// tower name
	CC_SYNTHESIZE(std::string, tower_name_, TowerName);
	// tower level
	CC_SYNTHESIZE(int, level_, Level);
	// attack scope
	CC_SYNTHESIZE(float, scope_, Scope);
	// next level scope
	CC_SYNTHESIZE(float, next_scope_, NextScope);
	// attack speed
	CC_SYNTHESIZE(float, rate_, Rate);
	// power
	CC_SYNTHESIZE(float, power_, Power);
	// price
	CC_SYNTHESIZE(int, upgrade_price_, UpgradePrice);
	// selling price
	CC_SYNTHESIZE(int, selling_price, SellingPrice);
	// target monster
	CC_SYNTHESIZE(Monster *, nearest_monster_, NearestMonster);

public:
	virtual void attack(float dt) = 0;
	virtual void upgradeTower() = 0; 
	virtual void sellTower() = 0;
	virtual void removeTower() = 0;
	virtual void showTowerInfo() = 0; 
	virtual void hideTowerInfo() = 0;
	virtual void upgradeOne() = 0;
	virtual void upgradeTwo() = 0;
	virtual void setRallyPoint(Vec2 pos) = 0;
	virtual void buildingAnimation() = 0;
	virtual void buildingSmokeAnimation() = 0;

protected:
	virtual void checkNearestMonster();//检测附近敌人
	virtual void initTower(int level) = 0;
	//virtual void showUpgradeMenu();//显示升级选项
	//virtual void hideUpgradeMenu();//隐藏
	//void setListener();//设置某些监听事件
};

#endif
