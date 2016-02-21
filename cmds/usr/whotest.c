#include <net/dns.h>
#include <net/daemons.h>
#include <net/macros.h>
#include <ansi.h>
inherit F_CLEAN_UP;
void create() { seteuid(getuid()); }
mixed main(object me, string arg, int remote)
{
	string str, *option;
	object *list;
	int i, j, ppl_cnt;
	int opt_long=1, opt_id, opt_wiz;
	mapping mud_list;
	mixed *muds;

	if( arg ) {
		option = explode(arg, " ");
		i = sizeof(option);
		while( i-- )
			switch(option[i]) {
				case "-l": opt_long = 0;	break;
				case "-i": opt_id = 1;		break;
				case "-w": opt_wiz = 1;		break;
				default:
					if(	option[i][0]=='@' ) {
						RWHO_Q->send_rwho_q(option[i][1..sizeof(option[i])],
							me, opt_long);
						write("网路讯息已送出，请稍候。\n");
						return 1;
					}
					return notify_fail("指令格式：who [-l|-i|-w]\n");
			}
	}

//	if( opt_long ) {
//		if( (int)me->query("sen") < 30 )
//			return notify_fail("你的精神太差了，没有办法得知其他玩家的详细资料。\n");
//		me->receive_damage("sen", 30);
//	}

	str = "◎ " + MUD_NAME + "\n";
	str += "—————————————————————————————————————\n";
	list = users();
	list = sort_array(users(), "sort_user", this_object());
	if( opt_long || opt_wiz ) {
		j = sizeof(list);
		while( j-- ) {
			// Skip those users in login limbo.
			if( !environment(list[j]) ) continue;
			if( !me->visible(list[j]) ) continue;
			if( opt_wiz && !wizardp(list[j]) ) continue;
			if( list[j]->is_ghost())
			str = sprintf("%12s %s\n" ,
                                str,
//                              RANK_D->query_rank(list[j]),
                                list[j]->short(1)
			);
			else
			str = sprintf( BOLD "%12s %s\n" NOR,
				str,
//				RANK_D->query_rank(list[j]),
				list[j]->short(1)
			);
		}
	} else {
		ppl_cnt = 0;
		j = sizeof(list);
		while( j-- ) {
			// Skip those users in login limbo.
			if( !environment(list[j]) ) continue;
			if( me && !me->visible(list[j]) ) continue;
			str = sprintf("%s%-15s%s",
				str,
				opt_id ? capitalize(list[j]->query("id")): list[j]->name(1),
				(ppl_cnt%5==4? "\n": "")
			);
			ppl_cnt++;
		}
		if( ppl_cnt%5 ) str += "\n";
// here is where we send rwho message
if( me && find_object(DNS_MASTER))
{
mud_list=(mapping)DNS_MASTER->query_muds();
muds = keys(mud_list);
for(i=0;i<sizeof(muds);i++)
	if(( muds[i] != lower_case(INTERMUD_MUD_NAME))
	 &&
	(muds[i] != "dnssvr"))
	{
		RWHO_Q->send_rwho_q(muds[i],me,1);
	}
}
	}	
	str += "—————————————————————————————————————\n";
	str = sprintf("%s共有%s位使用者连线中。\n", str, chinese_number(sizeof(list)));
	if (me &&wizardp(me))
	{
	str =sprintf("%s系统负担：%s\n",str, query_load_average());
	}
	if( remote ) return str;

	me->start_more(str);
	return 1;
}

int sort_user(object ob1, object ob2)
{
	if( wizardp(ob1) && !wizardp(ob2) ) return -1;
	
	if( wizardp(ob2) && !wizardp(ob1) ) return 1;

	if( wizardp(ob1) && wizardp(ob2) )
		return (int)SECURITY_D->get_wiz_level(ob2) 
			- (int)SECURITY_D->get_wiz_level(ob1);
	
//	return (int)ob2->query("combat_exp") - (int)ob1->query("combat_exp");
	return (int)ob2->query("score") - (int)ob1->query("score");
}

int help(object me)
{
write(@HELP
指令格式 : who [-l|-i|-w]

这个指令可以列出所有在线上的玩家及其等级。

-l 选项列出较长的讯息。
-i 只列出玩家的英文代号。
-w 只列出线上所有的巫师。

相关指令： finger
HELP
    );
    return 1;
}
