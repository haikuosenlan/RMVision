#ifndef INFO_H
#define INFO_H

#define small_x 12.0 / 2.0
#define small_y 5.3 / 2.0
#define big_x 23.1 / 2.0
#define big_y 5.8 / 2.0


enum EnemyColor//目标单位的颜色，图像处理用
{
    RED=0,
    BLUE
};
enum AttackPattern//目标类型
{
    ARMOR=0,
    FU
};
enum ArmorSize//装甲板大小
{
    SMALL_ARMOR=0,
    BIG_ARMOR
};
enum FindResult
{
    COUPLIE_LIGHT_FOUND=0,
    NO_COUPLIE_LIGHT_FOUND,
    ARMOR_FOUND,
    NO_ARMOR_FOUND
};
enum RobotType
{
    NO=0,
    HERO,
    TRUCK,
    INFANTRY_3,
    INFANTRY_4,
    INFANTRY_5,
    SENTRY,
    HOME

};
#endif // INFO_H
