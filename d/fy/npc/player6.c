// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
inherit NPC;
int custom();
void create()
{
        set_name("�Ž�", ({ "zji" }) );
        set("gender", "����" );
        set("age", 28);
	set("combat_exp", 1001900);
	set("nickname","��������ͽ");
	set("title","��ѩɽׯ�ڶ�������");
        set("chat_chance", 2);
        set("chat_msg", ({
		(: custom :)	
        }) );

        set("attitude", "friendly");
	set("max_force",1460);
	set("force",1276);
	set("force_factor",70/10);
	set("atman",1300);
	set("mana",2800);	
	set_skill("unarmed",150);
	set_skill("meihua-shou",88);
	map_skill("unarmed","meihua-shou");
	set_skill("dodge",200);
	set_skill("five-steps",100);
	map_skill("dodge","five-steps");
        setup();
        carry_object("/obj/cloth")->wear();

}

int custom()
{
command("hehe");
return 1;
}
