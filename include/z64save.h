#ifndef Z64SAVE_H
#define Z64SAVE_H

#include "ultra64.h"
#include "z64item.h"
#include "z64math.h"
#include "os.h"

struct GameState;
struct PlayState;
struct FileSelectState;

// TODO: properly name DOWN, RETURN and TOP
typedef enum RespawnMode {
    /* 0 */ RESPAWN_MODE_DOWN,                          // "RESTART_MODE_DOWN"
    /* 1 */ RESPAWN_MODE_RETURN,                        // "RESTART_MODE_RETURN"
    /* 2 */ RESPAWN_MODE_TOP,                           // "RESTART_MODE_TOP"
    /* 3 */ RESPAWN_MODE_UNK_3,                         // Related to grottos
    /* 4 */ RESPAWN_MODE_GORON,                         // "RESTART_MODE_GORON"
    /* 5 */ RESPAWN_MODE_ZORA,                          // "RESTART_MODE_ZORA"
    /* 6 */ RESPAWN_MODE_DEKU,                          // "RESTART_MODE_NUTS"
    /* 7 */ RESPAWN_MODE_HUMAN,                         // "RESTART_MODE_CHILD"
    /* 8 */ RESPAWN_MODE_MAX
} RespawnMode;

#define SAVE_BUFFER_SIZE 0x4000

typedef enum {
    /* 0  */ MAGIC_STATE_IDLE, // Regular gameplay
    /* 1  */ MAGIC_STATE_CONSUME_SETUP, // Sets the speed at which the magic border flashes
    /* 2  */ MAGIC_STATE_CONSUME, // Consume magic until target is reached or no more magic is available
    /* 3  */ MAGIC_STATE_METER_FLASH_1, // Flashes border
    /* 4  */ MAGIC_STATE_METER_FLASH_2, // Flashes border and draws yellow magic to preview target consumption
    /* 5  */ MAGIC_STATE_RESET, // Reset colors and return to idle
    /* 6  */ MAGIC_STATE_METER_FLASH_3, // Flashes border with no additional behaviour
    /* 7  */ MAGIC_STATE_CONSUME_LENS, // Magic slowly consumed by Lens of Truth
    /* 8  */ MAGIC_STATE_STEP_CAPACITY, // Step `magicCapacity` to full capacity
    /* 9  */ MAGIC_STATE_FILL, // Add magic until magicFillTarget is reached
    /* 10 */ MAGIC_STATE_CONSUME_GORON_ZORA_SETUP,
    /* 11 */ MAGIC_STATE_CONSUME_GORON_ZORA, // Magic slowly consumed by Goron spiked rolling or Zora electric barrier.
    /* 12 */ MAGIC_STATE_CONSUME_GIANTS_MASK // Magic slowly consumed by Giant's Mask
} MagicState;

typedef enum {
    /* 0 */ MAGIC_CONSUME_NOW, // Consume magic immediately without preview
    /* 1 */ MAGIC_CONSUME_WAIT_NO_PREVIEW, // Sets consume target but waits to consume. No yellow magic preview to target consumption. Unused
    /* 2 */ MAGIC_CONSUME_NOW_ALT, // Identical behaviour to MAGIC_CONSUME_NOW. Unused
    /* 3 */ MAGIC_CONSUME_LENS, // Lens of Truth consumption
    /* 4 */ MAGIC_CONSUME_WAIT_PREVIEW, // Sets consume target but waits to consume. Show magic to be consumed in yellow.
    /* 5 */ MAGIC_CONSUME_GORON_ZORA, // Goron spiked rolling or Zora electric barrier slow consumption
    /* 6 */ MAGIC_CONSUME_GIANTS_MASK, // Giant's Mask slow consumption
    /* 7 */ MAGIC_CONSUME_DEITY_BEAM // Fierce Deity Beam consumption, consumed magic now and not via request
} MagicChangeType;

#define MAGIC_NORMAL_METER 0x30
#define MAGIC_DOUBLE_METER (2 * MAGIC_NORMAL_METER)

// See `R_MAGIC_DBG_SET_UPGRADE`
#define MAGIC_DBG_SET_UPGRADE_NO_ACTION 0
#define MAGIC_DBG_SET_UPGRADE_NORMAL_METER -1
#define MAGIC_DBG_SET_UPGRADE_DOUBLE_METER 1

#define ENV_HAZARD_TEXT_TRIGGER_HOTROOM (1 << 0)
#define ENV_HAZARD_TEXT_TRIGGER_UNDERWATER (1 << 1)

#define SECONDS_TO_TIMER(seconds) ((seconds) * 100)

#define OSTIME_TO_TIMER(osTime) ((osTime) * 64 / 3000 / 10000)
#define OSTIME_TO_TIMER_ALT(osTime) ((osTime) / 10000 * 64 / 3000)

// 1 centisecond = 10 milliseconds = 1/100 seconds
#define SECONDS_TO_TIMER_PRECISE(seconds, centiSeconds) ((seconds) * 100 + (centiSeconds))

typedef enum {
    /*  0 */ TIMER_ID_POSTMAN, // postman's counting minigame
    /*  1 */ TIMER_ID_MINIGAME_1, // minigame timer
    /*  2 */ TIMER_ID_2,
    /*  3 */ TIMER_ID_MOON_CRASH, // timer used for mooncrash on the clocktower roof
    /*  4 */ TIMER_ID_MINIGAME_2, // minigame timer
    /*  5 */ TIMER_ID_ENV_HAZARD, // environmental hazard timer (underwater or hot room)
    /*  6 */ TIMER_ID_GORON_RACE_UNUSED,
    /*  7 */ TIMER_ID_MAX,
    /* 99 */ TIMER_ID_NONE = 99,
} TimerId;

typedef enum {
    /* 0 */ TIMER_COUNT_DOWN,
    /* 1 */ TIMER_COUNT_UP
} TimerDirection;

typedef enum {
    /*  0 */ TIMER_STATE_OFF,
    /*  1 */ TIMER_STATE_START,
    /*  2 */ TIMER_STATE_HOLD_TIMER, // Hold timer frozen at the screen center
    /*  3 */ TIMER_STATE_MOVING_TIMER, // Move timer to a target location
    /*  4 */ TIMER_STATE_COUNTING,
    /*  5 */ TIMER_STATE_STOP,
    /*  6 */ TIMER_STATE_6, // like `TIMER_STATE_STOP` but with extra minigame checks
    /*  7 */ TIMER_STATE_7, // stopped but still update `timerCurTimes`
    /*  8 */ TIMER_STATE_ENV_HAZARD_START,
    /*  9 */ TIMER_STATE_ALT_START,
    /* 10 */ TIMER_STATE_10, // precursor to `TIMER_STATE_ALT_COUNTING`
    /* 11 */ TIMER_STATE_ALT_COUNTING,
    /* 12 */ TIMER_STATE_12, // Updated paused time?
    /* 13 */ TIMER_STATE_POSTMAN_START,
    /* 14 */ TIMER_STATE_POSTMAN_COUNTING,
    /* 15 */ TIMER_STATE_POSTMAN_STOP,
    /* 16 */ TIMER_STATE_POSTMAN_END
} TimerState;

typedef enum {
    /* 0 */ BOTTLE_TIMER_STATE_OFF,
    /* 1 */ BOTTLE_TIMER_STATE_COUNTING
} BottleTimerState;

typedef enum {
    /* 0 */ MINIGAME_STATUS_INACTIVE,
    /* 1 */ MINIGAME_STATUS_ACTIVE,
    /* 3 */ MINIGAME_STATUS_END = 3
} MinigameStatus;

typedef enum {
    /*  0 */ HUD_VISIBILITY_IDLE,
    /*  1 */ HUD_VISIBILITY_NONE,
    /*  2 */ HUD_VISIBILITY_NONE_ALT, // Identical to HUD_VISIBILITY_NONE
    /*  3 */ HUD_VISIBILITY_HEARTS_WITH_OVERWRITE, // Uses Interface_UpdateButtonAlphas so gives the opportunity to dim only disabled buttons
    /*  4 */ HUD_VISIBILITY_A,
    /*  5 */ HUD_VISIBILITY_A_HEARTS_MAGIC_WITH_OVERWRITE, // Uses Interface_UpdateButtonAlphas so gives the opportunity to dim only disabled buttons
    /*  6 */ HUD_VISIBILITY_A_HEARTS_MAGIC_MINIMAP_WITH_OVERWRITE, // Uses Interface_UpdateButtonAlphas so gives the opportunity to dim only disabled buttons
    /*  7 */ HUD_VISIBILITY_ALL_NO_MINIMAP_W_DISABLED, // Only raises button alphas if not disabled
    /*  8 */ HUD_VISIBILITY_B,
    /*  9 */ HUD_VISIBILITY_HEARTS_MAGIC,
    /* 10 */ HUD_VISIBILITY_B_ALT,
    /* 11 */ HUD_VISIBILITY_HEARTS,
    /* 12 */ HUD_VISIBILITY_A_B_MINIMAP,
    /* 13 */ HUD_VISIBILITY_HEARTS_MAGIC_WITH_OVERWRITE, // Uses Interface_UpdateButtonAlphas so gives the opportunity to dim only disabled buttons
    /* 14 */ HUD_VISIBILITY_HEARTS_MAGIC_C,
    /* 15 */ HUD_VISIBILITY_ALL_NO_MINIMAP,
    /* 16 */ HUD_VISIBILITY_A_B_C,
    /* 17 */ HUD_VISIBILITY_B_MINIMAP,
    /* 18 */ HUD_VISIBILITY_HEARTS_MAGIC_MINIMAP,
    /* 19 */ HUD_VISIBILITY_A_HEARTS_MAGIC_MINIMAP,
    /* 20 */ HUD_VISIBILITY_B_MAGIC,
    /* 21 */ HUD_VISIBILITY_A_B,
    /* 22 */ HUD_VISIBILITY_A_B_HEARTS_MAGIC_MINIMAP,
    /* 50 */ HUD_VISIBILITY_ALL = 50,
    /* 52 */ HUD_VISIBILITY_NONE_INSTANT = 52
} HudVisibility;

#define PICTO_PHOTO_WIDTH 160
#define PICTO_PHOTO_HEIGHT 112

#define PICTO_PHOTO_TOPLEFT_X ((SCREEN_WIDTH - PICTO_PHOTO_WIDTH) / 2)
#define PICTO_PHOTO_TOPLEFT_Y ((SCREEN_HEIGHT - PICTO_PHOTO_HEIGHT) / 2)

#define PICTO_PHOTO_SIZE (PICTO_PHOTO_WIDTH * PICTO_PHOTO_HEIGHT)
#define PICTO_PHOTO_COMPRESSED_SIZE (PICTO_PHOTO_SIZE * 5 / 8)

typedef struct SramContext {
    /* 0x00 */ u8* readBuff;
    /* 0x04 */ u8 *saveBuf;
    /* 0x08 */ char unk_08[4];
    /* 0x0C */ s16 status;
    /* 0x10 */ u32 curPage;
    /* 0x14 */ u32 numPages;
    /* 0x18 */ OSTime unk_18;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ s16 unk_24;
} SramContext; // size = 0x28

typedef struct ItemEquips {
    /* 0x00 */ u8 buttonItems[4][4];                    // "register_item"
    /* 0x10 */ u8 cButtonSlots[4][4];                   // "register_item_pt"
    /* 0x20 */ u16 equipment;
} ItemEquips; // size = 0x22

typedef struct Inventory {
    /* 0x00 */ u8 items[48];                            // "item_register", first 24 elements are normal items and the other 24 are masks
    /* 0x30 */ s8 ammo[24];                             // "item_count"
    /* 0x48 */ u32 upgrades;                            // "non_equip_register" some bits are wallet upgrades
    /* 0x4C */ u32 questItems;                          // "collect_register"
    /* 0x50 */ u8 dungeonItems[10];                     // "key_compass_map"
    /* 0x5A */ s8 dungeonKeys[9];                       // "key_register"
    /* 0x63 */ s8 defenseHearts;
    /* 0x64 */ s8 strayFairies[10];                     // "orange_fairy"
    /* 0x6E */ char dekuPlaygroundPlayerName[3][8];     // "degnuts_memory_name" Stores playerName (8 char) over (3 days) when getting a new high score
} Inventory; // size = 0x88

typedef struct HorseData {
    /* 0x0 */ s16 sceneId;                             // "spot_no"
    /* 0x2 */ Vec3s pos;                               // "horse_x", "horse_y" and "horse_z"
    /* 0x8 */ s16 yaw;                                 // "horse_a"
} HorseData; // size = 0xA

typedef struct RespawnData {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ s16 yaw;
    /* 0x0E */ s16 playerParams;
    /* 0x10 */ u16 entrance;
    /* 0x12 */ u8 roomIndex;
    /* 0x13 */ s8 data;
    /* 0x14 */ u32 tempSwitchFlags;
    /* 0x18 */ u32 unk_18;
    /* 0x1C */ u32 tempCollectFlags;
} RespawnData; // size = 0x20

typedef struct PermanentSceneFlags {
    /* 0x00 */ u32 chest;
    /* 0x04 */ u32 switch0;
    /* 0x08 */ u32 switch1;
    /* 0x0C */ u32 clearedRoom;
    /* 0x10 */ u32 collectible;
    /* 0x14 */ u32 unk_14; // varies based on scene. For dungeons, floors visited. 
    /* 0x18 */ u32 rooms;
} PermanentSceneFlags; // size = 0x1C

typedef struct CycleSceneFlags {
    /* 0x00 */ u32 chest;
    /* 0x04 */ u32 switch0;
    /* 0x08 */ u32 switch1;
    /* 0x0C */ u32 clearedRoom;
    /* 0x10 */ u32 collectible;
} CycleSceneFlags; // size = 0x14

typedef struct SaveOptions {
    /* 0x0 */ u16 optionId;                            // "option_id"
    /* 0x2 */ u8 language;                             // "j_n"
    /* 0x3 */ s8 audioSetting;                         // "s_sound"
    /* 0x4 */ u8 languageSetting;                      // "language"
    /* 0x5 */ u8 zTargetSetting;                       // "z_attention", 0: Switch; 1: Hold
} SaveOptions; // size = 0x6

typedef struct SavePlayerData {
    /* 0x00 */ char newf[6];                          // "newf"               Will always be "ZELDA3 for a valid save
    /* 0x06 */ u16 deaths;                            // "savect"
    /* 0x08 */ char playerName[8];                    // "player_name"
    /* 0x10 */ s16 healthCapacity;                    // "max_life"
    /* 0x12 */ s16 health;                            // "now_life"
    /* 0x14 */ s8 magicLevel; // 0 for no magic/new load, 1 for magic, 2 for double magic "magic_max"
    /* 0x15 */ s8 magic; // current magic available for use "magic_now"
    /* 0x16 */ s16 rupees;                            // "lupy_count"
    /* 0x18 */ u16 swordHealth;                       // "long_sword_hp"
    /* 0x1A */ u16 tatlTimer;                         // "navi_timer"
    /* 0x1C */ u8 isMagicAcquired;                    // "magic_mode"
    /* 0x1D */ u8 isDoubleMagicAcquired;              // "magic_ability"
    /* 0x1E */ u8 doubleDefense;                      // "life_ability"
    /* 0x1F */ u8 unk_1F;                             // "ocarina_round"
    /* 0x20 */ u8 unk_20;                             // "first_memory"
    /* 0x22 */ u16 owlActivationFlags;                // "memory_warp_point"
    /* 0x24 */ u8 unk_24;                             // "last_warp_pt"
    /* 0x26 */ s16 savedSceneId;                      // "scene_data_ID"
} SavePlayerData; // size = 0x28

typedef struct Save {
    /* 0x0000 */ s32 entrance;                          // "scene_no"
    /* 0x0004 */ u8 equippedMask;                       // "player_mask"
    /* 0x0005 */ u8 isFirstCycle;                       // "opening_flag"
    /* 0x0006 */ u8 unk_06;
    /* 0x0007 */ u8 linkAge;                            // "link_age"
    /* 0x0008 */ s32 cutscene;                          // "day_time"
    /* 0x000C */ u16 time;                              // "zelda_time"
    /* 0x000E */ u16 owlSaveLocation;
    /* 0x0010 */ s32 isNight;                           // "asahiru_fg"
    /* 0x0014 */ s32 timeSpeedOffset;                   // "change_zelda_time"
    /* 0x0018 */ s32 day;                               // "totalday"
    /* 0x001C */ s32 daysElapsed;                       // "eventday"
    /* 0x0020 */ u8 playerForm;                         // "player_character"
    /* 0x0021 */ u8 snowheadCleared;                    // "spring_flag"
    /* 0x0022 */ u8 hasTatl;                            // "bell_flag"
    /* 0x0023 */ u8 isOwlSave;
    /* 0x0024 */ SavePlayerData playerData;
    /* 0x004C */ ItemEquips equips;
    /* 0x0070 */ Inventory inventory;
    /* 0x00F8 */ PermanentSceneFlags permanentSceneFlags[120];
    /* 0x0E18 */ u8 unk_E18[0x54];
    /* 0x0E6C */ u32 dekuPlaygroundHighScores[3];
    /* 0x0E78 */ u32 pictoFlags0;                       // Flags set by `PictoActor`s if pictograph is valid
    /* 0x0E7C */ u32 pictoFlags1;                       // Flags set by Snap_ValidatePictograph() to record errors; volatile since that function is run many times in succession
    /* 0x0E80 */ u32 unk_E80;
    /* 0x0E84 */ u32 unk_E84;
    /* 0x0E88 */ u32 unk_E88[7];                        // Invadepoh flags
    /* 0x0EA4 */ u32 scenesVisible[7];                  // tingle maps and clouded regions on pause map. Stores scenes bitwise for up to 224 scenes even though there are not that many scenes
    /* 0x0EC0 */ u32 skullTokenCount;                   // upper 16 bits store Swamp skulls, lower 16 bits store Ocean skulls
    /* 0x0EC4 */ u32 unk_EC4;                           // Gossic stone heart piece flags
    /* 0x0EC8 */ u32 unk_EC8;
    /* 0x0ECC */ u32 unk_ECC[2];                        // Related to blue warps
    /* 0x0ED4 */ u32 stolenItems;                       // Items stolen by Takkuri and given to Curiosity Shop Man
    /* 0x0ED8 */ u32 unk_DD8;
    /* 0x0EDC */ u32 bankRupees;
    /* 0x0EE0 */ u32 unk_EE0;
    /* 0x0EE4 */ u32 unk_EE4;                           // Fishing flags
    /* 0x0EE8 */ u32 unk_EE8;
    /* 0x0EEC */ u32 horseBackBalloonHighScore;
    /* 0x0EF0 */ u32 lotteryCodeGuess;                  // Lottery code chosen by player (only uses lower three hex digits)
    /* 0x0EF4 */ u32 shootingGalleryHighScores;         // High scores for both shooting galleries. Town uses lower 16 bits, Swamp uses higher 16 bits.
    /* 0x0EF8 */ u8 weekEventReg[100];                  // "week_event_reg"
    /* 0x0F5C */ u32 regionsVisited;                    // "area_arrival"
    /* 0x0F60 */ u32 worldMapCloudVisibility;           // "cloud_clear"
    /* 0x0F64 */ u8 unk_F64;                            // "oca_rec_flag"                   has scarecrows song
    /* 0x0F65 */ u8 unk_F65;                            // "oca_rec_flag8"                  scarecrows song set?
    /* 0x0F66 */ u8 scarecrowSpawnSong[128];
    /* 0x0FE6 */ s8 bombersCaughtNum;                   // "aikotoba_index"
    /* 0x0FE7 */ s8 bombersCaughtOrder[5];              // "aikotoba_table"
    /* 0x0FEC */ s8 lotteryCodes[3][3];                 // "numbers_table", Preset lottery codes
    /* 0x0FF5 */ s8 spiderHouseMaskOrder[6];            // "kinsta_color_table"
    /* 0x0FFB */ s8 bomberCode[5];                      // "bombers_aikotoba_table"
    /* 0x1000 */ HorseData horseData;
    /* 0x100A */ u16 checksum;                          // "check_sum"
} Save; // size = 0x100C

typedef struct SaveContext {
    /* 0x0000 */ Save save;
    /* 0x100C */ u8 eventInf[8];                        // "event_inf"
    /* 0x1014 */ u8 unk_1014;                           // "stone_set_flag"
    /* 0x1015 */ u8 unk_1015;
    /* 0x1016 */ u16 jinxTimer;
    /* 0x1018 */ s16 rupeeAccumulator;                  // "lupy_udct"
    /* 0x101A */ u8 bottleTimerStates[BOTTLE_MAX]; // See the `BottleTimerState` enum. "bottle_status"
    /* 0x1020 */ OSTime bottleTimerStartOsTimes[BOTTLE_MAX]; // The osTime when the timer starts. "bottle_ostime"
    /* 0x1050 */ u64 bottleTimerTimeLimits[BOTTLE_MAX]; // The original total time given before the timer expires, in centiseconds (1/100th sec). "bottle_sub"
    /* 0x1080 */ u64 bottleTimerCurTimes[BOTTLE_MAX]; // The remaining time left before the timer expires, in centiseconds (1/100th sec). "bottle_time"
    /* 0x10B0 */ OSTime bottleTimerPausedOsTimes[BOTTLE_MAX]; // The cumulative osTime spent with the timer paused. "bottle_stop_time"
    /* 0x10E0 */ u8 pictoPhotoI5[PICTO_PHOTO_COMPRESSED_SIZE]; // buffer containing the pictograph photo, compressed to I5 from I8
    /* 0x3CA0 */ s32 fileNum;                           // "file_no"
    /* 0x3CA4 */ s16 powderKegTimer;                    // "big_bom_timer"
    /* 0x3CA6 */ u8 unk_3CA6;
    /* 0x3CA7 */ u8 unk_3CA7;                           // "day_night_flag"
    /* 0x3CA8 */ s32 gameMode;                          // "mode"
    /* 0x3CAC */ s32 sceneLayer;                        // "counter"
    /* 0x3CB0 */ s32 respawnFlag;                       // "restart_flag"
    /* 0x3CB4 */ RespawnData respawn[RESPAWN_MODE_MAX]; // "restart_data"
    /* 0x3DB4 */ f32 entranceSpeed;                     // "player_wipe_speedF"
    /* 0x3DB8 */ u16 entranceSound;                     // "player_wipe_door_SE"
    /* 0x3DBA */ u8 unk_3DBA;                           // "player_wipe_item"
    /* 0x3DBB */ u8 unk_3DBB;                           // "next_walk"
    /* 0x3DBC */ s16 dogParams;                         // "dog_flag"
    /* 0x3DBE */ u8 envHazardTextTriggerFlags;          // "guide_status"
    /* 0x3DBF */ u8 showTitleCard;                      // "name_display"
    /* 0x3DC0 */ s16 unk_3DC0;                          // "shield_magic_timer"
    /* 0x3DC2 */ u8 unk_3DC2;                           // "pad1"
    /* 0x3DC8 */ OSTime postmanTimerStopOsTime; // The osTime when the timer stops for the postman minigame. "get_time"
    /* 0x3DD0 */ u8 timerStates[TIMER_ID_MAX]; // See the `TimerState` enum. "event_fg"
    /* 0x3DD7 */ u8 timerDirections[TIMER_ID_MAX]; // See the `TimerDirection` enum. "calc_flag"
    /* 0x3DE0 */ u64 timerCurTimes[TIMER_ID_MAX]; // For countdown, the remaining time left. For countup, the time since the start. In centiseconds (1/100th sec). "event_ostime"
    /* 0x3E18 */ u64 timerTimeLimits[TIMER_ID_MAX]; // The original total time given for the timer to count from, in centiseconds (1/100th sec). "event_sub"
    /* 0x3E50 */ OSTime timerStartOsTimes[TIMER_ID_MAX]; // The osTime when the timer starts. "func_time"
    /* 0x3E88 */ u64 timerStopTimes[TIMER_ID_MAX];  // The total amount of time taken between the start and end of the timer, in centiseconds (1/100th sec). "func_end_time"
    /* 0x3EC0 */ OSTime timerPausedOsTimes[TIMER_ID_MAX]; // The cumulative osTime spent with the timer paused. "func_stop_time"
    /* 0x3EF8 */ s16 timerX[TIMER_ID_MAX];              // "event_xp"
    /* 0x3F06 */ s16 timerY[TIMER_ID_MAX];              // "event_yp"
    /* 0x3F14 */ s16 unk_3F14;                          // "character_change"
    /* 0x3F16 */ u8 seqId;                              // "old_bgm"
    /* 0x3F17 */ u8 ambienceId;                         // "old_env"
    /* 0x3F18 */ u8 buttonStatus[6];                    // "button_item"
    /* 0x3F1E */ u8 hudVisibilityForceButtonAlphasByStatus; // if btn alphas are updated through Interface_UpdateButtonAlphas, instead update them through Interface_UpdateButtonAlphasByStatus "ck_fg"
    /* 0x3F20 */ u16 nextHudVisibility; // triggers the hud to change visibility to the requested value. Reset to HUD_VISIBILITY_IDLE when target is reached "alpha_type"
    /* 0x3F22 */ u16 hudVisibility; // current hud visibility "prev_alpha_type"
    /* 0x3F24 */ u16 hudVisibilityTimer; // number of frames in the transition to a new hud visibility. Used to step alpha "alpha_count"
    /* 0x3F26 */ u16 prevHudVisibility; // used to store and recover hud visibility for pause menu and text boxes "last_time_type"
    /* 0x3F28 */ s16 magicState; // determines magic meter behavior on each frame "magic_flag"
    /* 0x3F2A */ s16 isMagicRequested; // a request to add magic has been given "recovery_magic_flag"
    /* 0x3F2C */ s16 magicFlag; // Set to 0 in func_80812D94(), otherwise unused "keep_magic_flag"
    /* 0x3F2E */ s16 magicCapacity; // maximum magic available "magic_now_max"
    /* 0x3F30 */ s16 magicFillTarget; // target used to fill magic "magic_now_now"
    /* 0x3F32 */ s16 magicToConsume; // accumulated magic that is requested to be consumed "magic_used"
    /* 0x3F34 */ s16 magicToAdd; // accumulated magic that is requested to be added "magic_recovery"
    /* 0x3F36 */ u16 mapIndex;                          // "scene_ID"
    /* 0x3F38 */ u16 minigameStatus;                    // "yabusame_mode"
    /* 0x3F3A */ u16 minigameScore;                     // "yabusame_total"
    /* 0x3F3C */ u16 minigameHiddenScore;               // "yabusame_out_ct"
    /* 0x3F3E */ u8 unk_3F3E;                           // "no_save"
    /* 0x3F3F */ u8 unk_3F3F;                           // "flash_flag"
    /* 0x3F40 */ SaveOptions options;
    /* 0x3F46 */ u16 unk_3F46;                          // "NottoriBgm"
    /* 0x3F48 */ u8 cutsceneTransitionControl;          // "fade_go"
    /* 0x3F4A */ u16 nextCutsceneIndex;                 // "next_daytime"
    /* 0x3F4C */ u8 cutsceneTrigger;                    // "doukidemo"
    /* 0x3F4D */ u8 unk_3F4D;                           // "Kenjya_no"
    /* 0x3F4E */ u16 nextDayTime;                       // "next_zelda_time"
    /* 0x3F50 */ u8 transFadeDuration;                  // "fade_speed"
    /* 0x3F51 */ u8 transWipeSpeed;                     // "wipe_speed"           transition related
    /* 0x3F52 */ u16 skyboxTime;                        // "kankyo_time"
    /* 0x3F54 */ u8 dogIsLost;                          // "dog_event_flag"
    /* 0x3F55 */ u8 nextTransitionType;                 // "next_wipe"
    /* 0x3F56 */ s16 worldMapArea;                      // "area_type"
    /* 0x3F58 */ s16 sunsSongState;                     // "sunmoon_flag"
    /* 0x3F5A */ s16 healthAccumulator;                 // "life_mode"
    /* 0x3F5C */ s32 unk_3F5C;                          // "bet_rupees"
    /* 0x3F60 */ u8 screenScaleFlag;                    // "framescale_flag"
    /* 0x3F64 */ f32 screenScale;                       // "framescale_scale"
    /* 0x3F68 */ CycleSceneFlags cycleSceneFlags[120];  // Scene flags that are temporarily stored over the duration of a single 3-day cycle
    /* 0x48C8 */ u16 dungeonIndex;                      // "scene_id_mix"
    /* 0x48CA */ u8 masksGivenOnMoon[27];               // bit-packed, masks given away on the Moon. "mask_mask_bit"
} SaveContext; // size = 0x48C8

typedef enum ButtonStatus {
    /* 0x00 */ BTN_ENABLED,
    /* 0xFF */ BTN_DISABLED = 0xFF
} ButtonStatus;

typedef enum SunsSongState {
    /* 0 */ SUNSSONG_INACTIVE,
    /* 1 */ SUNSSONG_START, // the suns ocarina effect signals that the song has finished playing
    /* 2 */ SUNSSONG_SPEED_TIME, // suns was played where time passes, speed up the advancement of time
    /* 3 */ SUNSSONG_SPECIAL // time does not advance, but signals the song was played. used for freezing redeads
} SunsSongState;

// linkAge still exists in MM, but is always set to 0 (always adult)
// There are remnants of these macros from OOT, but they are essentially useless
#define LINK_IS_CHILD (gSaveContext.save.linkAge == 1)
#define LINK_IS_ADULT (gSaveContext.save.linkAge == 0)

#define CURRENT_DAY (((void)0, gSaveContext.save.day) % 5)

// The day begins at CLOCK_TIME(6, 0) so it must be offset.
#define TIME_UNTIL_MOON_CRASH \
    ((4 - CURRENT_DAY) * DAY_LENGTH - (u16)(((void)0, gSaveContext.save.time) - CLOCK_TIME(6, 0)));
#define TIME_UNTIL_NEW_DAY (DAY_LENGTH - (u16)(((void)0, gSaveContext.save.time) - CLOCK_TIME(6, 0)));

#define GET_PLAYER_FORM ((void)0, gSaveContext.save.playerForm)

#define SLOT(item) gItemSlots[item]
#define AMMO(item) gSaveContext.save.inventory.ammo[SLOT(item)]
#define INV_CONTENT(item) gSaveContext.save.inventory.items[SLOT(item)]
#define GET_INV_CONTENT(item) ((void)0, gSaveContext.save.inventory.items)[SLOT(item)]

#define CUR_FORM ((gSaveContext.save.playerForm == PLAYER_FORM_HUMAN) ? 0 : gSaveContext.save.playerForm)

#define GET_SAVE_EQUIPS_EQUIPMENT ((void)0, gSaveContext.save.equips.equipment)
#define GET_SAVE_INVENTORY_UPGRADES ((void)0, gSaveContext.save.inventory.upgrades)
#define GET_SAVE_INVENTORY_QUEST_ITEMS ((void)0, gSaveContext.save.inventory.questItems)

#define GET_CUR_EQUIP_VALUE(equip) ((GET_SAVE_EQUIPS_EQUIPMENT & gEquipMasks[equip]) >> gEquipShifts[equip])

#define CUR_UPG_VALUE(upg) ((gSaveContext.save.inventory.upgrades & gUpgradeMasks[upg]) >> gUpgradeShifts[upg])
#define GET_CUR_UPG_VALUE(upg) ((GET_SAVE_INVENTORY_UPGRADES & gUpgradeMasks[upg]) >> gUpgradeShifts[upg])

#define SET_EQUIP_VALUE(equip, value) (gSaveContext.save.equips.equipment = ((GET_SAVE_EQUIPS_EQUIPMENT & gEquipNegMasks[equip]) | (u16)((u16)(value) << gEquipShifts[equip])))

#define BUTTON_ITEM_EQUIP(form, button) (gSaveContext.save.equips.buttonItems[form][button])
#define CUR_FORM_EQUIP(button) BUTTON_ITEM_EQUIP(CUR_FORM, button)

#define C_SLOT_EQUIP(form, button) (gSaveContext.save.equips.cButtonSlots[form][button])
#define CHECK_QUEST_ITEM(item) (GET_SAVE_INVENTORY_QUEST_ITEMS & gBitFlags[item])
#define SET_QUEST_ITEM(item) (gSaveContext.save.inventory.questItems = (GET_SAVE_INVENTORY_QUEST_ITEMS | gBitFlags[item]))
#define REMOVE_QUEST_ITEM(item) (gSaveContext.save.inventory.questItems = (GET_SAVE_INVENTORY_QUEST_ITEMS & (-1 - gBitFlags[item])))

#define GET_QUEST_HEART_PIECE_COUNT ((GET_SAVE_INVENTORY_QUEST_ITEMS & 0xF0000000) >> QUEST_HEART_PIECE_COUNT)
#define EQ_MAX_QUEST_HEART_PIECE_COUNT ((GET_SAVE_INVENTORY_QUEST_ITEMS & 0xF0000000) == (4 << QUEST_HEART_PIECE_COUNT))
#define LEQ_MAX_QUEST_HEART_PIECE_COUNT ((GET_SAVE_INVENTORY_QUEST_ITEMS & 0xF0000000) <= (4 << QUEST_HEART_PIECE_COUNT))
#define INCREMENT_QUEST_HEART_PIECE_COUNT (gSaveContext.save.inventory.questItems += (1 << QUEST_HEART_PIECE_COUNT))
#define DECREMENT_QUEST_HEART_PIECE_COUNT (gSaveContext.save.inventory.questItems -= (1 << QUEST_HEART_PIECE_COUNT))
#define RESET_HEART_PIECE_COUNT (gSaveContext.save.inventory.questItems ^= (4 << QUEST_HEART_PIECE_COUNT))

#define CHECK_DUNGEON_ITEM(item, dungeonIndex) (gSaveContext.save.inventory.dungeonItems[(void)0, dungeonIndex] & gBitFlags[item])
#define SET_DUNGEON_ITEM(item, dungeonIndex) (gSaveContext.save.inventory.dungeonItems[(void)0, dungeonIndex] |= (u8)gBitFlags[item])
#define DUNGEON_KEY_COUNT(dungeonIndex) (gSaveContext.save.inventory.dungeonKeys[(void)0, dungeonIndex])

#define GET_CUR_FORM_BTN_ITEM(btn) ((u8)((btn) == EQUIP_SLOT_B ? BUTTON_ITEM_EQUIP(CUR_FORM, btn) : BUTTON_ITEM_EQUIP(0, btn)))
#define GET_CUR_FORM_BTN_SLOT(btn) ((u8)((btn) == EQUIP_SLOT_B ? C_SLOT_EQUIP(CUR_FORM, btn) : C_SLOT_EQUIP(0, btn)))

#define C_BTN_ITEM(btn)                                 \
    ((gSaveContext.buttonStatus[(btn)] != BTN_DISABLED) \
         ? BUTTON_ITEM_EQUIP(0, (btn))                  \
         : ((gSaveContext.hudVisibility == HUD_VISIBILITY_A_B_C) ? BUTTON_ITEM_EQUIP(0, (btn)) : ITEM_NONE))

#define SET_CUR_FORM_BTN_ITEM(btn, item)             \
    if ((btn) == EQUIP_SLOT_B) {                     \
        BUTTON_ITEM_EQUIP(CUR_FORM, (btn)) = (item); \
    } else {                                         \
        BUTTON_ITEM_EQUIP(0, (btn)) = (item);        \
    }                                                \
    (void)0

#define SET_CUR_FORM_BTN_SLOT(btn, item)        \
    if ((btn) == EQUIP_SLOT_B) {                \
        C_SLOT_EQUIP(CUR_FORM, (btn)) = (item); \
    } else {                                    \
        C_SLOT_EQUIP(0, (btn)) = (item);        \
    }                                           \
    (void)0

#define STOLEN_ITEM_NONE (0)

#define STOLEN_ITEM_1 ((gSaveContext.save.stolenItems & 0xFF000000) >> 0x18)
#define STOLEN_ITEM_2 ((gSaveContext.save.stolenItems & 0x00FF0000) >> 0x10)

#define SET_STOLEN_ITEM_1(itemId) \
    (gSaveContext.save.stolenItems = (gSaveContext.save.stolenItems & ~0xFF000000) | ((itemId & 0xFF) << 0x18))
#define SET_STOLEN_ITEM_2(itemId) \
    (gSaveContext.save.stolenItems = (gSaveContext.save.stolenItems & ~0x00FF0000) | ((itemId & 0xFF) << 0x10))

#define GET_TOWN_SHOOTING_GALLERY_HIGH_SCORE() ((s32)(gSaveContext.save.shootingGalleryHighScores & 0xFFFF))
#define GET_SWAMP_SHOOTING_GALLERY_HIGH_SCORE() ((s32)((gSaveContext.save.shootingGalleryHighScores & 0xFFFF0000) >> 0x10))
#define SET_TOWN_SHOOTING_GALLERY_HIGH_SCORE(score) (gSaveContext.save.shootingGalleryHighScores = (gSaveContext.save.shootingGalleryHighScores & 0xFFFF0000) | ((u16)(score)))
#define SET_SWAMP_SHOOTING_GALLERY_HIGH_SCORE(score) (gSaveContext.save.shootingGalleryHighScores = ((gSaveContext.save.shootingGalleryHighScores) & 0xFFFF) | ((u16)(score) << 0x10))

/**
 * gSaveContext.save.weekEventReg
 */

#define PACK_WEEKEVENTREG_FLAG(index, mask) (((index) << 8) | (mask))

#define WEEKEVENTREG_00_01 PACK_WEEKEVENTREG_FLAG(0, 0x01)
#define WEEKEVENTREG_00_02 PACK_WEEKEVENTREG_FLAG(0, 0x02)
#define WEEKEVENTREG_00_04 PACK_WEEKEVENTREG_FLAG(0, 0x04)
#define WEEKEVENTREG_00_08 PACK_WEEKEVENTREG_FLAG(0, 0x08)
#define WEEKEVENTREG_00_10 PACK_WEEKEVENTREG_FLAG(0, 0x10)
#define WEEKEVENTREG_00_20 PACK_WEEKEVENTREG_FLAG(0, 0x20)
#define WEEKEVENTREG_00_40 PACK_WEEKEVENTREG_FLAG(0, 0x40)
#define WEEKEVENTREG_00_80 PACK_WEEKEVENTREG_FLAG(0, 0x80)
#define WEEKEVENTREG_01_01 PACK_WEEKEVENTREG_FLAG(1, 0x01)
#define WEEKEVENTREG_01_02 PACK_WEEKEVENTREG_FLAG(1, 0x02)
#define WEEKEVENTREG_01_04 PACK_WEEKEVENTREG_FLAG(1, 0x04)
#define WEEKEVENTREG_01_08 PACK_WEEKEVENTREG_FLAG(1, 0x08)
#define WEEKEVENTREG_01_10 PACK_WEEKEVENTREG_FLAG(1, 0x10)
#define WEEKEVENTREG_01_20 PACK_WEEKEVENTREG_FLAG(1, 0x20)
#define WEEKEVENTREG_01_40 PACK_WEEKEVENTREG_FLAG(1, 0x40)
#define WEEKEVENTREG_01_80 PACK_WEEKEVENTREG_FLAG(1, 0x80)
#define WEEKEVENTREG_02_01 PACK_WEEKEVENTREG_FLAG(2, 0x01)
#define WEEKEVENTREG_02_02 PACK_WEEKEVENTREG_FLAG(2, 0x02)
#define WEEKEVENTREG_02_04 PACK_WEEKEVENTREG_FLAG(2, 0x04)
#define WEEKEVENTREG_02_08 PACK_WEEKEVENTREG_FLAG(2, 0x08)
#define WEEKEVENTREG_02_10 PACK_WEEKEVENTREG_FLAG(2, 0x10)
#define WEEKEVENTREG_02_20 PACK_WEEKEVENTREG_FLAG(2, 0x20)
#define WEEKEVENTREG_02_40 PACK_WEEKEVENTREG_FLAG(2, 0x40)
#define WEEKEVENTREG_02_80 PACK_WEEKEVENTREG_FLAG(2, 0x80)
#define WEEKEVENTREG_03_01 PACK_WEEKEVENTREG_FLAG(3, 0x01)
#define WEEKEVENTREG_03_02 PACK_WEEKEVENTREG_FLAG(3, 0x02)
#define WEEKEVENTREG_03_04 PACK_WEEKEVENTREG_FLAG(3, 0x04)
#define WEEKEVENTREG_03_08 PACK_WEEKEVENTREG_FLAG(3, 0x08)
#define WEEKEVENTREG_03_10 PACK_WEEKEVENTREG_FLAG(3, 0x10)
#define WEEKEVENTREG_03_20 PACK_WEEKEVENTREG_FLAG(3, 0x20)
#define WEEKEVENTREG_03_40 PACK_WEEKEVENTREG_FLAG(3, 0x40)
#define WEEKEVENTREG_03_80 PACK_WEEKEVENTREG_FLAG(3, 0x80)
#define WEEKEVENTREG_04_01 PACK_WEEKEVENTREG_FLAG(4, 0x01)
#define WEEKEVENTREG_04_02 PACK_WEEKEVENTREG_FLAG(4, 0x02)
#define WEEKEVENTREG_04_04 PACK_WEEKEVENTREG_FLAG(4, 0x04)
#define WEEKEVENTREG_04_08 PACK_WEEKEVENTREG_FLAG(4, 0x08)
#define WEEKEVENTREG_04_10 PACK_WEEKEVENTREG_FLAG(4, 0x10)
#define WEEKEVENTREG_04_20 PACK_WEEKEVENTREG_FLAG(4, 0x20)
#define WEEKEVENTREG_04_40 PACK_WEEKEVENTREG_FLAG(4, 0x40)
#define WEEKEVENTREG_04_80 PACK_WEEKEVENTREG_FLAG(4, 0x80)
#define WEEKEVENTREG_05_01 PACK_WEEKEVENTREG_FLAG(5, 0x01)
#define WEEKEVENTREG_05_02 PACK_WEEKEVENTREG_FLAG(5, 0x02)
#define WEEKEVENTREG_05_04 PACK_WEEKEVENTREG_FLAG(5, 0x04)
#define WEEKEVENTREG_05_08 PACK_WEEKEVENTREG_FLAG(5, 0x08)
#define WEEKEVENTREG_05_10 PACK_WEEKEVENTREG_FLAG(5, 0x10)
#define WEEKEVENTREG_05_20 PACK_WEEKEVENTREG_FLAG(5, 0x20)
#define WEEKEVENTREG_05_40 PACK_WEEKEVENTREG_FLAG(5, 0x40)
#define WEEKEVENTREG_05_80 PACK_WEEKEVENTREG_FLAG(5, 0x80)
#define WEEKEVENTREG_06_01 PACK_WEEKEVENTREG_FLAG(6, 0x01)
#define WEEKEVENTREG_06_02 PACK_WEEKEVENTREG_FLAG(6, 0x02)
#define WEEKEVENTREG_06_04 PACK_WEEKEVENTREG_FLAG(6, 0x04)
#define WEEKEVENTREG_06_08 PACK_WEEKEVENTREG_FLAG(6, 0x08)
#define WEEKEVENTREG_06_10 PACK_WEEKEVENTREG_FLAG(6, 0x10)
#define WEEKEVENTREG_06_20 PACK_WEEKEVENTREG_FLAG(6, 0x20)
#define WEEKEVENTREG_06_40 PACK_WEEKEVENTREG_FLAG(6, 0x40)
#define WEEKEVENTREG_06_80 PACK_WEEKEVENTREG_FLAG(6, 0x80)
#define WEEKEVENTREG_07_01 PACK_WEEKEVENTREG_FLAG(7, 0x01)
#define WEEKEVENTREG_07_02 PACK_WEEKEVENTREG_FLAG(7, 0x02)
#define WEEKEVENTREG_07_04 PACK_WEEKEVENTREG_FLAG(7, 0x04)
#define WEEKEVENTREG_07_08 PACK_WEEKEVENTREG_FLAG(7, 0x08)
#define WEEKEVENTREG_07_10 PACK_WEEKEVENTREG_FLAG(7, 0x10)
#define WEEKEVENTREG_07_20 PACK_WEEKEVENTREG_FLAG(7, 0x20)
#define WEEKEVENTREG_07_40 PACK_WEEKEVENTREG_FLAG(7, 0x40)
#define WEEKEVENTREG_07_80 PACK_WEEKEVENTREG_FLAG(7, 0x80)
#define WEEKEVENTREG_08_01 PACK_WEEKEVENTREG_FLAG(8, 0x01)
#define WEEKEVENTREG_08_02 PACK_WEEKEVENTREG_FLAG(8, 0x02)
#define WEEKEVENTREG_08_04 PACK_WEEKEVENTREG_FLAG(8, 0x04)
#define WEEKEVENTREG_08_08 PACK_WEEKEVENTREG_FLAG(8, 0x08)
#define WEEKEVENTREG_08_10 PACK_WEEKEVENTREG_FLAG(8, 0x10)
#define WEEKEVENTREG_08_20 PACK_WEEKEVENTREG_FLAG(8, 0x20)
#define WEEKEVENTREG_08_40 PACK_WEEKEVENTREG_FLAG(8, 0x40)
#define WEEKEVENTREG_08_80 PACK_WEEKEVENTREG_FLAG(8, 0x80)
#define WEEKEVENTREG_09_01 PACK_WEEKEVENTREG_FLAG(9, 0x01)
#define WEEKEVENTREG_09_02 PACK_WEEKEVENTREG_FLAG(9, 0x02)
#define WEEKEVENTREG_09_04 PACK_WEEKEVENTREG_FLAG(9, 0x04)
#define WEEKEVENTREG_09_08 PACK_WEEKEVENTREG_FLAG(9, 0x08)
#define WEEKEVENTREG_09_10 PACK_WEEKEVENTREG_FLAG(9, 0x10)
#define WEEKEVENTREG_09_20 PACK_WEEKEVENTREG_FLAG(9, 0x20)
#define WEEKEVENTREG_09_40 PACK_WEEKEVENTREG_FLAG(9, 0x40)
#define WEEKEVENTREG_09_80 PACK_WEEKEVENTREG_FLAG(9, 0x80)
#define WEEKEVENTREG_10_01 PACK_WEEKEVENTREG_FLAG(10, 0x01)
#define WEEKEVENTREG_10_02 PACK_WEEKEVENTREG_FLAG(10, 0x02)
#define WEEKEVENTREG_10_04 PACK_WEEKEVENTREG_FLAG(10, 0x04)
#define WEEKEVENTREG_10_08 PACK_WEEKEVENTREG_FLAG(10, 0x08)
#define WEEKEVENTREG_10_10 PACK_WEEKEVENTREG_FLAG(10, 0x10)
#define WEEKEVENTREG_10_20 PACK_WEEKEVENTREG_FLAG(10, 0x20)
#define WEEKEVENTREG_10_40 PACK_WEEKEVENTREG_FLAG(10, 0x40)
#define WEEKEVENTREG_10_80 PACK_WEEKEVENTREG_FLAG(10, 0x80)
#define WEEKEVENTREG_11_01 PACK_WEEKEVENTREG_FLAG(11, 0x01)
#define WEEKEVENTREG_11_02 PACK_WEEKEVENTREG_FLAG(11, 0x02)
#define WEEKEVENTREG_11_04 PACK_WEEKEVENTREG_FLAG(11, 0x04)
#define WEEKEVENTREG_11_08 PACK_WEEKEVENTREG_FLAG(11, 0x08)
#define WEEKEVENTREG_11_10 PACK_WEEKEVENTREG_FLAG(11, 0x10)
#define WEEKEVENTREG_11_20 PACK_WEEKEVENTREG_FLAG(11, 0x20)
#define WEEKEVENTREG_11_40 PACK_WEEKEVENTREG_FLAG(11, 0x40)
#define WEEKEVENTREG_11_80 PACK_WEEKEVENTREG_FLAG(11, 0x80)

// woodfall temple wood flower opened
#define WEEKEVENTREG_12_01 PACK_WEEKEVENTREG_FLAG(12, 0x01)

#define WEEKEVENTREG_12_02 PACK_WEEKEVENTREG_FLAG(12, 0x02)
#define WEEKEVENTREG_12_04 PACK_WEEKEVENTREG_FLAG(12, 0x04)
#define WEEKEVENTREG_12_08 PACK_WEEKEVENTREG_FLAG(12, 0x08)
#define WEEKEVENTREG_12_10 PACK_WEEKEVENTREG_FLAG(12, 0x10)
#define WEEKEVENTREG_12_20 PACK_WEEKEVENTREG_FLAG(12, 0x20)
#define WEEKEVENTREG_12_40 PACK_WEEKEVENTREG_FLAG(12, 0x40)
#define WEEKEVENTREG_12_80 PACK_WEEKEVENTREG_FLAG(12, 0x80)
#define WEEKEVENTREG_13_01 PACK_WEEKEVENTREG_FLAG(13, 0x01)
#define WEEKEVENTREG_13_02 PACK_WEEKEVENTREG_FLAG(13, 0x02)
#define WEEKEVENTREG_13_04 PACK_WEEKEVENTREG_FLAG(13, 0x04)
#define WEEKEVENTREG_13_08 PACK_WEEKEVENTREG_FLAG(13, 0x08)
#define WEEKEVENTREG_13_10 PACK_WEEKEVENTREG_FLAG(13, 0x10)
#define WEEKEVENTREG_13_20 PACK_WEEKEVENTREG_FLAG(13, 0x20)
#define WEEKEVENTREG_13_40 PACK_WEEKEVENTREG_FLAG(13, 0x40)
#define WEEKEVENTREG_13_80 PACK_WEEKEVENTREG_FLAG(13, 0x80)

// PlayedMilkMinigame
// Attempted Cremia Cart Ride
#define WEEKEVENTREG_14_01 PACK_WEEKEVENTREG_FLAG(14, 0x01)

#define WEEKEVENTREG_14_02 PACK_WEEKEVENTREG_FLAG(14, 0x02)
#define WEEKEVENTREG_14_04 PACK_WEEKEVENTREG_FLAG(14, 0x04)
#define WEEKEVENTREG_DRANK_CHATEAU_ROMANI PACK_WEEKEVENTREG_FLAG(14, 0x08)
#define WEEKEVENTREG_14_10 PACK_WEEKEVENTREG_FLAG(14, 0x10)
#define WEEKEVENTREG_14_20 PACK_WEEKEVENTREG_FLAG(14, 0x20)
#define WEEKEVENTREG_14_40 PACK_WEEKEVENTREG_FLAG(14, 0x40)
#define WEEKEVENTREG_14_80 PACK_WEEKEVENTREG_FLAG(14, 0x80)
#define WEEKEVENTREG_15_01 PACK_WEEKEVENTREG_FLAG(15, 0x01)
#define WEEKEVENTREG_15_02 PACK_WEEKEVENTREG_FLAG(15, 0x02)
#define WEEKEVENTREG_15_04 PACK_WEEKEVENTREG_FLAG(15, 0x04)
#define WEEKEVENTREG_15_08 PACK_WEEKEVENTREG_FLAG(15, 0x08)
#define WEEKEVENTREG_15_10 PACK_WEEKEVENTREG_FLAG(15, 0x10)
#define WEEKEVENTREG_15_20 PACK_WEEKEVENTREG_FLAG(15, 0x20)
#define WEEKEVENTREG_15_40 PACK_WEEKEVENTREG_FLAG(15, 0x40)
#define WEEKEVENTREG_15_80 PACK_WEEKEVENTREG_FLAG(15, 0x80)
#define WEEKEVENTREG_16_01 PACK_WEEKEVENTREG_FLAG(16, 0x01)
#define WEEKEVENTREG_16_02 PACK_WEEKEVENTREG_FLAG(16, 0x02)
#define WEEKEVENTREG_16_04 PACK_WEEKEVENTREG_FLAG(16, 0x04)
#define WEEKEVENTREG_16_08 PACK_WEEKEVENTREG_FLAG(16, 0x08)
#define WEEKEVENTREG_16_10 PACK_WEEKEVENTREG_FLAG(16, 0x10)
#define WEEKEVENTREG_16_20 PACK_WEEKEVENTREG_FLAG(16, 0x20)
#define WEEKEVENTREG_16_40 PACK_WEEKEVENTREG_FLAG(16, 0x40)
#define WEEKEVENTREG_16_80 PACK_WEEKEVENTREG_FLAG(16, 0x80)
#define WEEKEVENTREG_17_01 PACK_WEEKEVENTREG_FLAG(17, 0x01)
#define WEEKEVENTREG_17_02 PACK_WEEKEVENTREG_FLAG(17, 0x02)
#define WEEKEVENTREG_17_04 PACK_WEEKEVENTREG_FLAG(17, 0x04)
#define WEEKEVENTREG_17_08 PACK_WEEKEVENTREG_FLAG(17, 0x08)
#define WEEKEVENTREG_17_10 PACK_WEEKEVENTREG_FLAG(17, 0x10)
#define WEEKEVENTREG_17_20 PACK_WEEKEVENTREG_FLAG(17, 0x20)
#define WEEKEVENTREG_17_40 PACK_WEEKEVENTREG_FLAG(17, 0x40)
#define WEEKEVENTREG_17_80 PACK_WEEKEVENTREG_FLAG(17, 0x80)
#define WEEKEVENTREG_18_01 PACK_WEEKEVENTREG_FLAG(18, 0x01)
#define WEEKEVENTREG_18_02 PACK_WEEKEVENTREG_FLAG(18, 0x02)
#define WEEKEVENTREG_18_04 PACK_WEEKEVENTREG_FLAG(18, 0x04)
#define WEEKEVENTREG_18_08 PACK_WEEKEVENTREG_FLAG(18, 0x08)
#define WEEKEVENTREG_18_10 PACK_WEEKEVENTREG_FLAG(18, 0x10)
#define WEEKEVENTREG_18_20 PACK_WEEKEVENTREG_FLAG(18, 0x20)
#define WEEKEVENTREG_18_40 PACK_WEEKEVENTREG_FLAG(18, 0x40)
#define WEEKEVENTREG_18_80 PACK_WEEKEVENTREG_FLAG(18, 0x80)
#define WEEKEVENTREG_19_01 PACK_WEEKEVENTREG_FLAG(19, 0x01)
#define WEEKEVENTREG_19_02 PACK_WEEKEVENTREG_FLAG(19, 0x02)
#define WEEKEVENTREG_19_04 PACK_WEEKEVENTREG_FLAG(19, 0x04)
#define WEEKEVENTREG_19_08 PACK_WEEKEVENTREG_FLAG(19, 0x08)
#define WEEKEVENTREG_19_10 PACK_WEEKEVENTREG_FLAG(19, 0x10)
#define WEEKEVENTREG_19_20 PACK_WEEKEVENTREG_FLAG(19, 0x20)
#define WEEKEVENTREG_19_40 PACK_WEEKEVENTREG_FLAG(19, 0x40)
#define WEEKEVENTREG_19_80 PACK_WEEKEVENTREG_FLAG(19, 0x80)
#define WEEKEVENTREG_20_01 PACK_WEEKEVENTREG_FLAG(20, 0x01)

// woodfall temple purification cutscene watched
#define WEEKEVENTREG_20_02 PACK_WEEKEVENTREG_FLAG(20, 0x02)

#define WEEKEVENTREG_20_04 PACK_WEEKEVENTREG_FLAG(20, 0x04)
#define WEEKEVENTREG_20_08 PACK_WEEKEVENTREG_FLAG(20, 0x08)
#define WEEKEVENTREG_20_10 PACK_WEEKEVENTREG_FLAG(20, 0x10)
#define WEEKEVENTREG_20_20 PACK_WEEKEVENTREG_FLAG(20, 0x20)
#define WEEKEVENTREG_20_40 PACK_WEEKEVENTREG_FLAG(20, 0x40)
#define WEEKEVENTREG_20_80 PACK_WEEKEVENTREG_FLAG(20, 0x80)
#define WEEKEVENTREG_21_01 PACK_WEEKEVENTREG_FLAG(21, 0x01)
#define WEEKEVENTREG_21_02 PACK_WEEKEVENTREG_FLAG(21, 0x02)
#define WEEKEVENTREG_21_04 PACK_WEEKEVENTREG_FLAG(21, 0x04)
#define WEEKEVENTREG_21_08 PACK_WEEKEVENTREG_FLAG(21, 0x08)
#define WEEKEVENTREG_21_10 PACK_WEEKEVENTREG_FLAG(21, 0x10)
#define WEEKEVENTREG_21_20 PACK_WEEKEVENTREG_FLAG(21, 0x20)
#define WEEKEVENTREG_21_40 PACK_WEEKEVENTREG_FLAG(21, 0x40)
#define WEEKEVENTREG_21_80 PACK_WEEKEVENTREG_FLAG(21, 0x80)

// Aliens defeated
// "Winning" the alien invasion
#define WEEKEVENTREG_22_01 PACK_WEEKEVENTREG_FLAG(22, 0x01)

#define WEEKEVENTREG_22_02 PACK_WEEKEVENTREG_FLAG(22, 0x02)
#define WEEKEVENTREG_22_04 PACK_WEEKEVENTREG_FLAG(22, 0x04)
#define WEEKEVENTREG_22_08 PACK_WEEKEVENTREG_FLAG(22, 0x08)
#define WEEKEVENTREG_22_10 PACK_WEEKEVENTREG_FLAG(22, 0x10)
#define WEEKEVENTREG_22_20 PACK_WEEKEVENTREG_FLAG(22, 0x20)
#define WEEKEVENTREG_22_40 PACK_WEEKEVENTREG_FLAG(22, 0x40)
#define WEEKEVENTREG_22_80 PACK_WEEKEVENTREG_FLAG(22, 0x80)
#define WEEKEVENTREG_23_01 PACK_WEEKEVENTREG_FLAG(23, 0x01)
#define WEEKEVENTREG_23_02 PACK_WEEKEVENTREG_FLAG(23, 0x02)
#define WEEKEVENTREG_23_04 PACK_WEEKEVENTREG_FLAG(23, 0x04)
#define WEEKEVENTREG_23_08 PACK_WEEKEVENTREG_FLAG(23, 0x08)
#define WEEKEVENTREG_23_10 PACK_WEEKEVENTREG_FLAG(23, 0x10)
#define WEEKEVENTREG_23_20 PACK_WEEKEVENTREG_FLAG(23, 0x20)
#define WEEKEVENTREG_23_40 PACK_WEEKEVENTREG_FLAG(23, 0x40)
#define WEEKEVENTREG_23_80 PACK_WEEKEVENTREG_FLAG(23, 0x80)
#define WEEKEVENTREG_24_01 PACK_WEEKEVENTREG_FLAG(24, 0x01)
#define WEEKEVENTREG_24_02 PACK_WEEKEVENTREG_FLAG(24, 0x02)
#define WEEKEVENTREG_24_04 PACK_WEEKEVENTREG_FLAG(24, 0x04)
#define WEEKEVENTREG_24_08 PACK_WEEKEVENTREG_FLAG(24, 0x08)

// The player has already talked as a Goron at least once to Goron elder
#define WEEKEVENTREG_24_10 PACK_WEEKEVENTREG_FLAG(24, 0x10)

// The player has already talked as a non-Goron at least once
#define WEEKEVENTREG_24_20 PACK_WEEKEVENTREG_FLAG(24, 0x20)

#define WEEKEVENTREG_24_40 PACK_WEEKEVENTREG_FLAG(24, 0x40)

// The player has talked to the Goron Child at least once
#define WEEKEVENTREG_24_80 PACK_WEEKEVENTREG_FLAG(24, 0x80)

#define WEEKEVENTREG_25_01 PACK_WEEKEVENTREG_FLAG(25, 0x01)
#define WEEKEVENTREG_25_02 PACK_WEEKEVENTREG_FLAG(25, 0x02)
#define WEEKEVENTREG_25_04 PACK_WEEKEVENTREG_FLAG(25, 0x04)

// breman mask was already used
#define WEEKEVENTREG_25_08 PACK_WEEKEVENTREG_FLAG(25, 0x08)

#define WEEKEVENTREG_25_10 PACK_WEEKEVENTREG_FLAG(25, 0x10)
#define WEEKEVENTREG_25_20 PACK_WEEKEVENTREG_FLAG(25, 0x20)
#define WEEKEVENTREG_25_40 PACK_WEEKEVENTREG_FLAG(25, 0x40)
#define WEEKEVENTREG_25_80 PACK_WEEKEVENTREG_FLAG(25, 0x80)
#define WEEKEVENTREG_26_01 PACK_WEEKEVENTREG_FLAG(26, 0x01)
#define WEEKEVENTREG_26_02 PACK_WEEKEVENTREG_FLAG(26, 0x02)
#define WEEKEVENTREG_26_04 PACK_WEEKEVENTREG_FLAG(26, 0x04)
#define WEEKEVENTREG_26_08 PACK_WEEKEVENTREG_FLAG(26, 0x08)
#define WEEKEVENTREG_26_10 PACK_WEEKEVENTREG_FLAG(26, 0x10)
#define WEEKEVENTREG_26_20 PACK_WEEKEVENTREG_FLAG(26, 0x20)
#define WEEKEVENTREG_26_40 PACK_WEEKEVENTREG_FLAG(26, 0x40)
#define WEEKEVENTREG_26_80 PACK_WEEKEVENTREG_FLAG(26, 0x80)
#define WEEKEVENTREG_27_01 PACK_WEEKEVENTREG_FLAG(27, 0x01)
#define WEEKEVENTREG_27_02 PACK_WEEKEVENTREG_FLAG(27, 0x02)
#define WEEKEVENTREG_27_04 PACK_WEEKEVENTREG_FLAG(27, 0x04)
#define WEEKEVENTREG_27_08 PACK_WEEKEVENTREG_FLAG(27, 0x08)
#define WEEKEVENTREG_27_10 PACK_WEEKEVENTREG_FLAG(27, 0x10)
#define WEEKEVENTREG_27_20 PACK_WEEKEVENTREG_FLAG(27, 0x20)
#define WEEKEVENTREG_27_40 PACK_WEEKEVENTREG_FLAG(27, 0x40)
#define WEEKEVENTREG_27_80 PACK_WEEKEVENTREG_FLAG(27, 0x80)
#define WEEKEVENTREG_28_01 PACK_WEEKEVENTREG_FLAG(28, 0x01)
#define WEEKEVENTREG_28_02 PACK_WEEKEVENTREG_FLAG(28, 0x02)
#define WEEKEVENTREG_28_04 PACK_WEEKEVENTREG_FLAG(28, 0x04)
#define WEEKEVENTREG_28_08 PACK_WEEKEVENTREG_FLAG(28, 0x08)
#define WEEKEVENTREG_28_10 PACK_WEEKEVENTREG_FLAG(28, 0x10)
#define WEEKEVENTREG_28_20 PACK_WEEKEVENTREG_FLAG(28, 0x20)
#define WEEKEVENTREG_28_40 PACK_WEEKEVENTREG_FLAG(28, 0x40)
#define WEEKEVENTREG_28_80 PACK_WEEKEVENTREG_FLAG(28, 0x80)
#define WEEKEVENTREG_29_01 PACK_WEEKEVENTREG_FLAG(29, 0x01)
#define WEEKEVENTREG_29_02 PACK_WEEKEVENTREG_FLAG(29, 0x02)
#define WEEKEVENTREG_29_04 PACK_WEEKEVENTREG_FLAG(29, 0x04)
#define WEEKEVENTREG_29_08 PACK_WEEKEVENTREG_FLAG(29, 0x08)
#define WEEKEVENTREG_29_10 PACK_WEEKEVENTREG_FLAG(29, 0x10)
#define WEEKEVENTREG_29_20 PACK_WEEKEVENTREG_FLAG(29, 0x20)
#define WEEKEVENTREG_29_40 PACK_WEEKEVENTREG_FLAG(29, 0x40)
#define WEEKEVENTREG_29_80 PACK_WEEKEVENTREG_FLAG(29, 0x80)
#define WEEKEVENTREG_30_01 PACK_WEEKEVENTREG_FLAG(30, 0x01)
#define WEEKEVENTREG_30_02 PACK_WEEKEVENTREG_FLAG(30, 0x02)
#define WEEKEVENTREG_30_04 PACK_WEEKEVENTREG_FLAG(30, 0x04)
#define WEEKEVENTREG_30_08 PACK_WEEKEVENTREG_FLAG(30, 0x08)
#define WEEKEVENTREG_30_10 PACK_WEEKEVENTREG_FLAG(30, 0x10)
#define WEEKEVENTREG_30_20 PACK_WEEKEVENTREG_FLAG(30, 0x20)
#define WEEKEVENTREG_30_40 PACK_WEEKEVENTREG_FLAG(30, 0x40)
#define WEEKEVENTREG_30_80 PACK_WEEKEVENTREG_FLAG(30, 0x80)
#define WEEKEVENTREG_31_01 PACK_WEEKEVENTREG_FLAG(31, 0x01)
#define WEEKEVENTREG_31_02 PACK_WEEKEVENTREG_FLAG(31, 0x02)

// Unconfirmed: "Tatl's Second Cycle Text?"
#define WEEKEVENTREG_31_04 PACK_WEEKEVENTREG_FLAG(31, 0x04)

#define WEEKEVENTREG_31_08 PACK_WEEKEVENTREG_FLAG(31, 0x08)
#define WEEKEVENTREG_31_10 PACK_WEEKEVENTREG_FLAG(31, 0x10)
#define WEEKEVENTREG_31_20 PACK_WEEKEVENTREG_FLAG(31, 0x20)

// Cremia asked the player to accompany her to town
#define WEEKEVENTREG_31_40 PACK_WEEKEVENTREG_FLAG(31, 0x40)
// Player is playing the Milk Run
#define WEEKEVENTREG_31_80 PACK_WEEKEVENTREG_FLAG(31, 0x80)

#define WEEKEVENTREG_32_01 PACK_WEEKEVENTREG_FLAG(32, 0x01)
#define WEEKEVENTREG_32_02 PACK_WEEKEVENTREG_FLAG(32, 0x02)
#define WEEKEVENTREG_32_04 PACK_WEEKEVENTREG_FLAG(32, 0x04)
#define WEEKEVENTREG_32_08 PACK_WEEKEVENTREG_FLAG(32, 0x08)
#define WEEKEVENTREG_32_10 PACK_WEEKEVENTREG_FLAG(32, 0x10)
#define WEEKEVENTREG_32_20 PACK_WEEKEVENTREG_FLAG(32, 0x20)

// Woodfall Temple Frog Returned
#define WEEKEVENTREG_32_40 PACK_WEEKEVENTREG_FLAG(32, 0x40)
// Great Bay Temple Frog Returned
#define WEEKEVENTREG_32_80 PACK_WEEKEVENTREG_FLAG(32, 0x80)
// Southern Swamp Frog Returned
#define WEEKEVENTREG_33_01 PACK_WEEKEVENTREG_FLAG(33, 0x01)
// Laundry Pool Frog Returned
#define WEEKEVENTREG_33_02 PACK_WEEKEVENTREG_FLAG(33, 0x02)

#define WEEKEVENTREG_33_04 PACK_WEEKEVENTREG_FLAG(33, 0x04)
#define WEEKEVENTREG_33_08 PACK_WEEKEVENTREG_FLAG(33, 0x08)
#define WEEKEVENTREG_33_10 PACK_WEEKEVENTREG_FLAG(33, 0x10)
#define WEEKEVENTREG_33_20 PACK_WEEKEVENTREG_FLAG(33, 0x20)
#define WEEKEVENTREG_33_40 PACK_WEEKEVENTREG_FLAG(33, 0x40)

// Mountain village is unfrozen
#define WEEKEVENTREG_33_80 PACK_WEEKEVENTREG_FLAG(33, 0x80)
// Spoken to MINIFROG_YELLOW
#define WEEKEVENTREG_34_01 PACK_WEEKEVENTREG_FLAG(34, 0x01)

#define WEEKEVENTREG_34_02 PACK_WEEKEVENTREG_FLAG(34, 0x02)
#define WEEKEVENTREG_34_04 PACK_WEEKEVENTREG_FLAG(34, 0x04)
#define WEEKEVENTREG_34_08 PACK_WEEKEVENTREG_FLAG(34, 0x08)
#define WEEKEVENTREG_34_10 PACK_WEEKEVENTREG_FLAG(34, 0x10)
#define WEEKEVENTREG_34_20 PACK_WEEKEVENTREG_FLAG(34, 0x20)
#define WEEKEVENTREG_34_40 PACK_WEEKEVENTREG_FLAG(34, 0x40)

// Cremia did Milk Run alone. Player didn't interact or didn't accept the ride
#define WEEKEVENTREG_34_80 PACK_WEEKEVENTREG_FLAG(34, 0x80)

#define WEEKEVENTREG_35_01 PACK_WEEKEVENTREG_FLAG(35, 0x01)
#define WEEKEVENTREG_35_02 PACK_WEEKEVENTREG_FLAG(35, 0x02)
#define WEEKEVENTREG_35_04 PACK_WEEKEVENTREG_FLAG(35, 0x04)
#define WEEKEVENTREG_35_08 PACK_WEEKEVENTREG_FLAG(35, 0x08)
#define WEEKEVENTREG_35_10 PACK_WEEKEVENTREG_FLAG(35, 0x10)
#define WEEKEVENTREG_35_20 PACK_WEEKEVENTREG_FLAG(35, 0x20)
#define WEEKEVENTREG_35_40 PACK_WEEKEVENTREG_FLAG(35, 0x40)

// Obtained Heart Piece from Five Frogs of the Frog Choir
#define WEEKEVENTREG_35_80 PACK_WEEKEVENTREG_FLAG(35, 0x80)

#define WEEKEVENTREG_36_01 PACK_WEEKEVENTREG_FLAG(36, 0x01)
#define WEEKEVENTREG_36_02 PACK_WEEKEVENTREG_FLAG(36, 0x02)
#define WEEKEVENTREG_36_04 PACK_WEEKEVENTREG_FLAG(36, 0x04)
#define WEEKEVENTREG_36_08 PACK_WEEKEVENTREG_FLAG(36, 0x08)
#define WEEKEVENTREG_36_10 PACK_WEEKEVENTREG_FLAG(36, 0x10)
#define WEEKEVENTREG_36_20 PACK_WEEKEVENTREG_FLAG(36, 0x20)
#define WEEKEVENTREG_36_40 PACK_WEEKEVENTREG_FLAG(36, 0x40)
#define WEEKEVENTREG_36_80 PACK_WEEKEVENTREG_FLAG(36, 0x80)
#define WEEKEVENTREG_37_01 PACK_WEEKEVENTREG_FLAG(37, 0x01)
#define WEEKEVENTREG_37_02 PACK_WEEKEVENTREG_FLAG(37, 0x02)
#define WEEKEVENTREG_37_04 PACK_WEEKEVENTREG_FLAG(37, 0x04)
#define WEEKEVENTREG_37_08 PACK_WEEKEVENTREG_FLAG(37, 0x08)
#define WEEKEVENTREG_37_10 PACK_WEEKEVENTREG_FLAG(37, 0x10)
#define WEEKEVENTREG_37_20 PACK_WEEKEVENTREG_FLAG(37, 0x20)
#define WEEKEVENTREG_37_40 PACK_WEEKEVENTREG_FLAG(37, 0x40)
#define WEEKEVENTREG_37_80 PACK_WEEKEVENTREG_FLAG(37, 0x80)
#define WEEKEVENTREG_38_01 PACK_WEEKEVENTREG_FLAG(38, 0x01)
#define WEEKEVENTREG_38_02 PACK_WEEKEVENTREG_FLAG(38, 0x02)
#define WEEKEVENTREG_38_04 PACK_WEEKEVENTREG_FLAG(38, 0x04)
#define WEEKEVENTREG_38_08 PACK_WEEKEVENTREG_FLAG(38, 0x08)
#define WEEKEVENTREG_38_10 PACK_WEEKEVENTREG_FLAG(38, 0x10)
#define WEEKEVENTREG_38_20 PACK_WEEKEVENTREG_FLAG(38, 0x20)
#define WEEKEVENTREG_38_40 PACK_WEEKEVENTREG_FLAG(38, 0x40)
#define WEEKEVENTREG_38_80 PACK_WEEKEVENTREG_FLAG(38, 0x80)
#define WEEKEVENTREG_39_01 PACK_WEEKEVENTREG_FLAG(39, 0x01)
#define WEEKEVENTREG_39_02 PACK_WEEKEVENTREG_FLAG(39, 0x02)
#define WEEKEVENTREG_39_04 PACK_WEEKEVENTREG_FLAG(39, 0x04)
#define WEEKEVENTREG_39_08 PACK_WEEKEVENTREG_FLAG(39, 0x08)
#define WEEKEVENTREG_39_10 PACK_WEEKEVENTREG_FLAG(39, 0x10)
#define WEEKEVENTREG_39_20 PACK_WEEKEVENTREG_FLAG(39, 0x20)
#define WEEKEVENTREG_39_40 PACK_WEEKEVENTREG_FLAG(39, 0x40)
#define WEEKEVENTREG_39_80 PACK_WEEKEVENTREG_FLAG(39, 0x80)
#define WEEKEVENTREG_40_01 PACK_WEEKEVENTREG_FLAG(40, 0x01)
#define WEEKEVENTREG_40_02 PACK_WEEKEVENTREG_FLAG(40, 0x02)
#define WEEKEVENTREG_40_04 PACK_WEEKEVENTREG_FLAG(40, 0x04)
#define WEEKEVENTREG_40_08 PACK_WEEKEVENTREG_FLAG(40, 0x08)
#define WEEKEVENTREG_40_10 PACK_WEEKEVENTREG_FLAG(40, 0x10)
#define WEEKEVENTREG_40_20 PACK_WEEKEVENTREG_FLAG(40, 0x20)
#define WEEKEVENTREG_40_40 PACK_WEEKEVENTREG_FLAG(40, 0x40)
#define WEEKEVENTREG_40_80 PACK_WEEKEVENTREG_FLAG(40, 0x80)
#define WEEKEVENTREG_41_01 PACK_WEEKEVENTREG_FLAG(41, 0x01)
#define WEEKEVENTREG_41_02 PACK_WEEKEVENTREG_FLAG(41, 0x02)
#define WEEKEVENTREG_41_04 PACK_WEEKEVENTREG_FLAG(41, 0x04)
#define WEEKEVENTREG_41_08 PACK_WEEKEVENTREG_FLAG(41, 0x08)
#define WEEKEVENTREG_41_10 PACK_WEEKEVENTREG_FLAG(41, 0x10)
#define WEEKEVENTREG_41_20 PACK_WEEKEVENTREG_FLAG(41, 0x20)
#define WEEKEVENTREG_41_40 PACK_WEEKEVENTREG_FLAG(41, 0x40)
#define WEEKEVENTREG_41_80 PACK_WEEKEVENTREG_FLAG(41, 0x80)
#define WEEKEVENTREG_42_01 PACK_WEEKEVENTREG_FLAG(42, 0x01)
#define WEEKEVENTREG_42_02 PACK_WEEKEVENTREG_FLAG(42, 0x02)
#define WEEKEVENTREG_42_04 PACK_WEEKEVENTREG_FLAG(42, 0x04)
#define WEEKEVENTREG_42_08 PACK_WEEKEVENTREG_FLAG(42, 0x08)
#define WEEKEVENTREG_42_10 PACK_WEEKEVENTREG_FLAG(42, 0x10)
#define WEEKEVENTREG_42_20 PACK_WEEKEVENTREG_FLAG(42, 0x20)
#define WEEKEVENTREG_42_40 PACK_WEEKEVENTREG_FLAG(42, 0x40)
#define WEEKEVENTREG_42_80 PACK_WEEKEVENTREG_FLAG(42, 0x80)
#define WEEKEVENTREG_43_01 PACK_WEEKEVENTREG_FLAG(43, 0x01)
#define WEEKEVENTREG_43_02 PACK_WEEKEVENTREG_FLAG(43, 0x02)
#define WEEKEVENTREG_43_04 PACK_WEEKEVENTREG_FLAG(43, 0x04)
#define WEEKEVENTREG_43_08 PACK_WEEKEVENTREG_FLAG(43, 0x08)
#define WEEKEVENTREG_43_10 PACK_WEEKEVENTREG_FLAG(43, 0x10)
#define WEEKEVENTREG_43_20 PACK_WEEKEVENTREG_FLAG(43, 0x20)
#define WEEKEVENTREG_43_40 PACK_WEEKEVENTREG_FLAG(43, 0x40)
#define WEEKEVENTREG_43_80 PACK_WEEKEVENTREG_FLAG(43, 0x80)
#define WEEKEVENTREG_44_01 PACK_WEEKEVENTREG_FLAG(44, 0x01)
#define WEEKEVENTREG_44_02 PACK_WEEKEVENTREG_FLAG(44, 0x02)
#define WEEKEVENTREG_44_04 PACK_WEEKEVENTREG_FLAG(44, 0x04)
#define WEEKEVENTREG_44_08 PACK_WEEKEVENTREG_FLAG(44, 0x08)
#define WEEKEVENTREG_44_10 PACK_WEEKEVENTREG_FLAG(44, 0x10)
#define WEEKEVENTREG_44_20 PACK_WEEKEVENTREG_FLAG(44, 0x20)
#define WEEKEVENTREG_44_40 PACK_WEEKEVENTREG_FLAG(44, 0x40)
#define WEEKEVENTREG_44_80 PACK_WEEKEVENTREG_FLAG(44, 0x80)
#define WEEKEVENTREG_45_01 PACK_WEEKEVENTREG_FLAG(45, 0x01)
#define WEEKEVENTREG_45_02 PACK_WEEKEVENTREG_FLAG(45, 0x02)
#define WEEKEVENTREG_45_04 PACK_WEEKEVENTREG_FLAG(45, 0x04)
#define WEEKEVENTREG_45_08 PACK_WEEKEVENTREG_FLAG(45, 0x08)
#define WEEKEVENTREG_45_10 PACK_WEEKEVENTREG_FLAG(45, 0x10)
#define WEEKEVENTREG_45_20 PACK_WEEKEVENTREG_FLAG(45, 0x20)
#define WEEKEVENTREG_45_40 PACK_WEEKEVENTREG_FLAG(45, 0x40)
#define WEEKEVENTREG_45_80 PACK_WEEKEVENTREG_FLAG(45, 0x80)
#define WEEKEVENTREG_46_01 PACK_WEEKEVENTREG_FLAG(46, 0x01)
#define WEEKEVENTREG_46_02 PACK_WEEKEVENTREG_FLAG(46, 0x02)
#define WEEKEVENTREG_46_04 PACK_WEEKEVENTREG_FLAG(46, 0x04)
#define WEEKEVENTREG_46_08 PACK_WEEKEVENTREG_FLAG(46, 0x08)
#define WEEKEVENTREG_46_10 PACK_WEEKEVENTREG_FLAG(46, 0x10)
#define WEEKEVENTREG_46_20 PACK_WEEKEVENTREG_FLAG(46, 0x20)
#define WEEKEVENTREG_46_40 PACK_WEEKEVENTREG_FLAG(46, 0x40)
#define WEEKEVENTREG_46_80 PACK_WEEKEVENTREG_FLAG(46, 0x80)
#define WEEKEVENTREG_47_01 PACK_WEEKEVENTREG_FLAG(47, 0x01)
#define WEEKEVENTREG_47_02 PACK_WEEKEVENTREG_FLAG(47, 0x02)
#define WEEKEVENTREG_47_04 PACK_WEEKEVENTREG_FLAG(47, 0x04)
#define WEEKEVENTREG_47_08 PACK_WEEKEVENTREG_FLAG(47, 0x08)
#define WEEKEVENTREG_47_10 PACK_WEEKEVENTREG_FLAG(47, 0x10)
#define WEEKEVENTREG_47_20 PACK_WEEKEVENTREG_FLAG(47, 0x20)
#define WEEKEVENTREG_47_40 PACK_WEEKEVENTREG_FLAG(47, 0x40)
#define WEEKEVENTREG_47_80 PACK_WEEKEVENTREG_FLAG(47, 0x80)
#define WEEKEVENTREG_48_01 PACK_WEEKEVENTREG_FLAG(48, 0x01)
#define WEEKEVENTREG_48_02 PACK_WEEKEVENTREG_FLAG(48, 0x02)
#define WEEKEVENTREG_48_04 PACK_WEEKEVENTREG_FLAG(48, 0x04)
#define WEEKEVENTREG_48_08 PACK_WEEKEVENTREG_FLAG(48, 0x08)
#define WEEKEVENTREG_48_10 PACK_WEEKEVENTREG_FLAG(48, 0x10)
#define WEEKEVENTREG_48_20 PACK_WEEKEVENTREG_FLAG(48, 0x20)
#define WEEKEVENTREG_48_40 PACK_WEEKEVENTREG_FLAG(48, 0x40)
#define WEEKEVENTREG_48_80 PACK_WEEKEVENTREG_FLAG(48, 0x80)
#define WEEKEVENTREG_49_01 PACK_WEEKEVENTREG_FLAG(49, 0x01)
#define WEEKEVENTREG_49_02 PACK_WEEKEVENTREG_FLAG(49, 0x02)
#define WEEKEVENTREG_49_04 PACK_WEEKEVENTREG_FLAG(49, 0x04)
#define WEEKEVENTREG_49_08 PACK_WEEKEVENTREG_FLAG(49, 0x08)
#define WEEKEVENTREG_49_10 PACK_WEEKEVENTREG_FLAG(49, 0x10)
#define WEEKEVENTREG_49_20 PACK_WEEKEVENTREG_FLAG(49, 0x20)
#define WEEKEVENTREG_49_40 PACK_WEEKEVENTREG_FLAG(49, 0x40)
#define WEEKEVENTREG_49_80 PACK_WEEKEVENTREG_FLAG(49, 0x80)
#define WEEKEVENTREG_50_01 PACK_WEEKEVENTREG_FLAG(50, 0x01)
#define WEEKEVENTREG_50_02 PACK_WEEKEVENTREG_FLAG(50, 0x02)
#define WEEKEVENTREG_50_04 PACK_WEEKEVENTREG_FLAG(50, 0x04)
#define WEEKEVENTREG_50_08 PACK_WEEKEVENTREG_FLAG(50, 0x08)
#define WEEKEVENTREG_50_10 PACK_WEEKEVENTREG_FLAG(50, 0x10)
#define WEEKEVENTREG_50_20 PACK_WEEKEVENTREG_FLAG(50, 0x20)
#define WEEKEVENTREG_50_40 PACK_WEEKEVENTREG_FLAG(50, 0x40)
#define WEEKEVENTREG_50_80 PACK_WEEKEVENTREG_FLAG(50, 0x80)
#define WEEKEVENTREG_51_01 PACK_WEEKEVENTREG_FLAG(51, 0x01)
#define WEEKEVENTREG_51_02 PACK_WEEKEVENTREG_FLAG(51, 0x02)
#define WEEKEVENTREG_51_04 PACK_WEEKEVENTREG_FLAG(51, 0x04)
#define WEEKEVENTREG_51_08 PACK_WEEKEVENTREG_FLAG(51, 0x08)
#define WEEKEVENTREG_51_10 PACK_WEEKEVENTREG_FLAG(51, 0x10)
#define WEEKEVENTREG_51_20 PACK_WEEKEVENTREG_FLAG(51, 0x20)
#define WEEKEVENTREG_51_40 PACK_WEEKEVENTREG_FLAG(51, 0x40)
#define WEEKEVENTREG_51_80 PACK_WEEKEVENTREG_FLAG(51, 0x80)

// ProtectedCremia
#define WEEKEVENTREG_52_01 PACK_WEEKEVENTREG_FLAG(52, 0x01)
// Lose Milk Run minigame
#define WEEKEVENTREG_52_02 PACK_WEEKEVENTREG_FLAG(52, 0x02)

#define WEEKEVENTREG_52_04 PACK_WEEKEVENTREG_FLAG(52, 0x04)
#define WEEKEVENTREG_52_08 PACK_WEEKEVENTREG_FLAG(52, 0x08)
#define WEEKEVENTREG_52_10 PACK_WEEKEVENTREG_FLAG(52, 0x10)

// cleared Stone Tower Temple
#define WEEKEVENTREG_52_20 PACK_WEEKEVENTREG_FLAG(52, 0x20)

#define WEEKEVENTREG_52_40 PACK_WEEKEVENTREG_FLAG(52, 0x40)
#define WEEKEVENTREG_52_80 PACK_WEEKEVENTREG_FLAG(52, 0x80)
#define WEEKEVENTREG_53_01 PACK_WEEKEVENTREG_FLAG(53, 0x01)
#define WEEKEVENTREG_53_02 PACK_WEEKEVENTREG_FLAG(53, 0x02)
#define WEEKEVENTREG_53_04 PACK_WEEKEVENTREG_FLAG(53, 0x04)
#define WEEKEVENTREG_53_08 PACK_WEEKEVENTREG_FLAG(53, 0x08)
#define WEEKEVENTREG_53_10 PACK_WEEKEVENTREG_FLAG(53, 0x10)
#define WEEKEVENTREG_53_20 PACK_WEEKEVENTREG_FLAG(53, 0x20)
#define WEEKEVENTREG_53_40 PACK_WEEKEVENTREG_FLAG(53, 0x40)
#define WEEKEVENTREG_53_80 PACK_WEEKEVENTREG_FLAG(53, 0x80)
#define WEEKEVENTREG_54_01 PACK_WEEKEVENTREG_FLAG(54, 0x01)
#define WEEKEVENTREG_54_02 PACK_WEEKEVENTREG_FLAG(54, 0x02)
#define WEEKEVENTREG_54_04 PACK_WEEKEVENTREG_FLAG(54, 0x04)
#define WEEKEVENTREG_54_08 PACK_WEEKEVENTREG_FLAG(54, 0x08)
#define WEEKEVENTREG_54_10 PACK_WEEKEVENTREG_FLAG(54, 0x10)
#define WEEKEVENTREG_54_20 PACK_WEEKEVENTREG_FLAG(54, 0x20)
#define WEEKEVENTREG_54_40 PACK_WEEKEVENTREG_FLAG(54, 0x40)
#define WEEKEVENTREG_54_80 PACK_WEEKEVENTREG_FLAG(54, 0x80)
#define WEEKEVENTREG_55_01 PACK_WEEKEVENTREG_FLAG(55, 0x01)

// Unconfirmed: "Link the Goron Claims His Reservation: 4:30 PM"
#define WEEKEVENTREG_55_02 PACK_WEEKEVENTREG_FLAG(55, 0x02)

#define WEEKEVENTREG_55_04 PACK_WEEKEVENTREG_FLAG(55, 0x04)
#define WEEKEVENTREG_55_08 PACK_WEEKEVENTREG_FLAG(55, 0x08)
#define WEEKEVENTREG_55_10 PACK_WEEKEVENTREG_FLAG(55, 0x10)
#define WEEKEVENTREG_55_20 PACK_WEEKEVENTREG_FLAG(55, 0x20)
#define WEEKEVENTREG_55_40 PACK_WEEKEVENTREG_FLAG(55, 0x40)

// Gyorg has been defeated
#define WEEKEVENTREG_55_80 PACK_WEEKEVENTREG_FLAG(55, 0x80)

#define WEEKEVENTREG_56_01 PACK_WEEKEVENTREG_FLAG(56, 0x01)
#define WEEKEVENTREG_56_02 PACK_WEEKEVENTREG_FLAG(56, 0x02)
#define WEEKEVENTREG_56_04 PACK_WEEKEVENTREG_FLAG(56, 0x04)
#define WEEKEVENTREG_56_08 PACK_WEEKEVENTREG_FLAG(56, 0x08)
#define WEEKEVENTREG_56_10 PACK_WEEKEVENTREG_FLAG(56, 0x10)
#define WEEKEVENTREG_56_20 PACK_WEEKEVENTREG_FLAG(56, 0x20)
#define WEEKEVENTREG_56_40 PACK_WEEKEVENTREG_FLAG(56, 0x40)
#define WEEKEVENTREG_56_80 PACK_WEEKEVENTREG_FLAG(56, 0x80)
#define WEEKEVENTREG_57_01 PACK_WEEKEVENTREG_FLAG(57, 0x01)
#define WEEKEVENTREG_57_02 PACK_WEEKEVENTREG_FLAG(57, 0x02)
#define WEEKEVENTREG_57_04 PACK_WEEKEVENTREG_FLAG(57, 0x04)
#define WEEKEVENTREG_57_08 PACK_WEEKEVENTREG_FLAG(57, 0x08)
#define WEEKEVENTREG_57_10 PACK_WEEKEVENTREG_FLAG(57, 0x10)
#define WEEKEVENTREG_57_20 PACK_WEEKEVENTREG_FLAG(57, 0x20)
#define WEEKEVENTREG_57_40 PACK_WEEKEVENTREG_FLAG(57, 0x40)
#define WEEKEVENTREG_57_80 PACK_WEEKEVENTREG_FLAG(57, 0x80)
#define WEEKEVENTREG_58_01 PACK_WEEKEVENTREG_FLAG(58, 0x01)
#define WEEKEVENTREG_58_02 PACK_WEEKEVENTREG_FLAG(58, 0x02)
#define WEEKEVENTREG_58_04 PACK_WEEKEVENTREG_FLAG(58, 0x04)
#define WEEKEVENTREG_58_08 PACK_WEEKEVENTREG_FLAG(58, 0x08)
#define WEEKEVENTREG_58_10 PACK_WEEKEVENTREG_FLAG(58, 0x10)
#define WEEKEVENTREG_58_20 PACK_WEEKEVENTREG_FLAG(58, 0x20)
#define WEEKEVENTREG_58_40 PACK_WEEKEVENTREG_FLAG(58, 0x40)
#define WEEKEVENTREG_58_80 PACK_WEEKEVENTREG_FLAG(58, 0x80)
#define WEEKEVENTREG_59_01 PACK_WEEKEVENTREG_FLAG(59, 0x01)
#define WEEKEVENTREG_59_02 PACK_WEEKEVENTREG_FLAG(59, 0x02)

// Unconfirmed: "Entered South Clock Town"
#define WEEKEVENTREG_59_04 PACK_WEEKEVENTREG_FLAG(59, 0x04)

#define WEEKEVENTREG_59_08 PACK_WEEKEVENTREG_FLAG(59, 0x08)
#define WEEKEVENTREG_59_10 PACK_WEEKEVENTREG_FLAG(59, 0x10)
#define WEEKEVENTREG_59_20 PACK_WEEKEVENTREG_FLAG(59, 0x20)
#define WEEKEVENTREG_59_40 PACK_WEEKEVENTREG_FLAG(59, 0x40)
#define WEEKEVENTREG_59_80 PACK_WEEKEVENTREG_FLAG(59, 0x80)
#define WEEKEVENTREG_60_01 PACK_WEEKEVENTREG_FLAG(60, 0x01)
#define WEEKEVENTREG_DAMPE_REMOVED_BATS PACK_WEEKEVENTREG_FLAG(60, 0x02)
#define WEEKEVENTREG_60_04 PACK_WEEKEVENTREG_FLAG(60, 0x04)
#define WEEKEVENTREG_60_08 PACK_WEEKEVENTREG_FLAG(60, 0x08)
#define WEEKEVENTREG_60_10 PACK_WEEKEVENTREG_FLAG(60, 0x10)
#define WEEKEVENTREG_60_20 PACK_WEEKEVENTREG_FLAG(60, 0x20)
#define WEEKEVENTREG_60_40 PACK_WEEKEVENTREG_FLAG(60, 0x40)
#define WEEKEVENTREG_60_80 PACK_WEEKEVENTREG_FLAG(60, 0x80)
#define WEEKEVENTREG_61_01 PACK_WEEKEVENTREG_FLAG(61, 0x01)
#define WEEKEVENTREG_61_02 PACK_WEEKEVENTREG_FLAG(61, 0x02)
#define WEEKEVENTREG_61_04 PACK_WEEKEVENTREG_FLAG(61, 0x04)
#define WEEKEVENTREG_61_08 PACK_WEEKEVENTREG_FLAG(61, 0x08)
#define WEEKEVENTREG_61_10 PACK_WEEKEVENTREG_FLAG(61, 0x10)
#define WEEKEVENTREG_61_20 PACK_WEEKEVENTREG_FLAG(61, 0x20)
#define WEEKEVENTREG_61_40 PACK_WEEKEVENTREG_FLAG(61, 0x40)
#define WEEKEVENTREG_61_80 PACK_WEEKEVENTREG_FLAG(61, 0x80)
#define WEEKEVENTREG_62_01 PACK_WEEKEVENTREG_FLAG(62, 0x01)
#define WEEKEVENTREG_62_02 PACK_WEEKEVENTREG_FLAG(62, 0x02)
#define WEEKEVENTREG_62_04 PACK_WEEKEVENTREG_FLAG(62, 0x04)
#define WEEKEVENTREG_62_08 PACK_WEEKEVENTREG_FLAG(62, 0x08)
#define WEEKEVENTREG_62_10 PACK_WEEKEVENTREG_FLAG(62, 0x10)
#define WEEKEVENTREG_62_20 PACK_WEEKEVENTREG_FLAG(62, 0x20)
#define WEEKEVENTREG_62_40 PACK_WEEKEVENTREG_FLAG(62, 0x40)
#define WEEKEVENTREG_62_80 PACK_WEEKEVENTREG_FLAG(62, 0x80)
#define WEEKEVENTREG_63_01 PACK_WEEKEVENTREG_FLAG(63, 0x01)
#define WEEKEVENTREG_63_02 PACK_WEEKEVENTREG_FLAG(63, 0x02)
#define WEEKEVENTREG_63_04 PACK_WEEKEVENTREG_FLAG(63, 0x04)
#define WEEKEVENTREG_63_08 PACK_WEEKEVENTREG_FLAG(63, 0x08)
#define WEEKEVENTREG_63_10 PACK_WEEKEVENTREG_FLAG(63, 0x10)
#define WEEKEVENTREG_63_20 PACK_WEEKEVENTREG_FLAG(63, 0x20)
#define WEEKEVENTREG_63_40 PACK_WEEKEVENTREG_FLAG(63, 0x40)

// showed Couple's Mask to meeting
#define WEEKEVENTREG_63_80 PACK_WEEKEVENTREG_FLAG(63, 0x80)

#define WEEKEVENTREG_64_01 PACK_WEEKEVENTREG_FLAG(64, 0x01)
#define WEEKEVENTREG_64_02 PACK_WEEKEVENTREG_FLAG(64, 0x02)
#define WEEKEVENTREG_64_04 PACK_WEEKEVENTREG_FLAG(64, 0x04)
#define WEEKEVENTREG_64_08 PACK_WEEKEVENTREG_FLAG(64, 0x08)
#define WEEKEVENTREG_64_10 PACK_WEEKEVENTREG_FLAG(64, 0x10)
#define WEEKEVENTREG_64_20 PACK_WEEKEVENTREG_FLAG(64, 0x20)
#define WEEKEVENTREG_64_40 PACK_WEEKEVENTREG_FLAG(64, 0x40)
#define WEEKEVENTREG_64_80 PACK_WEEKEVENTREG_FLAG(64, 0x80)
#define WEEKEVENTREG_65_01 PACK_WEEKEVENTREG_FLAG(65, 0x01)
#define WEEKEVENTREG_65_02 PACK_WEEKEVENTREG_FLAG(65, 0x02)
#define WEEKEVENTREG_65_04 PACK_WEEKEVENTREG_FLAG(65, 0x04)
#define WEEKEVENTREG_65_08 PACK_WEEKEVENTREG_FLAG(65, 0x08)
#define WEEKEVENTREG_65_10 PACK_WEEKEVENTREG_FLAG(65, 0x10)
#define WEEKEVENTREG_65_20 PACK_WEEKEVENTREG_FLAG(65, 0x20)
#define WEEKEVENTREG_65_40 PACK_WEEKEVENTREG_FLAG(65, 0x40)
#define WEEKEVENTREG_65_80 PACK_WEEKEVENTREG_FLAG(65, 0x80)
#define WEEKEVENTREG_66_01 PACK_WEEKEVENTREG_FLAG(66, 0x01)
#define WEEKEVENTREG_66_02 PACK_WEEKEVENTREG_FLAG(66, 0x02)
#define WEEKEVENTREG_66_04 PACK_WEEKEVENTREG_FLAG(66, 0x04)
#define WEEKEVENTREG_66_08 PACK_WEEKEVENTREG_FLAG(66, 0x08)
#define WEEKEVENTREG_66_10 PACK_WEEKEVENTREG_FLAG(66, 0x10)
#define WEEKEVENTREG_66_20 PACK_WEEKEVENTREG_FLAG(66, 0x20)
#define WEEKEVENTREG_66_40 PACK_WEEKEVENTREG_FLAG(66, 0x40)
#define WEEKEVENTREG_66_80 PACK_WEEKEVENTREG_FLAG(66, 0x80)
#define WEEKEVENTREG_67_01 PACK_WEEKEVENTREG_FLAG(67, 0x01)
#define WEEKEVENTREG_67_02 PACK_WEEKEVENTREG_FLAG(67, 0x02)
#define WEEKEVENTREG_67_04 PACK_WEEKEVENTREG_FLAG(67, 0x04)
#define WEEKEVENTREG_67_08 PACK_WEEKEVENTREG_FLAG(67, 0x08)
#define WEEKEVENTREG_67_10 PACK_WEEKEVENTREG_FLAG(67, 0x10)
#define WEEKEVENTREG_67_20 PACK_WEEKEVENTREG_FLAG(67, 0x20)
#define WEEKEVENTREG_67_40 PACK_WEEKEVENTREG_FLAG(67, 0x40)
#define WEEKEVENTREG_67_80 PACK_WEEKEVENTREG_FLAG(67, 0x80)
#define WEEKEVENTREG_68_01 PACK_WEEKEVENTREG_FLAG(68, 0x01)
#define WEEKEVENTREG_68_02 PACK_WEEKEVENTREG_FLAG(68, 0x02)
#define WEEKEVENTREG_68_04 PACK_WEEKEVENTREG_FLAG(68, 0x04)
#define WEEKEVENTREG_68_08 PACK_WEEKEVENTREG_FLAG(68, 0x08)
#define WEEKEVENTREG_68_10 PACK_WEEKEVENTREG_FLAG(68, 0x10)
#define WEEKEVENTREG_68_20 PACK_WEEKEVENTREG_FLAG(68, 0x20)
#define WEEKEVENTREG_68_40 PACK_WEEKEVENTREG_FLAG(68, 0x40)
#define WEEKEVENTREG_68_80 PACK_WEEKEVENTREG_FLAG(68, 0x80)
#define WEEKEVENTREG_69_01 PACK_WEEKEVENTREG_FLAG(69, 0x01)
#define WEEKEVENTREG_69_02 PACK_WEEKEVENTREG_FLAG(69, 0x02)
#define WEEKEVENTREG_69_04 PACK_WEEKEVENTREG_FLAG(69, 0x04)
#define WEEKEVENTREG_69_08 PACK_WEEKEVENTREG_FLAG(69, 0x08)
#define WEEKEVENTREG_69_10 PACK_WEEKEVENTREG_FLAG(69, 0x10)
#define WEEKEVENTREG_69_20 PACK_WEEKEVENTREG_FLAG(69, 0x20)
#define WEEKEVENTREG_69_40 PACK_WEEKEVENTREG_FLAG(69, 0x40)
#define WEEKEVENTREG_69_80 PACK_WEEKEVENTREG_FLAG(69, 0x80)
#define WEEKEVENTREG_70_01 PACK_WEEKEVENTREG_FLAG(70, 0x01)
#define WEEKEVENTREG_70_02 PACK_WEEKEVENTREG_FLAG(70, 0x02)
#define WEEKEVENTREG_70_04 PACK_WEEKEVENTREG_FLAG(70, 0x04)
#define WEEKEVENTREG_70_08 PACK_WEEKEVENTREG_FLAG(70, 0x08)
#define WEEKEVENTREG_70_10 PACK_WEEKEVENTREG_FLAG(70, 0x10)
#define WEEKEVENTREG_70_20 PACK_WEEKEVENTREG_FLAG(70, 0x20)
#define WEEKEVENTREG_70_40 PACK_WEEKEVENTREG_FLAG(70, 0x40)
#define WEEKEVENTREG_70_80 PACK_WEEKEVENTREG_FLAG(70, 0x80)
#define WEEKEVENTREG_71_01 PACK_WEEKEVENTREG_FLAG(71, 0x01)
#define WEEKEVENTREG_71_02 PACK_WEEKEVENTREG_FLAG(71, 0x02)
#define WEEKEVENTREG_71_04 PACK_WEEKEVENTREG_FLAG(71, 0x04)
#define WEEKEVENTREG_71_08 PACK_WEEKEVENTREG_FLAG(71, 0x08)
#define WEEKEVENTREG_71_10 PACK_WEEKEVENTREG_FLAG(71, 0x10)
#define WEEKEVENTREG_71_20 PACK_WEEKEVENTREG_FLAG(71, 0x20)
#define WEEKEVENTREG_71_40 PACK_WEEKEVENTREG_FLAG(71, 0x40)
#define WEEKEVENTREG_71_80 PACK_WEEKEVENTREG_FLAG(71, 0x80)
#define WEEKEVENTREG_72_01 PACK_WEEKEVENTREG_FLAG(72, 0x01)
#define WEEKEVENTREG_72_02 PACK_WEEKEVENTREG_FLAG(72, 0x02)
#define WEEKEVENTREG_72_04 PACK_WEEKEVENTREG_FLAG(72, 0x04)
#define WEEKEVENTREG_72_08 PACK_WEEKEVENTREG_FLAG(72, 0x08)
#define WEEKEVENTREG_72_10 PACK_WEEKEVENTREG_FLAG(72, 0x10)
#define WEEKEVENTREG_72_20 PACK_WEEKEVENTREG_FLAG(72, 0x20)
#define WEEKEVENTREG_72_40 PACK_WEEKEVENTREG_FLAG(72, 0x40)
#define WEEKEVENTREG_72_80 PACK_WEEKEVENTREG_FLAG(72, 0x80)
#define WEEKEVENTREG_73_01 PACK_WEEKEVENTREG_FLAG(73, 0x01)
#define WEEKEVENTREG_73_02 PACK_WEEKEVENTREG_FLAG(73, 0x02)
#define WEEKEVENTREG_73_04 PACK_WEEKEVENTREG_FLAG(73, 0x04)
#define WEEKEVENTREG_73_08 PACK_WEEKEVENTREG_FLAG(73, 0x08)

// Unconfirmed: "Bombers Hide & Seek started on Day 1?"
#define WEEKEVENTREG_73_10 PACK_WEEKEVENTREG_FLAG(73, 0x10)

#define WEEKEVENTREG_73_20 PACK_WEEKEVENTREG_FLAG(73, 0x20)
#define WEEKEVENTREG_73_40 PACK_WEEKEVENTREG_FLAG(73, 0x40)
#define WEEKEVENTREG_73_80 PACK_WEEKEVENTREG_FLAG(73, 0x80)
#define WEEKEVENTREG_74_01 PACK_WEEKEVENTREG_FLAG(74, 0x01)
#define WEEKEVENTREG_74_02 PACK_WEEKEVENTREG_FLAG(74, 0x02)
#define WEEKEVENTREG_74_04 PACK_WEEKEVENTREG_FLAG(74, 0x04)
#define WEEKEVENTREG_74_08 PACK_WEEKEVENTREG_FLAG(74, 0x08)
#define WEEKEVENTREG_74_10 PACK_WEEKEVENTREG_FLAG(74, 0x10)
#define WEEKEVENTREG_74_20 PACK_WEEKEVENTREG_FLAG(74, 0x20)
#define WEEKEVENTREG_74_40 PACK_WEEKEVENTREG_FLAG(74, 0x40)
#define WEEKEVENTREG_74_80 PACK_WEEKEVENTREG_FLAG(74, 0x80)
#define WEEKEVENTREG_75_01 PACK_WEEKEVENTREG_FLAG(75, 0x01)
#define WEEKEVENTREG_75_02 PACK_WEEKEVENTREG_FLAG(75, 0x02)
#define WEEKEVENTREG_75_04 PACK_WEEKEVENTREG_FLAG(75, 0x04)
#define WEEKEVENTREG_75_08 PACK_WEEKEVENTREG_FLAG(75, 0x08)
#define WEEKEVENTREG_75_10 PACK_WEEKEVENTREG_FLAG(75, 0x10)
#define WEEKEVENTREG_75_20 PACK_WEEKEVENTREG_FLAG(75, 0x20)
#define WEEKEVENTREG_75_40 PACK_WEEKEVENTREG_FLAG(75, 0x40)
#define WEEKEVENTREG_75_80 PACK_WEEKEVENTREG_FLAG(75, 0x80)
#define WEEKEVENTREG_76_01 PACK_WEEKEVENTREG_FLAG(76, 0x01)
#define WEEKEVENTREG_76_02 PACK_WEEKEVENTREG_FLAG(76, 0x02)
#define WEEKEVENTREG_76_04 PACK_WEEKEVENTREG_FLAG(76, 0x04)
#define WEEKEVENTREG_76_08 PACK_WEEKEVENTREG_FLAG(76, 0x08)
#define WEEKEVENTREG_76_10 PACK_WEEKEVENTREG_FLAG(76, 0x10)
#define WEEKEVENTREG_76_20 PACK_WEEKEVENTREG_FLAG(76, 0x20)
#define WEEKEVENTREG_76_40 PACK_WEEKEVENTREG_FLAG(76, 0x40)
#define WEEKEVENTREG_76_80 PACK_WEEKEVENTREG_FLAG(76, 0x80)
#define WEEKEVENTREG_77_01 PACK_WEEKEVENTREG_FLAG(77, 0x01)
#define WEEKEVENTREG_77_02 PACK_WEEKEVENTREG_FLAG(77, 0x02)
#define WEEKEVENTREG_77_04 PACK_WEEKEVENTREG_FLAG(77, 0x04)
#define WEEKEVENTREG_77_08 PACK_WEEKEVENTREG_FLAG(77, 0x08)
#define WEEKEVENTREG_77_10 PACK_WEEKEVENTREG_FLAG(77, 0x10)
#define WEEKEVENTREG_77_20 PACK_WEEKEVENTREG_FLAG(77, 0x20)
#define WEEKEVENTREG_77_40 PACK_WEEKEVENTREG_FLAG(77, 0x40)

// The player has heard the Goron Shrine cheer as a Goron at least once.
#define WEEKEVENTREG_77_80 PACK_WEEKEVENTREG_FLAG(77, 0x80)

#define WEEKEVENTREG_78_01 PACK_WEEKEVENTREG_FLAG(78, 0x01)
#define WEEKEVENTREG_78_02 PACK_WEEKEVENTREG_FLAG(78, 0x02)
#define WEEKEVENTREG_78_04 PACK_WEEKEVENTREG_FLAG(78, 0x04)
#define WEEKEVENTREG_78_08 PACK_WEEKEVENTREG_FLAG(78, 0x08)
#define WEEKEVENTREG_78_10 PACK_WEEKEVENTREG_FLAG(78, 0x10)
#define WEEKEVENTREG_78_20 PACK_WEEKEVENTREG_FLAG(78, 0x20)
#define WEEKEVENTREG_78_40 PACK_WEEKEVENTREG_FLAG(78, 0x40)
#define WEEKEVENTREG_78_80 PACK_WEEKEVENTREG_FLAG(78, 0x80)
#define WEEKEVENTREG_79_01 PACK_WEEKEVENTREG_FLAG(79, 0x01)
#define WEEKEVENTREG_79_02 PACK_WEEKEVENTREG_FLAG(79, 0x02)
#define WEEKEVENTREG_79_04 PACK_WEEKEVENTREG_FLAG(79, 0x04)
#define WEEKEVENTREG_79_08 PACK_WEEKEVENTREG_FLAG(79, 0x08)
#define WEEKEVENTREG_79_10 PACK_WEEKEVENTREG_FLAG(79, 0x10)
#define WEEKEVENTREG_79_20 PACK_WEEKEVENTREG_FLAG(79, 0x20)
#define WEEKEVENTREG_79_40 PACK_WEEKEVENTREG_FLAG(79, 0x40)
#define WEEKEVENTREG_79_80 PACK_WEEKEVENTREG_FLAG(79, 0x80)
#define WEEKEVENTREG_80_01 PACK_WEEKEVENTREG_FLAG(80, 0x01)
#define WEEKEVENTREG_80_02 PACK_WEEKEVENTREG_FLAG(80, 0x02)
#define WEEKEVENTREG_80_04 PACK_WEEKEVENTREG_FLAG(80, 0x04)
#define WEEKEVENTREG_80_08 PACK_WEEKEVENTREG_FLAG(80, 0x08)
#define WEEKEVENTREG_80_10 PACK_WEEKEVENTREG_FLAG(80, 0x10)
#define WEEKEVENTREG_80_20 PACK_WEEKEVENTREG_FLAG(80, 0x20)
#define WEEKEVENTREG_80_40 PACK_WEEKEVENTREG_FLAG(80, 0x40)
#define WEEKEVENTREG_80_80 PACK_WEEKEVENTREG_FLAG(80, 0x80)
#define WEEKEVENTREG_81_01 PACK_WEEKEVENTREG_FLAG(81, 0x01)
#define WEEKEVENTREG_81_02 PACK_WEEKEVENTREG_FLAG(81, 0x02)
#define WEEKEVENTREG_81_04 PACK_WEEKEVENTREG_FLAG(81, 0x04)
#define WEEKEVENTREG_81_08 PACK_WEEKEVENTREG_FLAG(81, 0x08)
#define WEEKEVENTREG_81_10 PACK_WEEKEVENTREG_FLAG(81, 0x10)
#define WEEKEVENTREG_81_20 PACK_WEEKEVENTREG_FLAG(81, 0x20)
#define WEEKEVENTREG_81_40 PACK_WEEKEVENTREG_FLAG(81, 0x40)
#define WEEKEVENTREG_81_80 PACK_WEEKEVENTREG_FLAG(81, 0x80)
#define WEEKEVENTREG_82_01 PACK_WEEKEVENTREG_FLAG(82, 0x01)
#define WEEKEVENTREG_82_02 PACK_WEEKEVENTREG_FLAG(82, 0x02)

// check if already healed Kamaro the Dancing Ghost
#define WEEKEVENTREG_82_04 PACK_WEEKEVENTREG_FLAG(82, 0x04)

#define WEEKEVENTREG_82_08 PACK_WEEKEVENTREG_FLAG(82, 0x08)
#define WEEKEVENTREG_82_10 PACK_WEEKEVENTREG_FLAG(82, 0x10)
#define WEEKEVENTREG_82_20 PACK_WEEKEVENTREG_FLAG(82, 0x20)
#define WEEKEVENTREG_82_40 PACK_WEEKEVENTREG_FLAG(82, 0x40)
#define WEEKEVENTREG_82_80 PACK_WEEKEVENTREG_FLAG(82, 0x80)
#define WEEKEVENTREG_83_01 PACK_WEEKEVENTREG_FLAG(83, 0x01)
#define WEEKEVENTREG_83_02 PACK_WEEKEVENTREG_FLAG(83, 0x02)
#define WEEKEVENTREG_83_04 PACK_WEEKEVENTREG_FLAG(83, 0x04)
#define WEEKEVENTREG_83_08 PACK_WEEKEVENTREG_FLAG(83, 0x08)
#define WEEKEVENTREG_83_10 PACK_WEEKEVENTREG_FLAG(83, 0x10)
#define WEEKEVENTREG_83_20 PACK_WEEKEVENTREG_FLAG(83, 0x20)
#define WEEKEVENTREG_83_40 PACK_WEEKEVENTREG_FLAG(83, 0x40)
#define WEEKEVENTREG_83_80 PACK_WEEKEVENTREG_FLAG(83, 0x80)
#define WEEKEVENTREG_84_01 PACK_WEEKEVENTREG_FLAG(84, 0x01)
#define WEEKEVENTREG_84_02 PACK_WEEKEVENTREG_FLAG(84, 0x02)
#define WEEKEVENTREG_84_04 PACK_WEEKEVENTREG_FLAG(84, 0x04)
#define WEEKEVENTREG_84_08 PACK_WEEKEVENTREG_FLAG(84, 0x08)
#define WEEKEVENTREG_84_10 PACK_WEEKEVENTREG_FLAG(84, 0x10)

// Unconfirmed: "Obtained Fierce Deity's Mask?"
#define WEEKEVENTREG_84_20 PACK_WEEKEVENTREG_FLAG(84, 0x20)

#define WEEKEVENTREG_84_40 PACK_WEEKEVENTREG_FLAG(84, 0x40)
#define WEEKEVENTREG_84_80 PACK_WEEKEVENTREG_FLAG(84, 0x80)
#define WEEKEVENTREG_85_01 PACK_WEEKEVENTREG_FLAG(85, 0x01)

// Unconfirmed: "Bombers Hide & Seek in Progress"
#define WEEKEVENTREG_85_02 PACK_WEEKEVENTREG_FLAG(85, 0x02)

#define WEEKEVENTREG_85_04 PACK_WEEKEVENTREG_FLAG(85, 0x04)
#define WEEKEVENTREG_85_08 PACK_WEEKEVENTREG_FLAG(85, 0x08)
#define WEEKEVENTREG_85_10 PACK_WEEKEVENTREG_FLAG(85, 0x10)
#define WEEKEVENTREG_85_20 PACK_WEEKEVENTREG_FLAG(85, 0x20)
#define WEEKEVENTREG_85_40 PACK_WEEKEVENTREG_FLAG(85, 0x40)

// Unconfirmed: "Postman showing priority mail to Madame"
#define WEEKEVENTREG_85_80 PACK_WEEKEVENTREG_FLAG(85, 0x80)

#define WEEKEVENTREG_86_01 PACK_WEEKEVENTREG_FLAG(86, 0x01)
#define WEEKEVENTREG_86_02 PACK_WEEKEVENTREG_FLAG(86, 0x02)
#define WEEKEVENTREG_86_04 PACK_WEEKEVENTREG_FLAG(86, 0x04)
#define WEEKEVENTREG_86_08 PACK_WEEKEVENTREG_FLAG(86, 0x08)
#define WEEKEVENTREG_86_10 PACK_WEEKEVENTREG_FLAG(86, 0x10)
#define WEEKEVENTREG_86_20 PACK_WEEKEVENTREG_FLAG(86, 0x20)
#define WEEKEVENTREG_86_40 PACK_WEEKEVENTREG_FLAG(86, 0x40)
#define WEEKEVENTREG_86_80 PACK_WEEKEVENTREG_FLAG(86, 0x80)
#define WEEKEVENTREG_87_01 PACK_WEEKEVENTREG_FLAG(87, 0x01)
#define WEEKEVENTREG_87_02 PACK_WEEKEVENTREG_FLAG(87, 0x02)
#define WEEKEVENTREG_87_04 PACK_WEEKEVENTREG_FLAG(87, 0x04)
#define WEEKEVENTREG_87_08 PACK_WEEKEVENTREG_FLAG(87, 0x08)
#define WEEKEVENTREG_87_10 PACK_WEEKEVENTREG_FLAG(87, 0x10)
#define WEEKEVENTREG_87_20 PACK_WEEKEVENTREG_FLAG(87, 0x20)
#define WEEKEVENTREG_87_40 PACK_WEEKEVENTREG_FLAG(87, 0x40)
#define WEEKEVENTREG_87_80 PACK_WEEKEVENTREG_FLAG(87, 0x80)
#define WEEKEVENTREG_88_01 PACK_WEEKEVENTREG_FLAG(88, 0x01)
#define WEEKEVENTREG_88_02 PACK_WEEKEVENTREG_FLAG(88, 0x02)
#define WEEKEVENTREG_88_04 PACK_WEEKEVENTREG_FLAG(88, 0x04)
#define WEEKEVENTREG_88_08 PACK_WEEKEVENTREG_FLAG(88, 0x08)
#define WEEKEVENTREG_88_10 PACK_WEEKEVENTREG_FLAG(88, 0x10)
#define WEEKEVENTREG_88_20 PACK_WEEKEVENTREG_FLAG(88, 0x20)
#define WEEKEVENTREG_88_40 PACK_WEEKEVENTREG_FLAG(88, 0x40)
#define WEEKEVENTREG_88_80 PACK_WEEKEVENTREG_FLAG(88, 0x80)
#define WEEKEVENTREG_89_01 PACK_WEEKEVENTREG_FLAG(89, 0x01)
#define WEEKEVENTREG_89_02 PACK_WEEKEVENTREG_FLAG(89, 0x02)
#define WEEKEVENTREG_89_04 PACK_WEEKEVENTREG_FLAG(89, 0x04)

// Unconfirmed: "Postman has delivered priority mail"
#define WEEKEVENTREG_89_08 PACK_WEEKEVENTREG_FLAG(89, 0x08)

#define WEEKEVENTREG_89_10 PACK_WEEKEVENTREG_FLAG(89, 0x10)
#define WEEKEVENTREG_89_20 PACK_WEEKEVENTREG_FLAG(89, 0x20)

// Unconfirmed: "Postman is about to flee"
#define WEEKEVENTREG_89_40 PACK_WEEKEVENTREG_FLAG(89, 0x40)

#define WEEKEVENTREG_89_80 PACK_WEEKEVENTREG_FLAG(89, 0x80)

// Unconfirmed: "Postman fleeing town"
#define WEEKEVENTREG_90_01 PACK_WEEKEVENTREG_FLAG(90, 0x01)

#define WEEKEVENTREG_90_02 PACK_WEEKEVENTREG_FLAG(90, 0x02)
#define WEEKEVENTREG_90_04 PACK_WEEKEVENTREG_FLAG(90, 0x04)
#define WEEKEVENTREG_90_08 PACK_WEEKEVENTREG_FLAG(90, 0x08)
#define WEEKEVENTREG_90_10 PACK_WEEKEVENTREG_FLAG(90, 0x10)
#define WEEKEVENTREG_90_20 PACK_WEEKEVENTREG_FLAG(90, 0x20)
#define WEEKEVENTREG_90_40 PACK_WEEKEVENTREG_FLAG(90, 0x40)
#define WEEKEVENTREG_90_80 PACK_WEEKEVENTREG_FLAG(90, 0x80)
#define WEEKEVENTREG_91_01 PACK_WEEKEVENTREG_FLAG(91, 0x01)
#define WEEKEVENTREG_91_02 PACK_WEEKEVENTREG_FLAG(91, 0x02)
#define WEEKEVENTREG_91_04 PACK_WEEKEVENTREG_FLAG(91, 0x04)
#define WEEKEVENTREG_91_08 PACK_WEEKEVENTREG_FLAG(91, 0x08)
#define WEEKEVENTREG_91_10 PACK_WEEKEVENTREG_FLAG(91, 0x10)
#define WEEKEVENTREG_91_20 PACK_WEEKEVENTREG_FLAG(91, 0x20)
#define WEEKEVENTREG_91_40 PACK_WEEKEVENTREG_FLAG(91, 0x40)
#define WEEKEVENTREG_91_80 PACK_WEEKEVENTREG_FLAG(91, 0x80)

// RACE_FLAGS
//#define WEEKEVENTREG_92_01 PACK_WEEKEVENTREG_FLAG(92, 0x01)
//#define WEEKEVENTREG_92_02 PACK_WEEKEVENTREG_FLAG(92, 0x02)
//#define WEEKEVENTREG_92_04 PACK_WEEKEVENTREG_FLAG(92, 0x04)

#define WEEKEVENTREG_92_08 PACK_WEEKEVENTREG_FLAG(92, 0x08)
#define WEEKEVENTREG_92_10 PACK_WEEKEVENTREG_FLAG(92, 0x10)
#define WEEKEVENTREG_92_20 PACK_WEEKEVENTREG_FLAG(92, 0x20)
#define WEEKEVENTREG_92_40 PACK_WEEKEVENTREG_FLAG(92, 0x40)
#define WEEKEVENTREG_92_80 PACK_WEEKEVENTREG_FLAG(92, 0x80)
#define WEEKEVENTREG_93_01 PACK_WEEKEVENTREG_FLAG(93, 0x01)
#define WEEKEVENTREG_93_02 PACK_WEEKEVENTREG_FLAG(93, 0x02)
#define WEEKEVENTREG_93_04 PACK_WEEKEVENTREG_FLAG(93, 0x04)
#define WEEKEVENTREG_93_08 PACK_WEEKEVENTREG_FLAG(93, 0x08)
#define WEEKEVENTREG_93_10 PACK_WEEKEVENTREG_FLAG(93, 0x10)
#define WEEKEVENTREG_93_20 PACK_WEEKEVENTREG_FLAG(93, 0x20)
#define WEEKEVENTREG_93_40 PACK_WEEKEVENTREG_FLAG(93, 0x40)
#define WEEKEVENTREG_93_80 PACK_WEEKEVENTREG_FLAG(93, 0x80)
#define WEEKEVENTREG_94_01 PACK_WEEKEVENTREG_FLAG(94, 0x01)
#define WEEKEVENTREG_94_02 PACK_WEEKEVENTREG_FLAG(94, 0x02)
#define WEEKEVENTREG_94_04 PACK_WEEKEVENTREG_FLAG(94, 0x04)
#define WEEKEVENTREG_94_08 PACK_WEEKEVENTREG_FLAG(94, 0x08)
#define WEEKEVENTREG_94_10 PACK_WEEKEVENTREG_FLAG(94, 0x10)
#define WEEKEVENTREG_94_20 PACK_WEEKEVENTREG_FLAG(94, 0x20)
#define WEEKEVENTREG_94_40 PACK_WEEKEVENTREG_FLAG(94, 0x40)
#define WEEKEVENTREG_94_80 PACK_WEEKEVENTREG_FLAG(94, 0x80)
#define WEEKEVENTREG_95_01 PACK_WEEKEVENTREG_FLAG(95, 0x01)
#define WEEKEVENTREG_95_02 PACK_WEEKEVENTREG_FLAG(95, 0x02)
#define WEEKEVENTREG_95_04 PACK_WEEKEVENTREG_FLAG(95, 0x04)
#define WEEKEVENTREG_95_08 PACK_WEEKEVENTREG_FLAG(95, 0x08)
#define WEEKEVENTREG_95_10 PACK_WEEKEVENTREG_FLAG(95, 0x10)
#define WEEKEVENTREG_95_20 PACK_WEEKEVENTREG_FLAG(95, 0x20)
#define WEEKEVENTREG_95_40 PACK_WEEKEVENTREG_FLAG(95, 0x40)
#define WEEKEVENTREG_95_80 PACK_WEEKEVENTREG_FLAG(95, 0x80)
#define WEEKEVENTREG_96_01 PACK_WEEKEVENTREG_FLAG(96, 0x01)
#define WEEKEVENTREG_96_02 PACK_WEEKEVENTREG_FLAG(96, 0x02)
#define WEEKEVENTREG_96_04 PACK_WEEKEVENTREG_FLAG(96, 0x04)
#define WEEKEVENTREG_96_08 PACK_WEEKEVENTREG_FLAG(96, 0x08)
#define WEEKEVENTREG_96_10 PACK_WEEKEVENTREG_FLAG(96, 0x10)
#define WEEKEVENTREG_96_20 PACK_WEEKEVENTREG_FLAG(96, 0x20)
#define WEEKEVENTREG_96_40 PACK_WEEKEVENTREG_FLAG(96, 0x40)
#define WEEKEVENTREG_96_80 PACK_WEEKEVENTREG_FLAG(96, 0x80)
#define WEEKEVENTREG_97_01 PACK_WEEKEVENTREG_FLAG(97, 0x01)
#define WEEKEVENTREG_97_02 PACK_WEEKEVENTREG_FLAG(97, 0x02)
#define WEEKEVENTREG_97_04 PACK_WEEKEVENTREG_FLAG(97, 0x04)
#define WEEKEVENTREG_97_08 PACK_WEEKEVENTREG_FLAG(97, 0x08)
#define WEEKEVENTREG_97_10 PACK_WEEKEVENTREG_FLAG(97, 0x10)
#define WEEKEVENTREG_97_20 PACK_WEEKEVENTREG_FLAG(97, 0x20)
#define WEEKEVENTREG_97_40 PACK_WEEKEVENTREG_FLAG(97, 0x40)
#define WEEKEVENTREG_97_80 PACK_WEEKEVENTREG_FLAG(97, 0x80)
#define WEEKEVENTREG_98_01 PACK_WEEKEVENTREG_FLAG(98, 0x01)
#define WEEKEVENTREG_98_02 PACK_WEEKEVENTREG_FLAG(98, 0x02)
#define WEEKEVENTREG_98_04 PACK_WEEKEVENTREG_FLAG(98, 0x04)
#define WEEKEVENTREG_98_08 PACK_WEEKEVENTREG_FLAG(98, 0x08)
#define WEEKEVENTREG_98_10 PACK_WEEKEVENTREG_FLAG(98, 0x10)
#define WEEKEVENTREG_98_20 PACK_WEEKEVENTREG_FLAG(98, 0x20)
#define WEEKEVENTREG_98_40 PACK_WEEKEVENTREG_FLAG(98, 0x40)
#define WEEKEVENTREG_98_80 PACK_WEEKEVENTREG_FLAG(98, 0x80)
#define WEEKEVENTREG_99_01 PACK_WEEKEVENTREG_FLAG(99, 0x01)
#define WEEKEVENTREG_99_02 PACK_WEEKEVENTREG_FLAG(99, 0x02)
#define WEEKEVENTREG_99_04 PACK_WEEKEVENTREG_FLAG(99, 0x04)
#define WEEKEVENTREG_99_08 PACK_WEEKEVENTREG_FLAG(99, 0x08)
#define WEEKEVENTREG_99_10 PACK_WEEKEVENTREG_FLAG(99, 0x10)
#define WEEKEVENTREG_99_20 PACK_WEEKEVENTREG_FLAG(99, 0x20)
#define WEEKEVENTREG_99_40 PACK_WEEKEVENTREG_FLAG(99, 0x40)
#define WEEKEVENTREG_99_80 PACK_WEEKEVENTREG_FLAG(99, 0x80)

#define WEEKEVENTREG(index) (gSaveContext.save.weekEventReg[(index)])
#define GET_WEEKEVENTREG(index) ((void)0, WEEKEVENTREG(index))

#define CHECK_WEEKEVENTREG(flag) (WEEKEVENTREG((flag) >> 8) & ((flag) & 0xFF))
#define CHECK_WEEKEVENTREG_ALT(flag) (GET_WEEKEVENTREG((flag) >> 8) & ((flag) & 0xFF))
#define SET_WEEKEVENTREG(flag) (WEEKEVENTREG((flag) >> 8) = GET_WEEKEVENTREG((flag) >> 8) | ((flag) & 0xFF))
#define CLEAR_WEEKEVENTREG(flag) (WEEKEVENTREG((flag) >> 8) = GET_WEEKEVENTREG((flag) >> 8) & (u8)~((flag) & 0xFF))

#define WEEKEVENTREG_RACE_FLAG_END 0
#define WEEKEVENTREG_RACE_FLAG_START 1
#define WEEKEVENTREG_RACE_FLAG_2 2
#define WEEKEVENTREG_RACE_FLAG_3 3
#define WEEKEVENTREG_RACE_FLAG_4 4
#define WEEKEVENTREG_RACE_FLAGS 7

#define GET_WEEKEVENTREG_RACE_FLAGS (WEEKEVENTREG(92) & WEEKEVENTREG_RACE_FLAGS)

#define SET_WEEKEVENTREG_RACE_FLAGS(flag)             \
    WEEKEVENTREG(92) &= (u8)~WEEKEVENTREG_RACE_FLAGS; \
    WEEKEVENTREG(92) = WEEKEVENTREG(92) | (u8)((WEEKEVENTREG(92) & ~WEEKEVENTREG_RACE_FLAGS) | (flag))

/**
 * gSaveContext.eventInf
 */

#define EVENTINF_00 0x00
#define EVENTINF_01 0x01
#define EVENTINF_02 0x02
#define EVENTINF_03 0x03
#define EVENTINF_04 0x04
#define EVENTINF_05 0x05
#define EVENTINF_06 0x06
#define EVENTINF_07 0x07
#define EVENTINF_10 0x10
#define EVENTINF_11 0x11
#define EVENTINF_12 0x12
#define EVENTINF_13 0x13
#define EVENTINF_14 0x14
#define EVENTINF_15 0x15
#define EVENTINF_16 0x16
#define EVENTINF_17 0x17
#define EVENTINF_20 0x20
#define EVENTINF_21 0x21
#define EVENTINF_22 0x22
#define EVENTINF_23 0x23
#define EVENTINF_24 0x24
#define EVENTINF_25 0x25
#define EVENTINF_26 0x26
#define EVENTINF_27 0x27
#define EVENTINF_30 0x30

// EVENTINF_31 is used to track if Player is within range of EnGakufu (2D Song Buttons Appearing on Wall)
#define EVENTINF_31 0x31
// EVENTINF_32 is used to track if Player has played the notes of EnGakufu (2D Song Buttons Appearing on Wall)
#define EVENTINF_32 0x32

#define EVENTINF_33 0x33
#define EVENTINF_34 0x34
#define EVENTINF_35 0x35
#define EVENTINF_36 0x36
#define EVENTINF_37 0x37
#define EVENTINF_40 0x40
#define EVENTINF_41 0x41
#define EVENTINF_42 0x42
#define EVENTINF_43 0x43
#define EVENTINF_44 0x44
#define EVENTINF_45 0x45
#define EVENTINF_46 0x46
#define EVENTINF_47 0x47
#define EVENTINF_50 0x50
#define EVENTINF_51 0x51
#define EVENTINF_52 0x52
#define EVENTINF_53 0x53
#define EVENTINF_54 0x54
#define EVENTINF_55 0x55

// Enabled when Gyorg's intro cutscene has been watched
#define EVENTINF_56 0x56

#define EVENTINF_57 0x57
#define EVENTINF_60 0x60
#define EVENTINF_61 0x61
#define EVENTINF_62 0x62
#define EVENTINF_63 0x63
#define EVENTINF_64 0x64
#define EVENTINF_65 0x65
#define EVENTINF_66 0x66
#define EVENTINF_67 0x67
#define EVENTINF_70 0x70
#define EVENTINF_71 0x71
#define EVENTINF_72 0x72
#define EVENTINF_73 0x73
#define EVENTINF_74 0x74
#define EVENTINF_75 0x75
#define EVENTINF_76 0x76
#define EVENTINF_77 0x77

#define CHECK_EVENTINF(flag) (gSaveContext.eventInf[(flag) >> 4] & (1 << ((flag) & 0xF)))
#define SET_EVENTINF(flag) (gSaveContext.eventInf[(flag) >> 4] |= (1 << ((flag) & 0xF)))
#define CLEAR_EVENTINF(flag) (gSaveContext.eventInf[(flag) >> 4] &= (u8)~(1 << ((flag) & 0xF)))
#define CLEAR_EVENTINF_ALT(flag) (gSaveContext.eventInf[(flag) >> 4] &= ~(1 << ((flag) & 0xF)))


typedef enum {
    /* 0 */ DUNGEON_INDEX_WOODFALL_TEMPLE,
    /* 1 */ DUNGEON_INDEX_SNOWHEAD_TEMPLE,
    /* 2 */ DUNGEON_INDEX_GREAT_BAY_TEMPLE,
    /* 3 */ DUNGEON_INDEX_STONE_TOWER_TEMPLE, // Also applies to Inverted Stone Tower Temple
} DungeonIndex;

void Sram_ActivateOwl(u8 owlId);
void Sram_ClearFlagsAtDawnOfTheFirstDay(void);
void Sram_SaveEndOfCycle(struct PlayState* play);
void Sram_IncrementDay(void);
u16 Sram_CalcChecksum(void* data, size_t count);
void Sram_InitNewSave(void);
void Sram_InitDebugSave(void);
void func_80144A94(SramContext* sramCtx);
void Sram_OpenSave(struct FileSelectState* fileSelect, SramContext* sramCtx);
void func_8014546C(SramContext* sramCtx);
void func_801457CC(struct FileSelectState* fileSelect, SramContext* sramCtx);
void func_80146580(struct FileSelectState* fileSelect2, SramContext* sramCtx, s32 fileNum);
void func_80146628(struct FileSelectState* fileSelect2, SramContext* sramCtx);
void Sram_InitSave(struct FileSelectState* fileSelect2, SramContext* sramCtx);
void func_80146DF8(SramContext* sramCtx);
void Sram_InitSram(struct GameState* gameState, SramContext* sramCtx);
void Sram_Alloc(struct GameState* gameState, SramContext* sramCtx);
void Sram_SaveSpecialEnterClockTown(struct PlayState* play);
void Sram_SaveSpecialNewDay(struct PlayState* play);
void func_80147008(SramContext* sramCtx, u32 curPage, u32 numPages);
void func_80147020(SramContext* sramCtx);
void func_80147068(SramContext* sramCtx);
void func_80147138(SramContext* sramCtx, s32 curPage, s32 numPages);
void func_80147150(SramContext* sramCtx);
void func_80147198(SramContext* sramCtx);

extern s32 D_801C6798[];
extern u8 gAmmoItems[];
extern s32 D_801C67C8[];
extern s32 D_801C67F0[];
extern s32 D_801C6818[];
extern s32 D_801C6840[];
extern s32 D_801C6850[];

#endif
