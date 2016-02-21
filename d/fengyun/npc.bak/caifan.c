// tea_waiter.c

inherit NPC;
inherit F_VENDOR;

void create()
{
        set_name("卖菜的", ({ "caifan" }) );
        set("gender", "男性" );
        set("age", 40);
        set("long",
                "一个为生活而终日奔波的小商人．\n");
	set("combat_exp", 5);
        set("attitude", "friendly");
        set("rank_info/respect", "老二哥");
        set("chat_chance", 3);
        set("chat_msg", ({
                "卖菜的笑道：那一着天外飞仙，七搏一赌叶孤城胜．．\n",
        }) );

        set("vendor_goods", ([
                "小白菜": __DIR__"obj/smallvege",
                "大青菜": __DIR__"obj/bigvege",
                "胡萝卜": __DIR__"obj/midvege",

        ]) );
        setup();
}

void init()
{
        add_action("do_vendor_list", "list");
}
