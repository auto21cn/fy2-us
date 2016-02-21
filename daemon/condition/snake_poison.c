// snake_poison.c

#include <ansi.h>

int update_condition(object me, int duration)
{
	me->receive_wound("kee", 7);
	me->receive_damage("sen", 10);
	me->apply_condition("snake_poison", duration - 1);
        if( duration < 1 )
		tell_object(me, HIG "你中的蛇毒终于发作光了！\n" NOR );
	else
		tell_object(me, HIG "你中的蛇毒发作了！\n" NOR );
	if( duration < 1 ) 
		return 0;
	return 1;
}
