// ping.c ƽһָ

inherit NPC;
inherit F_VENDOR;
//inherit F_DEALER;

void create()
{
	set_name("ƽһָ", ({ "ping yizhi", "ping", "yizhi" }));
	set("title", "ҩ���ϰ�");
	set("gender", "����");
	set("long", "������ҽ���߳��ġ�ɱ����ҽ��ƽһָ���������Ը�Ź֣�����ʲô�˶�ҽ�ġ�\n");
	set("age", 65);

	set("int", 30);
	
	set("kee", 1000);
	set("max_kee", 1000);
	set("gin", 1000);
	set("max_gin", 1000);
	set("shen_type", 1);

	set("combat_exp", 500000);
	set("attitude", "heroism");

	set_skill("unarmed", 80);
	set_skill("dodge", 80);
	set_skill("parry", 60);
	set_temp("apply/attack", 70);
	set_temp("apply/defense", 70);
	set_temp("apply/damage", 50);

	set("vendor_goods", ({
	}));

	setup();
	add_money("gold", 1);
	carry_object("/obj/cloth")->wear();
}

void init()
{
//add_action("do_buy", "buy");
}
