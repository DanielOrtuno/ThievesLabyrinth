#pragma once


#pragma region Entity

struct eEntity
{
	enum { PLAYER, ENEMY, PROJECTILE, CAMERA, ROOM, ENVIRONMENT, DOOR, TRAP, SPAWN, ITEM, PARTICLE, COUNT };
};

struct eEnemyType
{
	enum { MAGE, CHICKEN, VIKING, ARCHER, KNIGHT, COUNT };
};

#pragma endregion


#pragma region Emitter

struct eEmitter
{
	enum {CONE, RADIAL, PLANE, STATIC, COUNT};
};

#pragma endregion


#pragma region Event Manager

struct eSystems
{
	enum { DEBUG };
};

#pragma endregion


#pragma region Component

struct eComponent
{
	enum 
	{ 
		TRANSFORM, 
		BOX_COLLIDER, 
		CAPSULE_COLLIDER, 
		RIGIDBODY,
		MESH_RENDERER, 
		ANIMATOR,
		STATS,
		FIRE_DEMON_CONTROLLER, 
		CAMERA_CONTROLLER,
		MAGE_CONTROLLER,
		CHICKEN_CONTROLLER,
		VIKING_CONTROLLER,
		ARCHER_CONTROLLER,
		KNIGHT_CONTROLLER,
		PROJECTILE_COMPONENT,
		LIGHT,
		INVENTORY,
		SPIKE_TRAP_COMPONENT,
		PATH_SURFACE,
		PATH_AGENT,
		PARTICLE_EMITTER,
		CLICK_INDICATOR,
		COUNT
	};
};

#pragma endregion


#pragma region Render


struct eRasterizerState
{
	enum { DEFAULT, NO_CULLING, WIREFRAME, COUNT };
};

struct eDepthStencilView
{
	enum { DEFAULT, GLOW, COUNT };
};

struct eDepthStencilState
{
	enum { DEFAULT, DEPTH_ALWAYS, STENCIL_ALWAYS, STENCIL_EQUAL, COUNT };
};

struct eVertexBuffer
{
	enum 
	{ 
		FIRE_DEMON,
		ENEMY_MAGE, ENEMY_CHICKEN, ENEMY_VIKING, ENEMY_ARCHER, ENEMY_KNIGHT,
		SPHERE, AOE_MESH, ARROW,
		ROOM1, ROOM2, ROOM3, ROOM5, 
		BARREL01, CHAIR, FLAG, ROCK01, ROCK02, ROCK03, STATUE, TABLE,
		DOOR, PILLAR, WALL, SPIKE_TRAP, SPIKE_PLATFORM, /*SPAWN,*/ TORCH, QUAD, FIREWALL, OPENDOOR, LOOTCHEST, POTION,
		LOGS, BARREL02, SACK, CART, CHEST, PLATFORM_CIRCLE, PLATFORM, ALTAR, ARCHES, BOOKCASE, BOOKS,
		DEBUG_LINES, COUNT
	};
};

struct eIndexBuffer
{
	enum 
	{ 
		FIRE_DEMON,
		ENEMY_MAGE, ENEMY_CHICKEN, ENEMY_VIKING, ENEMY_ARCHER, ENEMY_KNIGHT, 
		SPHERE, AOE_MESH, ARROW,
		ROOM1, ROOM2, ROOM3, ROOM5,
		BARREL01, CHAIR, FLAG, ROCK01, ROCK02, ROCK03, STATUE, TABLE,
		DOOR, PILLAR, WALL, SPIKE_TRAP, SPIKE_PLATFORM,/* SPAWN,*/ TORCH, QUAD, FIREWALL, OPENDOOR, LOOTCHEST, POTION,
		LOGS, BARREL02, SACK, CART, CHEST, PLATFORM_CIRCLE, PLATFORM, ALTAR, ARCHES, BOOKCASE, BOOKS,
		COUNT
	};
};

struct eConstantBuffer
{
	enum { MODEL, CAMERA, JOINT_MATRICES, LIGHTS, RESOURCES, COLOR, VECTOR, COUNT };
};

struct eVertexShader
{
	enum { DEFAULT, SKINNED, FULLSCREEN_QUAD, DEBUG_SHADER, COUNT };
};

struct ePixelShader
{
	enum
	{
		DEFAULT,
		SOLID_COLOR,
		PASS_2D,
		BRIGHTNESS,
		DISSOLVE,
		SEE_THROUGH,
		TORCH_FIRE,
		FIREWALL,
		HOR_BLUR, VER_BLUR,
		FADE_OUT,
		FLASH,
		PARTICLE,
		AoE,

		DEBUG_SHADER, COUNT };
};

struct eInputLayout
{
	enum { DEFAULT, SKINNED, DEBUG, COUNT };
};

struct eSRV
{
	enum
	{
		NONE = -1,
		//MINOTAUR_DIFFUSE,
		FIRE_DEMON_DIFFUSE, FIRE_DEMON_EXTINGUISHED, DIRECTION_INDICATOR,

		ENEMY_MAGE_DIFFUSE, ENEMY_MAGE_NORMAL, ENEMY_MAGE_SPECULAR,
		ENEMY_CHICKEN_DIFFUSE,
		ENEMY_VIKING_DIFFUSE, ENEMY_VIKING_NORMAL, ENEMY_VIKING_SPECULAR,
		ENEMY_ARCHER_DIFFUSE, ENEMY_ARCHER_SPECULAR,
		ENEMY_KNIGHT_DIFFUSE,

		BASIC_ATTACK_DIFFUSE,
		FIREBALL_DIFFUSE,
		AOE_DIFFUSE,
		ARROW_DIFFUSE,
		MAGE_PROJECTILE_DIFFUSE,

		FLOOR_DIFFUSE, FLOOR_NORMAL, FLOOR_SPECULAR,
		DOOR_DIFFUSE, DOOR_NORMAL, DOOR_SPECULAR,
		PILLAR_DIFFUSE, PILLAR_NORMAL, PILLAR_SPECULAR,
		WALL_DIFFUSE, WALL_NORMAL, WALL_SPECULAR,
		SPIKE_TRAP_DIFFUSE, SPAWN,
		TORCH_DIFFUSE, TORCH_NORMAL,

		BARREL_DIFFUSE, BARREL_NORMAL, BARREL_SPECULAR,
		// Table and chair share same texture
		CHAIR_TABLE_DIFFUSE, CHAR_TABLE_NORMAL,
		// Rocks share same textures
		ROCKS_DIFFUSE, ROCKS_NORMAL, ROCKS_SPECULAR,
		// logs, barrel, sack share same texture
		SACK_LOG_BARREL_DIFFUSE, SACK_LOG_BARREL_NORMAL,

		STATUE_DIFFUSE, STATUE_NORMAL, STATUE_SPECULAR,
		FLAG_DIFFUSE, FLAG_NORMAL,
		CART_DIFFUSE, CART_NORMAL,
		CHEST_DIFFUSE, CHEST_NORMAL, CHEST_SPECULAR,
		PLATFORM_DIFFUSE, PLATFORM_NORMAL,
		ALTAR_DIFFUSE, ALTAR_NORMAL,
		ARCHES_DIFFUSE, ARCHES_NORMAL,
		BOOKCASE_DIFFUSE, BOOKCASE_NORMAL, BOOKS_DIFFUSE, BOOKS_NORMAL,
		LOOT_CHEST_DIFFUSE, LOOT_CHEST_NORMAL, LOOT_CHEST_SPECULAR,
		POTION, 

		LAVA_TEXTURE, SMOKE_NOISE, PERLIN_NOISE, CLOUD_NOISE, PARTICLE_SMOKE, PARTICLE_FIRE,
		FLAME_SHAPE, FADE, FIREWALL_NOISE, FLASH, SHIELD_EFFECT, FIREBALL_PARTICLE_EFFECT,
		BASIC_ATTACK_PARTICLE_EFFECT, FIREWALL_PARTICLE_EFFECT, TORCH_PARTICLE_EFFECT, PARTICLE_SPARK, HEALTH_PARTICLE,
		MANA_PARTICLE, DEFENSE_PARTICLE, DAMAGE_PARTICLE, ARCANE_PARTICLE, CHICKEN_PARTICLE, FEATHER_PARTICLE,
		EXPLOSION_PARTICLE,

		GLOW_1, GLOW_2,
		SCENE, BACKBUFFER,

		RICARDO, CLICK_INDICATOR, 

		COUNT
	};
};

struct eUAV
{
	enum { SCENE, COUNT };

};

struct eRenderTargetView
{
	enum
	{
		SCENE_TARGET,
		GLOW_TARGET_1,
		GLOW_TARGET_2,
		BACKBUFFER,	//Used to render final quad (after postprocessing) to the back buffer.
		COUNT
	};
};

struct eTexture
{
	enum
	{
		SCENE,
		GLOW_1,
		GLOW_2,
		BACKBUFFER,
		COUNT
	};
};

struct eViewport
{
	enum { DEFAULT, COUNT };
};

struct eSampler
{
	enum { BORDER, CLAMP, MIRROR, WRAP, ANIMATION_SAMPLER, COUNT};
};

struct eBlendState
{
	enum { DEFAULT, ADDITIVE, COUNT}; //, 
};

#pragma endregion


#pragma region Animator

struct eAnimator
{
	enum { MAGE, FIRE_DEMON, VIKING, ARCHER, KNIGHT, COUNT };
};

struct eEnemyAnimation
{
	enum { IDLE, WALK, ATTACK, DEATH, HURT, COUNT, BLOCK = 4 }; // ATTACK, DEATH,
};

struct ePlayerAnimation
{
	enum { IDLE, WALK, MELEE, FIREBALL, AOE, FIREWALL, FLINCH, DEATH, COUNT}; //, ATTACK, SPELL_1, SPELL_2, SPELL_3, DEATH,
};

#pragma endregion


#pragma region GUI

struct eSprite
{
	enum { HEALTHBAR, MANABAR, COUNT};
};

struct eMenu
{
	enum { START = 0, START_OPTIONS, START_CONTROLS, CREDITS, SELECT, PAUSE, PAUSE_OPTIONS, PAUSE_CONTROLS, INVENTORY, WIN, LOSE, GAME, COUNT };
};

#pragma endregion


#pragma region Audio

struct eAudio
{
	enum { SFX, MUSIC, COUNT};
};

struct eSFX
{
	enum { 
		BUTTON, PLAYERMOVE,
		HIT, HIT2, HIT3, HIT4,
		FIREBALL1, FIREBALL2, FIREWALL, ARROW_WOOSH, SPIKES, FUSE,
		/*MAGE_ATTACK,  VIKING_ATTACK, */KNIGHT_ATTACK, BLOCK, EXPLOSION, POTION, TELEPORT,
		STONE_IMPACT_1, STONE_IMPACT_2, STONE_IMPACT_3, STONE_IMPACT_4, STONE_IMPACT_5,
		DOOR_OPEN, DOOR_CLOSE, LOSE,
		COUNT};
};

struct eMusic
{
	enum { 
		//DOOM,
		THIEVES_PLUNDER,
		TOMB_OF_THIEVES,
		THIEVES_BOUNTY,
		COUNT };
};
#pragma endregion


#pragma region Collision

struct eCollisionState
{
	enum { COLLISION_ENTER, COLLISION_STAY, COLLISION_EXIT, TRIGGER_ENTER, TRIGGER_STAY, TRIGGER_EXIT };
};

#pragma endregion


#pragma region Game State

struct eGameState
{
	enum { MAIN_MENU, LOADING_LEVEL, PLAYING, PAUSED, END_TIMER, QUIT };
};

#pragma endregion


#pragma region Room Types

struct eRoomTypes
{
	enum { DEFULT, COUNT };
};

#pragma endregion


#pragma region Collision Types

struct eCollisionTypes
{
	enum { BOX_BOX, CAPSULE_CAPSULE, BOX_CAPSULE };
};

#pragma endregion


#pragma region Items

struct eItemClass
{
	enum { PASSIVE = 0, ACTIVE, CONSUMABLE, COUNT };
};

struct ePassiveItems
{
	enum { NONE = 0, RING, THIMBLE, BELT, GAUNTLET, BOOTS, HASTE, HAT, COIN, COUNT };
};

struct eActiveItems
{
	enum { NONE = 0, SHIELD, HORN, LAVA, BOMB, BREEZE, TELEPORTER, COUNT };
};

struct eConsumableItems
{
	enum { NONE = 0, HEALTH, MANA, DAMAGE, HASTE, RESIST, COUNT };
};

#pragma endregion