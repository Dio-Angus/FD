#include "SpriteShape.h"  

SpriteShape::SpriteShape()
	: m_col(0)
	, m_row(0)
	, m_imgIndex(0)
	, m_isNeedRemove(false)
{
}
SpriteShape *SpriteShape::create(int row, int col)
{
	SpriteShape *spr = new SpriteShape();
	spr->m_row = row;
	spr->m_col = col;
	spr->m_imgIndex = rand() % (TOTAL_SPRITE-3);
	spr->initWithSpriteFrameName(spriteNormal[spr->m_imgIndex]);
	spr->autorelease();
	return spr;
}

SpriteShape *SpriteShape::createBlock(int row, int col, int blockIndex)
{
	SpriteShape *spr = new SpriteShape();
	spr->m_row = row;
	spr->m_col = col;
	if (blockIndex == 0)
	{		
		spr->m_imgIndex = 5;//spriteNormal 0-4ÌÇ¹û£¬5¹Ì¶¨×©¿é£¬6¿ÉÆÆ»µ×©¿é£¬7 6µÄ»Ù»µĞÎÌ¬
	}
	else if (blockIndex==1)
	{
		spr->m_imgIndex = 6;
	}
	else if (blockIndex == 2)
	{
		spr->m_imgIndex = 7;
	}
	spr->initWithSpriteFrameName(spriteNormal[spr->m_imgIndex]);
	spr->setIgnoreCheck(true);
	spr->autorelease();
	return spr;
}