#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"

#define TITLE "title.png"
#define CAUTION "caution.png"
#define STAGE_1 "stage_1.png"
#define BASE  "base.png"
#define DAY "stage_1_day_1.png"
#define LIST_1 "list_1.png"
#define WHITE "usa_white.png"
#define BLACK "usa_black.png"
#define LISTEN "listen.png"
#define YAKUSYOKU "listen_yakusyoku.png"
#define KOBUTSU "listen_kobutsu.png"
#define COUNT1 "countdown_1.png"
#define COUNT2 "countdown_2.png"
#define COUNT3 "countdown_3.png"
#define ARROW_3 "arrow_3.png"
#define ARROW_9 "arrow_9.png"
#define EXECUTION  "execution.png"
#define ROPE  "rope.png"
#define MURA  "mura.png"
#define OKAMI "okami.png"
#define CLEAR "stage_clear.png"
#define MISS  "miss.png"
#define HINT  "hint.png"

#define MURA_3 "mura_3.wav" //３時方向から『ムラビトうさ』
#define MURA_9 "mura_9.wav"
#define OKAMI_3 "okami_3.wav" //３時方向から『オオカミうさ』
#define OKAMI_9 "okami_9.wav"
 //３時方向から『ニンジンうさ』

 //３時方向から『ニンゲンうさ』→『相手がウサギなのに…ぐぬぬ』


class GameScene : public cocos2d::CCLayer
{
protected:
	enum kTag
	{
		kTagBase,
		kTagBase1,
		kTagListen,
		kTagArrow,
		kTagUsa,
		kTagExecution,
		kTagRope,
		kTagTop,
	};
	enum kZOrder
	{
		kZOrderBase,
		kZOrderBase1,
		kZOrderListen,
		kZOrderArrow,
		kZOrderUsa,
		kZOrderExecution,
		kZOrderRope,
		kZOrderTop,
	};
	void okamiSet();
	void showTitle();
	void showCaution();
	void showStage();
	void showBase();
	void showUsa();
	void showCountdown();
	void showArrow();
	void playSound();
	void showRope();
	void tsuriCheck();
	void showDown();
	void stageClear();
	void gameOver();
	void nextDay();

	cocos2d::CCSprite* m_title;
	cocos2d::CCSprite* m_caution;
	cocos2d::CCSprite* m_stage;
	cocos2d::CCSprite* m_base;
	cocos2d::CCSprite* m_sd111;
	cocos2d::CCSprite* m_list;
	cocos2d::CCSprite* m_usa3;
	cocos2d::CCSprite* m_usa9;
	cocos2d::CCSprite* m_listen;
	cocos2d::CCSprite* m_yaku;
	cocos2d::CCSprite* m_count;
	cocos2d::CCSprite* m_count2;
	cocos2d::CCSprite* m_count3;
	cocos2d::CCSprite* m_arrow3;
	cocos2d::CCSprite* m_arrow9;
	cocos2d::CCSprite* m_kill;
	cocos2d::CCSprite* m_rope;
	cocos2d::CCSprite* m_mura;
	cocos2d::CCSprite* m_okami;
	cocos2d::CCSprite* m_black;
	cocos2d::CCSprite* m_clear;
	cocos2d::CCSprite* m_miss;
	cocos2d::CCSprite* m_hint;

	bool title;
	bool caution;
	bool stage;
	bool usa3;
	bool usa9;
	bool listen;
	bool countdown;
	bool arrow;
	bool kill3;
	bool kill9;
	bool rope;
	bool nextstage;
	bool gameover;
	bool nextday;

	int daycount;
	int usacount;
	int okamicount;
	int okaminumber;

	bool touch;
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(GameScene);
	virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
};

#endif /* __GAMESCENE_H__ */
