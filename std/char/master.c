#include <dbase.h>
#include <login.h>
#include <ansi.h>
int time_period(int timep, object me);
string sysmsg;
int prevent_learn(object me, string skill)
{
	mapping 	my_family, family;
        int 		betrayer, mylvl, lvl;

	lvl = this_object()->query_skill(skill, 1);
	mylvl = me->query_skill(skill, 1);
        if( betrayer = me->query("betrayer") ) {
                if( mylvl >= lvl - betrayer * 20 ) {
			message_vision("$N神色间似乎对$n不是十分信任，\n也许是想起$p从前背叛师门的事情\n...。\n", this_object(), me );
                        command("say 嗯 .... \n师父能教你的都教了，其他的你自己练吧。");
                        return 1;
                }
        }

        if( !me->is_apprentice_of(this_object())) {
		if( !mapp(my_family = me->query("family")) ) 
			return 0;
		if( !mapp(family = this_object()->query("family")) ) 
			return 0;
		if((my_family["family_name"] == family["family_name"]) && (lvl <=  mylvl * 3 )) {
                	command("hmm");
                	command("pat " + me->query("id"));
                	command("say 虽然你是我门下的弟子，可是并非我的嫡传弟子....");
                	command("say 我只能教你这些粗浅的本门功夫，其他的还是去找你师父学吧。");
                	return 1;
		}
        }

        return 0;
}
int give_quest(string arg)
{
	mapping quest ;
	object me;
	int j, combatexp, timep, lvl=0;
        mixed *local;
        int  t;
	string tag = "40000000";
 string *levels = ({
                        "0",
                        "4000",
                        "8000",
                        "16000",
                        "32000",
                        "64000",
                        "128000",
                        "256000",
                        "512000",
                        "1024000",
                        "1536000",
                        "2304000",
                        "3456000",
                        "5184000",
                        "7776000",
                        "11664000",
                        "17496000",
                        "26244000",
			"40000000"
        });
	if( ! arg || !sscanf(arg, "%d", lvl))
	lvl = 0;
	if(lvl<0) lvl=0;
	me = this_player();
// Let's see if this player is a ghost
        local = localtime(time()*60);
        t = local[2] * 60 + local[1];       
	if( t < 240 || t > 1380)
	{
		write("夜深了．．还要什么任务！！\n");
		return 1;
	}
	if((int) me->is_ghost())
	{
		write("鬼魂不可要任务．\n");
		return 1;
	}

// Let's see if this player still carries an un-expired task
        if((quest =  me->query("quest")))
	{
	if( ((int) me->query("task_time")) >  time() )
		return 0;
	else
		me->set("kee", me->query("kee")/2+1);
		me->delete_temp("quest_number");
	}
	combatexp = (int) me->query("combat_exp");
        for(j= sizeof(levels) - 1 ; j>=0; j--)
        {
                if( atoi(levels[j])  <= combatexp )
                        {
                                tag = levels[j];
				if(j < (sizeof(levels)- lvl)) tag = levels[j+lvl];
                                break;
                        }
        }
        if(!random(40) ) tag = "_new";
	if(!random(10) ) tag = "_common";
	quest = QUEST_D(tag)->query_quest();
//	to use less mem...
//	timep = quest["time"];	
	timep = 600;   // each quest give 10 mins.
// A factor here to make time random
	timep = random(timep/2)+timep/2;
	time_period(timep, me);
	if (quest["quest_type"] == "寻")
	{
        tell_object(me,"找回『"+quest["quest"]+"』给天机老人。\n" NOR);
	sysmsg +="找回『"+quest["quest"]+"』。";
	}
	        if (quest["quest_type"] == "杀")
        {
        tell_object(me,"替天机老人杀了『"+quest["quest"]+"』。\n" NOR);
	sysmsg +="杀了『"+quest["quest"]+"』。";
        }
 	me->set("quest", quest);
	me->set("task_time", (int) time()+(int) timep);
	if((int)me->query_temp("quest_number") < 5)
	me->add_temp("quest_number",1);
	CHANNEL_D->do_channel(this_object(), "qst", sprintf("%s(%s)：%s", 
	me->query("name"),me->query("id"),sysmsg));

return 1;
}

int time_period(int timep, object me)
{
        int t, d, h, m, s;
        string time;
        t = timep;
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;

        if(d) time = chinese_number(d) + "天";
        else time = "";

        if(h) time += chinese_number(h) + "小时";
        if(m) time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒";

        tell_object(me,HIW + sprintf("%s",this_object()->name()) +"说道：\n请在" + time + "内");
	sysmsg = "在" + time + "内";
        return 1;
}
