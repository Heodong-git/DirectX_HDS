#pragma once

enum class RenderOrder
{
	BACKGROUND,
	MAP,
	DOOR,
	MONSTER,
	BOSS,
	UI,
	FANBLADE,
	LASER,
	PLATFORM,
	BULLET,
	PLAYER,
	PLAYER_EFFECT,
	EFFECT,
	DEBUG,
	CURSOR,
};

enum class ColOrder
{
	NONE,
	PLAYER,
	PLAYER_ATTACK,
	PLAYER_BULLET,
	PLAYER_DOOR_BREAK,
	MONSTER,
	MONSTER_ATTACK,
	MONSTER_BULLET,
	MONSTER_CHASE,
	MONSTER_CHECK,
	MONSTER_RANGE_CHECK,
	CHECKBOX,
	CURSOR,
	DOOR,
	DOOR_OPEN_EVENT,
	STAGE_COL_OBJ,
	PLATFORM,
	LASER,
	FANBLADE,
	PARTITION,
	BULLET,
};