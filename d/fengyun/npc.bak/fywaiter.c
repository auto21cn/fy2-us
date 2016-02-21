// waiter.c

inherit NPC;
inherit F_VENDOR;

void create()
{
	set_name("�պ��", ({ "suhong" }) );
	set("gender", "Ů��" );
	set("age", 21);
	set("title", "�ϰ���");
	set("long",
		"��λ�ϰ�����б���ڹ�̨�ߣ�Ц����������㡣\n");
	set("combat_exp", 500000);
	set("attitude", "friendly");
	set("per",30);
	set("vendor_goods", ([
		"������˿": __DIR__"obj/yxrs",
		"�ɶ�����": __DIR__"obj/cddt",
	        "ܽ����Ƭ": __DIR__"obj/frsp",
                "��������": __DIR__"obj/ssqy",
                "��������": __DIR__"obj/ylzp",
                "�ζ����": __DIR__"obj/pwym",
                "��ζ��Ƭ": __DIR__"obj/cwgp",
                "��������": __DIR__"obj/ychz",
                "������˿": __DIR__"obj/jxyz",
                "�����Ź�": __DIR__"obj/zypg",
                "��������": __DIR__"obj/rxcy",
                "�峴����": __DIR__"obj/qcsh",
                "���ͼ�Ƭ": __DIR__"obj/hyjp",
                "���հǳ�": __DIR__"obj/szpc",
                "������": __DIR__"obj/glyc",
                "С����˿": __DIR__"obj/xcfs",
                "��Ƥ����": __DIR__"obj/cpcy",
                "��֭����": __DIR__"obj/gzyq",
                "�峴Ϻ��": __DIR__"obj/qcxr",
                "�������": __DIR__"obj/jymj",
                "�����㽶": __DIR__"obj/glxj",
                "��Ƥ��Ϻ": __DIR__"obj/cpdx",
                "��ѩ����": __DIR__"obj/pxhy",
                "����ę́": __DIR__"obj/kzmt",
                "�ƺӴ���": __DIR__"obj/hhdq",

	]) );
	set_skill("unarmed",50);
	set_skill("tenderzhi",50);
	set_skill("dodge",50);
	set_skill("stormdance",50);
	map_skill("dodge","stormdance");	
	map_skill("unarmed","tenderzhi");
	setup();
	carry_object(__DIR__"obj/pink_cloth")->wear();
}

void init()
{	
	object ob;

	::init();
	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
	add_action("do_vendor_list", "list");
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	switch( random(3) ) {
		case 0:
message_vision("$N�۽Ǻ�Ц��������������$nһ�ۡ�\n",this_object(),ob);
			break;
		case 1:
message_vision("$N����΢�ڣ�¶����֬�����ۣ���$n�������֡�\n",this_object(),ob);
			break;
		case 2:
message_vision("$N����$nһ�ۣ�����������ӣ��С����Ц������\n",this_object(),ob);
			break;
	}
}
