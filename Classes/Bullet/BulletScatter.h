#pragma once
#include"Bullet.h"

class BulletScatter :public Bullet {
	int rotation;
	int flag;
	int v_x;
	int v_y;
public:
	virtual void update(float dt);
	static BulletScatter * createWithImage(int flag);
	void shootBulletFromTank(OurTank * tank);

};

BulletScatter * BulletScatter::createWithImage(int flag)
{
	
	BulletScatter * bullet = new BulletScatter();
	bullet->flag = flag;
	if (bullet && bullet->initWithFile("bullet7.png"))
	{
		bullet->autorelease();
		bullet->setVisible(false);

		//auto body = PhysicsBody::createBox(bullet->getContentSize());

		/* There are some temp value */
		//body->setCategoryBitmask(0);
		//body->setCollisionBitmask(0);
		//body->setContactTestBitmask(0);

		//bullet->setPhysicsBody(body);
		auto body = PhysicsBody::createEdgeBox(Size(16, 16),
			PHYSICSBODY_MATERIAL_DEFAULT, 2.0f, Vec2(0, 0));
		body->setCategoryBitmask(0x02);
		body->setContactTestBitmask(0x02);
		bullet->setPhysicsBody(body);
		bullet->setTag(2);
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}


void BulletScatter::shootBulletFromTank(OurTank * tank)
{
	switch (tank->getDirection())
	{
	case 146:
		switch (flag) {
		case 1:
			rotation = -45;
			v_x = -500;
			v_y = 500;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(0, tank->getContentSize().height / 2));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		case 2:
			rotation = 0;
			v_x = 0;
			v_y = 500;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(0, tank->getContentSize().height / 2));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		case 3:
			rotation = 45;
			v_x = 500;
			v_y = 500;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(0, tank->getContentSize().height / 2));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		}
		break;
	case 142:
		switch (flag) {
		case 1:
			rotation = 135;
			v_x = -500;
			v_y = -500;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(0, tank->getContentSize().height / 2));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		case 2:
			rotation = 180;
			v_x = 0;
			v_y = -500;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(0, tank->getContentSize().height / 2));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		case 3:
			rotation = 225;
			v_x = 500;
			v_y =-500;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(0, tank->getContentSize().height / 2));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		}
		
		break;
	case 124:
		switch (flag) {
		case 1:
			rotation = 225;
			v_x = -500;
			v_y = 500;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(0, tank->getContentSize().height / 2));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		case 2:
			rotation = 270;
			v_x = -500;
			v_y = 0;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(0, tank->getContentSize().height / 2));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		case 3:
			rotation = 315;
			v_x = -500;
			v_y = -500;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(0, tank->getContentSize().height / 2));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		}
		break;
	case 127:
		switch (flag) {
		case 1:
			rotation = 45;
			v_x = 500;
			v_y = 500;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(0, tank->getContentSize().height / 2));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		case 2:
			rotation = 90;
			v_x = 500;
			v_y = 0;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(0, tank->getContentSize().height / 2));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		case 3:
			rotation = 135;
			v_x = 500;
			v_y = -500;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(0, tank->getContentSize().height / 2));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		}
		
		break;
	}
	this->setVisible(true);
	this->scheduleUpdate();
	this->scheduleUpdate();
}
void BulletScatter::update(float dt)
{
	//coordinate transformation
	Vec2 pos = this->getPosition();
	int X = pos.x / 32;
	int Y = ((20 * 32) - pos.y) / 32;
	Sprite *mytile = walklay->getTileAt(Vec2(X, Y));
	Sprite *mycoll = coll->getTileAt(Vec2(X, Y));
	if (mytile != nullptr && mytile->isVisible() && this->isVisible() && mycoll) {
		mytile->setVisible(false);
		mycoll->removeFromParent();
		this->setVisible(false);
		this->removeFromParent();
		return;
	}
	Size screenSize = Director::getInstance()->getVisibleSize();
	this->setPosition(this->getPosition() + velocity * dt);
	int y = this->getPosition().y;
	int x = this->getPosition().x;
	if (y >= screenSize.height || y <= 0 || x >= screenSize.width || x <= 0)
	{
		this->setVisible(false);
		this->unscheduleUpdate();
		this->removeFromParent();
	}
}