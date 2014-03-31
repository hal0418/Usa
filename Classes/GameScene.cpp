#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

CCScene* GameScene::scene()
{
	CCScene* scene = CCScene::create();
	GameScene* layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	this->removeAllChildrenWithCleanup(true);
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
	title = false;
	caution = false;
	stage = false;
	showTitle();
	daycount = 1;
	usacount = 1;
	okamicount = 1;
	okaminumber = 0;
	usa3 = false;
	usa9 = false;
	listen = false;
	countdown = false;
	arrow = false;
	kill3 = false;
	kill9 = false;
	rope = false;
	nextstage = false;
	gameover = false;
	nextday = false;
	okamiSet();

	SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
	SimpleAudioEngine::sharedEngine()->preloadEffect(MURA_3);
	SimpleAudioEngine::sharedEngine()->preloadEffect(MURA_9);
	SimpleAudioEngine::sharedEngine()->preloadEffect(OKAMI_3);
	SimpleAudioEngine::sharedEngine()->preloadEffect(OKAMI_9);

	touch = true;

	return true;
}

void GameScene::okamiSet()
{
	srand((unsigned int)time(NULL));
	int i = rand() % 2;

	if(i==0)
	{
		okaminumber = 9;
		CCLog("9");
	}
	else
	{
		okaminumber = 3;
		CCLog("3");
	}
}

void GameScene::showTitle()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_title = CCSprite::create(TITLE);
	m_title->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	m_title->setOpacity(0);
	addChild(m_title, kZOrderBase, kTagBase);
	title = true;
	CCFadeIn* fi = CCFadeIn::create(0.5);
	m_title->runAction(fi);
}

void GameScene::showCaution()
{
	touch = true;
	if(title)
	{
		m_title->removeFromParentAndCleanup(true);
		title = false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_caution = CCSprite::create(CAUTION);
	m_caution->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	m_caution->setOpacity(0);
	addChild(m_caution, kZOrderBase, kTagBase);
	caution = true;
	CCFadeIn* fi = CCFadeIn::create(0.5);
	m_caution->runAction(fi);
}

void GameScene::showStage()
{
	touch = true;
	if(caution)
	{
		m_caution->removeFromParentAndCleanup(true);
		caution = false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_stage = CCSprite::create(STAGE_1);
	m_stage->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	m_stage->setOpacity(0);
	addChild(m_stage, kZOrderBase, kTagBase);
	stage = true;
	CCFadeIn* fi = CCFadeIn::create(0.5);
	m_stage->runAction(fi);
}

void GameScene::showBase()
{
	touch = true;
	if(stage)
	{
		m_stage->removeFromParentAndCleanup(true);
		stage = false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_base = CCSprite::create(BASE);
	m_base->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	m_base->setOpacity(0);
	addChild(m_base, kZOrderBase, kTagBase);

	m_sd111 = CCSprite::create(DAY);
	m_sd111->setPosition(ccp(winSize.width / 10, winSize.height / 10*8));
	m_sd111->setOpacity(0);
	addChild(m_sd111, kZOrderBase1, kTagBase1);

	m_list = CCSprite::create(LIST_1);
	m_list->setPosition(ccp(winSize.width / 10*9, winSize.height / 10*8));
	m_list->setOpacity(0);
	addChild(m_list, kZOrderBase1, kTagBase1);

	CCFiniteTimeAction* fi = CCFadeTo::create(0.5, 96);
	CCFadeIn* fi2 = CCFadeIn::create(0.5);
	CCFadeIn* fi3 = CCFadeIn::create(0.5);
	//m_base->runAction(fi);
	m_sd111->runAction(fi2);
	m_list->runAction(fi3);

	CCCallFunc* cf = CCCallFunc::create(this, callfunc_selector(GameScene::showUsa));
	CCSequence* sq = CCSequence::create(fi, cf, NULL);
	m_base->runAction(sq);
}

void GameScene::showUsa()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_usa9 = CCSprite::create(WHITE);
	m_usa9->setPosition(ccp(winSize.width / 10*2, winSize.height / 2));
	m_usa9->setOpacity(0);
	addChild(m_usa9, kZOrderUsa, kTagUsa);
	usa9 = true;
	m_usa3 = CCSprite::create(WHITE);
	m_usa3->setPosition(ccp(winSize.width / 10*8, winSize.height / 2));
	m_usa3->setOpacity(0);
	addChild(m_usa3, kZOrderUsa, kTagUsa);
	usa3 = true;
	m_listen = CCSprite::create(LISTEN);
	m_listen->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	m_listen->setOpacity(0);
	addChild(m_listen, kZOrderListen, kTagListen);
	listen = true;
	CCFadeIn* fi = CCFadeIn::create(0.5);
	CCFadeIn* fi2 = CCFadeIn::create(0.5);
	CCFadeIn* fi3 = CCFadeIn::create(0.5);
	m_usa9->runAction(fi);
	m_usa3->runAction(fi2);
	m_listen->runAction(fi3);
}

void GameScene::showCountdown()
{
	if(listen)
	{
		m_listen->removeFromParentAndCleanup(true);
		listen = false;
	}
	countdown = true;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_yaku = CCSprite::create(YAKUSYOKU);
	m_yaku->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	m_yaku->setOpacity(0);
	addChild(m_yaku, kZOrderListen, kTagListen);
	CCFadeIn* fi = CCFadeIn::create(1.5);
	CCFadeOut* fo = CCFadeOut::create(1.5);
	CCSequence* sq = CCSequence::create(fi, fo, NULL);
	m_yaku->runAction(sq);

	m_count3 = CCSprite::create(COUNT3);
	m_count3->setPosition(ccp(winSize.width / 2, winSize.height / 20*9));
	addChild(m_count3, kZOrderListen, kTagListen);
	CCFadeOut* fo2 = CCFadeOut::create(1.0);
	CCFiniteTimeAction* sc = CCScaleTo::create(1, 0.5);
	CCSpawn* sp = CCSpawn::createWithTwoActions(fo2, sc);
	m_count3->runAction(sp);

	m_count2 = CCSprite::create(COUNT2);
	m_count2->setPosition(ccp(winSize.width / 2, winSize.height / 20*9));
	m_count2->setOpacity(0); //‚ [‚ [
	addChild(m_count2, kZOrderListen, kTagListen);
	CCFadeOut* fo3 = CCFadeOut::create(1.0);
	CCFiniteTimeAction* sc2 = CCScaleTo::create(1, 0.5);
	CCDelayTime* dt = CCDelayTime::create(1);
	CCFadeIn* fi2 = CCFadeIn::create(0); //‚ [‚ [
	CCSpawn* sp2 = CCSpawn::createWithTwoActions(fo3, sc2);
	CCSequence* sq2 = CCSequence::create(dt, fi2, sp2, NULL);
	m_count2->runAction(sq2);

	m_count = CCSprite::create(COUNT1);
	m_count->setPosition(ccp(winSize.width / 2, winSize.height / 20*9));
	m_count->setOpacity(0); //‚ [‚ [
	addChild(m_count, kZOrderListen, kTagListen);
	CCFadeOut* fo4 = CCFadeOut::create(1.0);
	CCFiniteTimeAction* sc3 = CCScaleTo::create(1, 0.5);
	CCDelayTime* dt2 = CCDelayTime::create(2);
	CCFadeIn* fi3 = CCFadeIn::create(0); //‚ [‚ [
	CCSpawn* sp3 = CCSpawn::createWithTwoActions(fo4, sc3);
	CCCallFunc* cf = CCCallFunc::create(this, callfunc_selector(GameScene::showArrow));
	CCSequence* sq3 = CCSequence::create(dt2, fi3, sp3, cf, NULL);
	m_count->runAction(sq3);
}

void GameScene::showArrow()
{
	touch = true;
	if(countdown)
	{
		m_yaku->removeFromParentAndCleanup(true);
		m_count->removeFromParentAndCleanup(true);
		m_count2->removeFromParentAndCleanup(true);
		m_count3->removeFromParentAndCleanup(true);
		countdown = false;
	}
	arrow = true;

	playSound();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_arrow3 = CCSprite::create(ARROW_3);
	m_arrow3->setPosition(ccp(winSize.width / 20*13, winSize.height / 2));
	m_arrow3->setOpacity(0);
	addChild(m_arrow3, kZOrderArrow, kTagArrow);
	m_arrow9 = CCSprite::create(ARROW_9);
	m_arrow9->setPosition(ccp(winSize.width / 20*7, winSize.height / 2));
	m_arrow9->setOpacity(0);
	addChild(m_arrow9, kZOrderArrow, kTagArrow);
	CCFadeIn* fi = CCFadeIn::create(0.5);
	CCFadeIn* fi2 = CCFadeIn::create(0.5);
	m_arrow3->runAction(fi);
	m_arrow9->runAction(fi2);
}

void GameScene::playSound()
{
	if(okaminumber==3)
	{
		int soundID = SimpleAudioEngine::sharedEngine()->playEffect(MURA_9);
		int soundID2 = SimpleAudioEngine::sharedEngine()->playEffect(OKAMI_3);
	}
	if(okaminumber==9)
	{
		int soundID = SimpleAudioEngine::sharedEngine()->playEffect(MURA_3);
		int soundID2 = SimpleAudioEngine::sharedEngine()->playEffect(OKAMI_9);
	}
}

void GameScene::showRope()
{
	CCSprite* pTarget = (CCSprite*)this->getChildByTag(kTagRope);
	this->reorderChild(pTarget, kZOrderUsa-1);

	CCDelayTime* dt = CCDelayTime::create(0.5);
	CCFiniteTimeAction* mv = CCMoveBy::create( 0.5, ccp(0, 20));
	CCSequence* sq = CCSequence::create(dt, mv, NULL);
	m_rope->runAction(sq);
	rope = false;
	if(kill9){
		CCDelayTime* dt2 = CCDelayTime::create(0.5);
		CCFiniteTimeAction* fo = CCFadeTo::create( 0.5, 128);
		CCFiniteTimeAction* mv2 = CCMoveBy::create( 0.5, ccp(0, 20));
		CCSpawn* sp = CCSpawn::createWithTwoActions(fo, mv2);
		CCCallFunc* cf = CCCallFunc::create(this, callfunc_selector(GameScene::tsuriCheck));
		CCSequence* sq2 = CCSequence::create(dt2, sp, cf, NULL);
		m_usa9->runAction(sq2);
	}
	if(kill3){
		CCDelayTime* dt2 = CCDelayTime::create(0.5);
		CCFiniteTimeAction* fo = CCFadeTo::create( 0.5, 128);
		CCFiniteTimeAction* mv2 = CCMoveBy::create( 0.5, ccp(0, 20));
		CCSpawn* sp = CCSpawn::createWithTwoActions(fo, mv2);
		CCCallFunc* cf = CCCallFunc::create(this, callfunc_selector(GameScene::tsuriCheck));
		CCSequence* sq2 = CCSequence::create(dt2, sp, cf, NULL);
		m_usa3->runAction(sq2);
	}
}

void GameScene::tsuriCheck()
{
	if(kill3&&okaminumber==3){
		kill3 = false;
		usa3 = false;
		okamicount--;
	}
	else if(kill9&&okaminumber==9){
		kill9 = false;
		usa9 = false;
		okamicount--;
	}
	else{
		usacount--;
	}

	showDown();
	if(okamicount==0){
		stageClear();
		nextstage = true;
		//CCLog("good kill !");
	}
	else if(!(usacount+1>okamicount)){
		gameOver();
		gameover = true;
		//CCLog("bad kill ...");
	}
	else{
		nextDay();
		nextday = true;
	}
}

void GameScene::showDown()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_mura = CCSprite::create(MURA);
	//m_mura->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	m_okami = CCSprite::create(OKAMI);
	//m_okami->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	CCPoint point;
	int opacity;
	m_black = CCSprite::create(BLACK);
	//m_black->setOpacity(128);
	if(okaminumber==3){
		m_mura->setPosition(ccp(winSize.width / 10*3, winSize.height / 2));
		m_okami->setPosition(ccp(winSize.width / 10*7, winSize.height / 2));
		point = m_usa3->getPosition();
		opacity = m_usa3->getOpacity();
		m_black->setPosition(ccp(point.x, point.y));
		m_black->setOpacity(opacity);
		m_usa3->removeFromParentAndCleanup(true);
	}
	else if(okaminumber==9){
		m_mura->setPosition(ccp(winSize.width / 10*7, winSize.height / 2));
		m_okami->setPosition(ccp(winSize.width / 10*3, winSize.height / 2));
		point = m_usa9->getPosition();
		opacity = m_usa9->getOpacity();
		m_black->setPosition(ccp(point.x, point.y));
		m_black->setOpacity(opacity);
		m_usa9->removeFromParentAndCleanup(true);
	}
	addChild(m_mura, kZOrderBase1, kTagBase1);
	addChild(m_okami, kZOrderBase1, kTagBase1);
	addChild(m_black, kZOrderUsa, kTagUsa);
	touch = true;
}

void GameScene::stageClear()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_clear = CCSprite::create(CLEAR);
	m_clear->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	m_clear->setOpacity(0);
	addChild(m_clear, kZOrderTop, kTagTop);
	CCFadeIn* fi = CCFadeIn::create(0.5);
	m_clear->runAction(fi);
}

void GameScene::gameOver()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_miss = CCSprite::create(MISS);
	m_miss->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	m_miss->setOpacity(0);
	addChild(m_miss, kZOrderTop, kTagTop);
	CCFadeIn* fi = CCFadeIn::create(0.5);
	m_miss->runAction(fi);

	m_hint = CCSprite::create(HINT);
	m_hint->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	m_hint->setOpacity(0);
	addChild(m_hint, kZOrderTop, kTagTop);
	CCDelayTime* dt = CCDelayTime::create(1);
	CCFadeIn* fi2 = CCFadeIn::create(0.5);
	CCSequence* sq = CCSequence::create(dt, fi2, NULL);
	m_hint->runAction(sq);
	CCLog("a");
}

void GameScene::nextDay()
{
	;
}

void GameScene::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	if(touch)
	{
		CCPoint location = pTouch->getLocation();
		CCLog("X:%f,Y:%f", location.x, location.y);
		if(title)
		{
			CCSize titleSize = m_title->getContentSize();
			if(titleSize.width/3<location.x&&location.x<titleSize.width/3*2&&titleSize.height/3<location.y&&location.y<titleSize.height/3*2)
			{
				touch = false;
				CCFadeOut* fo = CCFadeOut::create(0.5);
				CCCallFunc* cf = CCCallFunc::create(this, callfunc_selector(GameScene::showCaution));
				CCSequence* sq = CCSequence::create(fo, cf, NULL);
				m_title->runAction(sq);
			}
		}
		if(caution)
		{
			touch = false;
			CCFadeOut* fo = CCFadeOut::create(0.5);
			CCCallFunc* cf = CCCallFunc::create(this, callfunc_selector(GameScene::showStage));
			CCSequence* sq = CCSequence::create(fo, cf, NULL);
			m_caution->runAction(sq);
		}
		if(stage)
		{
			touch = false;
			CCFadeOut* fo = CCFadeOut::create(0.5);
			CCCallFunc* cf = CCCallFunc::create(this, callfunc_selector(GameScene::showBase));
			CCSequence* sq = CCSequence::create(fo, cf, NULL);
			m_stage->runAction(sq);
		}
		if(listen)
		{
			CCSize listenSize = m_listen->getContentSize();
			if(listenSize.width/10*4<location.x&&location.x<listenSize.width/10*6&&listenSize.height/20*7<location.y&&location.y<listenSize.height/20*13)
			{
				touch = false;
				CCFadeOut* fo = CCFadeOut::create(0.5);
				CCCallFunc* cf = CCCallFunc::create(this, callfunc_selector(GameScene::showCountdown));
				CCSequence* sq = CCSequence::create(fo, cf, NULL);
				m_listen->runAction(sq);
			}
		}
		if(arrow)
		{
			CCSize winSize = CCDirector::sharedDirector()->getWinSize();
			//Šg‘å if(daycount==1&&winSize.width/20*6<location.x&&location.x<winSize.width/20*8&&winSize.height/20*9<location.y&&location.y<winSize.height/20*11)
			if(winSize.width/20*3<location.x&&location.x<winSize.width/20*8&&winSize.height/20*8<location.y&&location.y<winSize.height/20*12)
			{
				if(kill3)
				{
					m_kill->removeFromParentAndCleanup(true);
					kill3 = false;
				}
				if(!kill9)
				{
					kill9 = true;
					m_kill = CCSprite::create(EXECUTION);
					m_kill->setPosition(ccp(winSize.width / 10*2, winSize.height / 20*9));
					addChild(m_kill, kZOrderExecution, kTagExecution);
					arrow = false;
				}
			}
			//Šg‘å else if(daycount==1&&winSize.width/20*12<location.x&&location.x<winSize.width/20*14&&winSize.height/20*9<location.y&&location.y<winSize.height/20*11)
			else if(winSize.width/20*12<location.x&&location.x<winSize.width/20*17&&winSize.height/20*8<location.y&&location.y<winSize.height/20*12)
			{
				if(kill9)
				{
					m_kill->removeFromParentAndCleanup(true);
					kill9 = false;
				}
				if(!kill3)
				{
					kill3 = true;
					m_kill = CCSprite::create(EXECUTION);
					m_kill->setPosition(ccp(winSize.width / 10*8, winSize.height / 20*9));
					addChild(m_kill, kZOrderExecution, kTagExecution);
					arrow = false;
				}
			}
			else
			{
				//Šg‘å if(kill3&&!(winSize.width/20*15<location.x&&location.x<winSize.width/20*17&&winSize.height/20*8<location.y&&location.y<winSize.height/20*10))
				if(winSize.width/20*12<location.x&&location.x<winSize.width/20*17&&winSize.height/20*8<location.y&&location.y<winSize.height/20*12)
				{
					m_kill->removeFromParentAndCleanup(true);
					kill3 = false;
				}
				//Šg‘å if(kill9&&!(winSize.width/20*3<location.x&&location.x<winSize.width/20*5&&winSize.height/20*8<location.y&&location.y<winSize.height/20*10))
				if(winSize.width/20*3<location.x&&location.x<winSize.width/20*8&&winSize.height/20*8<location.y&&location.y<winSize.height/20*12)
				{
					m_kill->removeFromParentAndCleanup(true);
					kill9 = false;
				}
			}
		}
		else if(kill3||kill9)
		{
			CCSize winSize = CCDirector::sharedDirector()->getWinSize();
			//Šg‘å if(winSize.width/20*3<location.x&&location.x<winSize.width/20*5&&winSize.height/20*8<location.y&&location.y<winSize.height/20*10)
			if(winSize.width/20*3<location.x&&location.x<winSize.width/20*8&&winSize.height/20*8<location.y&&location.y<winSize.height/20*12)
			{
				//m_kill->removeFromParentAndCleanup(true);
				//kill9 = false;
				m_arrow3->removeFromParentAndCleanup(true);
				m_arrow9->removeFromParentAndCleanup(true);
				//arrow = false;
				rope = true;
			}
			//Šg‘å if(winSize.width/20*15<location.x&&location.x<winSize.width/20*17&&winSize.height/20*8<location.y&&location.y<winSize.height/20*10)
			if(winSize.width/20*12<location.x&&location.x<winSize.width/20*17&&winSize.height/20*8<location.y&&location.y<winSize.height/20*12)
			{
				//m_kill->removeFromParentAndCleanup(true);
				//kill3 = false;
				m_arrow3->removeFromParentAndCleanup(true);
				m_arrow9->removeFromParentAndCleanup(true);
				//arrow = false;
				rope = true;
			}
			if(rope){
				touch = false;
				m_rope = CCSprite::create(ROPE);
				if(kill3)
				{
					//kill3 = false;
					m_rope->setPosition(ccp(winSize.width / 10*8, winSize.height / 800*485));
				}
				if(kill9)
				{
					//kill9 = false;
					m_rope->setPosition(ccp(winSize.width / 10*2, winSize.height / 800*485));
				}
				m_rope->setOpacity(0);
				addChild(m_rope, kZOrderRope, kTagRope);
				CCFadeIn* fi = CCFadeIn::create(2);
				CCFiniteTimeAction* mv = CCMoveBy::create( 2, ccp(0, -50));
				CCSpawn* sp = CCSpawn::createWithTwoActions(fi, mv);
				CCCallFunc* cf = CCCallFunc::create(this, callfunc_selector(GameScene::showRope));
				CCSequence* sq = CCSequence::create(sp, cf, NULL);
				m_rope->runAction(sq);
			}
		}
		if(nextstage)
		{
			CCSize winSize = CCDirector::sharedDirector()->getWinSize();
			//if(winSize.width/8*3<location.x&&location.x<winSize.width/8*5&&winSize.height/10*4<location.y&&location.y<winSize.height/10*6)
			if(1)
			{
				init();
			}
		}
		if(gameover)
		{
			CCSize winSize = CCDirector::sharedDirector()->getWinSize();
			//if(winSize.width/30*13<location.x&&location.x<winSize.width/30*17&&winSize.height/10*4<location.y&&location.y<winSize.height/10*6)
			if(1)
			{
				init();
			}
		}
	}
}
