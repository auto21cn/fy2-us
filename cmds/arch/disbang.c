// disbang.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string bangname;
	string wiz_status;

	string tmpstr;

	if( me!=this_player(1) ) return 0;

	if( !arg || sscanf(arg, "%s %s", arg, bangname)!=2 )
		return notify_fail("argument error!\n");

	wiz_status=SECURITY_D->get_status(me) ;

	if (wiz_status != "(admin)") 
		return notify_fail("you r not admin!\n");


                if( !(ob = present(arg, environment(me)))
                ||      !living(ob)
                ||      !ob->is_character()
                ||      ob==me )
			return notify_fail("ob error!\n");	
	tmpstr = "marks/" + bangname ;
	ob->delete("marks/帮派");
	ob->delete(tmpstr);
	message_vision( HIW "\n$N已经把$n的舵主撤去的了.\n\n" NOR, me,ob);	
	return 1;
}

int help(object me)
{
write(@HELP
指令格式 : promote <某人> (权限等级)

用来提升权限等级, (player) (immortal) (apprentice) (wizard)
(arch) (admin)
一个 admin 能提升权限至任何等级, 而 arch 只能提升至 arch。
HELP
    );
    return 1;
}
