typedef struct
{
  short DCcoupled;
  short range;
  short enabled;
}CHANNEL_SETTINGS;

typedef enum
  {
    MODEL_NONE = 0,
    MODEL_PS5203 = 5203,
    MODEL_PS5204 = 5204
  } MODEL_TYPE;

typedef struct tTriggerDirections
{
  enum enThresholdDirection channelA;
  enum enThresholdDirection channelB;
  enum enThresholdDirection channelC;
  enum enThresholdDirection channelD;
  enum enThresholdDirection ext;
  enum enThresholdDirection aux;
}TRIGGER_DIRECTIONS;

typedef struct tPwq
{
  struct tPwqConditions * conditions;
  short nConditions;
  enum enThresholdDirection direction;
  unsigned long lower;
  unsigned long upper;
  enum enPulseWidthType type;
}PWQ;

typedef struct
{
  short handle;
  MODEL_TYPE model;
  PS5000_RANGE firstRange;
  PS5000_RANGE lastRange;
  unsigned char signalGenerator;
  unsigned char external;
  short ChannelCount;
  CHANNEL_SETTINGS channelSettings [MAX_CHANNELS];
  PS5000_RANGE triggerRange;
}UNIT_MODEL;
