// msword.c

#include <weapon.h>

inherit SWORD;

void create()
{
	set_name("七星剑", ({ "7*sword" }) );
	set_weight(700);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("long", "这是一把剑鞘上镶着七块宝石的宝剑。\n");
		set("value", 40000);
		set("real", 0);
		set("material", "blacksteel");
		set("rigidity", 700);
		set("wield_msg", "$N从噩鱼皮剑鞘中抽出一把闪闪发光的$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n插入腰间的噩鱼皮剑鞘。\n");
	}
	init_sword(40);
	setup();
}
