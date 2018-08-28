#include "GameScene.h"
#include "Gold.h"
#include "Bullet.h"
#include "VictoryLayer.h"

USING_NS_CC;
TMXTiledMap *Game::_tileMap = nullptr;
TMXLayer * EnemyAI::layer = nullptr;
Enemy * Game::enemy[10] = { NULL };
Sprite* Game::portal_1 = nullptr;
Sprite* Game::portal_2 = nullptr;
int Game::mapSizeHeight = 0;
int Game::mapSizeWidth = 0;
int Game::tileSize = 0;
bool Game::bVictory = false;

EnemyAI * Game::enemyAIs[10] = { nullptr };
int Game::nEnemy = 0;

int Game::nPickup = 0;

Size Game::_mapSize = Size(Vec2::ZERO);
Size Game::_tileSize = Size(Vec2::ZERO);

OurTank * Game::_player = nullptr;

Label *Game::lifeTTF = Label::create();
Label *Game::gradeTTF = Label::create();
Layer * Game::menuLayer = Layer::create();

Scene *Game::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
<<<<<<< HEAD

=======
>>>>>>> hbj
	auto layer = Game::create();
	scene->addChild(layer);
	return scene;
}

bool Game::init()
{
	if (!Layer::init())
	{
		return false;
	}

	for (int i = 0; i < 10; ++i)
	{
		enemyAIs[i] = nullptr;
	}
	nEnemy = 0;

	//gamescene = this;


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [this](PhysicsContact & contact)
	{
		log("onContactBegin");
		auto spriteA = (Sprite *)contact.getShapeA()->getBody()->getNode();
		auto spriteB = (Sprite *)contact.getShapeB()->getBody()->getNode();
		if (spriteA && spriteB)
		{
			//log("A: %d, B: %d", spriteA->getTag(), spriteB->getTag());
		}
		if (spriteA && spriteB && spriteA->getTag() == 3 && spriteB->getTag() == 2 && spriteA->isVisible())
		{
			((Enemy *)spriteA)->setHP(((Enemy *)spriteA)->getHP() - 1);
			if (((Enemy *)spriteA)->getHP() == 0)
			{
				spriteA->setVisible(false);
				spriteA->getPhysicsBody()->removeFromWorld();
				playBoomAnimation(spriteA->getPosition());
				nEnemy--;
			}
			spriteB->removeFromParent();
			//log("%d", nEnemy);
		}
		else if (spriteA && spriteB && spriteA->getTag() == 2 && spriteB->getTag() == 3 && spriteB->isVisible())
		{
			((Enemy *)spriteB)->setHP(((Enemy *)spriteB)->getHP() - 1);
			if (((Enemy *)spriteB)->getHP() == 0)
			{
				spriteB->setVisible(false);
				spriteB->getPhysicsBody()->removeFromWorld();
				playBoomAnimation(spriteA->getPosition());
				nEnemy--;
			}
			spriteA->removeFromParent();
			//log("%d", nEnemy);
		}
		else if (spriteA && spriteB && spriteA->getTag() == 1 && spriteB->getTag() == 6)
		{
			((PickupBase *)spriteB)->isContact((OurTank *)spriteA);
		}
		else if (spriteA && spriteB && spriteA->getTag() == 6 && spriteB->getTag() == 1)
		{
			((PickupBase *)spriteA)->isContact((OurTank *)spriteB);
		}
		else if (spriteA && spriteB && spriteA->getTag() == 1 && spriteB->getTag() == 2)
		{
			Game::_player->setHP(Game::_player->getHP() - 1);
			lifeTTF->setString(to_string(Game::_player->getHP()));
			//changeLifeTTF(Game::_player->getHP());
			spriteB->removeFromParent();
			//log("HP: %d", Game::_player->getHP());
			if (Game::_player->getHP() == 0)
			{
				auto layer = GameoverLayer::create();
				layer->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
					Director::getInstance()->getVisibleSize().height / 2));
				layer->setTag(99);
				Director::getInstance()->getRunningScene()->addChild(layer, 0);
				Director::getInstance()->pause();
			}
		}
		else if (spriteA && spriteB && spriteA->getTag() == 2 && spriteB->getTag() == 1)
		{
			Game::_player->setHP(Game::_player->getHP() - 1);
			lifeTTF->setString(to_string(Game::_player->getHP()));
			spriteA->removeFromParent();
			//log("HP: %d", Game::_player->getHP());
			if (Game::_player->getHP() == 0)
			{
				auto layer = GameoverLayer::create();
				layer->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
					Director::getInstance()->getVisibleSize().height / 2));
				layer->setTag(99);
				Director::getInstance()->getRunningScene()->addChild(layer);
				Director::getInstance()->pause();
			}
		}
		else if (spriteA && spriteB && spriteA->getTag() == 200 && spriteB->getTag() == 2 && spriteB->isVisible()) {
			spriteB->removeFromParent();
		}
		else if (spriteA && spriteB && spriteA->getTag() == 2 && spriteB->getTag() == 200 && spriteA->isVisible()) {
			spriteA->removeFromParent();
		}
		else if (spriteA && spriteB  && (spriteA->getTag()==3|| spriteA->getTag() == 1)&&spriteB->getTag() == 11 && spriteA->isVisible()) {
				spriteA->setPosition(portal_2->getPosition()+ ((OurTank *)spriteA)->getVel()*3/10);	
		}
		else if (spriteA && spriteB  && spriteA->getTag() == 11 && (spriteB->getTag() == 3 || spriteB->getTag() == 1) &&spriteB->isVisible()) {
			spriteB->setPosition(portal_2->getPosition() + ((OurTank *)spriteB)->getVel() * 3 / 10);
		}
		else if (spriteA && spriteB  && spriteB->getTag() == 12 && (spriteA->getTag() == 3 || spriteA->getTag() ==1) &&spriteA->isVisible()) {
			spriteA->setPosition(portal_1->getPosition() + ((OurTank *)spriteA)->getVel() * 3 / 10);
		}
		else if (spriteA && spriteB  && spriteA->getTag() == 12 && (spriteB->getTag() == 3 || spriteB->getTag() == 1) && spriteB->isVisible()) {
			spriteB->setPosition(portal_1->getPosition() + ((OurTank *)spriteB)->getVel() *3 / 10);
		}
		else if (spriteA && spriteB && (spriteA->getTag() == 2) && spriteB->getTag() == 11 && spriteA->isVisible()) {
			spriteA->setPosition(portal_2->getPosition() + ((Bullet *)spriteA)->getVel()  / 8.3);
		}
		else if (spriteA && spriteB  && spriteA->getTag() == 11 && (spriteB->getTag() == 2) && spriteB->isVisible()) {
			spriteB->setPosition(portal_2->getPosition() + ((Bullet *)spriteB)->getVel()  / 8.3);
		}
		else if (spriteA && spriteB  && spriteB->getTag() == 12 && (spriteA->getTag() == 2 ) && spriteA->isVisible()) {
			spriteA->setPosition(portal_1->getPosition() + ((Bullet *)spriteA)->getVel()  / 8.3);
		}
		else if (spriteA && spriteB  && spriteA->getTag() == 12 && (spriteB->getTag() == 2 ) && spriteB->isVisible()) {
			spriteB->setPosition(portal_1->getPosition() + ((Bullet *)spriteB)->getVel() /8.3);
		}
		//else if (spriteA && spriteB && spriteA->getTag() == 1 && spriteB->getTag() == 3)
		//{
		//	spriteA->pause();
		//	spriteA->unschedule(schedule_selector(Game::keepMoving));
		//}
		//else if (spriteA && spriteB && spriteA->getTag() == 3 && spriteB->getTag() == 1)
		//{
		//	spriteB->pause();
		//}
		if (nEnemy == 0) {
			Game::bVictory = true;
		}

		return true;
	};

	listener->onContactSeparate = [](PhysicsContact & contact)
	{
		log("onContactSeparate");
		auto spriteA = (Sprite *)contact.getShapeA()->getBody()->getNode();
		auto spriteB = (Sprite *)contact.getShapeB()->getBody()->getNode();
		//if (spriteA && spriteB && spriteA->getTag() == 1 && spriteB->getTag() == 3)
		//{
		//	spriteA->resume();
		//}
		//else if (spriteA && spriteB && spriteA->getTag() == 3 && spriteB->getTag() == 1)
		//{
		//	spriteB->resume();
		//}
		return true;
	};

	listener->onContactPreSolve = [](PhysicsContact & contact, PhysicsContactPreSolve & solve)
	{
		return true;
	};

	listener->onContactPostSolve = [](PhysicsContact & contact, const PhysicsContactPostSolve & solve)
	{

	};

	menuLayer = Layer::create();
	auto text1 = Label::createWithTTF(MyUtility::gbk_2_utf8("HP��    ���֣�"), "fonts/minijtj.ttf", 40);
	text1->setAnchorPoint(Vec2(0, 0));
	text1->setPosition(Vec2(10, 10));
	text1->setColor(Color3B(255, 255, 255));
	menuLayer->addChild(text1);
	lifeTTF = Label::createWithTTF(MyUtility::gbk_2_utf8("0"), "fonts/minijtj.ttf", 40);
	lifeTTF->setAnchorPoint(Vec2(0, 0));
	lifeTTF->setPosition(Vec2(100, 10));
	lifeTTF->setColor(Color3B(255, 255, 255));
	menuLayer->addChild(lifeTTF);
	gradeTTF = Label::createWithTTF(MyUtility::gbk_2_utf8("0"), "fonts/minijtj.ttf", 40);
	gradeTTF->setAnchorPoint(Vec2(0, 0));
	gradeTTF->setPosition(Vec2(300, 10));
	gradeTTF->setColor(Color3B(255, 255, 255));
	menuLayer->addChild(gradeTTF);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

	string s1 = to_string(levelNum), s2 = "map/map" + s1 + ".tmx";
	_tileMap = TMXTiledMap::create(s2);
	_mapSize = _tileMap->getMapSize();
	_tileSize = _tileMap->getTileSize();

	mapSizeHeight = _mapSize.height;
	mapSizeWidth = _mapSize.width;
	tileSize = _tileSize.width;

	Bullet::_breakable0 = _tileMap->getLayer("breakable0");
	Bullet::_breakable1 = _tileMap->getLayer("breakable1");
	tileX = _tileMap->getTileSize().width;
	tileY = _tileMap->getTileSize().height;
	mapX = _tileMap->getMapSize().width;
	mapY = _tileMap->getMapSize().height;

	this->addChild(_tileMap);


	TMXObjectGroup *group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint_0 = group->getObject("playerA");
	ValueMap spawnPoint_portal_1 = group->getObject("portal_1");
	ValueMap spawnPoint_portal_2;

	int x1, x2, y1, y2;
	if (spawnPoint_portal_1 != ValueMap()) {
		spawnPoint_portal_2 = group->getObject("portal_2");
		x1=spawnPoint_portal_1 ["x"].asInt();
		y1= spawnPoint_portal_1["y"].asInt();
		x2 = spawnPoint_portal_2["x"].asInt();
		y2 = spawnPoint_portal_2["y"].asInt();
		portal_1 = Sprite::create("Door.png");
		portal_2 = Sprite::create("Door.png");
		portal_1->setPosition(Vec2(x1, y1));
		portal_2->setPosition(Vec2(x2, y2));
		portal_1->setTag(11);
		portal_2->setTag(12);
		this->addChild(portal_1);
		this->addChild(portal_2);
		auto body1 = PhysicsBody::createEdgeBox(portal_1->getContentSize());
		body1->setCategoryBitmask(0xff);
		body1->setContactTestBitmask(0xff);
		body1->setCollisionBitmask(0x00);
		portal_1->setPhysicsBody(body1);
		auto body2 = PhysicsBody::createEdgeBox(portal_2->getContentSize());
		body2->setCategoryBitmask(0xff);
		body2->setContactTestBitmask(0xff);
		body2->setCollisionBitmask(0x00);
		portal_2->setPhysicsBody(body2);
	}

	int  x0 = spawnPoint_0["x"].asInt();
	int  y0 = spawnPoint_0["y"].asInt();
	EnemyAI::layer = _collidable;

	_player = OurTank::createWithImage(3);
	string slife = to_string(3);
	lifeTTF->setString(slife);
	_player->setAnchorPoint(Vec2(0.5, 0.5));
	_player->setPosition(Vec2(x0, y0));
	addChild(_player);
	this->setViewpointCenter(Vec2(x0, y0));
	//log("%f,%f", viewPoint.x, viewPoint.y);
	//this->setPosition(Vec2(200, 200));


	/**/
	_player->addenemy();
	_player->addpickup();
	_player->setTag(1);

	if (levelNum == 5)
	{
		srand(time(NULL));
		for (int i = 0; i < nEnemy; ++i)
		{
			if (rand() % 10 >= 5)
			{
				enemy[i]->setOpacity(50);
			}
		}
	}
	for (int i = 0; i < nEnemy; ++i)
	{
		int nType = rand() % 5;
		switch (nType)
		{
		case 0:
			enemy[i]->setWeaponType(WEAPON_0);
			break;
		case 1:
			enemy[i]->setWeaponType(WEAPON_1);
			break;
		case 2:
			enemy[i]->setWeaponType(WEAPON_2);
			break;
		case 3:
			enemy[i]->setWeaponType(WEAPON_3);
			break;
		case 4:
			enemy[i]->setWeaponType(WEAPON_4);
			break;
		}
	}
	/*enemy[0]->scheduleUpdate();*/
	_collidable = _tileMap->getLayer("collidable");
	Bullet::coll = _collidable;

	EnemyAI::layer = _collidable;

	Vec2 playerPos = _player->getPosition();


	setKeyboardEnabled(true);

	this->scheduleUpdate();


	//menuLayer->runAction(MoveTo::create(0.2, -viewPoint));
	menuLayer->setPosition(Vec2(0, 0));
	this->addChild(menuLayer);
	auto itemPause = MenuItemImage::create("UI/menu_pause.png", "UI/menu_pause1.png",
		CC_CALLBACK_1(Game::menuItemCallbackPause, this));
	itemPause->setOpacity(200);
	itemPause->setAnchorPoint(Vec2(0, 0));
	itemPause->setPosition(Vec2(0, visibleSize.height - itemPause->getContentSize().height));
	auto menu = Menu::create(itemPause, NULL);
	menu->setPosition(Vec2::ZERO);
	menuLayer->addChild(menu);
	//log("%f,%f", menuLayer->getPosition().x, menuLayer->getPosition().y);
	//log("%d,%d",this->getPosition().x,this->getPosition().y);


	log("There are %d enemys ***************************", nEnemy);

	//this->setScale(1.2);

	return true;
}

void Game::setPlayerPosition(Vec2 position)
{
	Size screenSize = Director::getInstance()->getVisibleSize();
	if (position.y > tileY*mapY || position.y < 0 || position.x > tileX*tileX || position.x < 0)
	{
		return;
	}
	Vec2 tileCoord = this->tileCoordFromPosition(position);
	int tileGid = _collidable->getTileGIDAt(tileCoord);
	if (tileGid > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();
		std::string collision = propValueMap["collidable"].asString();
		if (collision == "true") {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.mp3");
			return;
		}

	}
	_player->runAction(MoveTo::create(0.2, position));
}
Vec2 Game::tileCoordFromPosition(Vec2 pos) {
	int x = (int)pos.x / tileX;
	int y = (int)(mapY*tileY - pos.y) / tileY;
	return Vec2(x, y);
}

void Game::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	log("%d has been pressed", keyCode);
	Vec2 playerPos = _player->getPosition();
	if ((int)keyCode == 59)
	{
		if (_player->mydt < 0) {
			_player->openFire(true);
			_player->mydt = 1;
		}
		return;
	}
	if ((int)keyCode == 129)
	{
		_player->useSkill();
		return;
	}
	if ((int)keyCode != _player->getDirection())
	{
		switch ((int)keyCode)
		{
		case 146:
			_player->runAction(RotateTo::create(0.2, 0));
			_player->setVel(Vec2(0, _player->nVel));
			break;
		case 142:
			_player->runAction(RotateTo::create(0.2, 180));
			_player->setVel(Vec2(0, -_player->nVel));
			break;
		case 124:
			_player->runAction(RotateTo::create(0.2, 270));
			_player->setVel(Vec2(-_player->nVel, 0));
			break;
		case 127:
			_player->runAction(RotateTo::create(0.2, 90));
			_player->setVel(Vec2(_player->nVel, 0));
			break;
		}
		_player->setDirection((int)keyCode);
	}

	if (!isMoveable(playerPos)) return;
	this->setViewpointCenter(playerPos);

	this->schedule(schedule_selector(Game::keepMoving), 1.0/60);
}

void Game::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	if ((int)keyCode == _player->getDirection())
		this->unschedule(schedule_selector(Game::keepMoving));
}

void Game::keepMoving(float dt)
{
	//log("dt : %f", dt);
	//log("getContantSize : %d, %d", _player->getContentSize().width, _player->getContentSize().height);
	auto playerSize = Size(Vec2(40, 40));

	Vec2 playerPos = _player->getPosition() + _player->getVel() * dt;
	Vec2 forwardLeft = playerPos;
	Vec2 forwardRight = playerPos;

	switch (_player->getDirection())
	{
	case 146:
		forwardLeft += Vec2(-playerSize.width / 2, playerSize.height / 2 + 1);
		forwardRight += Vec2(playerSize.width / 2, playerSize.height / 2 + 1);
		break;
	case 142:
		forwardLeft += Vec2(playerSize.width / 2, -playerSize.height / 2 - 1);
		forwardRight += Vec2(-playerSize.width / 2, -playerSize.height / 2 - 1);
		break;
	case 127:
		forwardLeft += Vec2(playerSize.width / 2 + 1, playerSize.height / 2);
		forwardRight += Vec2(playerSize.width / 2 + 1, -playerSize.height / 2);
		break;
	case 124:
		forwardLeft += Vec2(-playerSize.width / 2 - 1, -playerSize.height / 2);
		forwardRight += Vec2(-playerSize.width / 2 - 1, playerSize.height / 2);
		break;
	}

	if (!isMoveable(forwardLeft) || !isMoveable(forwardRight))
		return;

	this->setViewpointCenter(playerPos);

	_player->runAction(MoveTo::create(0, playerPos));

	//this->setPlayerPosition(playerPos);

}

void Game::update(float dt)
{
	_player->mydt -= dt;
	if (bVictory)
	{
		bVictory = false;
		auto layer = VictoryLayer::create();
		layer->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
			Director::getInstance()->getVisibleSize().height / 2));
		layer->setTag(99);
		menuLayer->addChild(layer, 5);
		Director::getInstance()->pause();
	}
	for (int i = 0; enemyAIs[i]; ++i)
	{
		enemyAIs[i]->update(dt);
	}
}

void Game::menuItemCallbackPause(Ref * pSender)
{
	static bool isPause = false;
	if (!isPause)
	{
		auto layer = PauseLayer::create();
		layer->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
			Director::getInstance()->getVisibleSize().height / 2));
		layer->setTag(13);
		menuLayer->addChild(layer);
		isPause = true;
		Director::getInstance()->pause();
	}
	else
	{
		menuLayer->removeChildByTag(13);
		Director::getInstance()->resume();
		isPause = false;
	}
}

void Game::setViewpointCenter(Point position) {
	auto winSize = Director::getInstance()->getWinSize();
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	auto mapSize = _tileMap->getMapSize();
	auto tileSize = _tileMap->getTileSize();

	x = MIN(x, mapSize.width*tileSize.width - winSize.width / 2);
	y = MIN(y, mapSize.height*tileSize.height - winSize.height / 2);

	auto centerPoint = Point(winSize.width / 2, winSize.height / 2);
	auto actualPoint = Point(x, y);
	viewPoint = centerPoint - actualPoint;


	this->runAction(MoveTo::create(0, viewPoint));
	//log("%f,%f", this->getPosition().x, this->getPosition().y);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	menuLayer->runAction(MoveTo::create(0, -viewPoint));
}

bool Game::isMoveable(Vec2 position) {
	Size screenSize = Director::getInstance()->getVisibleSize();
	if (position.y > tileY*mapY || position.y < 0 || position.x > tileX*mapX || position.x < 0)
	{
		return false;
	}
	Vec2 tileCoord = this->tileCoordFromPosition(position);
	//log("%f, %f", tileCoord.x, tileCoord.y);
	int tileGid = _collidable->getTileGIDAt(tileCoord);
	if (tileGid > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();
		std::string collision = propValueMap["collidable"].asString();
		if (collision == "true") {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.mp3");
			return false;
		}
	}
	return true;
}

void Game::changeLifeTTF(int lifeNum) {
	if (lifeNum < 0) lifeNum = 0;
	lifeTTF->setString(to_string(lifeNum));
}

void Game::playBoomAnimation(Vec2 position) {
	auto dic = Dictionary::createWithContentsOfFile("animation/boom.plist");
	auto frameDic = (__Dictionary*)dic->objectForKey("frames");
	int num = frameDic->allKeys()->count();
	Vector<SpriteFrame*> sfme = Vector<SpriteFrame*>::Vector();
	CCSpriteFrameCache * cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("animation/boom.plist");
	for (int i = 0; i < num; i++) {
		char frame[50];
		sprintf(frame, "%d.png", i + 1);
		auto frameName = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frame);
		sfme.pushBack(frameName);
	}
	auto animation = Animation::createWithSpriteFrames(sfme, 0.1);
	auto animate = Animate::create(animation);
	auto sp = Sprite::create();
	sp->setPosition(Vec2(position.x, position.y));
	sp->runAction(animate);
	_player->getParent()->addChild(sp);
	//this->addChild(sp);
}

