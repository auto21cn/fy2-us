
#include <weapon.h>
#include <ansi.h>
inherit STAFF;
void create()
{
	set_name("÷ľ����" , ({ "chair" }) );
	set_weight(70000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 400);
		set("material", "wood");
	}
	init_staff(20);
	setup();
}
