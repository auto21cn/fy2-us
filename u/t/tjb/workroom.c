// Room: /u/t/tjb/workroom.c

# include <room.h>
# include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "大愚工作室");
	set("long", @LONG
这里是老六的工作室, 陋室一间, 一张不大的办公桌上摆满
了乱七八糟的书和纸。桌前一张宽大的椅子，看来坐着挺舒
服的。
LONG
	);
	set("valid_startroom" ,1);
	set("exits", ([
	"west" : __DIR__ "bedroom",
        "south" : "/d/wiz/jobroom",
	"east" : "/u/c/cat/workroom",
	]));
        set("objects", ([
         __DIR__ "guo" : 2 , 
         __DIR__ "tjb2" : 1 ,
         ]) ); 
        setup();
        call_other("/obj/board/tjb_b","???");
}

void init()
{
   add_action("do_dance","dancing");
}

int do_dance(string arg)
{
     message_vision("也不知道老六怎么弄的，$N跳出的舞步太美了。\n",
                this_player());
      return 1;
}

int valid_leave(object me, string dir)
{       
        tell_object(me, "你离开了老六的工作室!\n" NOR );
        return 1;
}

