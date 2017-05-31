#ifndef BASETOWER_H
#define BASETOWER_H

#include "cocos2d.h"
#include "Monster.h"

USING_NS_CC;

class BaseTower: public Sprite {
public:
	BaseTower();
	~BaseTower();

	bool init() override;

	enum TowerType {
		ARCHER, MILITIA, MAGE, BOMBARD
	};

private:
	// 类型
	CC_SYNTHESIZE(TowerType, type_, Type);
	// 名称
	CC_SYNTHESIZE(std::string, tower_name_, TowerName);
	// 等级
	CC_SYNTHESIZE(int, level_, Level);
	// 范围
	CC_SYNTHESIZE(float, scope_, Scope);
	// 升级后范围
	CC_SYNTHESIZE(float, next_scope_, NextScope);
	// 攻击速度
	CC_SYNTHESIZE(float, rate_, Rate);
	// 攻击力
	CC_SYNTHESIZE(int, power_, Power);
	// 升级所需金钱
	CC_SYNTHESIZE(int, upgrade_price_, UpgradePrice);
	// 售出时返还金钱
	CC_SYNTHESIZE(int, selling_price, SellingPrice);
	// 最近的敌人
	CC_SYNTHESIZE(Monster *, nearest_monster_, NearestMonster);

public:
	virtual void upgradeTower() = 0; 
	virtual void sellTower() = 0;
	virtual void removeTower() = 0;
	virtual void showTowerInfo() = 0; 
	virtual void upgradeOne() = 0;
	virtual void upgradeTwo() = 0;
	virtual void setRallyPoint(Vec2 pos) = 0;

protected:
	virtual void checkNearestMonster();//检测附近敌人  
	//virtual void showUpgradeMenu();//显示升级选项
	//virtual void hideUpgradeMenu();//隐藏
	//void setListener();//设置某些监听事件
};

#endif
